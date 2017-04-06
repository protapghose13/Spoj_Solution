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
int arr[mx];
void build(int node,int b,int e){
    if(b==e){
        tree[node].pb(arr[b]);
        return;
    }
    int mid = (b+e)>>1;
    int l = node<<1;
    int r=l+1;
    build(node<<1,b,mid);
    build((node<<1)+1,mid+1,e);
    merge( tree[l].begin(),tree[l].end(),tree[r].begin(),tree[r].end(), std::back_inserter(tree[node]) );
}
void query(int node,int b,int e,int i,int j){
    if(e<i || b>j){
        return;
    }
    if(b>=i&&e<=j){
        vec.pb(node);
        return;
    }
    int mid=(b+e)>>1;
    query(node<<1,b,mid,i,j);
    query((node<<1)+1,mid+1,e,i,j);
}
int findans(){
    int l,r,k;
    l = scan();
    r = scan();
    k = scan();
    vec.clear();
    query(1,1,n,l,r);
    int low = -1e9,high=1e9;
    int sz=vec.size();
    while(high-low>4){
        int mid = (low+high)>>1;
        int res=0;
        bool flag=0;
        for(int i=0;i<sz;i++){
            res+=upper_bound(tree[ vec[i] ].begin(),tree[ vec[i] ].end(),mid)-tree[ vec[i] ].begin();
            if(binary_search(tree[ vec[i] ].begin(),tree[ vec[i] ].end(),mid))flag=1;
        }
        if(res>=k){
            high = mid;
        }
        else{
            low = mid;
        }
    }
    for(int i=low;i<=high;i++){
        int res=0;
        bool flag=0;
        for(int j=0;j<sz;j++){
            res+=upper_bound(tree[ vec[j] ].begin(),tree[ vec[j] ].end(),i)-tree[ vec[j] ].begin();
            if(binary_search(tree[ vec[j] ].begin(),tree[ vec[j] ].end(),i))flag=1;
        }
        if(res>=k && flag)return i;
    }
}
int main(){
   // freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    n = scan();
    m = scan();
    for(int i=1;i<=n;i++){
        arr[i] = scan();
    }
    build(1,1,n);
    while(m--){
        printf("%d\n",findans());
    }
    return 0;
}
