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


using namespace std;
typedef pair <double,double> Point;

class Newdon_it
{
public:
    Newdon_it(const int num_of_inter_point)
    :NOIP(num_of_inter_point)
    {
        array = new Point[NOIP];
        ans = new double[NOIP];
        
        for(int i=0;i<NOIP;i++)
        {
            cin>>array[i].first>>array[i].second;
            ans[i] = array[i].second;
        }
    };
    
    void calcaute();
private:
    int NOIP; //插值点个数
    Point *array; //插值点数组
    
    double *ans; //牛顿插值表
};

void Newdon_it::calcaute()
{
    for(int i=0;i<NOIP;i++)
    {
        for(int j=NOIP-1;j>i;j--)
        {
            ans[j] = (ans[j] - ans[j-1] ) /
                ( array[j].first - array[j-1-i].first);
        }
        
    }
    
    for(int i=0;i<NOIP;i++)
    {
        cout<<ans[i]<<endl;
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
    int num_of_inter_point;
    
    cout<<"输入插值点个数: ";
    cin>>num_of_inter_point;
    
    Newdon_it Ni(num_of_inter_point);
    Ni.calcaute();
    
}

/*
 0.40 0.41075
 0.55 0.57815
 0.65 0.69675
 0.80 0.88811
 0.90 1.02652
 1.05 1.25382
 
 0.017037 1.017183
 0.146447 1.157713
 0.370590 1.448590
 0.629410 1.876502
 0.853553 2.347975
 0.982963 2.672363
 */

