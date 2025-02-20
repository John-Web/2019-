#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
long long calc(const vector<int>& kind_of_coin,int target)
{
	long long *count=new long long[target+1]();
	count[0]=1;
	for(int idx=0; idx<kind_of_coin.size(); idx++)
		for(int money_now=kind_of_coin[idx]; money_now<=target; money_now++)
			count[money_now]+=count[money_now-kind_of_coin[idx]];
	long long ans=count[target];
	delete[] count;
	return ans;
}
int main()
{
	const vector<int> CNY{1,2,5,10,50,100};
	const vector<int> USD{1,5,10,25,50,100};
	const vector<int> Euro{1,2,5,10,20,50,100,200};
	const vector<int> kinds_of_coin[3]={CNY,USD,Euro};
	const string names[3]={"人民币","美元","欧元"};
	const int target=1000;

	int max_kind=0;
	long long max_count;
	cout<<"各种货币构成"<<target<<"分的组合数："<<endl;
	for(int kind=0; kind<3; kind++)
	{
		long long count=calc(kinds_of_coin[kind],target);
		if(kind==0)
			max_count=count;
		else if(count>max_count)
		{
			max_kind=kind;
			max_count=count;
		}
		cout<<names[kind]<<"的组合数为："<<count<<"种。"<<endl;
	}
	cout<<"最有表现力的是"<<names[max_kind]<<endl;
}
