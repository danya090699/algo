template <typename T>
class Edge
{
public:
    int to, rev;
    T flow, cap, cost;
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
    }

    add_edge(int fr, int to, T cap, T cost)
    {
        if(cost<0) negative=true;
        sv[fr].push_back({to, sv[to].size(), 0, cap, cost});
        sv[to].push_back({fr, sv[fr].size()-1, 0, 0, -cost});
    }

    pair <T, T> mincost()
    {
        T pot[n];
        for(int a=0; a<n; a++) pot[a]=0;
        if(negative)
        {
            bool stop=1;
            for(int a=0; a<n; a++)
            {
                bool stop=1;
                for(int b=0; b<n; b++)
                {
                    for(int c=0; c<sv[b].size(); c++)
                    {
                        if(sv[b][c].cap)
                        {
                            int to=sv[b][c].to;
                            T w=pot[b]+sv[b][c].cost;
                            if(pot[to]>w)
                            {
                                if(a==n-1)
                                {
                                    cout<<"Negative cycle!";
                                    exit(0);
                                }
                                pot[to]=w, stop=0;
                            }
                        }
                    }
                }
                if(stop) break;
            }
        }
        T flow=0, cost=0;
        while(1)
        {
            T di[n];
            int pr[n];
            for(int a=0; a<n; a++) di[a]=inf;
            di[s]=0;
            set <pair <T, int> > se;
            se.insert({0, s});
            while(se.size())
            {
                int v=(*se.begin()).second;
                se.erase(se.begin());
                for(int a=0; a<sv[v].size(); a++)
                {
                    if(sv[v][a].flow<sv[v][a].cap)
                    {
                        int to=sv[v][a].to;
                        T w=di[v]+pot[v]+sv[v][a].cost-pot[to];
                        if(di[to]>w)
                        {
                            se.erase({di[to], to});
                            di[to]=w, pr[to]=sv[v][a].rev;
                            se.insert({di[to], to});
                        }
                    }
                }
            }
            if(di[t]==inf) break;
            for(int a=0; a<n; a++)
            {
                if(di[a]==inf) pot[a]=inf;
                else pot[a]+=di[a];
            }
            T f=inf;
            for(int v=t; v!=s; v=sv[v][pr[v]].to)
            {
                int to=sv[v][pr[v]].to, i=sv[v][pr[v]].rev;
                f=min(f, sv[to][i].cap-sv[to][i].flow);
            }
            flow+=f;
            for(int v=t; v!=s; v=sv[v][pr[v]].to)
            {
                int to=sv[v][pr[v]].to, i=sv[v][pr[v]].rev;
                sv[v][pr[v]].flow-=f;
                sv[to][i].flow+=f;
                cost+=f*sv[to][i].cost;
            }
        }
        return {flow, cost};
    }

    ~Network()
    {
        delete [] sv;
    }

private:

    int n, s, t;
    bool negative=false;
    static const T inf=sizeof(T)==4 ? INT_MAX : LLONG_MAX;
};
