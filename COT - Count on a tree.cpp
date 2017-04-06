#include <bits/stdc++.h>
#define mx 100011
#define mp make_pair
#define pb push_back
#define ppb pop_back
#define mod 1000000009
#define ff first
#define ss second
#define ll long long
#define PII pair<int,int>

#define RIGHT 131072
#define SIZE 262144
using namespace std;

struct node{
    int l,r,cnt;
    node(){
        cnt=0;
        l=-1;
        r=-1;
    }
    node(int a,int b,int c){
        cnt=a,l=b,r=c;
    }
};
node tree[mx+6000000];
int arr[mx],Root[mx],lvl[mx],Real[mx],arr1[mx],global;
vector<int>vec[mx];
int dp[20][mx];
map<int,int>mapa;
int upd(int root,int b,int e,int val){
    if(val<b || val>e)
        return root;
    ++global;
    int id = global;
    if(val==b && b==e){
        tree[id] = node(tree[root].cnt+1,-1,-1);
        return id;
    }
    tree[id] = node(tree[root].cnt+1,upd( tree[root].l,b,(b+e)>>1,val),upd(tree[root].r,((b+e)>>1)+1 ,e ,val) );
    return id;
}

int tap(int root1,int root2,int root3,int root4,int b,int e,int k){
    if(b==e)// && k==1 && tree[root2].cnt-tree[root1].cnt==1
        return b;
    int val = tree[tree[root1].l].cnt + tree[tree[root2].l].cnt - tree[tree[root3].l].cnt - tree[tree[root4].l].cnt;
    int mid=(b+e)>>1;
    if(val>=k)
        return tap(tree[root1].l,tree[root2].l,tree[root3].l,tree[root4].l,b,mid,k);
    else
        return tap(tree[root1].r,tree[root2].r,tree[root3].r,tree[root4].r,mid+1,e,k-val);
}
void dfs(int nd,int pr){
    dp[0][nd]= ((pr==0)?-1:pr);
    Root[nd] = upd(Root[pr],1,mx,mapa[ arr[nd] ]);
    for(int i=0;i<vec[nd].size();i++){
        int v=vec[nd][i];
        if(v!=pr){
            lvl[v]=lvl[nd]+1;
            dfs(v,nd);
        }
    }
}
int lca(int u,int v){
    if(lvl[u]<lvl[v])
        return lca(v,u);
    int val;
    for(val=0;val<17;val++){
        if((1<<val)>=lvl[u]){
            break;
        }
    }
    if(val==17)val--;
    for(int i=val;i>=0;i--){
        if( (1<<i)<=(lvl[u]-lvl[v]) ){
            u = dp[i][u];
        }
    }
    if(u==v)return u;
    for(int i=val;i>=0;i--){
        if( dp[i][v]!=-1 && dp[i][v]!=dp[i][u] ){
            u = dp[i][u];
            v = dp[i][v];
        }
    }
    return dp[0][u];
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(dp,-1,sizeof(dp));
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        arr1[i]=arr[i];
    }
    sort(arr1+1,arr1+n+1);
    for(int i=1;i<=n;i++){
        mapa[ arr1[i] ]=i;
        Real[ i ]=arr1[i];
    }

    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        vec[u].pb(v);
        vec[v].pb(u);
    }
    dfs(1,0);
    for(int i=1;i<18;i++){
        for(int j=1;j<=n;j++){
            if(dp[i-1][j]!=-1){
                dp[i][j] = dp[i-1][dp[i-1][j] ];
            }
        }
    }

    for(int i=0;i<m;i++){
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int node = lca(l,r);
        printf("%d\n",Real[ tap(Root[l],Root[r],Root[node],Root[dp[0][node]],1,mx,k) ]);
    }

    return 0;
}
