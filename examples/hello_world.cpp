#include <string>
#include <stdlib.h> 
#include <iostream> 
#include "fcgi_stdio.h" 

#ifndef _WIN32
#include <signal.h>
#include <execinfo.h>
#endif
#include "fcgio.h"

using std::cin;
using std::cout;
using std::cerr;
using std::streambuf;

#if ! defined(_WIN32)

static void _dumpCrashLog()
{
	void* addresses[32];
	size_t addressNum = backtrace(addresses, 32);
	int fd = fileno(stderr);
	FILE* fp = fopen("crash_dump", "w");
	if (fp != NULL)
	{
		fd = fileno(fp);
	}
	backtrace_symbols_fd(addresses, addressNum, fd);
	fclose(fp);
}

static void _handler(int signo)
{
	_dumpCrashLog();
}

#endif


int main(void)
{
#if ! defined(_WIN32)
	atexit(_dumpCrashLog);
	if (signal(SIGSEGV, _handler) == SIG_ERR)
	{
		perror("signal error");
		exit(1);
	}
#endif

	if (FCGX_Init())
		exit(1);

	FCGX_Request request;
	FCGX_InitRequest(&request, 0, 0);

	streambuf* cin_streambuf = cin.rdbuf();
	streambuf* cout_streambuf = cout.rdbuf();
	streambuf* cerr_streambuf = cerr.rdbuf();

	int count = 0;
	while (FCGX_Accept_r(&request) == 0)
	{
		fcgi_streambuf cin_fcgi_streambuf(request.in);
		fcgi_streambuf cout_fcgi_streambuf(request.out);
		fcgi_streambuf cerr_fcgi_streambuf(request.err);

		cin.rdbuf(&cin_fcgi_streambuf);
		cout.rdbuf(&cout_fcgi_streambuf);
		cerr.rdbuf(&cerr_fcgi_streambuf);

		do {
			cin.ignore(1024);
		} while (cin.gcount() == 1024);

		cout << "Content-type: text/html\r\n"
			"\r\n"
			"<title>FastCGI Hello! (C, fcgi_stdio library)</title>"
			"<h1>FastCGI Hello! (C, fcgi_stdio library)</h1>";

		cout << "Request number " << ++count << " running on host <i>" << getenv("SERVER_HOSTNAME") << "</i>\n";
	}

	cin.rdbuf(cin_streambuf);
	cout.rdbuf(cout_streambuf);
	cerr.rdbuf(cerr_streambuf);

	return 0;
}