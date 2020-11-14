#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    string s;
    cin>>s;
    int n=s.size();
    int p1[n], p2[n-1], l=-1, r=-1;
    for(int a=0; a<n; a++)//p1[a] is for odd palindromes with center in a
    {
        p1[a]=0;
        if(a<=r) p1[a]=min(p1[l-(a-l)], r-a);
        while(p1[a]<a and p1[a]<(n-(a+1)))
        {
            if(s[a-(p1[a]+1)]==s[a+(p1[a]+1)]) p1[a]++;
            else break;
        }
        if(r<a+p1[a])
        {
            r=a+p1[a], l=a;
        }
    }
    l=-1, r=-1;
    for(int a=0; a<n-1; a++)//p2[a] is for even palindromes with center between a and a+1
    {
        p2[a]=0;
        if(a<r) p2[a]=min(p2[l-(a-l)], r-a);
        while(p2[a]<(a+1) and p2[a]<(n-(a+1)))
        {
            if(s[a-p2[a]]==s[a+(p2[a]+1)]) p2[a]++;
            else break;
        }
        if(r<a+p2[a])
        {
            r=a+p2[a], l=a;
        }
    }
}
