#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/
#define MAXN 100000
vector<int> node[MAXN];
vector<int> renode[MAXN];
int postnum[MAXN]= {0};
bool visited[MAXN]={0};
bool isvisited[MAXN]={0};
int redfs(int u, int ordernum)
{
    visited[u]=true;
    if(renode[u].empty())
    {
        ordernum++;
        postnum[u]=ordernum;
        return ordernum;
    }
    int post=ordernum;
    for(int i=0; i<renode[u].size(); i++)
    {

        if(visited[renode[u][i]]==false)
        {
            post=redfs(renode[u][i],post+1);
        }
    }
    postnum[u]=post+1;
    return post+1;
}
int findmax()
{
    int maxn=-1;
    int i=0;
    for(i=0; i<MAXN; i++)
    {
        if(postnum[i]>0&&isvisited[i]==false)
            {maxn=i;break;}
    }
    for(; i<MAXN; i++)
    {
        if(postnum[i]>postnum[maxn]&&isvisited[i]==false)
            maxn=i;
    }
    if(maxn==-1)
        return -1;
    return maxn;

}
void dfs(int u)
{
    isvisited[u]=true;
    if(node[u].empty())
        return;
    for(int i=0; i<node[u].size(); i++)
    {
        if(isvisited[node[u][i]]==false)
            dfs(node[u][i]);
    }
    return;
}
int SCC(int n, vector<pair<int,int>>& edge)
{
    for(int i=0; i<edge.size(); i++)
    {
        node[edge[i].first].push_back(edge[i].second);
        renode[edge[i].second].push_back(edge[i].first);
    }
    int ordernum=1;
    for(int i=0; i<MAXN; i++)
    {
        if(visited[i]==false)
        {
            ordernum=redfs(i,ordernum);
            postnum[i]=ordernum;
            visited[i]=true;
            ordernum++;
        }
    }
    int res=0;
    while(true)
    {
        int a=findmax();
        if(a==-1)
            break;
        dfs(a);
        res++;
    }
    return res;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    fin>>n>>m;
    int tmp1,tmp2;
    for(int i=0; i<m; i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
