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
    :_noip(num_of_inter_point),
     _rcon(0)
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
    double calcaute_ret(int lhs,int rhs);
    
    void show_list();
private:
    int _noip; //插值点个数
    int _order;
    int _rcon; // ret_controal_order_num
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

double Newdon_it::calcaute_ret(int lhs,int rhs)
{
    if(lhs==rhs)
    {
        return _array[lhs].second;
    }
    else
    {
        double a,b,s;
        
        a=calcaute_ret(lhs+1,rhs);
        b=calcaute_ret(lhs,rhs-1);
        
        s= (a-b)/(_array[rhs].first-_array[lhs].first);
        
        if(lhs==0)
        {
            _ans[_rcon]=s;
            _rcon++;
        }
        return s;
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

void Newdon_it::show_list()
{
    for(int i=0;i<_noip;i++)
    {
        cout<<_ans[i]<<endl;
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
    
    Ni.calcaute_ret(0,num_of_inter_point);
    Ni.show_list();
    
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
 
 0.41075
 1.116
 0.28
 0.197333
 0.0312381
 0.00029304
 
 0.017037 1.017183
 0.146447 1.157713
 0.370590 1.448590
 0.629410 1.876502
 0.853553 2.347975
 0.982963 2.672363
 */

