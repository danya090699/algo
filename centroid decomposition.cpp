#include <bits/stdc++.h>
using namespace std;
const int sz=1e5+10;
int si[sz];
vector <int> sv[sz];
void siz(int v, int pr)
{
    si[v]=1;
    for(int a=0; a<sv[v].size(); a++)
    {
        int ne=sv[v][a];
        if(ne!=pr)
        {
            siz(ne, v), si[v]+=si[ne];
        }
    }
}
int find_ce(int v, int pr, int q)
{
    for(int a=0; a<sv[v].size(); a++)
    {
        int ne=sv[v][a];
        if(ne!=pr and si[ne]>q/2) return find_ce(ne, v, q);
    }
    if(pr!=-1) si[pr]=q-si[v];
    return v;
}
void dfs(int v, int q)
{
    siz(v, -1);
    int ce=find_ce(v, -1, q);
    for(int a=0; a<sv[ce].size(); a++)
    {
        int ne=sv[ce][a];
        for(int b=0; b<sv[ne].size(); b++)
        {
            if(sv[ne][b]==ce) sv[ne].erase(sv[ne].begin()+b);
        }
        dfs(ne, si[ne]);
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    cin>>n;
    for(int a=0; a<n-1; a++)
    {
        int u, v;
        cin>>u>>v;
        u--, v--;
        sv[u].push_back(v);
        sv[v].push_back(u);
    }
    dfs(0, n);
}
