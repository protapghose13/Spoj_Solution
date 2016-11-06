#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define mx 40011
#define mod 1000000007
#define pi acos(-1.0)
#define inf 1000000000000000001

using namespace std;

map<int,int>mymap;
int arr[2*mx],ara[mx],st[mx],en[mx],L[mx],P[mx][16],cnt[mx],rem[mx],ans[100011];
vector<int>vec[mx];
int tim,BLOCK;
int answer;

struct node {
    int L, R,i,id;
}q[100011];

bool cmp(node x, node y) {
    if(x.L/BLOCK != y.L/BLOCK) {
        return x.L/BLOCK < y.L/BLOCK;
    }
    return x.R < y.R;
}


void dfs(int node,int par){
    st[node]=tim;
    arr[tim]=node;
    tim++;
    int sz=vec[node].size();
    for(int i=0;i<sz;i++){
        int v=vec[node][i];
        if(v==par)continue;
        L[v]=L[node]+1;
        P[v][0]=node;
        dfs(v,node);
    }
    en[node]=tim;
    arr[tim]=node;
    tim++;
}

int lca(int p, int q)
{
    int log=1, i;
    while(1){
        int next=log+1;
        if((1<<next)>L[p])break;
        log++;
    }
    for (i = log; i >= 0; i--)
        if (L[p] - (1 << i) >= L[q])
            p = P[p][i];
    if (p == q)
        return p;

    for (i = log; i >= 0; i--)
        if (P[p][i] != -1 && P[p][i] != P[q][i])
            p = P[p][i], q = P[q][i];

    return P[p][0];
}


void add(int pos){
    int node=arr[pos];
	rem[node]++;
	cnt[ara[node]]++;
	if (rem[node] == 2){
		cnt[ara[node]] -= 2;
		if (cnt[ara[node]] == 0)
			answer--;
	}
	else if (cnt[ara[node]] == 1) answer++;
}
void remove(int pos){
    int node=arr[pos];
	int wt = ara[node];
	rem[node]--;

	if (rem[node] == 1){
		cnt[wt]++;
		if (cnt[wt] == 1)
			answer++;
		return;
	}
	cnt[wt]--;
	if (cnt[wt] == 0) answer--;
}

int main(){
    int n,m;
    cin>>n>>m;
    BLOCK=sqrt(n);
    int k=1;
    for(int i=0;i<n;i++){
        int p;
        cin>>p;
        if (mymap.find(p) == mymap.end())
			mymap[p] = k++;
        ara[i+1]=mymap[p];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        vec[u].pb(v);
        vec[v].pb(u);
    }
    tim=1;
    memset (P,-1,sizeof(P));
    dfs(1,-1);

    for (int j = 1; (1 << j) < (n+1); j++)
        for (int i = 0; i < (n+1); i++)
            if (P[i][j - 1] != -1)
                P[i][j] = P[P[i][j - 1]][j - 1];

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        if(L[u]<L[v])swap(u,v);
        int p=lca(u,v);
        if(p==v){
            q[i].L=st[v];
            q[i].R=st[u];
            q[i].id=-1;
        }
        else{
            if(en[u]<st[v]){
                q[i].L=en[u];
                q[i].R=st[v];
            }
            else{
                q[i].L=en[v];
                q[i].R=st[u];
            }
            q[i].id=ara[p];
        }
        q[i].i=i;
    }

    sort(q, q + m, cmp);



    int currentL = 1, currentR = 1;
    answer=0;
    for(int i=0; i<m; i++) {
        int L = q[i].L, R = q[i].R;
        while(currentL < L) {
            remove(currentL);
            currentL++;
        }
        while(currentL > L) {
            add(currentL-1);
            currentL--;
        }
        while(currentR <= R) {
            add(currentR);
            currentR++;
        }
        while(currentR > R+1) {
            remove(currentR-1);
            currentR--;
        }
        ans[q[i].i] = answer;
        if(q[i].id!=-1){
            if(cnt[q[i].id]==0){
                ans[q[i].i]++;
            }
        }
    }

    for(int i=0; i<m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
