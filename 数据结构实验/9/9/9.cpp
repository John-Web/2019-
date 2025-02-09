#include "pch.h"
#include <iostream>
#include <string>
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
	string *names;
	int size;
	int findroot(int x);
	void unionroot(int root1,int root2);
public:
	ufset(int s=DAFAULT_SIZE2);
	~ufset(){ delete[] parent,names; }
	void link(int x1,int x2);
	//注意：operator=是不可以friend化的
	bool islinked(int x1,int x2);
	void output_all_sets();
	void setname(int idx,string name){ names[idx]=name; }
	int findbyName(string name);
};
ufset::ufset(int s)
{
	parent=new int[s];
	for(int i=0; i<s; i++)
		parent[i]=-1;
	size=s;
	names=new string[s];
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
int ufset::findbyName(string name)
{
	for(int i=0; i<size; i++)
		if(name==names[i])
			return i;
	return -1;
}
class program
{
	minHeap minedges;
	ufset* points;
	bool minimumTreeisBuilded;
	int totalCost;
	heapnode* resultEdges;
public:
	void exe();
	void initialize();
	char chooseFunction();
	void wrongFunction();
	void buildPoints();
	void addEdges();
	bool buildMinimumTree();
	void showMinimumTree();
	program():minimumTreeisBuilded(false){}
	~program(){ delete points,resultEdges; }
};
void program::initialize()
{
	cout<<"**************************"<<endl;
	cout<<"*     电网造价模拟系统      *"<<endl;
	cout<<"**************************"<<endl;
	cout<<"*     A创建电网顶点        *"<<endl;
	cout<<"*     B添加电网的边        *"<<endl;
	cout<<"*     C构造最小生成树      *"<<endl;
	cout<<"*     D显示最小生成树      *"<<endl;
	cout<<"*     C退出程序           *"<<endl;
	cout<<"**************************"<<endl;
}
char program::chooseFunction()
{
	char ans;
	cout<<"请选择操作：";
	cin>>ans;
	return ans;
}
void program::wrongFunction()
{
	cout<<"输入的字母有误，请重新输入。";
}
void program::exe()
{
	initialize();
	char fun; 
	while(1)
	{
		fun=chooseFunction();
		switch(fun)
		{
		case 'A':
			buildPoints();
			break;
		case 'B':
			addEdges();
			break;
		case 'C':
			buildMinHeap();
			break;
		case 'D':
			showMinHeap();
			break;
		case 'E':
			return;
		default:
			wrongFunction();
			break;
		}
	}
}
void program::buildPoints()
{
	int numofPoints;
	cout<<"请输入顶点的个数：";
	cin>>numofPoints;

	points=new ufset(numofPoints);
	string name;
	cout<<"请依次输入各顶点的名称："<<endl;
	for(int i=0; i<numofPoints; i++)
	{
		cin>>name;
		points->setname(i,name);
	}
}
void program::addEdges()
{
	int numofEdges;
	cout<<"请输入顶点的个数：";
	cin>>numofEdges;
	
	string head,tail;
	int cost;
	int headIdx,tailIdx;
	for(int i=0; i<numofEdges; i++)
	{
		cout<<"请输入两个顶点和边：";
		cin>>head>>tail>>cost;
		headIdx=points->findbyName(head);
		tailIdx=points->findbyName(tail);
		minedges.push(heapnode(headIdx,tailIdx,cost));
	}
}
bool program::buildMinimumTree()
{
	minimumTreeisBuilded=false;
	int numOfChecked = 0;
	while (!allPointChecked)
	{
		int index = getMinFromFeatureList();//找到当前未达到最优状态的权值最小的点
		if (index == -1)
		{
			cerr << "请先添加电网的边！" << endl;
			return false;
		}

		Node* temp = adjaList[index];//从邻接表中提取index的邻接点
		while (temp != NULL)
		{
			int name = temp->insideName;
			if(!featureList[name].known)
				featureList[name].update(temp->money, index);//更新权值
			temp = temp->next;
		}
		featureList[index].known = true;//index已被检测完毕，达到最优
		++numOfChecked;//被检测过的点的数目加1

		if (numOfChecked == numOfNode)//所有点都被检测完毕
			allPointChecked = true;
	}
	return true;
}
void program::showMinimumTree()
{
	if(!minimumTreeisBuilded)
	{
		cout<<"尚未生成最小生成树。请检查每个点是否已相互联通。"<<endl;
		return;
	}
	cout<<""

}
int main()
{
	program Program;
	Program.exe();


	int totalcost=0;
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