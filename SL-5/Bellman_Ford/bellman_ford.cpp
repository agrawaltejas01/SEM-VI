#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

int n,e,directed,src = 1;
vector< pair<int,int> > g[20];
int dist[20],parent[20];

void init()
{
	for(int i=1;i<n+1;i++)
	{
		dist[i] = 999;
		parent[i] = -1;
	}

	parent[src] = src;
	dist[src] = 0;
}

void bellman_ford()
{
	init();

	for(int i=0;i<n;i++)				// relaxation
	{
		int update = 0;

		for(int i=1;i<n+1;i++)
		{
			for(int j=0;j<g[i].size();j++)
			{
				int u=i, v=g[i][j].first, w=g[i][j].second;

				if(dist[v] > dist[u] + w)
				{
					update = 1;
					dist[v] = dist[u] + w;
					parent[v] = u;
				}
			}
		}

		if(!update)
			break;

		for(int i=1;i<n+1;i++)
			cout<<dist[i]<<" ";		
		cout<<"\n";

		for(int i=1;i<n+1;i++)
			cout<<parent[i]<<" ";		
		cout<<"\n\n";

		
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<g[i].size();j++)
		{
			int u=i, v=g[i][j].first, w=g[i][j].second;

			if(dist[v] > dist[u] + w)		// means there exists -cycle
			{
				cout<<"There exists negative cycle \n";
				return;
			}
		}
	}

}

void path(int dest)
{
	int curr_parent = parent[dest];
	vector<int>route;

	route.pb(dest);
	route.pb(curr_parent);

	while(curr_parent != src)
	{
		curr_parent = parent[curr_parent];
		route.pb(curr_parent);
	}
	
	for(int i=route.size()-1;i>=0;i--)
		cout<<route[i]<<" ";
	cout<<"\n";
}

int main()
{
	
	cout<<"Enter no. of nodes : ";
	cin>>n;
	cout<<"\n";

	cout<<"Enter no. of edges : ";
	cin>>e;
	cout<<"\n";

	

	cout<<"Graph is directed(1) undirected(1) : ";
	cin>>directed;
	cout<<"\n";

	for(int i=0;i<e;i++)
	{
		cout<<"u,v,w : ";
		int u,v,w;

		cin>>u>>v>>w;

		g[u].pb(mp(v,w));

		if(!directed)
			g[v].pb(mp(u,w));

	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<g[i].size();j++)
			cout<<i<<" "<<g[i][j].first<<" "<<g[i][j].second<<"\n";
	}
	cout<<"\n";

	

	bellman_ford(); 
	path(5);
}