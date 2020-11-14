#include <bits/stdc++.h>
using namespace std;
const double eps=1e-9;
int main()
{
    freopen("input.txt", "r", stdin);
    int x1, y1, r1, x2, y2, r2;
    cin>>x1>>y1>>r1>>x2>>y2>>r2;
    if(x1==x2 and y1==y2) cout<<"Centers are the same";
    else
    {
        double a1=2*x1-2*x2, b1=2*y1-2*y2, c1=-pow(x1, 2)+pow(x2, 2)-pow(y1, 2)+pow(y2, 2)+pow(r1, 2)-pow(r2, 2), a2, b2, c2;
        a2=b1, b2=-a1, c2=-a2*x1-b2*y1;
        double x0=(-c1*b2+c2*b1)/(a1*b2-a2*b1);
        double y0=(-c1*a2+c2*a1)/(b1*a2-b2*a1);
        double d=pow(x0-x1, 2)+pow(y0-y1, 2);
        if(d-pow(r1, 2)>eps) cout<<"No intersection";
        else if(abs(d-pow(r1, 2))<eps) cout<<fixed<<setprecision(10)<<x0<<" "<<y0;
        else
        {
            double k=sqrt((pow(r1, 2)-d)/(pow(a1, 2)+pow(b1, 2)));
            double x3=x0+b1*k, y3=y0-a1*k, x4=x0-b1*k, y4=y0+a1*k;
            cout<<fixed<<setprecision(10)<<x3<<" "<<y3<<" "<<x4<<" "<<y4;
        }
    }
}
