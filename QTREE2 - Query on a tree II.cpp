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
int n,ptr,dis[mx];
vector<int>vec[mx],edge[mx],cost[mx];
int dp[16][mx],lvl[mx];
void dfs(int nd,int pr){
    dp[0][nd]=pr;
    for(int i=0;i<vec[nd].size();i++){
        int v = vec[nd][i];
        if(v==pr)continue;
        dis[v] = dis[nd]+cost[nd][i];
        lvl[v] = lvl[nd]+1;
        dfs(v,nd);
    }
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
        if((lvl[u]-lvl[v])>=(1<<i)){
            u = dp[i][u];
        }
    }
    if(u==v)return u;
    for(int i=val;i>=0;i--){
        if( dp[i][u]!=-1 && dp[i][u]!=dp[i][v] ){
            u=dp[i][u];
            v=dp[i][v];
        }
    }
    return dp[0][u];
}
int query(int u,int value){
    int val;
    value = lvl[u]-value;
    for(val=0;val<16;val++){
        if((1<<val)>=lvl[u]){
            break;
        }
    }
    for(int i=val;i>=0;i--){
        if((lvl[u]-value)>=(1<<i)){
            u = dp[i][u];
        }
    }
    return u;
}
void clr(int n){
    for(int i=0;i<=n;i++){
        vec[i].clear();
        cost[i].clear();
        for(int j=0;j<=15;j++){
            dp[j][i]=-1;
        }
    }
    lvl[1]=0;
    dis[1]=0;
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
        }
        dfs(1,-1);
        for(int i=1;i<16;i++){
            for(int j=1;j<=n;j++){
                if(dp[i-1][j]!=-1){
                    dp[i][j] = dp[i-1][dp[i-1][j]];
                }
            }
        }
        while(true){
            char st[10];
            scanf("%s",st);
            if(st[0]=='D' && st[1]=='O')break;
            if(st[0]=='D'){
                int u,v;
                scanf("%d%d",&u,&v);
                printf("%d\n",dis[u]+dis[v]-2*dis[ lca(u,v) ]);
            }
            else{
                int u,v,k;
                scanf("%d%d%d",&u,&v,&k);
                int nd = lca(u,v);
                if( lvl[u]-lvl[nd]+1 > k ){
                    int val = k;
                    printf("%d\n",query(u,val-1));
                }
                else if( lvl[u]-lvl[nd]+1 == k  ){
                    printf("%d\n",nd);
                }
                else{
                    k -= (lvl[u]-lvl[nd]+1);
                    int val = lvl[v]-lvl[nd]-k;
                    printf("%d\n",query(v,val));
                }
            }
        }
    }
    return 0;
}
