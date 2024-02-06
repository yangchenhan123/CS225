CXX = clang++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -lpthread -lm

mp1 : main.o HSLAPixel.o PNG.o mp1.o lodepng.o 
	$(LD) main.o HSLAPixel.o PNG.o mp1.o lodepng.o $(LDFLAGS) -o mp1

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

mp1.o : mp1.cpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) mp1.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

test : unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o
	$(LD) unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o test
 
unit_tests.o : tests/unit_tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) tests/unit_tests.cpp


