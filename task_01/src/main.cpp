#include <iostream>
#include <vector>
#include <stack>
using namespace std;


void topologicalSortUtil(vector<vector<int>> &g, int v, vector<bool> &visited, stack<int> &Stack)
{
    visited[v] = true;
    
    vector<int>::iterator i;
    for (i = g[v].begin(); i != g[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(g, *i, visited, Stack);

    Stack.push(v);
}

void topologicalSort(vector<vector<int>> &g)
{
    stack<int> Stack;
    int V = g.size();
    vector<bool> visited(V, false);
  
    for (int i = 0; i < V; i++)
      if (visited[i] == false)
        topologicalSortUtil(g, i, visited, Stack);
  
    while (Stack.empty() == false)
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

int main()
{
    vector<vector<int>> g = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,1,0,0},{0,1,0,0,0,0},{1,1,0,0,0,0},{1,0,1,0,0,0}};
    int N = g.size();
    topologicalSort(g);
  
    return 0;
}