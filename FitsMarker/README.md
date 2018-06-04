## FitsMarker

This is a tool for users to run canny detector and check the result of edge detection. Research-oriented.  

### Installation

Make sure **OpenCV(>=2.4)** and **g++(C++11 features supported)** have been installed on your computer before installation.  
To install this tool, just use **make** like below:  

```
make
```

It will generate a executable file in the current path.  

### Usage

To use canny detector to generate a dataset, please use the following command:  

```
./FitsMarker -d [filename] [optional:thresh1] [optional:thresh2]
```

The file contains all paths to the image to be processed, we encourage to use absolute path. A sample is shown below:  

```
/Users/yuchenwang/Documents/openLib/casinidataset/FITSImages/N1485951682_2.fits
/Users/yuchenwang/Documents/openLib/casinidataset/FITSImages/N1747231577_1.fits
/Users/yuchenwang/Documents/openLib/casinidataset/FITSImages/N1865298435_1.fits
```

**thresh1** and **thresh2** is two parameters required by canny detector, it is ok you do not provide it.  

This command will generate a 'txt' file which contains all edge in it, the path corresponding above is here:  

```
/Users/yuchenwang/Documents/openLib/casinidataset/Annotation/N1485951682_2.txt
/Users/yuchenwang/Documents/openLib/casinidataset/Annotation/N1747231577_1.txt
/Users/yuchenwang/Documents/openLib/casinidataset/Annotation/N1865298435_1.txt
```

To run canny detector on a single image, use the following command:  

```
./FitsMarker -ds [filename] [optional:thresh1] [optional:thresh2]
```

**Filename** is an adress to a single fits file.

To check the edge, run the following command:  

```
./FitsMarker -p [filename]
```

#### Mark or Unmark pixels with keyboard and mouse

- Shift+Mouse[left]: Set ROI and unmark every edge pixel inside the ROI
- Control+Mouse[left]: Set ROI and unmark every edge pixel ouside the ROI
- Enter: Mark or unmark the pixel in the center of [dst] window

Have fun with this tool, any futher question, please come up with an issue or contact wyc8094@gmail.com
