#include<bits/stdc++.h>
#define mp make_pair
#define ll long long
#define pb push_back
#define ppb pop_back
#define mod 1000000007
#define mx 100011
#define inf 1e9
#define ff first
#define ss second
using namespace std;
int n,m;
int arr[mx],tree[mx],ans[4*mx];
vector<pair<int,int> >vec;
vector< pair<int,pair<int,pair<int,int> > > > vec1;
void upd(int idx){
    while(idx<=n){
        tree[idx]++;
        idx += (idx&-idx);
    }
}
int query(int idx){
    int sum=0;
    while(idx){
        sum += tree[idx];
        idx -= (idx&-idx);
    }
    return sum;
}
int  main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        vec.pb(mp(arr[i],i));
    }
    sort(vec.rbegin(),vec.rend());
    int q;
    scanf("%d",&q);

    for(int i=1;i<=q;i++){
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        vec1.pb( mp(k,mp(l,mp(r,i)))  );
    }
    sort(vec1.begin(),vec1.end());
    for(int i=0;i<n;i++){
        while(vec1.size()){
            if(vec1.back().ff>=vec[i].ff){
                ans[ vec1.back().ss.ss.ss ] = query(vec1.back().ss.ss.ff)-query( vec1.back().ss.ff-1 );
                vec1.ppb();
            }
            else{
                break;
            }
        }
        upd( vec[i].ss );
    }
    while(vec1.size()){
        ans[ vec1.back().ss.ss.ss ] = query(vec1.back().ss.ss.ff)-query( vec1.back().ss.ff-1 );
        vec1.ppb();
    }
    for(int i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
