#include <bits/stdc++.h>
#include <iostream>
#include <string>
#define mx 30011
#define mp make_pair
#define pb push_back
#define mod 100003
#define xx first
#define yy second

using namespace std;

int n,arr[mx];
vector<int>vec[4*mx];

void build(int node,int b,int e){
    if(b==e){
        vec[node].pb(arr[b]);
        return;
    }
    int mid=(b+e)>>1;
    int l=node<<1;
    int r=l+1;

    build(l,b,mid);
    build(r,mid+1,e);

    merge(vec[l].begin(),vec[l].end(),vec[r].begin(),vec[r].end(),back_inserter(vec[node]));
}

int query(int node,int b,int e,int i,int j,int val){
    if(e<i || b>j)
        return 0;

    if(b>=i && e<=j){
        int p = upper_bound(vec[node].begin(),vec[node].end(),val)-vec[node].begin();
        return (e-b+1)-p;
    }

    int mid=(b+e)>>1;
    int l=node<<1;
    int r=l+1;

    int x = query(l,b,mid,i,j,val);
    int y = query(r,mid+1,e,i,j,val);

    return x+y;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(false);
    cout.tie(false);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int q;
    build(1,1,n);
    cin>>q;
    int a,b,c;
    int last=0;
    for(int i=0;i<q;i++){
        int p,q,r;
        cin>>p>>q>>r;
        a=p^last;
        b=q^last;
        c=r^last;
        int ans=query(1,1,n,a,b,c);
        cout<<ans<<endl;
        last=ans;
    }
    return 0;
}


