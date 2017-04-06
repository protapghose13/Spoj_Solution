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
const int sqn = 1005;
int n,q;
int arr[250005];
int block[250005];
int tree[505][50005];
int sz[sqn+5];
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
void upd(int blk,int idx,int val){
    while(idx<=50000){
        tree[blk][idx] += val;
        idx += (idx & -idx);
    }
}
int query(int blk,int idx){
    int sum=0;
    while(idx){
        sum += tree[blk][idx];
        idx -= (idx & -idx);
    }
    return sum;
}
int get_larger(int l,int r,int val){
    if(l>r)return 0;
    int ans=0;
    if(block[l]==block[r]){
        for(int i=l;i<=r;i++)
            ans += (arr[i]>val);
        return ans;
    }
    for(int i=l;i<=n&&block[i]==block[l];i++)
        ans += (arr[i]>val);
    for(int i=block[l]+1;i<block[r];i++)
        ans += sz[i]-query(i,val);
    for(int i=r;i>=1&&block[i]==block[r];i--)
        ans += (arr[i]>val);
    return ans;
}
int get_smaller(int l,int r,int val){
    if(l>r)return 0;
    int ans=0;
    if(block[l]==block[r]){
        for(int i=l;i<=r;i++)
            ans += (arr[i]<val);
        return ans;
    }
    for(int i=l;i<=n&&block[i]==block[l];i++)
        ans += (arr[i]<val);
    for(int i=block[l]+1;i<block[r];i++)
        ans += query(i,val-1);
    for(int i=r;i>=1&&block[i]==block[r];i--)
        ans += (arr[i]<val);
    return ans;
}
int main(){
   // freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    n = scan();
    for(int i=1;i<=n;i++){
        arr[i] = scan();
        block[i] = i/sqn;
        sz[block[i]]++;
        upd(block[i],arr[i],1);
    }
    q = scan();
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans += query(500,50000)-query(500,arr[i]);
        upd(500,arr[i],1);
    }
    while(q--){
        int x,y;
        x = scan();
        y = scan();
        ans -= get_larger(1,x-1,arr[x]);
        ans -= get_smaller(x+1,n,arr[x]);
        ans += get_larger(1,x-1,y);
        ans += get_smaller(x+1,n,y);
        upd(block[x],arr[x],-1);
        upd(block[x],y,1);
        arr[x]=y;
        printf("%lld\n",ans);
    }
    return 0;
}
