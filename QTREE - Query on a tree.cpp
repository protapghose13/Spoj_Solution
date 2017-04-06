#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
#define pb push_back
#define ppb pop_back
#define mod 1000000007
#define mx 10011
#define inf 1000000007
#define ff first
#define ss second
using namespace std;
int n,ptr;
vector<int>vec[mx],edge[mx],cost[mx];
int tree[4*mx],edgecost[mx],edgetrack[mx],lvl[mx],dp[16][mx],subtree[mx];
int chainHead[mx],chainNo[mx],baseArray[mx],baseArrayposition[mx];
void build(int nd,int b,int e){
    if(b==e){
        tree[nd] = edgecost[ baseArray[b] ];
        return;
    }
    build(nd<<1,b,(b+e)>>1);
    build(nd<<1|1,( (b+e)>>1 )+1,e);
    tree[nd] = max(tree[nd<<1],tree[nd<<1|1]);
    return;
}
int query(int nd,int b,int e,int i,int j){
    if(e<i || b>j)return 0;
    else if(b>=i && e<=j)return tree[nd];
    return max(  query(nd<<1,b,(b+e)>>1,i,j) , query(nd<<1|1,((b+e)>>1)+1,e,i,j) );
}
int query_up(int u,int v){ /// v is ancestor of u
    if(u==v)return 0;
    int ans=0;
    while(true){
        if(chainNo[u]==chainNo[v]){
            ans = max(ans,query(1,1,ptr,baseArrayposition[v]+1,baseArrayposition[u]) );
            break;
        }
        ans = max(ans,query(1,1,ptr, baseArrayposition[ chainHead[chainNo[u]] ],baseArrayposition[u] ) );
        u = dp[0][ chainHead[chainNo[u]] ];
    }
    return ans;
}
void update(int nd,int b,int e,int i,int j,int val){
    if(e<i || b>j)return;
    if(b>=i && e<=j){
        tree[nd]=val;
        return;
    }
    update(nd<<1,b,(b+e)>>1,i,j,val);
    update(nd<<1|1,((b+e)>>1)+1,e,i,j,val);
    tree[nd]=max(tree[nd<<1],tree[nd<<1|1]);
    return;
}
void change(int ind,int val){
    update( 1,1,ptr, baseArrayposition[ edgetrack[ ind ] ],baseArrayposition[ edgetrack[ ind ] ],val );
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
        edgecost[v]=cost[nd][i];
        edgetrack[edge[nd][i]]=v;
        lvl[v]=lvl[nd]+1;
        dfs(v,nd);
        subtree[nd] += subtree[v];
    }
}
void clr(int n){
    for(int i=1;i<=n;i++){
        vec[i].clear();
        edge[i].clear();
        cost[i].clear();
        for(int j=0;j<=15;j++){
            dp[j][i]=-1;
        }
        chainHead[i]=0;
    }
    chain=1;
    ptr=0;
}
int main(){
   // freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        clr(n);
        for(int i=1;i<n;i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            vec[u].pb(v);
            vec[v].pb(u);
            cost[u].pb(w);
            cost[v].pb(w);
            edge[u].pb(i);
            edge[v].pb(i);
        }
        dfs(1,-1);
        HLD(1,-1);
        build(1,1,ptr);
        for(int i=1;i<=15;i++){
            for(int j=1;j<=n;j++){
                if(dp[i-1][j]!=-1){
                    dp[i][j] = dp[i-1][ dp[i-1][j] ];
                }
            }
        }
        while(true){
            char str[10];
            scanf("%s",str);
            if(str[0]=='D')break;
            int l,r;
            scanf("%d%d",&l,&r);
            if(str[0]=='C'){
                change(l,r);
            }
            else{
                int node = lca(l,r);
                printf("%d\n",max( query_up(l,node),query_up(r,node) ));
            }
        }
    }
    return 0;
}
