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
    :_noip(num_of_inter_point)
    {
        _array = new Point[_noip];
        _ans = new double[_noip];
        
        for(int i=0;i<_noip;i++)
        {
            cin>>_array[i].first>>_array[i].second;
            _ans[i] = _array[i].second;
        }
    };
    
    void set_order(int order)
    {
        _order = order;
    }
    
    void res(double xt);
    void calcaute();
private:
    int _noip; //插值点个数
    int _order;
    Point *_array; //插值点数组
    
    double *_ans; //牛顿插值表
};

void Newdon_it::calcaute()
{
    for(int i=0;i<_noip;i++)
    {
        for(int j=_noip-1;j>i;j--)
        {
            _ans[j] = (_ans[j] - _ans[j-1] ) /
            ( _array[j].first - _array[j-1-i].first);
        }
        
    }
}

void Newdon_it::res(double xt)
{
    double Res = 0;
    double iteration_part = 1;
    
    Res = _ans[0];
    
    for(int i=1;i<_order;i++)
    {
        iteration_part *= (xt - _array[i-1].first);
        Res += _ans[i] * iteration_part;
    }
    
    cout<<Res<<endl;
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
    int num_of_inter_point; //插值点的个数
    int Order; //阶数
    double xt; //欲计算的点
    
    cout<<"输入插值点个数: ";
    cin>>num_of_inter_point;
    
    Newdon_it Ni(num_of_inter_point);
    Ni.calcaute();
    
    cout << "输入欲计算阶数: ";
    cin >> Order;
    Ni.set_order(Order);
    
    cout << "输入欲计算点xt(control + c退出运算): ";
    while( cin>>xt ) Ni.res(xt);
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

