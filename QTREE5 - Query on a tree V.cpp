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
int n,m;
set<int>myset[mx];
int lvl[mx],dp[mx][20];
int color[mx];

inline int ReadInt() {
    int n = 0, ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}

void dfs(int node,int par){
    for(int v : myset[node]){
        if(v==par)continue;
        lvl[v] = lvl[node]+1;
        dp[v][0] = node;
        dfs(v,node);
    }
}
void precalc(){
    memset(dp,-1,sizeof(dp));
    dfs(1,-1);
    for(int i=1;i<20;i++){
        for(int j=1;j<=n;j++){
            if(dp[j][i-1]==-1)continue;
            dp[j][i] = dp[ dp[j][i-1] ][i-1];
        }
    }
}
int lca(int a,int b){
    if(lvl[a]<lvl[b]){
        return lca(b,a);
    }
    for(int i=17;i>=0;i--){
        if(lvl[a]-(1<<i)>=lvl[b]){
            a = dp[a][i];
        }
    }
    if(a==b)return a;
    for(int i=17;i>=0;i--){
        if( dp[a][i]!=-1 && dp[a][i]!=dp[b][i] ){
            a = dp[a][i],b=dp[b][i];
        }
    }
    return dp[a][0];
}

/***************   DEcomposing Part ****************/
int subtree[mx];
int cnt;
void dfs1(int node,int par){
    subtree[node]=1;
    cnt++;
    for(int v : myset[node]){
        if(v==par)continue;
        dfs1(v,node);
        subtree[node] += subtree[v];
    }
}
int dfs2(int node,int par){
    for(int v : myset[node]){
        if(v==par)continue;
        if(subtree[v]>cnt/2){
            return dfs2(v,node);
        }
    }
    return node;
}
int parent[mx];
void decompose(int node,int par){
    cnt=0;
    dfs1(node,par);
    int center = dfs2(node,par);
    parent[center] = par;
    for(int v : myset[center]){
        if(v==par)continue;
        myset[v].erase(center);
        decompose(v,center);
    }
    myset[center].clear();
}

/************** Query Part ************/
set< pair<int,int> > tree[mx];
set< pair<int,int> > :: iterator it;
//struct node{
//    int u,w;
//    bool operator < (const node &p) const{
//        return w>p.w;
//    }
//};
//priority_queue<node>pq;

int dist(int a,int b){
    return (  lvl[a]+lvl[b]-( lvl[ lca(a,b) ]<<1 ) );
}
void upd(int node,int rednode){
    while(node!=-1){
        tree[node].insert(  mp(  dist(rednode,node), rednode ) );
        node = parent[node];
    }
}
int tap(int node){
    while(tree[node].size()){
        it = tree[node].begin();
     //   cout<<it->first<<" "<<it->second<<endl;
        if(!color[it->ss]){
            tree[node].erase(it);
        }
        else{
            return it->ff;
        }
    }
    return inf;
}

int main(){

    n=ReadInt();
    for(int i=0;i<n-1;i++){
        int u,v;
        u=ReadInt();
        v=ReadInt();
        myset[u].insert(v);
        myset[v].insert(u);
    }
    precalc();
    decompose(1,-1);

    m=ReadInt();
    for(int i=0;i<m;i++){
        int type,v;
        type=ReadInt();
        v=ReadInt();
        if(type==0){
            color[v]=!color[v];
            if(color[v]){
                upd(v,v);
            }
        }
        else{
            int ret=inf;
            int node=v;
            while(node!=-1){
                ret = min(ret, dist(v,node)+tap(node) );
                node = parent[node];
            }
            if(ret>=inf)ret=-1;
            printf("%d\n",ret);
        }
    }
    return 0;
}
