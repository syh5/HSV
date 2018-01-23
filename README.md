# HSV

This is inspired by inbuilt functioanality in OpenCV on converting RGB images to HSV(Hue, Saturation and Value) images. The code was written for a competition where a yellow and black caution tape needed to be detected and it's distance from the camera had to be determined. The camera was mounted to a drone and distance is calculated knowing the height of the drone and the camera angles.

This is a simple implementation where the HSV threshold is set for the required color. This code is really fast compared doing machine learning or using features and hence was used in the competition. 

To run the code download and extract the zip. Go to the folder in the terminal and do:

- cmake.
- make

and if there are no errors:

- ./Yellow test.jpg

it should look something like this:

![alt text](https://github.com/syh5/HSV/blob/master/hsv.png)
