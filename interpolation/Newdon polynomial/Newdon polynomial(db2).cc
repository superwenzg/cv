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

void caculate(const double *Part_x,const double *Part_y,double *List,
                const int Left,const int Right)
{
    double Ans[10];
    memset(Ans,0,sizeof Ans);
    for(int i=0;i<6;i++)
    {
        Ans[i]=Part_y[i];
    }
    
    //i cows
    //j rows
   /* for(int i=1;i<Right;i++)
    {
        for(int j=i;j<Right;j++)
        {
            Ans[j-1]=(Ans[j]-Ans[j-1])/(Part_x[j]-Part_x[j-1]);
            //Ans[j][i]=(Ans[j][i-1]-Ans[j-1][i-1])/(Part_x[j]-Part_x[j-i]);
        }
    }
    */
    
    for(int i=1;i<Right;i++)
    {
        for(int j=Right-1;j>=i;j--)
        {
            Ans[j]=(Ans[j]-Ans[j-1])/(Part_x[j]-Part_x[j-i]);
        }
    }
    for(int i=0;i<Right;i++)
    {
        cout<<Ans[i]<<endl;
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
    
    init(Num_of_interpolation,&Part_x,&Part_y,Left,Right,sigma);
    caculate(Part_x,Part_y,list,0,5);
}