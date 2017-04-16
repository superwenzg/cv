#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
using namespace cv;

void init(int *maze)
{
    for(int i=0;i<256;i++)
    {
        double b=(i+0.5)/256;
        double c=pow( b ,0.4);
        maze[i]=(int)(c*256 - 0.5);
    }
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
    Pic = imread("9.jpeg",IMREAD_GRAYSCALE);
    if( !Pic.data )  printf("Error loding pic\n");
        imshow("1111",Pic);
    cvWaitKey();
    
    init(Mark);
    reversal(Pic,Mark);
    
    imshow("222222",Pic);
    imwrite("/Users/ama/Desktop/2.jpg", Pic);
    cvWaitKey();
}
