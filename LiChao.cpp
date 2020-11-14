template <typename T>
class LiChao
{
public:

    LiChao(T l, T r, string ty="min")
    {
        type = ty, L = l, R = r;
        T inf = sizeof(T)==4 ? INT_MAX : LLONG_MAX;

        tree=new pair <T, T>[(R-L+1)*4];
        for(int a=0; a<(R-L+1)*4; a++) tree[a]={0, inf};
    }

    ~LiChao()
    {
        delete [] tree;
    }

    void insert(T k, T b)
    {
        if(type=="max") k=-k, b=-b;
        ins(1, L, R, {k, b});
    }

    T query(T x)
    {
        int re=que(1, L, R, x);
        if(type=="max") re=-re;
        return re;
    }

private:

    void ins(int nu, T l, T r, pair <T, T> line)
    {
        int mid=(l+r)>>1;
        bool ly=f(line, l) < f(tree[nu], l);
        bool my=f(line, mid) < f(tree[nu], mid);

        if(my) swap(line, tree[nu]);

        if(l!=r)
        {
            if(ly!=my) ins(nu*2, l, mid, line);
            else ins(nu*2+1, mid+1, r, line);
        }
    }

    T que(int nu, T l, T r, T x)
    {
        T y=f(tree[nu], x);

        if(l==r) return y;
        else
        {
            T mid=(l+r)>>1;
            if(x<=mid) return min(y, que(nu*2, l, mid, x));
            else return min(y, que(nu*2+1, mid+1, r, x));
        }
    }

    T f(pair <T, T> line, T x)
    {
        return line.first*x+line.second;
    }

    string type;
    T L, R;
    pair <T, T> *tree;
};
