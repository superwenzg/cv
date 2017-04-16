/*
	used to caculate the sin fuc
	@	amaswz superwenzg@gmail.com
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>

const double RIGHT=0.3367;
const double LEFT=0.000;
const double SIGMA=0.0001;

using namespace std;

void init(int n,double **Part_x,double **Part_y,double &Left,double &Right,double &Sigma)
{
    Left=LEFT;
    Right=RIGHT;
    Sigma=SIGMA;
    *Part_x=new double[n];
    *Part_y=new double[n];
    
    cout<<"input the interpolation argv"<<endl;
    for(int i=0;i<n;i++)
    {
        //cout<<"The "<<i<<' '<<"pointer"<<" x: y:";
        (*Part_x)[i]=0;
        cin>>(*Part_x)[i];
        (*Part_y)[i]=0;
        cin>>(*Part_y)[i];
    }
}

void caculate(const double *Part_x,const double *Part_y,const int Num,
              const double Left,const double Right,const double sigma)
{
    
    ofstream file;
    ofstream file2;
    file.open("/Users/ama/Desktop/test.txt");
    file2.open("/Users/ama/Desktop/test2.txt");
    double list[Num];
    for(int i=0;i<Num;i++)
    {
        list[i]=1;
        for(int j=0;j<Num;j++)
        {
            if(j==i) continue;
            else
            {
                list[i]*=(Part_x[i]-Part_x[j]);
            }
        }
    }
    
    double fuc_res;
    double numerator;
    for(double x=Left;x<=Right;x+=sigma)
    {
        fuc_res=0;

        for(int l=0;l<Num;l++)
        {
            numerator=1;
            for(int i=0;i<Num-1;i++)
            {
                numerator*=(x-Part_x[(l+i+1)%Num]);
            }
            fuc_res+=Part_y[l]*numerator/list[l];
        }
        file<<fuc_res<<endl;
        file2<<sin(x)-fuc_res<<endl;
    }
}



int main(int argc,char** argv)
{
    if(argc<=1)
    {
        cout<<"Error argv input"<<endl;
        exit(0);
    }
    
    int Num_of_interpolation;
    double Left;
    double Right;
    double sigma;
    double *Part_x;
    double *Part_y;
    
    //transf the string to num
    stringstream s;
    s<<argv[1];
    s>>Num_of_interpolation;
    
    init(Num_of_interpolation,&Part_x,&Part_y,Left,Right,sigma);
    caculate(Part_x,Part_y,Num_of_interpolation,Left,Right,sigma);
}