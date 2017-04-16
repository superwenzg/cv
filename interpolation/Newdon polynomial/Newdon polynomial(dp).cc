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

const long double RIGHT=0.3367;
const long double LEFT=0.000;
const long double SIGMA=0.0001;

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
        (*Part_x)[i]=0;
        cin>>(*Part_x)[i];
        (*Part_y)[i]=0;
        cin>>(*Part_y)[i];
    }
}

double caculate(const double *Part_x,const double *Part_y,double *List,int jie,
                const int Left,const int Right)
{
    if(Left==Right)
    {
        
        return Part_y[Left];
    }
    else
    {
        double a,b,s;
        a=caculate(Part_x,Part_y,List,jie-1,Left+1,Right);
        b=caculate(Part_x,Part_y,List,jie-1,Left,Right-1);
        s= (a-b)/(Part_x[Right]-Part_x[Left]);
        
        if(Left==0)
        {
            List[jie]=s;
        }
        return s;
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
    int Num_of_argv;
    int cnt;
    
    double Left;
    double Right;
    double sigma;
    double *Part_x;
    double *Part_y;
    double list[100];
    
    //transf the string to num
    stringstream s;
    s<<argv[1];
    s>>Num_of_interpolation;
    cout<<Num_of_interpolation;
    //s>>Num_of_argv;
    cnt=Num_of_argv;
    
    
    
    init(Num_of_interpolation,&Part_x,&Part_y,Left,Right,sigma);
    caculate(Part_x,Part_y,list,5,0,5);
    
    list[0]=Part_y[0];
    for(int i=0;i<5;i++)
    {
        cout<<list[i]<<endl;
    }
}