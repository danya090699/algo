#include <bits/stdc++.h>
using namespace std;
const int sz=5e5+10;
int c[20][sz], p[sz], st[sz], N, step;

void build(string &s)//nlogn, large constant
{
    N=s.size();
    int pn[N], cnt[max(N, 26)];
    for(int a=0; a<26; a++) cnt[a]=0;
    for(int a=0; a<N; a++) cnt[s[a]-'a']++;
    for(int a=1; a<26; a++) cnt[a]+=cnt[a-1];
    for(int a=0; a<N; a++)
    {
        cnt[s[a]-'a']--, p[cnt[s[a]-'a']]=a;
    }
    c[0][p[0]]=0;
    int cq=1;
    for(int a=1; a<N; a++)
    {
        if(s[p[a]]!=s[p[a-1]]) cq++;
        c[0][p[a]]=cq-1;
    }
    for(step=0; (1<<step)<N; step++)
    {
        for(int a=0; a<N; a++)
        {
            pn[a]=p[a]-(1<<step);
            if(pn[a]<0) pn[a]+=N;
        }
        for(int a=0; a<N; a++) cnt[a]=0;
        for(int a=0; a<N; a++) cnt[c[step][a]]++;
        for(int a=1; a<N; a++) cnt[a]+=cnt[a-1];
        for(int a=N-1; a>=0; a--)
        {
            cnt[c[step][pn[a]]]--, p[cnt[c[step][pn[a]]]]=pn[a];
        }
        c[step+1][p[0]]=0;
        int cq=1;
        for(int a=1; a<N; a++)
        {
            int p1=(p[a-1]+(1<<step))%N, p2=(p[a]+(1<<step))%N;
            if(c[step][p[a-1]]!=c[step][p[a]] or c[step][p1]!=c[step][p2]) cq++;
            c[step+1][p[a]]=cq-1;
        }
    }
    for(int i=0; i<=step; i++)
    {
        for(int a=(1<<i); a<min(N+1, (1<<(i+1))); a++) st[a]=i;
    }
}

bool sufcmp(int x, int y)
{
    if (c[step][x] != c[step][y]) return c[step][x] < c[step][y];
    x+=(1<<step); y += (1<<step);
    if(x>=N) x-=N;
    if(y>=N) y-=N;
    return c[step][x] < c[step][y];
}
void build2(string &s)//n*(logn)^2, small constant
{
    N=s.size();
    for(int a=0; a<N; a++) p[a]=a, c[0][a]=s[a]-'a';
    for(step=0; (1<<step)<N; step++)
    {
        sort(p, p+N, sufcmp);
        c[step+1][p[0]]=0;
        for(int a=1; a<N; a++) c[step+1][p[a]]=c[step+1][p[a-1]]+sufcmp(p[a-1], p[a]);
    }
    for(int i=0; i<=step; i++)
    {
        for(int a=(1<<i); a<min(N+1, (1<<(i+1))); a++) st[a]=i;
    }
}

bool comp(int p1, int p2, int l)
{
    int i=st[l];
    return (c[i][p1]==c[i][p2] and c[i][p1+l-(1<<i)]==c[i][p2+l-(1<<i)]);
}

int main()
{
    ifstream in("input.txt");
    string s;
    in>>s;

    build(s);
    //build2(s);

    int p1, p2, l;
    while(cin>>p1>>p2>>l) cout<<comp(p1-1, p2-1, l)<<"\n";
}
