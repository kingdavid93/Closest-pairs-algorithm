CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGETS = bruteforce divideconquer

all: $(TARGETS)

bruteforce: bruteforce.cpp
	$(CXX) $(CXXFLAGS) bruteforce.cpp -o bruteforce

divideconquer: divideconquer.cpp
	$(CXX) $(CXXFLAGS) divideconquer.cpp -o divideconquer

clean:
	rm -f $(TARGETS)
	
.PHONY: all clean