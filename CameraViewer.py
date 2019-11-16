import cv2
import sys
import platform



usingplatform = ""
video_capture = None

def Init ():
    print("Python version: ", sys.version)
    print("OpenCV Version: {}".format(cv2.__version__))
    usingplatform = GetPlatform ()
    OpenCVUsingCuda()


def GetPlatform ():
    usingplatform = platform.machine()
    if usingplatform  == "aarch64":
        print("Platform", usingplatform, "Using Jetson Nano\n")
    elif usingplatform  == "AMD64":
        print("Platform: " , usingplatform, "Running on a Windows System")
    return usingplatform

def DlibUsingCuda():
    # this checks if CUDA was build with Dlib, but you can also do sudo tegrastats on the nano
    print(cuda.get_num_devices())
    if dlib.DLIB_USE_CUDA:
        print("Successfully using CUDA")
    else:
        print("Dlib Not using CUDA")

def OpenCVUsingCuda():
    buildinfo = cv2.getBuildInformation().split("\n")
    foundSomething=0
    for item in buildinfo:
        if "Use Cuda" in item:
            print (item.strip())
            foundSomething+=1
        if "NVIDIA" in item:
            print (item.strip())
            foundSomething+=1

    if foundSomething == 0:
        print("Could Not Find CUDA")

def GetVideoObject():
    usingplatform = platform.machine()

    if usingplatform  == "aarch64":
        # to find the device use gst-device-monitor-1.0 and it will list the camera specs, 
        # from there I grabbed the with and height 
        # read here: https://gstreamer.freedesktop.org/documentation/tools/gst-launch.html?gi-language=c
        # also, this dude in github has a gstream python script to open bunch of cameras, but mine is simpler
        # https://gist.github.com/jkjung-avt/86b60a7723b97da19f7bfa3cb7d2690e#
        gst_str = ('v4l2src device=/dev/video{} ! '
               'video/x-raw, width=(int){}, height=(int){} ! '
               #'videoconvert ! appsink').format(0, 800, 600) # no speed improvement when reduce video size
               'videoconvert ! appsink').format(0, 1280, 720)
        video_capture = cv2.VideoCapture(gst_str, cv2.CAP_GSTREAMER)
        #video_capture = cv2.VideoCapture(0,cv2.CAP_GSTREAMER)
        #video_capture = cv2.VideoCapture("http://10.1.10.165:8081", cv2.CAP_GSTREAMER)
        if video_capture.isOpened() !=  True:  
            print("Cannot find camera, quitting")
            sys.exit()
    elif usingplatform  == "AMD64": 
        #video_capture = cv2.VideoCapture(0+cv2.CAP_DSHOW)
        #video_capture = cv2.VideoCapture(1+cv2.CAP_DSHOW)
        video_capture = cv2.VideoCapture(1+cv2.CAP_DSHOW)
        if video_capture.isOpened() !=  True:  
            print("Cannot find camera, quitting")
            sys.exit()

    elif video_capture is None:
        print("Cannot find camera, quitting")
        sys.exit()
    
    return video_capture


def CaptureVideo():
    video_capture = GetVideoObject()
    return video_capture



def main():
    Init()
    video_capture = CaptureVideo()

    while True: 
        # process each frame
        ret, frame = video_capture.read()
        if ret == False:
            continue    

        # Display frame 
        cv2.imshow('Video', frame)
        # Hit 'q' on the keyboard to quit
        keypressed = 0xFF & cv2.waitKey(1)
        if keypressed == ord('q') or keypressed == ord('Q') :
            break

        continue

        ReleaseResources (video_capture)


if __name__ == "__main__":
   main()