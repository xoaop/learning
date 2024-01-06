#include <iostream>
#include <queue>
#include <vector>
#include<stdlib.h>
using namespace std;

int map1[5][5]={{0,1,1,0,0},{0,0,1,1,1},{0,0,0,1,1},{0,0,0,0,1},{0,0,0,1,0}};
vector<int> result;

void BFS(int start,int end)
{
    queue<int> q1;
    bool visited[5]={false};
    q1.push(start);
    int size;

    while(!q1.empty())
    {   
        size=q1.size();
        for(int i=0;i<size;i++)
        {
            if(visited[q1.front()]==false)
            {
                for(int j=0;j<5;j++)
                {
                    if(map1[q1.front()][j]==1)
                    {
                        q1.push(j);
                    }
                }
                visited[q1.front()]=true;
                result.push_back(q1.front());
            }
            q1.pop();
            
        }        
    }
} 

int main()
{
    BFS(0,4);
    for(int i=0;i<5;i++)
    {
        cout<<result[i]<<" ";
    }
    system("pause");
}
