CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGETS = bruteforce divideconquer create

all: $(TARGETS)

bruteforce: bruteforce.cpp
	$(CXX) $(CXXFLAGS) bruteforce.cpp -o bruteforce

divideconquer: divideconquer.cpp
	$(CXX) $(CXXFLAGS) divideconquer.cpp -o divideconquer

create: create.cc
	$(CXX) $(CXXFLAGS) create.cc -o create

clean:
	rm -f create divideconquer bruteforce 
	rm -rf .vscode/
	
.PHONY: all clean