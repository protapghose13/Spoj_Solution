#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll tree[200001];

struct node
{
    ll a,ind,val;
}ara[200001];

bool cmp1(node p,node q)
{
    return p.a<q.a;
}

bool cmp2(node p,node q)
{
    return p.ind<q.ind;
}

ll query(ll idx)
{
    ll sum=0;
    while(idx>0)
    {
        sum += tree[idx];
        idx -= (idx&-idx);
    }
    return sum;
}

void update(ll idx,ll n,ll val)
{
    while(idx<=n)
    {
        tree[idx]+=val;
        idx += (idx&-idx);
    }
}

int main()
{
   // freopen("in.txt","r",stdin);
    ll i,j,k,l=0,m,n,t,p,q;
    scanf("%lld",&t);
    while(t--)
    {
        l++;
        memset(tree,0,sizeof(tree));
        scanf("%lld",&n);
        for(i=0;i<n;i++)
        {
            scanf("%lld",&ara[i].a);
            ara[i].ind=i+1;
        }
        sort(ara,ara+n,cmp1);
        for(i=0;i<n;i++)
            ara[i].val=i+1;
        sort(ara,ara+n,cmp2);
        ll ans=0;
        for(i=0;i<n;i++)
        {
            p=query(n);
            q=query(ara[i].val);
            ans += p-q;
            update(ara[i].val,n,1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
