#include "pch.h"
#include <iostream>
using namespace std;
const int DAFAULT_SIZE1=10000;
const int DAFAULT_SIZE2=100;
class heapnode
{
	int key;
	int head,tail;
	friend class minHeap;
public:
	heapnode(int key=0,int head=0,int tail=0):key(key),head(head),tail(tail){}
	int& Key(){ return key; }
	int& Head(){ return head; }
	int& Tail(){ return tail; }
};
class minHeap
{
	int maxsize;
	int size;
	heapnode *heap;
	void expendsize();
	void filterdown(int start,int end);
	void filterup(int start);
public:
	minHeap(int max_size=DAFAULT_SIZE1);
	minHeap(heapnode arr[],int max_size);
	~minHeap(){ delete[] heap; }
	void push(heapnode node);
	heapnode pop();
	heapnode top();
	int Size(){ return size; }
};
void minHeap::expendsize()
{
	heapnode *temp=new heapnode[2*maxsize];
	for(int i=0; i<maxsize; i++)
		temp[i]=heap[i];
	delete[] heap;
	heap=temp;
	maxsize*=2;
}
void minHeap::filterdown(int start,int end)
{
	int i=start,j=2*start+1;
	heapnode temp=heap[i];
	while(j<=end)
	{
		if(j<end && heap[j].key>heap[j+1].key)
			j++;
		if(temp.key<=heap[j].key) break;
		else
		{
			heap[i]=heap[j];
			i=j;
			j=2*i+1;
		}
	}
	heap[i]=temp;
}
void minHeap::filterup(int start)
{
	int j=start,i=(start-1)/2;
	heapnode temp=heap[j];
	while(j>0)
	{
		if(temp.key>=heap[i].key) break;
		else
		{
			heap[j]=heap[i];
			j=i;
			i=(j-1)/2;
		}
	}
	heap[j]=temp;
}
minHeap::minHeap(int max_size)
{
	if(max_size<DAFAULT_SIZE1)
		max_size=DAFAULT_SIZE1;
	maxsize=max_size;
	size=0;
	heap=new heapnode[maxsize];
}
minHeap::minHeap(heapnode arr[],int max_size)
{
	size=max_size;
	if(max_size<DAFAULT_SIZE1)
		max_size=DAFAULT_SIZE1;
	maxsize=max_size;
	heap=new heapnode[maxsize];
	for(int i=0; i<size; i++)
		heap[i]=arr[i];
	int pos=(size-2)/2;
	while(pos>=0)
	{
		filterdown(pos,size-1);
		pos--;
	}
}
void minHeap::push(heapnode node)
{
	if(size==maxsize)
		expendsize();
	heap[size]=node;
	filterup(size);
	size++;
}
heapnode minHeap::pop()
{
	if(size==0)
		return heapnode();
	heapnode ans=heap[0];
	size--;
	heap[0]=heap[size];
	filterdown(0,size-1);
	return ans;
}
heapnode minHeap::top()
{
	if(size==0)
		return heapnode();
	return heap[0];
}

class ufset
{
	int *parent;
	int size;
	int findroot(int x);
	void unionroot(int root1,int root2);
public:
	ufset(int s=DAFAULT_SIZE2);
	~ufset(){ delete[] parent; }
	void link(int x1,int x2);
	//注意：operator=是不可以friend化的
	bool islinked(int x1,int x2);
	void output_all_sets();
};
ufset::ufset(int s)
{
	parent=new int[s];
	for(int i=0; i<s; i++)
		parent[i]=-1;
	size=s;
}
int ufset::findroot(int x)
{
	while(parent[x]>=0)
		x=parent[x];
	return x;
}
void ufset::unionroot(int root1,int root2)
{
	if(parent[root1]>=0||parent[root2]>=0) return;
	if(parent[root1]<=parent[root2])
	{
		parent[root1]+=parent[root2];
		parent[root2]=root1;
	}
	else
	{
		parent[root2]+=parent[root1];
		parent[root1]=root2;
	}
}
void ufset::link(int x1,int x2)
{
	int root1=findroot(x1);
	int root2=findroot(x2);
	unionroot(root1,root2);
}
bool ufset::islinked(int x1,int x2)
{
	return findroot(x1)==findroot(x2);
}
void ufset::output_all_sets()
{
	bool *isfound=new bool[size]();
	int startidx=0;
	while(1)
	{
		while(isfound[startidx]==true && startidx<size)
			startidx++;
		if(startidx>=size) break;
		int root=findroot(startidx);
		for(int idx=startidx;idx<size;idx++)
			if(isfound[idx]==false && findroot(idx)==root)
			{
				cout<<idx<<' ';
				isfound[idx]=true;
			}
		cout<<endl;
		//待记到编程结论上的
		//看代码的严谨性，就看变量的严谨性
		//变量的范围限制是什么
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	
	int totalcost=0;
	minHeap minedges;
	ufset points(m);
	int head,tail,cost;
	for(int i=0; i<m; i++)
	{
		cin>>head>>tail>>cost;
		minedges.push(heapnode(cost,head,tail));
	}
	while(minedges.Size()>0)
	{
		heapnode minedge=minedges.pop();
		if(!points.islinked(minedge.Head(),minedge.Tail()))
		{
			points.link(minedge.Head(),minedge.Tail());
			totalcost+=minedge.Key();
			cout<<minedge.Head()<<' '<<minedge.Tail()<<endl;
		}
	}
	cout<<totalcost;
}
/*
8
9 9
3 3
7 7
6 6
5 5
1 1
10 10
2 2
int n;
cin>>n;
minHeap mymin(n);
heapnode temp;
for(int i=0; i<n; i++)
{
cin>>temp.Key()>>temp.Value();
mymin.push(temp);
}
while(mymin.Size()>0)
cout<<mymin.pop().Value()<<' ';



*/
/*
7 9
0 1 28
0 5 10
1 6 14
1 2 16
5 4 25
4 6 24
6 3 18
2 3 12
4 3 22



*/