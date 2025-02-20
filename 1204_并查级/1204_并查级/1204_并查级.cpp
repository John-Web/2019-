#include "pch.h"
#include <iostream>
using namespace std;
//这题是树的并查集
int main()
{
	int n,m;
	int *parent=new int[n];
	bool *hassearch=new bool[n]();
	for(int i=0; i<n; i++)
		parent[i]=-1;
	char ci,cj;
	int i,j;
	for(int i=0; i<m; i++)
	{
		cin>>ci>>cj;
		i=ci-'A',j=cj-'A';
		//bug:parent[i-'A']=j-'A';
		//要考虑两个parent不为-1的情况
		if(parent[i]==-1)
			parent[i]=j;
		else if(parent[j]==-1)
			parent[j]=i;
		else
		{
			while(parent[i]!=-1)
				i=parent[i];
			parent[i]=j;
			//bug:还是无法解决闭环的问题
		}
	}

	int count=n;
	while(count)
	{
		for(int i=0; i<n; i++)
		{
			//最初setroot<0，代表还没有setroot
			int setroot=-1;
			int root=i;
			while(parent[root]!=-1)
				root=parent[root];
			if(setroot==-1)
				setroot=root;
			if(setroot==root)
			{
				cout<<(char)i+'A'<<' ';
				hassearch[i]=true;
				count--;
			}
		}
		cout<<endl;
	}
}
/*
15 16
A B
A C
A D
A E
B F
F E
G E
F G
I H
H J
J I

*/