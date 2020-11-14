#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    string s;
    cin>>s;
    int n=s.size();
    int pf[n];
    pf[0]=0;
    for(int a=1; a<n; a++)
    {
        int t=pf[a-1];
        while(t)
        {
            if(s[t]!=s[a]) t=pf[t-1];
            else break;
        }
        if(s[t]==s[a]) t++;
        pf[a]=t;
    }

    int al=26;
    int aut[n+1][al];
    for(int a=0; a<n; a++)
    {
        for(int i=0; i<al; i++)
        {
            if(s[a]-'a'==i) aut[a][i]=a+1;
            else
            {
                if(a) aut[a][i]=aut[pf[a-1]][i];
                else aut[a][i]=0;
            }
        }
    }
    for(int i=0; i<al; i++) aut[n][i]=aut[pf[n-1]][i];
}
