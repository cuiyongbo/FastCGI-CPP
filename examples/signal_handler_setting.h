#pragma once

#include <atomic>

#ifndef _WIN32
#include <signal.h>
#include <execinfo.h>
#endif

class SignalHandlerSetting
{
public:
	SignalHandlerSetting();
	~SignalHandlerSetting();

	bool toExit() { return m_toExit; }

private:

#ifndef _WIN32
	void installSignalHandlers(bool force);
	void installSignalHandler(int signo, const struct sigaction* act, bool force);
	static void sigTermHandler(int signo);
	static void sigSegvHandler(int signo);
	static void _dumpCrashLog();
#endif

private:
	static std::atomic_bool m_toExit;
};

