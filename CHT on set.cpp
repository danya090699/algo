#include <bits/stdc++.h>
#define int long long
#define iter set <el, comp>::iterator
using namespace std;
const int inf=1e18;
struct el
{
    int l, r, k, b;
};
struct comp
{
    bool operator() (const el &a, const el &b) const
    {
        return a.k>b.k;
    }
};
struct comp2
{
    bool operator() (const el &a, const el &b) const
    {
        return a.r<b.r;
    }
};
set <el, comp> hull;
set <el, comp2> hull2;
int de(int a, int b){return a/b+(a%b>0);}
int intersect(int k, int b, int k2, int b2)
{
    if(k<k2)
    {
        swap(k, k2);
        swap(b, b2);
    }
    if(b<b2) return (b2-b)/(k-k2);
    else return -de(b-b2, k-k2);
}
void ins(el cu)
{
    cu.l=-inf, cu.r=inf;
    iter it=hull.lower_bound(cu);
    vector <iter> ve;
    for(it; it!=hull.end(); it++)
    {
        el f=*it;
        int x;
        if(f.k==cu.k)
        {
            if(f.b<cu.b) x=-inf*2;
            else x=inf*2;
        }
        else x=intersect(cu.k, cu.b, f.k, f.b);
        if(x<f.r)
        {
            if(x>=f.l)
            {
                hull.erase(f);
                hull2.erase(f);
                f.l=x+1;
                hull.insert(f);
                hull2.insert(f);
            }
            cu.r=x;
            break;
        }
        else ve.push_back(it);
    }
    it=hull.lower_bound(cu);
    while(it!=hull.begin())
    {
        it--;
        el f=*it;
        int x=intersect(cu.k, cu.b, f.k, f.b);
        if(x>=f.l)
        {
            if(x<f.r)
            {
                hull.erase(f);
                hull2.erase(f);
                f.r=x;
                hull.insert(f);
                hull2.insert(f);
            }
            cu.l=x+1;
            break;
        }
        else ve.push_back(it);
    }
    for(int a=0; a<ve.size(); a++)
    {
        hull.erase(ve[a]);
        hull2.erase(*ve[a]);
    }
    if(cu.l<=cu.r)
    {
        hull.insert(cu), hull2.insert(cu);
    }
}
int que(int x)
{
    el f=*hull2.lower_bound({0, x, 0, 0});
    return f.k*x+f.b;
}
main()
{
    while(1)
    {
        int ty;
        cin>>ty;
        if(ty==1)
        {
            int k, b;
            cin>>k>>b;
            ins({0, 0, k, b});
        }
        else
        {
            int x;
            cin>>x;
            cout<<que(x)<<"\n";
        }
    }
}
