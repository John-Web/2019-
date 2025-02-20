#include "pch.h"
#include <iostream>
#include <stack>
using namespace std;
struct node
{
	int value;
	node *next;
	node(int value):value(value),next(0){}
};
int main()
{
	int n,m;
	cin>>n>>m;
	node **start,**end;
	//bug:start=end=new node*[n]
	//不能连在一起！！！！
	start=new node*[n];
	end=new node*[n];
	for(int i=0; i<n; i++)
		start[i]=end[i]=new node(0);

	int a,b;
	node *nodea,*nodeb;
	for(int i=0; i<m; i++)
	{
		cin>>a>>b;
		//bug:写成nodea=new node(a)了
		nodea=new node(b);
		nodeb=new node(a);
		end[a]->next=nodea;
		end[b]->next=nodeb;
		end[a]=nodea;
		end[b]=nodeb;
	}

	stack<int> mystack;
	//add () after new bool to ensure initial value=false
	bool *issearch=new bool[n]();
	for(int i=0; i<n; i++)
		if(!issearch[i])
		{
			mystack.push(i);
			while(!mystack.empty())
			{
				int now;
				now=mystack.top();
				mystack.pop();
				issearch[now]=true;
				cout<<now<<" ";
				//change now
				for(node* nownode=start[now]; nownode!=NULL; nownode=nownode->next)
					if(!issearch[nownode->value])
						mystack.push(nownode->value);
			}
			cout<<endl;
		}
}
/*
12 9
0 4
3 1
6 10
8 9
7 4
6 8
3 5
2 11
11 0


*/
