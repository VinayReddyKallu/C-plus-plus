#include<bits/stdc++.h>
#include<algorithm>
#include<iostream>
using namespace std;
typedef vector<int> vi;
const int N = 2e5;
const int LG = 20;
vi g[N];
int p[N][LG],lvl[N];
void dfs(int u,int parent){
    lvl[u]=1+lvl[parent];
    p[u][0]=parent;
    for(int v:g[u]){
        if(v==parent)
            continue;
        dfs(v,u);
    }
}
int lca(int u,int v){
    if(lvl[u]<lvl[v])
         swap(u,v);
    int i;
    int l;
    for( l=0;(1<<l)<=lvl[u];l++);
    l--;
    for(i=l;i>=0;i--){
        if(lvl[u]-(1<<i)>=lvl[v])
            u=p[u][i];
    }
    if(u==v)
        return u;
    for(i=l;i>=0;i--){
        if(p[u][i]!=-1 && p[u][i]!=p[v][i]){
            u=p[u][i];
            v=p[v][i];

        }
    }
    return p[u][0];


}
int getAncestor(int u, int dis){
    dis = lvl[u] - dis;
    int i, lg = 0;
    for(; (1<<lg) <= lvl[u]; lg++); lg--;

    for(i=lg; i>=0; i--){
        if (lvl[u] - (1<<i) >= dis)
            u = p[u][i];
    }

    return u;
}
int main(){
    //16cout<<"hello"<<"\n";
    int n,i,j,u,v;
    cout<<"Enter the no of nodes"<<"\n";
    cin>>n;
    cout<<"Enter the edges"<<"\n";
    for(i=0;i<n-1;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout<<"Enter the two nodes:"<<"\n";
    cin>>u>>v;
    for(i=1;i<LG;i++){
        for(j=1;j<=N;j++){
            p[j][i]=-1;
        }
    }

    lvl[0]=-1;
    dfs(1,0);

    for(i=1;i<LG;i++){
        for(j=1;j<=N;j++){
            if(p[j][i-1]!=-1)
                p[j][i]=p[p[j][i-1]][i-1];
        }
    }
    
    cout<<"The LCA of the given two nodes is: "<<lca(u,v)<<"\n";
    cout<<"The ancestor of the given node at certain distance is:"<<getAncestor(11,31616);



}