template <typename T>
class Edge
{
public:
    int to, rev;
    T flow, cap;
};

template <typename T>
class Network
{
public:

    vector < Edge<T> > *sv;

    Network(int n, int s, int t)
    {
        this->n=n, this->s=s, this->t=t;
        sv=new vector < Edge<T> >[n];
        ptr=new int[n];
        di=new int[n];
    }

    add_edge(int fr, int to, T cap, bool bidirectional=false)
    {
        max_cap=max(max_cap, cap);
        sv[fr].push_back({to, sv[to].size(), 0, cap});
        sv[to].push_back({fr, sv[fr].size()-1, 0, bidirectional ? cap : 0});
    }

    T maxflow(bool scaling=true)
    {
        min_flow=1;
        T flow=0;
        while(min_flow<max_cap and scaling) min_flow<<=1;

        for(min_flow; min_flow; min_flow>>=1)
        {
            while(bfs())
            {
                for(int a=0; a<n; a++) ptr[a]=0;
                while(1)
                {
                    T add=dfs(s, inf);
                    if(!add) break;
                    flow+=add;
                }
            }
        }
        return flow;
    }

    ~Network()
    {
        delete [] sv;
        delete [] ptr;
        delete [] di;
    }

private:

    int n, s, t, *ptr, *di;
    T max_cap=0, min_flow;
    static const T inf=sizeof(T)==4 ? INT_MAX : LLONG_MAX;

    bool bfs()
    {
        int qu[n], l=0, r=1;
        qu[0]=s;
        for(int a=0; a<n; a++) di[a]=-1;
        di[s]=0;
        while(l<r)
        {
            int v=qu[l];
            for(int a=0; a<sv[v].size(); a++)
            {
                int to=sv[v][a].to;
                if(di[to]==-1 and sv[v][a].cap-sv[v][a].flow>=min_flow)
                {
                    di[to]=di[v]+1;
                    qu[r++]=to;
                }
            }
            l++;
        }
        return di[t]!=-1;
    }

    T dfs(int v, T flow)
    {
        if(v==t) return flow;

        while(ptr[v]<sv[v].size())
        {
            Edge<T> &edge=sv[v][ptr[v]];

            if(di[v]+1==di[edge.to] and edge.cap-edge.flow>=min_flow)
            {
                T add=dfs(edge.to, min(flow, edge.cap-edge.flow));

                if(add)
                {
                    edge.flow+=add;
                    sv[edge.to][edge.rev].flow-=add;
                    return add;
                }
            }
            ptr[v]++;
        }
        return 0;
    }
};
