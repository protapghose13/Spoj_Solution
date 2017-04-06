#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define mx 100011
#define inf 1e8
#define mp make_pair

using namespace std;
int scan() {
    bool minus = false;
    int result = 0;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-') break;
        if (ch >= '0' && ch <= '9') break;
        ch = getchar();
    }
    if (ch == '-') minus = true; else result = ch-'0';
    while (true) {
        ch = getchar();
        if (ch < '0' || ch > '9') break;
        result = result*10 + (ch - '0');
    }
    if (minus)
        return -result;
    else
        return result;
}
int n,m;
vector<int> tree[4*mx],vec;
vector<pair<int,int> >arr;
void build(int node,int b,int e){
    if(b==e){
        tree[node].pb(arr[b-1].ss);
        return;
    }
    int mid = (b+e)>>1;
    int l = node<<1;
    int r=l+1;
    build(node<<1,b,mid);
    build((node<<1)+1,mid+1,e);
    merge( tree[l].begin(),tree[l].end(),tree[r].begin(),tree[r].end(), std::back_inserter(tree[node]) );
}
int L,R;
int query(int node,int b,int e,int k){
    if(b==e){
        return b;
    }
    int mid=(b+e)>>1;
    int l = node<<1;
    int r = l+1;
    int val = (upper_bound(tree[l].begin(),tree[l].end(),R)-tree[l].begin())-
                 (lower_bound(tree[l].begin(),tree[l].end(),L)-tree[l].begin());
    if(val>=k){
        return query(l,b,mid,k);
    }
    else{
        return query(r,mid+1,e,k-val);
    }
}
int findans(){
    int k;
    L = scan();
    R = scan();
    k = scan();

    return query(1,1,n,k);
}
int main(){
   // freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    n = scan();
    m = scan();
    for(int i=1;i<=n;i++){
        int p = scan();
        arr.pb( mp(p,i) );
    }
    sort(arr.begin(),arr.end());
    build(1,1,n);
    while(m--){
        printf("%d\n",arr[findans()-1].ff);
    }
    return 0;
}
