template <typename T>
struct CHT_line
{
    T k, b, r;
    operator < (const CHT_line &x) const
    {
        return r>x.r;
    }
};

template <typename T>
class CHT
{
public:

    CHT(string k, string f)
    {
        if(f=="min")
        {
            dy=1;
            if(k=="inc") dx=1;
            else dx=-1;
        }
        else
        {
            dy=-1;
            if(k=="inc") dx=-1;
            else dx=1;
        }
    }

    void insert(T k, T b)
    {
        k*=(dx*dy), b*=dy;
        while(hull.size())
        {
            T k2=hull.back().k, b2=hull.back().b, r2=hull.back().r, r;
            if(k==k2)
            {
                if(b>b2) break;
                else hull.pop_back();
            }
            else
            {
                if(b<=b2) r=(b2-b)/(k-k2);
                else r=-((b-b2)/(k-k2)+1);

                if(r>=r2) hull.pop_back();
                else
                {
                    hull.push_back({k, b, r});
                    break;
                }
            }
        }
        if(hull.size()==0) hull.push_back({k, b, inf});
    }

    T query(T x)
    {
        x*=dx;
        CHT_line <T> cu={0, 0, x};
        int p=upper_bound(hull.begin(), hull.end(), cu)-hull.begin()-1;
        return hull[p].k*x+hull[p].b;
    }

private:

    int dx, dy;
    vector <CHT_line <T> > hull;
    static const T inf=sizeof(T)==4 ? INT_MAX : LLONG_MAX;
};
