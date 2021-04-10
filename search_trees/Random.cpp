mt19937 rnd(0);

template <class T>
struct Node
{
    T key;
    int sz = 1;
    Node <T> *l=0, *r=0;
    Node(T x){key = x;}
};

template <class T>
struct Random
{
    Node <T> *root = 0;

    void recalc(Node <T> *v)
    {
        v->sz = 1;
        if(v->l) v->sz += v->l->sz;
        if(v->r) v->sz += v->r->sz;
    }

    Node <T>* left_turn(Node <T> *v)
    {
        Node <T> *v2 = v->r;
        v->r = v2->l;
        recalc(v);
        v2->l = v;
        recalc(v2);
        return v2;
    }

    Node <T>* right_turn(Node <T> *v)
    {
        Node <T> *v2 = v->l;
        v->l = v2->r;
        recalc(v);
        v2->r = v;
        recalc(v2);
        return v2;
    }

    bool find(T x)
    {
        Node <T> *v = root;

        while(v != 0)
        {
            if(v->key == x) return true;
            else if(v->key > x) v = v->l;
            else v = v->r;
        }
        return false;
    }

    bool insert(T x)
    {
        if(find(x)) return false;
        int sz = (root) ? root->sz+1 : 1;
        root = rec_insert(root, x, rnd()%sz == 0);
        return true;
    }

    Node <T> *rec_insert(Node <T> *v, T x, bool rt)
    {
        if(!v) return new Node <T>(x);
        else if(v->key > x)
        {
            v->l = rec_insert(v->l, x, rt);
            if(rt) v = right_turn(v);
            else recalc(v);
            return v;
        }
        else
        {
            v->r = rec_insert(v->r, x, rt);
            if(rt) v = left_turn(v);
            else recalc(v);
            return v;
        }
    }

    bool erase(T x)
    {
        if(!find(x)) return false;
        root = rec_erase(root, x);
        return true;
    }

    Node <T> *rec_erase(Node <T> *v, T x)
    {
        if(v->key == x)
        {
            Node <T> *v2 = merge(v->l, v->r, x);
            delete v;
            return v2;
        }
        else if(v->key > x)
        {
            v->l = rec_erase(v->l, x);
        }
        else
        {
            v->r = rec_erase(v->r, x);
        }
        recalc(v);
        return v;
    }

    Node <T>* merge(Node <T> *l, Node <T> *r, T x)
    {
        if(l == 0) return r;
        if(r == 0) return l;

        if(rnd()%(l->sz + r->sz) < l->sz)
        {
            l->r = merge(l->r, r, x);
            recalc(l);
            return l;
        }
        else
        {
            r->l = merge(l, r->l, x);
            recalc(r);
            return r;
        }
    }
};
