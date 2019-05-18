#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>
#include <iostream>

using namespace cv;
using std::cout; using std::cerr; using std::endl;

int main(int, char**)
{
    Mat frame, fgMask;
    Mat processed;
    int64 tp0;

    //create Background Subtractor objects
    Ptr<BackgroundSubtractor> pBackSub;

    pBackSub = createBackgroundSubtractorMOG2();
    //pBackSub = createBackgroundSubtractorKNN();

    cout << "Opening camera..." << endl;
    VideoCapture capture(0); // open the first camera

    if (!capture.isOpened())
    {
        cerr << "ERROR: Can't initialize camera capture" << endl;
        return 1;
    }

    cout << "Frame width: " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "     height: " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "Capturing FPS: " << capture.get(CAP_PROP_FPS) << endl;

    cout << endl << "Press 'ESC' to quit, 'space' to toggle frame processing" << endl;
    cout << endl << "Start grabbing..." << endl;

    size_t nFrames = 0;
    short enableProcessing = 0;
    int64 t0 = cv::getTickCount();
    int64 processingTime = 0;
    for (;;)
    {
        capture >> frame; // read the next frame from camera
        if (frame.empty())
        {
            cerr << "ERROR: Can't grab camera frame." << endl;
            break;
        }
        nFrames++;
        if (nFrames % 10 == 0)
        {
            const int N = 10;
            int64 t1 = cv::getTickCount();
            cout << "Frames captured: " << cv::format("%5lld", (long long int)nFrames)
                 << "    Average FPS: " << cv::format("%9.1f", (double)getTickFrequency() * N / (t1 - t0))
                 << "    Average time per frame: " << cv::format("%9.2f ms", (double)(t1 - t0) * 1000.0f / (N * getTickFrequency()))
                 << "    Average processing time: " << cv::format("%9.2f ms", (double)(processingTime) * 1000.0f / (N * getTickFrequency()))
                 << std::endl;
            t0 = t1;
            processingTime = 0;
        }
        switch (enableProcessing) {
	case 0:
            imshow("Frame", frame);
	    break;
	case 1:
            tp0 = cv::getTickCount();
            cv::Canny(frame, processed, 400, 1000, 5);
            processingTime += cv::getTickCount() - tp0;
            imshow("Frame", processed);
	    break;
	case 2:
	    //update the background model
            tp0 = cv::getTickCount();
            pBackSub->apply(frame, fgMask);
            processingTime += cv::getTickCount() - tp0;
            imshow("Frame", fgMask);
	    break;
        }
        int key = waitKey(1);
        if (key == 27/*ESC*/ || key == 'q')
            break;
        if (key == 32/*SPACE*/)
        {
            if (enableProcessing)
		enableProcessing = 0;
	    else
		enableProcessing = 1;
            cout << "Enable frame processing ('space' key): " << enableProcessing << endl;
        }
        if (key == 49/* 1 */)
        {
		enableProcessing = 2;
        }
        if (key == 50/* 2 */)
        {
		cout << "dos" << endl;
        }
        if (key == '0')
        {
		enableProcessing = 0;
        }
    }
    std::cout << "Number of captured frames: " << nFrames << endl;
    return nFrames > 0 ? 0 : 1;
}
