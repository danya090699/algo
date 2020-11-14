#include <bits/stdc++.h>
using namespace std;
const double eps=1e-9;
void to_line(int x1, int y1, int x2, int y2, double &a, double &b, double &c)
{
    a=y2-y1, b=x1-x2, c=-a*x1-b*y1;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int x1, y1, x2, y2;
    double a1, b1, c1, a2, b2, c2;
    cin>>x1>>y1>>x2>>y2;
    to_line(x1, y1, x2, y2, a1, b1, c1);
    cin>>x1>>y1>>x2>>y2;
    to_line(x1, y1, x2, y2, a2, b2, c2);
    if(abs(a1*b2-a2*b1)<eps) cout<<"Parallel";
    else
    {
        double x=(-c1*b2+c2*b1)/(a1*b2-a2*b1);
        double y=(-c1*a2+c2*a1)/(b1*a2-b2*a1);
        cout<<fixed<<setprecision(10)<<x<<" "<<y;
    }
}
