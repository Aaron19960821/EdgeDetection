CXX = g++
CFLAGS = -lcfitsio -lopencv_core -lopencv_highgui -lopencv_imgproc
COMMON = -Wall -O2 -std=c++11 -I /usr/local/include
ADDITION = -c
OBJ=bin/fitsutils.o bin/imageutils.o bin/cannydetector.o bin/display.o bin/displayUtils.o bin/main.o

all: FitsMarker

fitsutils.o: src/fitsutils.cpp src/fitsutils.h
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) src/fitsutils.cpp -o bin/fitsutils.o

imageutils.o: src/imageutils.cpp src/imageutils.h
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) src/imageutils.cpp -o bin/imageutils.o

cannydetector.o: src/cannydetector.h src/cannydetector.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) src/cannydetector.cpp -o bin/cannydetector.o

display.o: src/display.h src/display.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) src/display.cpp -o bin/display.o

displayUtils.o: src/displayUtils.h src/displayUtils.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) src/displayUtils.cpp -o bin/displayUtils.o

main.o: main.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) main.cpp -o bin/main.o

FitsMarker: fitsutils.o imageutils.o cannydetector.o displayUtils.o display.o main.o
	$(CXX) $(COMMON) $(CFLAGS) $(OBJ) -o FitsMarker

clean:
	rm bin/*.o
	rm FitsMarker
