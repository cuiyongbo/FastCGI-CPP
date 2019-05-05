#include "fcgi_stdio.h"
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char* user = getenv("USER");
	if (user == NULL)
	{
		user = "doe";
	}

	char* password = getenv("PASSWORD");
	if (password == NULL)
	{
		password = "xxxx";
	}

	while (FCGI_Accept() >= 0)
	{
		char* remoteUser = getenv("REMOTE_USER");
		char* remotePassword = getenv("REMOTE_PASSWD");
		if ((remoteUser == NULL) || (remotePassword == NULL)
			 || strcmp(remoteUser, user) || strcmp(remotePassword, password))
		{
			 printf("Status: 401 Unauthorized\r\n"
				 "WWW-Authenticate: Basic realm=\"Test\"\r\n"
				 "\r\n");
		}
		else
		{
			char *processId = getenv("QUERY_STRING");
			if (processId == NULL || strlen(processId) == 0) {
				processId = "0";
		}
			printf("Status: 200 OK\r\n"
				"Variable-AUTH_TYPE: Basic\r\n"
				"Variable-REMOTE_PASSWD:\r\n"
				"Variable-PROCESS_ID: %s\r\n"
				"\r\n", processId);
		}
	}

	return 0;
}
