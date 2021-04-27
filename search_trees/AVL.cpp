template <class T>
struct Node
{
    T key;
    int h=1, dif=0;
    Node <T> *l=0, *r=0;

    Node(T x){ key = x; }
};

template <class T>
struct AVL
{
    Node <T>* root = 0;

    void recalc(Node <T> *v)
    {
        int lh = v->l ? v->l->h : 0, rh = v->r ? v->r->h : 0;

        v->h = max(lh, rh) + 1;
        v->dif = lh - rh;
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

    Node <T>* balance(Node <T> *v)
    {
        recalc(v);
        
        if(v->dif == -2)
        {
            if(v->r->dif == 1) v->r = right_turn(v->r);

            return left_turn(v);
        }
        if(v->dif == 2)
        {
            if(v->l->dif == -1) v->l = left_turn(v->l);

            return right_turn(v);
        }
        return v;
    }

    bool find(T x)
    {
        Node <T> *v = root;

        while(v != 0)
        {
            if(v->key == x) return true;
            else if(x < v->key) v = v->l;
            else v = v->r;
        }
        return false;
    }

    bool insert(T x)
    {
        if(find(x)) return false;

        root = rec_insert(root, x);

        return true;
    }

    Node <T>* rec_insert(Node <T> *v, T x)
    {
        if(v == 0) return new Node <T>(x);
        else if(x < v->key) v->l = rec_insert(v->l, x);
        else v->r = rec_insert(v->r, x);

        return balance(v);
    }

    bool erase(T x)
    {
        if(!find(x)) return false;

        root = rec_erase(root, x);

        return true;
    }

    Node <T>* rec_erase(Node <T> *v, T x)
    {
        if(v->key == x)
        {
            if(v->r == 0)
            {
                Node <T>* l = v->l;
                delete v;
                return l;
            }
            else
            {
                pair <Node <T>*, T> res = erase_min(v->r);
                v->r = res.first;
                v->key = res.second;
            }
        }
        else if(x < v->key) v->l = rec_erase(v->l, x);
        else v->r = rec_erase(v->r, x);

        return balance(v);
    }

    pair <Node <T>*, T> erase_min(Node <T>* v)
    {
        if(v->l == 0)
        {
            Node <T>* r = v->r;
            T key = v->key;
            delete v;
            return {r, key};
        }

        pair <Node <T>*, T> res = erase_min(v->l);

        v->l = res.first;

        return {balance(v), res.second};
    }
};
