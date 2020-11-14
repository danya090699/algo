#include <bits/stdc++.h>
using namespace std;
const int sz=(1<<20);

const int mod1=998244353, w1=3;//998244353=7*17*(2^23)+1

const int mod2=897581057, w2=3;//897581057=107*(2^23)+1

const int mod3=1004535809, w3=3;//1004535809=479*(2^21)+1

int po(int x, int y, int mod)
{
    int re=1;
    while(y)
    {
        if(y&1) re=(1ll*re*x)%mod;
        y>>=1;
        x=(1ll*x*x)%mod;
    }
    return re;
}
int rev(int x, int mod){return po(x, mod-2, mod);}

void ntt(int *A, int n, int w, int mod)
{
    int stw[n];
    stw[0]=1;
    for(int a=1; a<n; a++) stw[a]=(1ll*w*stw[a-1])%mod;
    for(int a=0, b=0; a<n; a++)
    {
        if(a<b) swap(A[a], A[b]);
        int i=(n>>1);
        while(b&i)
        {
            b-=i, i>>=1;
        }
        b+=i;
    }
    int cs=n;
    for(int i=1; i<n; i<<=1)
    {
        cs>>=1;
        for(int a=0; a<n; a+=(i<<1))
        {
            int st=0;
            for(int b=a; b<a+i; b++)
            {
                int x=A[b], y=(1ll*stw[st]*A[b+i])%mod;
                A[b]=x+y;
                if(A[b]>=mod) A[b]-=mod;
                A[b+i]=x-y;
                if(A[b+i]<0) A[b+i]+=mod;
                st+=cs;
            }
        }
    }
}

void copy(int *A2, int *A, int n)
{
    for(int a=0; a<n; a++) A2[a]=A[a];
}

void mul(int *A, int *B, long long *re, int n)
{
    int n2=1;
    while(n2<n*2) n2<<=1;
    n=n2;

    int mod[2]={mod1, mod2}, w[2]={po(w1, (mod1-1)/n, mod1), po(w2, (mod2-1)/n, mod2)}, A2[2][n], B2[2][n];

    for(int i=0; i<2; i++)
    {
        copy(A2[i], A, n), copy(B2[i], B, n);
        ntt(A2[i], n, w[i], mod[i]);
        ntt(B2[i], n, w[i], mod[i]);
        for(int a=0; a<n; a++) A2[i][a]=(1ll*A2[i][a]*B2[i][a])%mod[i];
        ntt(A2[i], n, rev(w[i], mod[i]), mod[i]);
        int rn=rev(n, mod[i]);
        for(int a=0; a<n; a++) A2[i][a]=(1ll*A2[i][a]*rn)%mod[i];
    }

    for(int i=0; i<n; i++)
    {
        int m1=mod[0], os1=A2[0][i], m2=mod[1], os2=A2[1][i];
        if(m1<m2)
        {
            swap(m1, m2), swap(os1, os2);
        }
        int a=m2, b=os1-os2, m=m1;//a*x=b(mod m)
        if(b<0) b+=m;
        int x=(1ll*b*rev(a, m))%m;
        re[i]=1ll*m2*x+os2;
    }
}

int A[sz], B[sz];
long long an[sz];

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    cin>>n>>m;
    for(int a=0; a<n; a++) cin>>A[a];
    for(int a=0; a<m; a++) cin>>B[a];

    mul(A, B, an, max(n, m));

    for(int a=0; a<10; a++) cout<<an[a]<<" ";
}
