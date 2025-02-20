#include "pch.h"
#include <iostream>
using namespace std;
struct node
{
	int value;
	node *next;
	node(int value):value(value),next(0){}
	node(){}
};
union nuitype
{
	int index;
	node *start;
};
//逻辑：如果该节点已经被转移了，end==NULL,start指向合并后的node的index
class equallink
{
private:
	int n;
	nuitype *start;
	node **end;
public:
	equallink(int num);
	void combine(int a,int b);
	void out();
};
equallink::equallink(int num)
{
	n=num;
	start=new nuitype[n];
	end=new node*[n];
	//bug:服了自己...写成了end[n]=new node[n];
	for(int i=0; i<n; i++)
	{
		end[i]=new node(i);
		start[i].start=end[i];
	}
}
void equallink::combine(int a,int b)
{
	while(end[a]==NULL)
		a=start[a].index;
	while(end[b]==NULL)
		b=start[b].index;
	if(a==b)return;
	end[a]->next=start[b].start;
	end[a]=end[b];
	end[b]=NULL;
	start[b].index=a;
}
void equallink::out()
{
	for(int i=0; i<n; i++)
		if(end[i]!=NULL)
		{
			for(node* p=start[i].start; p!=NULL; p=p->next)
				cout<<p->value<<" ";
			cout<<endl;
		}
}
int main()
{
	node *qqq=new node(3);
	int n,m,a,b;
	cin>>n>>m;
	equallink myequal(n);
	for(int i=0; i<m; i++)
	{
		cin>>a>>b;
		myequal.combine(a,b);
	}
	myequal.out();
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