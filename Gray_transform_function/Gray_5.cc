#include "amaswz.h"

void L_1_ready(Mat& Input)
{
    double Sum_slide[256];
    int nRows = Input.rows;
    int nCols = Input.cols;
    int Sum_array[256];
    uchar *pointer;
    
    memset(Sum_array,0,sizeof Sum_array);
    for(int i=0;i<256;i++)
        Sum_slide[i]=0;
    
    for(int i=0;i<nRows;i++)
    {
        pointer = Input.ptr<uchar>(i);
        for(int j=0;j<nCols;j++)
        {
            Sum_array[pointer[j]]++;
        }
    }
    
    Sum_slide[0] = ( (double)Sum_array[0] / (nRows*nCols));
    for(int i=1;i<256;i++)
    {
        Sum_slide[i] = ( (double)Sum_array[i] / (nRows*nCols)) + Sum_slide[i-1];
        cout<<Sum_slide[i]<<endl;
    }
    for(int i=0;i<nRows;i++)
    {
        pointer = Input.ptr<uchar>(i);
        for(int j=0;j<nCols;j++)
        {
            pointer[j] = (int)((Sum_slide[pointer[j]]) * 255);
        }
    }
}


int main(int argc,char **argv)
{
    
    Mat Pic;
    
    string Libs_ = Cv_libs;
    Libs_+="7.jpg";
    
    Pic = imread(Libs_,0);
    if( !Pic.data )  printf("Error loding pic\n");
    imshow("Pic1",Pic);
    cvWaitKey();
    
    L_1_ready(Pic);
    
    imshow("Pic2",Pic);
    imwrite("/Users/ama/Desktop/2.jpg", Pic);
    cvWaitKey();
}
