void transform(int *A, int n, bool invert, string type)
{
    int i=n>>1;
    if(invert) i=1;
    while(i>0 and i<n)
    {
        int a=0;
        while(a<n)
        {
            for(int b=a; b<a+i; b++)
            {
                int x=A[b], y=A[b+i];
                if(type=="and")
                {
                    if(!invert) A[b]=x+y, A[b+i]=y;
                    else A[b]=x-y, A[b+i]=y;
                }
                if(type=="or")
                {
                    if(!invert) A[b]=x+y, A[b+i]=x;
                    else A[b]=y, A[b+i]=x-y;
                }
                if(type=="xor")
                {
                    if(!invert) A[b]=x+y, A[b+i]=x-y;
                    else A[b]=(x+y)/2, A[b+i]=(x-y)/2;
                }
            }
            a+=i<<1;
        }
        if(!invert) i>>=1;
        else i<<=1;
    }
}
void multiply(int *A, int *B, int n, int *re, string type)
{
    transform(A, n, 0, type);
    transform(B, n, 0, type);
    for(int a=0; a<n; a++) re[a]=A[a]*B[a];
    transform(re, n, 1, type);
}
