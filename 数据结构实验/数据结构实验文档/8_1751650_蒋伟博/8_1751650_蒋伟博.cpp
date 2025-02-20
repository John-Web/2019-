#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
	Node(const int num, const int cost)
		:insideName(num) ,cost(cost), next(NULL) {}
	int insideName;//内部编号
	int cost;
	Node* next;
};
class Feature {
public:
	Feature(){}
	Feature(int weight, int name)
		:known(false), weight(weight), lastAdaj(name) {}
	bool update(int newWeight, int newAdaj);
	bool known;//描述节点是否以权值最小的形式连接到生成树上
	int weight;//节点权值
	int lastAdaj;//记录与它连接的那个点
};
class Graph {
public:
	Graph(int size);
	~Graph();
	void storeName(string name);//将名称储存起来
	int findName(string name);//将内部编号转化为原始名称
	void storeAdja(int num1, int num2, int cost);//将两个点储存在邻接表中
	bool canDoPrim(int index);//初始化最小生成树的各项相关参数,判断是否可以生成最小生成树
	int getMinFromFeatureList();
	bool buildPrimTree();//建立最小生成树
	void printPrimTree();//打印最小生成树
private:
	int numOfNode;//记录节点数量
	string* nameList;//对应节点名称和内部编号
	Node** adjaList;//储存图的邻接表
	Feature* featureList;//储存节点在生成树中的feature
};
bool Feature::update(int newWeight, int newAdaj)
{
	if (newWeight < weight)
	{
		weight = newWeight;
		lastAdaj = newAdaj;
		return true;
	}
	else
		return false;
}
Graph::Graph(int size)
{
	numOfNode = size;
	nameList = new string[numOfNode];
	adjaList = new Node*[numOfNode];
	featureList = new Feature[numOfNode];
	for (int i = 0;i < numOfNode;i++)//初始化邻接表
	{ 
		adjaList[i] = NULL;
		nameList[i]= "null";
	}

}
Graph::~Graph()
{
	delete[] nameList;
	delete[] featureList;
	for (int i = 0;i < numOfNode;i++)
	{
		Node* temp = adjaList[i];
		while (temp != NULL)
		{
			Node* next = temp->next;
			delete temp;
			temp = next;
			next = NULL;
		}
	}
}
void Graph::storeName(string name)
{
	for (int i = 0; i < numOfNode; i++)
	{
		//如果已经在名称列表中,则不执行任何操作
		if(nameList[i]=="null")//如果不在名称列表中
		{
			nameList[i] = name;
			return;
		}
	}
}
int Graph::findName(string name)
{
	for (int i = 0;i < numOfNode;++i)
		if (nameList[i] == name)//如果找到了名称
			return i;
	return -1;//未找到名称
}
void Graph::storeAdja(int num1, int num2, int cost)
{
	Node* temp = adjaList[num1];
	if(temp==NULL)//该点下邻接表为空
	{
		adjaList[num1] = new Node(num2, cost);
		return;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new Node(num2, cost);
}
bool Graph::canDoPrim(int index)
{
	for (int i = 0; i < numOfNode; i++)//初始化特征表中的每项数值
	{
		if (adjaList[i] == NULL)//检查图中是否有孤立点
		{
			cout << "有孤立点，无法生成最小生成树！" << endl;
			return false;
		}
		featureList[i] = Feature(INT_MAX, -1);
	}
	featureList[index].weight = 0;//确定起始点
	return true;
}
int Graph::getMinFromFeatureList()
{
	int min = INT_MAX, name = -1;
	for (int i = 0;i < numOfNode;++i)
	{
		if (!featureList[i].known && featureList[i].weight < min)
		{
			min = featureList[i].weight;
			name = i;
		}
	}
	return name;
}
bool Graph::buildPrimTree()
{
	bool allPointChecked = false;
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
				featureList[name].update(temp->cost, index);//更新权值
			temp = temp->next;
		}
		featureList[index].known = true;//index已被检测完毕，达到最优
		numOfChecked++;//被检测过的点的数目加1

		if (numOfChecked == numOfNode)//所有点都被检测完毕
			allPointChecked = true;
	}
	return true;
}
void Graph::printPrimTree()
{
	for (int i = 0;i < numOfNode;++i)
	{
		for (int j = 0;j < numOfNode;++j)
		{
			if (featureList[j].lastAdaj == i)
			{
				string name = nameList[j];
				string lastAdaj = nameList[featureList[j].lastAdaj];
				cout << lastAdaj << "-(" << featureList[j].weight << ")->" << name << '\t';
			}
		}
	}
}
class program
{
public:
	void enterNode(int, Graph*);
	void enterEdge(Graph*);
	void buildTree(Graph*);
	void init();
};
void program::enterNode(int size, Graph* graph)
{
	cout << "请依次输入各顶点的名称：" << endl;
	while (size--)
	{
		string name;
		cin >> name;
		graph->storeName(name);
	}
}

