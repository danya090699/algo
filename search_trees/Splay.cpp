template <class T>
struct Node
{
    T key;
    Node <T> *l=0, *r=0, *pr=0;
    Node(T x){key = x;}
};

template <class T>
struct Splay
{
    Node <T> *root = 0;

    void left_turn(Node <T> *v)
    {
        Node <T> *p = v->pr, *r = v->r, *B = r->l;
        if(p)
        {
            if(p->l == v) p->l = r;
            else p->r = r;
        }
        r->l = v;
        r->pr = p;
        v->r = B;
        v->pr = r;
        if(B) B->pr = v;
    }

    void right_turn(Node <T> *v)
    {
        Node <T> *p = v->pr, *l = v->l, *B = l->r;
        if(p)
        {
            if(p->l == v) p->l = l;
            else p->r = l;
        }
        l->r = v;
        l->pr = p;
        v->l = B;
        v->pr = l;
        if(B) B->pr = v;
    }

    void splay(T x)
    {
        Node <T> *v = root;

        while(1)
        {
            if(x < v->key and v->l) v = v->l;
            else if(x > v->key and v->r) v = v->r;
            else break;
        }

        while(v->pr)
        {
            Node <T> *p = v->pr, *p2 = p->pr;

            if(v == p->l)
            {
                if(p2 == 0) right_turn(p);
                else if(p == p2->l)
                {
                    right_turn(p2);
                    right_turn(p);
                }
                else
                {
                    right_turn(p);
                    left_turn(p2);
                }
            }
            else
            {
                if(p2 == 0) left_turn(p);
                else if(p == p2->r)
                {
                    left_turn(p2);
                    left_turn(p);
                }
                else
                {
                    left_turn(p);
                    right_turn(p2);
                }
            }
        }

        root = v;
    }

    bool search(T x)
    {
        Node <T> *v = root;
        while(v)
        {
            if(v->key == x) return true;
            else if(v->key > x) v = v->l;
            else v = v->r;
        }
        return false;
    }

    bool find(T x)
    {
        if(search(x))
        {
            splay(x);
            return true;
        }
        return false;
    }

    bool insert(T x)
    {
        if(search(x)) return false;

        Node <T> *l=0, *r=0;
        if(root)
        {
            splay(x);
            if(root->key < x)
            {
                l = root;
                r = root->r;
                root->r = 0;
            }
            else
            {
                r = root;
                l = root->l;
                root->l = 0;
            }
        }

        root = new Node<T>(x);
        if(l)
        {
            root->l = l, l->pr = root;
        }
        if(r)
        {
            root->r = r, r->pr = root;
        }

        return true;
    }

    bool erase(T x)
    {
        if(!search(x)) return false;

        splay(x);
        Node <T> *l=root->l, *r=root->r;
        delete root;

        if(l == 0)
        {
            if(r) root = r, r->pr = 0;
            else root = 0;
        }
        else
        {
            root = l, l->pr = 0;
            Node <T> *v = root;
            while(v->r) v = v->r;
            splay(v->key);
            if(r) root->r = r, r->pr = root;
        }

        return true;
    }
};
