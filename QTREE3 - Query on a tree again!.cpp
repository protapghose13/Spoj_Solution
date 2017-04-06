#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
#define pb push_back
#define ppb pop_back
#define mod 1000000007
#define mx 100011
#define inf 1000000007
#define ff first
#define ss second
using namespace std;
int n,ptr,q;
vector<int>vec[mx],edge[mx],cost[mx];
int tree[4*mx],edgecost[mx],edgetrack[mx],lvl[mx],dp[20][mx],subtree[mx];
int chainHead[mx],chainTail[mx],chainNo[mx],baseArray[mx],baseArrayposition[mx];
int value;
void query(int nd,int b,int e,int i,int j){
    if(value)return;
    if(e<i || b>j)return;
    if(b>=i && e<=j){
        int p=b,q=e;
        int node=nd;
        if(tree[node]){
            while(p!=q){
                int mid = (p+q)>>1;
                if(tree[node<<1]){
                    q=mid;
                    node=node<<1;
                }
                else{
                    p=mid+1;
                    node=node<<1|1;
                }
            }
            value = baseArray[p];
        }
        return;
    }
    if(value==0){
        query(nd<<1,b,(b+e)>>1,i,j);
        query(nd<<1|1,((b+e)>>1)+1,e,i,j);
    }
    return;
}
int query_up(int u,int v){ /// v is ancestor of u
    vector<pair<int,int> >gg;
    while(true){
        if(chainNo[u]==chainNo[v]){
            gg.pb(mp(baseArrayposition[v],baseArrayposition[u]));
            break;
        }
        gg.pb(mp(baseArrayposition[ chainHead[chainNo[u]] ],baseArrayposition[u]));
        u = dp[0][ chainHead[chainNo[u]] ];
    }
    for(int i=gg.size()-1;i>=0;i--){
        int u = gg[i].ff;
        int v = gg[i].ss;
        value=0;
        query(1,1,ptr,u,v);
        if(value)return value;
    }
    return -1;
}
void update(int nd,int b,int e,int i,int j){
    if(e<i || b>j)return;
    if(b>=i && e<=j){
        tree[nd]=!tree[nd];
        return;
    }
    update(nd<<1,b,(b+e)>>1,i,j);
    update(nd<<1|1,((b+e)>>1)+1,e,i,j);
    tree[nd]=(tree[nd<<1]+tree[nd<<1|1]);
    return;
}
int lca(int u,int v){
    if(lvl[u]<lvl[v]){
        return lca(v,u);
    }
    int val;
    for(val=0;val<16;val++){
        if((1<<val)>=lvl[u]){
            break;
        }
    }
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
int chain;
void HLD(int nd,int pr){
    ptr++;
    if(chainHead[chain]==0){
        chainHead[chain]=nd;
    }
    chainTail[chain]=nd;
    chainNo[nd]=chain;
    baseArray[ptr]=nd;
    baseArrayposition[nd]=ptr;
    int sc=-1,cst;
    for(int i=0;i<vec[nd].size();i++){
        int v=vec[nd][i];
        if(v==pr)continue;
        if(sc==-1 || subtree[v]>subtree[sc])
            sc=v;
    }
    if(sc!=-1){
        HLD(sc,nd);
    }
    for(int i=0;i<vec[nd].size();i++){
        int v=vec[nd][i];
        if(v==pr || v==sc)continue;
        chain++;
        HLD(v,nd);
    }
    return;
}
void dfs(int nd,int pr){
    dp[0][nd]=pr;
    subtree[nd]=1;
    for(int i=0;i<vec[nd].size();i++){
        int v=vec[nd][i];
        if(v==pr)continue;
        lvl[v]=lvl[nd]+1;
        dfs(v,nd);
        subtree[nd] += subtree[v];
    }
}
int main(){
  //  freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        vec[u].pb(v);
        vec[v].pb(u);
    }
    memset(dp,-1,sizeof(dp));
    chain=1;
    dfs(1,-1);
    HLD(1,-1);
    for(int i=1;i<20;i++){
        for(int j=1;j<=n;j++){
            if(dp[i-1][j]!=-1){
                dp[i][j] = dp[i-1][ dp[i-1][j] ];
            }
        }
    }
    while(q--){
        int type,v;
        scanf("%d%d",&type,&v);
        if(type){
            printf("%d\n",query_up(v,1));
        }
        else{
            update( 1,1,ptr, baseArrayposition[v],baseArrayposition[v] );
        }
    }
    return 0;
}