void program::enterEdge(Graph* graph)
{
	if (graph == NULL)
	{
		cerr << "请先创建电网顶点！" << endl;
		return;
	}

	int num1, num2, cost;
	string name1, name2;
	while(1)
	{
		cout << "请输入两个顶点及边：";
		cin >> name1 >> name2 >> cost;
		if (name1 == "?" || name2 == "?")
			break;
		num1 = graph->findName(name1);
		num2 = graph->findName(name2);
		if (num1 == -1 || num2 == -1)
		{
			cerr << "输入的顶点不存在！" << endl;
			cin.clear();
			cin.ignore();
			continue;//输入出错时，要求重新输入
		}
		if (cin.fail() || cost < 0)
		{
			cerr << "请输入正确的大于等于0的造价！" << endl;
			cin.clear();
			cin.ignore();
			continue;//输入出错时，要求重新输入
		}

		/*因为是无向图，所以两个点都要互相储存对方*/
		graph->storeAdja(num1, num2, cost);
		graph->storeAdja(num2, num1, cost);
	}
}

void program::buildTree(Graph* graph)
{
	if (graph == NULL)
	{
		cerr << "请先创建电网顶点！" << endl;
		return;
	}

	string name;
	cout << "请输入起始顶点：";
	cin >> name;
	int index = graph->findName(name);
	if (index == -1)
	{
		cerr << "不存在此顶点！" << endl;
		return;
	}
	if (!graph->canDoPrim(index))
	{
		cout << "Prim最小生成树生成失败！" << endl;
		return;
	}
	if (graph->buildPrimTree())
		cout << "生成Prim最小生成树！" << endl;
	else
		cout << "Prim最小生成树生成失败！" << endl;
}
void program::init()
{
	cout << "==================================================" << endl;
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
	cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
	cout << "**\t\tC --- 构造最小生成树\t\t**" << endl;
	cout << "**\t\tD --- 显示最小生成树\t\t**" << endl;
	cout << "**\t\tE --- 退出  程序\t\t**" << endl;
	cout << "==================================================" << endl;

	Graph* graph = NULL;

	while (1)
	{
		cout << endl << "请选择操作:";
		char operation;
		cin >> operation;

		switch (operation)
		{
		case 'A':
			cout << "请输入顶点的个数：";
			int num;
			cin >> num;
			while (cin.fail() || num < 1)
			{
				cerr << "请输入大于0小INT_MAX的顶点个数！" << endl;
				cin.clear();
				cin.ignore();//防止缓冲区溢出
				cin >> num;
			}

			if (graph != NULL)
				delete graph;
			graph = new Graph(num);
			if (graph == NULL)
			{
				cerr << "内存空间不足！" << endl;
				exit(1);
			}

			enterNode(num, graph);
			break;
		case 'B':
			enterEdge(graph);
			break;
		case 'C':
			buildTree(graph);
			break;
		case 'D':
			if (graph == NULL)
			{
				cerr << "请先创建电网顶点！" << endl;
				break;
			}
			graph->printPrimTree();
			break;
		}
	}
}
int main()
{
	program myprogram;
	myprogram.init();
}

/*
A
4
A B C D
B
A B 8
B C 7
C D 5
D A 11
A C 18
B D 12
? ? 0
C
A
D




*/