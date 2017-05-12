/*
	Romberg algo
	@amaswz superwenzg@gmail.com
 */

#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

class Romberg
{
public:
    Romberg(const double lhs,const double rhs,const int ct);
    
    inline double fuc_calculate(const double x);
    
    void calculate();
    void deep_calculate();
private:
    double _lhs,_rhs,_hight;
    double *_ans,*_deep_ans;
    
    int _cut_time;
    int _accdeep;
};

Romberg::Romberg(const double lhs,const double rhs,const int ct)
:_lhs(lhs),
_rhs(rhs),
_cut_time(ct),
_accdeep(ct)
{
    _hight = rhs - lhs;
    _ans = new double[ct];
    _deep_ans = new double[ct];
    
    _ans[0] = ( fuc_calculate(_lhs) + fuc_calculate(_rhs) ) * _hight / 2;
    _ans[1] = _ans[0] / 2 + fuc_calculate( _hight / 2 + _lhs ) * _hight / 2;
}

inline double Romberg::fuc_calculate(const double x)
{
    if(x == 0 ) return 1;
    return sin(x) / x;
}

void Romberg::calculate()
{
    int cut_cnt = 1;
    double omega = 0.25;
    double cal_first = 0;
    double Sum = 0;
    double footstep = _hight / 4;
    double x_point = _hight / 2 + _lhs;
    
    queue <double> q;
    q.push( x_point );
    
    for( int i = 2; i <= _cut_time; i++ )
    {
        Sum = 0;
        for( int j = 0; j < cut_cnt; j++)
        {
            x_point = q.front();
            q.pop();

            Sum += fuc_calculate( x_point - footstep );
            q.push( x_point - footstep );
            
            Sum += fuc_calculate( x_point + footstep );
            q.push( x_point + footstep );
            
        }
        cal_first = _ans[i-1] / 2;
        _ans[i] = cal_first + _hight * omega * Sum;
        
        cut_cnt <<= 1;
        omega /= 2;
        footstep /= 2;
    }
    
}

void Romberg::deep_calculate()
{
    double omega = 1;
    
    for( int i = 0; i < _cut_time; i++ )
        _deep_ans[i] = _ans[i];
    
    for( int i =1; i < _accdeep; i++ )
    {
        omega *= 4;
        for( int j=0; j < _cut_time-i; j++ )
        {
            _deep_ans[j] = (omega) / ( omega - 1 ) * _deep_ans[j+1] -
            _deep_ans[j] / ( omega - 1 );
        }
    }
    
    printf("%.16lf\n",_deep_ans[_cut_time-1]);
}

int main()
{
    double lhs;
    double rhs;
    int cnt = 20;
    
    cin>>lhs>>rhs;

    Romberg R(lhs,rhs,cnt);
    R.calculate();
    R.deep_calculate();
}

