#include "main.h"

void ScanImageAndGlur(Mat &Input,Core &core);


int main(int argc,char **argv)
{
    
    Core core;
    core._Init();
    
    //Load the img
    Mat Pic;
    Pic = imread("/Users/ama/Pictures/cv_pic_libs/2.jpg");
    if( !Pic.data )  printf("Error loding pic\n");
    imshow("1111",Pic);
    cvWaitKey();
    
    //Init the data that receive the property of the Gussin_core
    //double **Core_pointer=NULL;
    
    ScanImageAndGlur(Pic,core);
    
    imshow("222222",Pic);
    imwrite("/Users/ama/Desktop/2.jpg", Pic);
    cvWaitKey();
}


void ScanImageAndGlur(Mat& Input,Core &core)
{
    CV_Assert(Input.depth() != sizeof(uchar));
    
    int Gaussian_core_size=core.Get_core_size();
    
    int Center_of_core=Gaussian_core_size/2;
    int Cnt_of_iteration=Gaussian_core_size-Center_of_core;
    int channels=Input.channels();
    
    int nRows = Input.rows;
    int nCols = Input.cols * channels;
    
    int P_pos;
    int sum;
    int up;
    int down;
    int left;
    int right;
    
    if ( Input.isContinuous() )
    {
        nCols *= nRows;
        nRows = 1;
    }
    
    uchar *pointer_up;
    uchar *pointer;
    uchar *pointer_down;
    for(int i=0;i<nRows;i++)
    {
        for(int j=0;j<nCols;j++)
        {
            sum=0;
            P_pos=0;
            
            pointer = Input.ptr<uchar>(i);
            sum+=(pointer[j]*core.Core_element(Center_of_core,Center_of_core));
            for(int k=1;k<Cnt_of_iteration;k++)
            {
                P_pos=k;
                
                up=i-1;
                down=i+1;
                left=j-(P_pos*channels);
                right=j+(P_pos*channels);
                
                if(up < 0) up=down;
                if(down >= nRows ) down=up;
                if(left < 0) left=right;
                if(right >= nCols) right=left;
                
                pointer_up = Input.ptr<uchar>(up);
                pointer_down = Input.ptr<uchar>(down);
                
                sum+=(pointer[left]*core.Core_element(Center_of_core,Center_of_core-P_pos) );
                sum+=(pointer[right]*core.Core_element(Center_of_core,Center_of_core+P_pos) );
                
                sum+=(pointer_up[j]*core.Core_element(Center_of_core-P_pos,Center_of_core) );
                sum+=(pointer_up[left]*core.Core_element( Center_of_core-P_pos , Center_of_core-P_pos ) );
                sum+=(pointer_up[right]*core.Core_element( Center_of_core-P_pos , Center_of_core+P_pos ) );
                
                sum+=(pointer_down[j]*core.Core_element( Center_of_core+P_pos , Center_of_core ) );
                sum+=(pointer_down[left]*core.Core_element( Center_of_core+P_pos , Center_of_core-P_pos ) );
                sum+=(pointer_down[right]*core.Core_element( Center_of_core+P_pos , Center_of_core+P_pos ) );
            }
            pointer[j]=sum;
        }
    }
}
