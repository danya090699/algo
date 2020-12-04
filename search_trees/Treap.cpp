mt19937 rnd(time(0));

template <class T>
struct Node
{
    T key;
    unsigned int pri;
    Node <T> *l=0, *r=0;

    Node(T x)
    {
        key = x, pri = rnd();
    }
};

template <class T>
struct Treap
{
    Node <T> *root = 0;

    Node <T>* merge(Node <T> *l, Node <T> *r)
    {
        if(l == 0) return r;
        if(r == 0) return l;

        if(l->pri > r->pri)
        {
            l->r = merge(l->r, r);
            return l;
        }
        else
        {
            r->l = merge(r->l, l);
            return r;
        }
    }

    pair <Node <T>*, Node <T>*> split(Node <T> *v, T k)
    {
        if(v == 0) return {0, 0};
        else if(v->key > k)
        {
            pair <Node <T>*, Node <T>*> res = split(v->l, k);
            v->l = res.second;
            return {res.first, v};
        }
        else
        {
            pair <Node <T>*, Node <T>*> res = split(v->r, k);
            v->r = res.first;
            return {v, res.second};
        }
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

        pair <Node <T>*, Node <T>*> res = split(root, x);

        root = merge(merge(res.first, new Node<T>(x)), res.second);

        return true;
    }

    bool erase(T x)
    {
        if(!find(x)) return false;

        pair <Node <T>*, Node <T>*> res = split(root, x);

        if(res.first->r == 0)
        {
            Node <T> *v = res.first;

            res.first = v->l;

            delete v;
        }
        else
        {
            Node <T> *v = res.first;
            while(v->r->r != 0) v = v->r;

            Node <T> *v2 = v->r;
            v->r = v2->l;

            delete v2;
        }

        root = merge(res.first, res.second);

        return true;
    }
};
