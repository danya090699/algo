const int mod=998244353, sz=(1<<20);
// 3^(7*17*(2^23))=1 mod 998244353  998244353=7*17*(2^23)+1

//const int mod=7340033;
// 5^(2^20)=1 mod 7340033

int po(int x, int y)
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
int rev(int x){return po(x, mod-2);}

int stw[sz];

void ntt(vector <int> &A, int n, int w)
{
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

void mul(vector <int> &A, vector <int> &B, vector <int> &C)
{
    int n=1;
    while(n<max(int(A.size()), int(B.size()))) n<<=1;
    n<<=1;
    A.resize(n, 0), B.resize(n, 0), C.resize(n, 0);
    int w=po(3, (mod-1)/n);
    //int w=po(5, (1<<20)/n);
    ntt(A, n, w);
    ntt(B, n, w);
    for(int a=0; a<n; a++) C[a]=(1ll*A[a]*B[a])%mod;
    ntt(C, n, rev(w));
    int rn=rev(n);
    for(int a=0; a<n; a++) C[a]=(1ll*C[a]*rn)%mod;
}
