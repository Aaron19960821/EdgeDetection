CXX = g++
CFLAGS = -lcfitsio -lopencv_core -lopencv_highgui -lopencv_imgproc
COMMON = -std=c++11 -I /usr/local/include
ADDITION = -c

all: FitsMarker

fitsutils.o: fitsutils.cpp fitsutils.h
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) fitsutils.cpp -o fitsutils.o

imageutils.o: imageutils.cpp imageutils.h
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) imageutils.cpp -o imageutils.o

cannydetector.o: cannydetector.h cannydetector.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) cannydetector.cpp -o cannydetector.o

display.o: display.h display.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) display.cpp -o display.o

main.o: main.cpp
	$(CXX) $(ADDITION) $(COMMON) $(CFLAGS) main.cpp -o main.o

FitsMarker: cannydetector.o fitsutils.o imageutils.o display.o main.o 
	$(CXX) $(COMMON) $(CFLAGS) fitsutils.o cannydetector.o display.o imageutils.o main.o -o FitsMarker

clean:
	rm *.o
