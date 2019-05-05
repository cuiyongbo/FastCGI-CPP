#include "signal_handler_setting.h"
#include <stdio.h>
#include <stdlib.h>

std::atomic_bool SignalHandlerSetting::m_toExit;

SignalHandlerSetting::SignalHandlerSetting()
{
	m_toExit = false;

#ifndef _WIN32
	installSignalHandlers(true);
#endif // !_WIN32
}

SignalHandlerSetting::~SignalHandlerSetting()
{

}

#if !defined(_WIN32)

void SignalHandlerSetting::installSignalHandlers(bool force)
{
	atexit(_dumpCrashLog);

	struct sigaction sa;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	sa.sa_handler = sigSegvHandler;
	installSignalHandler(SIGSEGV, &sa, force);

	sa.sa_handler = sigTermHandler;
	installSignalHandler(SIGTERM, &sa, force);
}

void SignalHandlerSetting::installSignalHandler(int signo, const struct sigaction* act, bool force)
{
	struct sigaction sa;
	sigaction(signo, NULL, &sa);
	if (force || sa.sa_handler == SIG_DFL)
	{
		sigaction(signo, act, NULL);
	}
}

void SignalHandlerSetting::sigTermHandler(int signo)
{
	m_toExit = true;
}

void SignalHandlerSetting::sigSegvHandler(int signo)
{
	_dumpCrashLog();
}

void SignalHandlerSetting::_dumpCrashLog()
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

#endif