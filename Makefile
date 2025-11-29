# Makefile: add commands to test modules

CXX =  g++-14 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g -c
HEADERFLAGS = -c -x c++-system-header
SOURCES = resource.cc resource-impl.cc IObserver.cc ISubject.cc criteria.cc criteria-impl.cc goal.cc goal-impl.cc tile.cc tile-impl.cc board.cc board-impl.cc student.cc student-impl.cc game.cc game-impl.cc main.cc
OFILES = *.o
HEADERS = memory vector sstream iostream fstream string algorithm random stdexcept 
EXEC = watan

$(EXEC): $(SOURCES)
	rm -r gcm.cache
	$(CXX) $(HEADERFLAGS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) 
	$(CXX) $(OFILES) -o $(EXEC)
