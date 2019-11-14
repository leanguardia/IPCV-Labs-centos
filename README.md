g++ face.cpp /usr/lib64/libopencv_core.so.2.4 /usr/lib64/libopencv_highgui.so.2.4 /usr/lib64/libopencv_imgproc.so.2.4 /usr/lib64/libopencv_objdetect.so.2.4

# Dartboard dataset generator

"""
./opencv_createsamples -img dart.bmp -vec dart.vec -neg negatives.dat -w 20 -h 20 -num 500 -maxidev 80 -maxxangle 0.8 -maxyangle 0.8 -maxzangle 0.2
"""

"""
./opencv_traincascade -data dartcascade -vec dart.vec -bg negatives.dat -numPos 500 -numNeg 500 -numStages 3 -maxDepth 1 -w 20 -h 20 -minHitRate 0.999 -maxFalseAlarmRate 0.05 -mode ALL
"""
