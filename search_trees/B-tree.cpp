template <class T, int t>
struct Node
{
    int n;
    bool leaf;
    T keys[2*t];
    Node <T, t> *children[2*t+1];
};

template <class T, int t>
struct Btree
{
    Node <T, t> *root;

    Btree()
    {
        root = new Node <T, t>;
        root->n = 0;
        root->leaf = true;
    }

    bool find(T x)
    {
        Node <T, t> *v = root;

        while(1)
        {
            int i = 0;
            while(i < v->n and v->keys[i] < x) i++;

            if(i < v->n and v->keys[i] == x) return true;

            if(v->leaf) return false;
            else v = v->children[i];
        }
    }

    bool insert(T x)
    {
        Node <T, t> *v = root, *pr = 0;

        while(1)
        {
            int i = 0;
            while(i < v->n and v->keys[i] < x) i++;

            if(i < v->n and v->keys[i] == x) return false;

            if(v->n == 2*t-1)
            {
                if(pr == 0)
                {
                    root = new Node <T, t>;
                    root->n = 0;
                    root->leaf = false;
                    pr = root;
                }

                Node <T, t> *v2 = new Node <T, t>;
                v->n = t-1;
                v2->n = t-1;
                v2->leaf = v->leaf;

                for(int a=0; a<t-1; a++) v2->keys[a] = v->keys[a+t];
                for(int a=0; a<t; a++) v2->children[a] = v->children[a+t];

                int j = pr->n-1;

                while(j>=0 and pr->keys[j] > v->keys[t-1])
                {
                    pr->keys[j+1] = pr->keys[j];
                    pr->children[j+2] = pr->children[j+1];
                    j--;
                }
                j++;
                pr->n++;
                pr->keys[j] = v->keys[t-1];
                pr->children[j] = v;
                pr->children[j+1] = v2;

                if(i >= t) v = v2;
            }
            else
            {
                if(v->leaf)
                {
                    for(int a=v->n-1; a>=i; a--) v->keys[a+1] = v->keys[a];
                    v->keys[i] = x;
                    v->n++;
                    return true;
                }
                else pr = v, v = v->children[i];
            }
        }
    }

    bool erase(T x)
    {
        Node <T, t> *v = root;

        while(1)
        {
            int i = 0;
            while(i < v->n and v->keys[i] < x) i++;

            if(i < v->n and v->keys[i] == x)
            {
                if(v->leaf)
                {
                    for(int a=i+1; a<v->n; a++) v->keys[a-1] = v->keys[a];
                    v->n--;
                    return true;
                }
                else
                {
                    if(v->children[i]->n >= t)
                    {
                        Node <T, t> *v2 = v->children[i];

                        while(!v2->leaf) v2 = v2->children[v2->n];

                        int x2 = v2->keys[v2->n-1];

                        erase(x2);

                        v->keys[i] = x2;

                        return true;
                    }
                    else if(v->children[i+1]->n >=t)
                    {
                        Node <T, t> *v2 = v->children[i+1];

                        while(!v2->leaf) v2 = v2->children[0];

                        int x2 = v2->keys[0];

                        erase(x2);

                        v->keys[i] = x2;

                        return true;
                    }
                    else v = merge(v, i);
                }
            }
            else
            {
                if(v->leaf) return false;
                else
                {
                    if(v->children[i]->n >= t) v = v->children[i];
                    else
                    {
                        if(i>0)
                        {
                            if(v->children[i-1]->n >= t) v = move_right(v, i-1);
                            else v = merge(v, i-1);
                        }
                        else
                        {
                            if(v->children[i+1]->n >= t) v = move_left(v, i);
                            else v = merge(v, i);
                        }
                    }
                }
            }
        }
    }

    Node <T, t>* move_right(Node <T, t>* v, int i)
    {
        Node <T, t> *l = v->children[i], *r = v->children[i+1];

        for(int a=r->n-1; a>=0; a--) r->keys[a+1] = r->keys[a];
        r->keys[0] = v->keys[i];

        for(int a=r->n; a>=0; a--) r->children[a+1] = r->children[a];
        r->children[0] = l->children[l->n];

        r->n++;

        v->keys[i] = l->keys[l->n-1];

        l->n--;

        return r;
    }

    Node <T, t>* move_left(Node <T, t>* v, int i)
    {
        Node <T, t> *l = v->children[i], *r = v->children[i+1];

        l->keys[l->n] = v->keys[i];

        l->children[l->n+1] = r->children[0];

        l->n++;

        v->keys[i] = r->keys[0];

        for(int a=1; a<r->n; a++) r->keys[a-1] = r->keys[a];

        for(int a=1; a<=r->n; a++) r->children[a-1] = r->children[a];

        r->n--;

        return l;
    }

    Node <T, t>* merge(Node <T, t>* v, int i)
    {
        Node <T, t> *l = v->children[i], *r = v->children[i+1];

        l->keys[t-1] = v->keys[i];
        for(int a=0; a<t-1; a++) l->keys[a+t] = r->keys[a];

        for(int a=0; a<=t; a++) l->children[a+t] = r->children[a];

        delete r;

        l->n = 2*t-1;

        for(int a=i+1; a<v->n; a++)
        {
            v->keys[a-1] = v->keys[a];
            v->children[a] = v->children[a+1];
        }
        v->n--;

        if(v->n == 0)
        {
            delete v;
            root = l;
        }

        return l;
    }
};
