## FitsMarker

This is a tool for users to run canny detector and check the result of edge detection. Research-oriented.  

### Installation

Make sure OpenCV(>=2.4) have been installed on your computer before installation.  
To install this tool, just use **make** like below:  

```
make
```

It will generate a executable file in the current path.  

### Usage

To use canny detector to generate a dataset, please use the following command:  

```
./FitsMarker -d [filename] [option:thresh1] [option:thresh2]
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

To check the edge, run the following command:  

```
./FitsMarker -p [filename]
```
You can mark or unmark a pixel as an edge pixel by clicking left button.  
You can set ROI and eliminate all pixels that are not in the ROI by using [Ctrl] and left button.

Have fun with this tool, any futher question, please come up with an issue or contact wyc8094@gmail.com
