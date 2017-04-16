#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;

void init(int *maze)
{
    for(int i=0;i<256;i++)
        maze[i]=256-1-i;
}


void reversal(Mat& Input,int *maze)
{
    CV_Assert(Input.depth() != sizeof(uchar));
    
    int channels=Input.channels();
    
    int nRows = Input.rows;
    int nCols = Input.cols * channels;
    
    if ( Input.isContinuous() )
    {
        nCols *= nRows;
        nRows = 1;
    }
    
    uchar *pointer;
    for(int i=0;i<nRows;i++)
    {
        pointer = Input.ptr<uchar>(i);
        for(int j=0;j<nCols;j++)
        {
            pointer[j]= maze[pointer[j]];
        }
    }
}


int main(int argc,char **argv)
{
    int Mark[256];
    
    //Load the img
    Mat Pic;
    Pic = imread("1.jpeg");
    if( !Pic.data )  printf("Error loding pic\n");
        imshow("1111",Pic);
    cvWaitKey();
    
    init(Mark);
    reversal(Pic,Mark);
    
    imshow("222222",Pic);
    imwrite("/Users/ama/Desktop/2.jpg", Pic);
    cvWaitKey();
}

