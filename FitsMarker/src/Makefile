CXX = g++
CFLAGS = -lopencv_core -lopencv_highgui -lopencv_imgproc
COMMON = -c -I /usr/local/include

all: FitsMarker

fitsutils.o:
	g++ -c fitsutils.cpp -o fitsutils.o

imageutils.o:
	$(CXX) $(COMMON) $(CFLAGS) imageutils.cpp -o imageutils.o

main.o:
	$(CXX) $(COMMON) $(CFLAGS) main.cpp -o main.o

cannydetector.o:
	$(CXX) $(COMMON) $(CFLAGS) cannydetector.cpp -o cannydetector.o

FitsMarker: fitsutils.o imageutils.o main.o 
	$(CXX) $(COMMON) $(CFLAGS) fitsutils.o imageutils.o main.o -o FitsMarker

clean:
	rm *.o
