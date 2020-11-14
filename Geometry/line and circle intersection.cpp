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
    int cx, cy, r, x1, y1, x2, y2;
    cin>>cx>>cy>>r>>x1>>y1>>x2>>y2;
    double a1, b1, c1, a2, b2, c2;
    to_line(x1, y1, x2, y2, a1, b1, c1);
    a2=b1, b2=-a1, c2=-a2*cx-b2*cy;
    double x0=(-c1*b2+c2*b1)/(a1*b2-a2*b1);
    double y0=(-c1*a2+c2*a1)/(b1*a2-b2*a1);
    double d=pow(x0-cx, 2)+pow(y0-cy, 2);
    if(d-pow(r, 2)>eps) cout<<"No intersection";
    else if(abs(d-pow(r, 2))<eps) cout<<fixed<<setprecision(10)<<x0<<" "<<y0;
    else
    {
        double k=sqrt((pow(r, 2)-d)/(pow(a1, 2)+pow(b1, 2)));
        double x3=x0+b1*k, y3=y0-a1*k, x4=x0-b1*k, y4=y0+a1*k;
        cout<<fixed<<setprecision(10)<<x3<<" "<<y3<<" "<<x4<<" "<<y4;
    }
}
