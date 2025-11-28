# Makefile: add commands to test modules

CXX =  g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g -c
HEADERFLAGS = -c -x c++-system-header
SOURCES = resource*.cc ISubject.cc IObserver.cc criteria*.cc goal*.cc tile*.cc board*.cc student*.cc # game*.cc main.cc
OFILES = *.o
HEADERS = memory vector sstream iostream string algorithm random stdexcept
EXEC = watan.exe

$(EXEC): $(SOURCES)
	$(CXX) $(HEADERFLAGS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) 
	$(CXX) $(OFILES) -o $(EXEC)