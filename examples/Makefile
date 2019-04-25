.PHONY: all clean

CXX = g++
CPPFLAGS += -std=c++11 -Wall
CXXFLAGS += -pthread
LINKFLAGS = -lfcgi

TARGERS = authorizer  echo-c  echo-cpp  echo-x  hello_world  log-dump  size  threaded

all : $(TARGERS)

clean:
	rm -rf *.o *.dSYM $(TARGERS)

authorizer.o: authorizer.c
	$(CXX) $(CPPFLAGS) -c $<

authorizer: authorizer.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

echo.o: echo.c
	$(CXX) $(CPPFLAGS) -c $<

echo-c: echo.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

echo-cpp.o: echo-cpp.cpp
	$(CXX) $(CPPFLAGS) -c $<

echo-cpp: echo-cpp.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

echo-x.o: echo-x.c
	$(CXX) $(CPPFLAGS) -c $<

echo-x: echo-x.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

log-dump.o: log-dump.c
	$(CXX) $(CPPFLAGS) -c $<

log-dump: log-dump.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

size.o: size.c
	$(CXX) $(CPPFLAGS) -c $<

size: size.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

threaded.o: threaded.c
	$(CXX) $(CPPFLAGS) -c $<

threaded: threaded.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)

hello_world.o: hello_world.cpp
	$(CXX) $(CPPFLAGS) -c $<

hello_world: hello_world.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LINKFLAGS)
