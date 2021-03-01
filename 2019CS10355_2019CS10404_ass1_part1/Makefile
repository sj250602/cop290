CXX=g++
RM=rm -f

compile:crop.cpp
	$(CXX) crop.cpp -o testoutput2 -std=c++11 `pkg-config --cflags --libs opencv`
run:crop.cpp
	./testoutput2
clear:
	$(RM) testoutput2
