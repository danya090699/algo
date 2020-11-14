#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    string s;
    cin>>s;
    int n=s.size();
    int zf[n], l=0, r=-1;
    zf[0]=0;
    for(int a=1; a<n; a++)
    {
        zf[a]=0;
        if(r>=a) zf[a]=min(zf[a-l], r-a+1);
        while(a+zf[a]<n)
        {
            if(s[zf[a]]==s[a+zf[a]]) zf[a]++;
            else break;
        }
        if(a+zf[a]-1>r) l=a, r=a+zf[a]-1;
    }
    for(int a=0; a<n; a++) cout<<zf[a]<<" ";
}
