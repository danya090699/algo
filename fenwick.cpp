const int sz=1e5;
int fen[sz];
void cha(int p, int va)
{
    while(p<sz)
    {
        fen[p]+=va, p=p|(p+1);
    }
}
int que(int p)
{
    int re=0;
    while(p>=0)
    {
        re+=fen[p], p=(p&(p+1))-1;
    }
    return re;
}
