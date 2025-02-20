#include "pch.h"
#include <iostream>
#include <ctime>
using namespace std;
//交换。因为用一直用所以是inclne
inline void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void bubbleSort(int *source, int size, int *&ans, int& swaptime,clock_t& time)
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	for (int sizeNow = size; sizeNow >= 2; sizeNow--)
		for (int idx = 0; idx < sizeNow - 1; idx++)
			if (ans[idx] > ans[idx + 1])
			{
				swap(ans[idx], ans[idx + 1]);
				swaptime++;
			}
	endTime = clock();
	time = endTime - startTime;
}
void selectSort(int *source, int size, int *&ans, int& swaptime,clock_t& time)
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	int minIndex;
	for (int startPos = 0; startPos < size - 1; startPos++)
	{
		minIndex = startPos;
		for (int idx = startPos + 1; idx < size; idx++)
			if (ans[idx] < ans[minIndex])
				minIndex = idx;
		if (minIndex != startPos)
		{
			swap(ans[minIndex], ans[startPos]);
			swaptime++;
		}
	}

	endTime = clock();
	time = endTime - startTime;
}
void insertSort(int *source, int size, int *&ans, int& swaptime,clock_t& time)
{
	ans = new int[size];
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	for (int newArraySize = 0; newArraySize < size; newArraySize++)
	{
		int idxToInsert = newArraySize;
		for (; idxToInsert > 0; idxToInsert--)
		{
			if(source[newArraySize]<ans[idxToInsert-1])
			{
				ans[idxToInsert] = ans[idxToInsert - 1];
				swaptime++;
			}
			else break;
		}
		ans[idxToInsert] = source[newArraySize];
		swaptime++;
	}

	endTime = clock();
	time = endTime - startTime;
}
void shellSort(int *source,int size,int *&ans,int& swaptime,clock_t& time)
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	for(int gap=size/2; gap>0; gap/=2)
	{
		//shell排序内部是插入排序
		for (int i = gap;i < size;++i)
		{
			for (int j = i;j >= gap;j -= gap)
			{
				if (ans[j] < ans[j - gap])
				{
					swap(ans[j], ans[j - gap]);
					swaptime++;
				}
			}
		}
		if(gap==1) break;//gap==1等效于一次插入排序，一定现在已经排序好了
	}
	
	endTime = clock();
	time = endTime - startTime;
}
int quickSort(int *a,int left, int right)
{
	if(left>=right) return 0;
	int swaptime=0;
	int i = left, j = right;//分别指向数组的头尾
	int key=a[left];
	while (i < j)//若两数字交错，则退出循环
	{
		while (i<j && key < a[j])
			--j;//找到右侧第一个小于基准元的数
		if(i<j)
		{
			a[i++]=a[j];
			swaptime++;
		}
		while (i<j && key > a[i])
			++i;//找到左侧第一个大于基准元的数
		if(i<j)
		{
			a[j--]=a[i];
			swaptime++;
		}
	}
	a[i]=key;
	swaptime++;

	swaptime+=quickSort(a,left, i - 1);//继续处理左半部分
	swaptime+=quickSort(a,i + 1, right);//继续处理右半部分
	return swaptime;
}
void quickSort(int *source,int size,int *&ans,int& swaptime,clock_t& time)
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	swaptime=quickSort(ans,0,size-1);

	endTime = clock();
	time = endTime - startTime;
}
int percDown(int* a,int downIndex, int endIndex)
{
	int swaptime=0;
	int childIndex;//它将指向两个儿子中较大的那一个
	for (int i = downIndex;2 * i + 1 < endIndex;i = childIndex)
	{
		childIndex = 2 * i + 1;//现在指示的是左儿子的坐标
							   /*存在的前提下，若右儿子大于左儿子，则将childIndex改为左儿子坐标*/
		if (childIndex != endIndex - 1 && a[childIndex] < a[childIndex + 1])
			++childIndex;
		if (a[i] < a[childIndex])
		{
			swap(a[i], a[childIndex]);//元素下滤
			swaptime++;
		}
		else//下滤的元素找到了合适的位置；恢复了堆序性
			break;
	}
	return swaptime;
}
void heapSort(int *source,int size,int *&ans,int& swaptime,clock_t& time)
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	for (int i = size / 2;i >= 0;--i)//建堆,最大的元素位于根部
		swaptime+=percDown(ans,i, size);
	for (int i = size - 1;i > 0;--i)
	{
		/*将堆中最大元素排在排序区头部，排序区整体上为由小到大*/
		swap(ans[i], ans[0]);
		swaptime++;
		swaptime+=percDown(ans,0, i);
	}

	endTime = clock();
	time = endTime - startTime;
}
int maxBit(int *a,int size)
{
	int maxNum = 0;
	for (int i = 0;i < size;++i)
	{
		if (maxNum < a[i])
			maxNum = a[i];
	}
	int max = 1, ruler = 10;
	while (maxNum >= ruler)
	{
		++max;
		ruler *= 10;
	}
	return max;
}
void radixSort(int *source,int size,int *&ans,int& swaptime,clock_t& time)//LSD方法实现
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	int max = maxBit(source,size);
	int* bucket = new int[size];//桶（将来的所有桶都在里面分配空间）
								/*计数器，第一阶段计算某位为index的数据数量，第二阶段标记每个桶的结束位置*/
	int* count = new int[10];

	for (int i = 0, radixNum = 1;i < max;++i)//按位数进行max次排序，radixNum为基数
	{
		for (int j = 0;j < 10;++j)//每次排序前初始化计数器
			count[j] = 0;
		for (int j = 0;j < size;++j)
		{
			/*拿到数据第i位上的数字作为索引*/
			int index = (ans[j] / radixNum) % 10;
			++count[index];//数据量加1
		}
		for (int j = 1;j < 10;++j)//为每个桶分配空间
			count[j] = count[j - 1] + count[j];//桶的结束位置

		for (int j = size - 1;j >= 0;--j)//将数据放入对应的桶中，保持稳定性
		{
			int index = (ans[j] / radixNum) % 10;
			/*count[index]-1是数据在桶中的位置*/
			bucket[count[index] - 1] = ans[j];
			--count[index];//对应数据量减1
		}
		for (int j = 0;j < size;++j)
			ans[j] = bucket[j];//将桶中数据拷贝到操作数组中
		radixNum *= 10;//基数增加
	}

	delete[] bucket;
	delete[] count;
	count = bucket = NULL;
	
	endTime = clock();
	time = endTime - startTime;
}

void mergeSort(int *a,int startidx,int length)
{
	if(length<=1) return;
	mergeSort(a,startidx,length/2);
	mergeSort(a,startidx+length/2,length-length/2);

	int *ans=new int[length];
	int left=0,right=length/2,ansidx=0;
	while(left!=length/2&&right!=length)
	{
		if(a[startidx+left]<=a[startidx+right])
		{
			ans[ansidx]=a[startidx+left];
			left++;
			ansidx++;
		}
		//两个if就要判断循环条件
		if(left!=length/2&&a[startidx+left]>=a[startidx+right])
		{
			ans[ansidx]=a[startidx+right];
			right++;
			ansidx++;
		}
	}
	for(; left!=length/2; left++)
		ans[ansidx++]=a[startidx+left];
	for(; right!=length; right++)
		ans[ansidx++]=a[startidx+right];

	for(int i=0; i<length;i++)
		a[startidx+i]=ans[i];
	delete[] ans;
}
void mergeSort(int *source,int size,int *&ans,int& swaptime,clock_t& time)
{
	ans = new int[size];
	memcpy(ans, source, size * sizeof(int));
	swaptime = 0;
	clock_t startTime, endTime;
	startTime = clock();

	mergeSort(ans,0,size);

	endTime = clock();
	time = endTime - startTime;
}
int* numProducting(int size)
{
	srand((unsigned)time(NULL));//生成随机数种子
	int *ans = new int[size];
	for (int i = 0; i < size; i++)
		ans[i] = rand();
	return ans;
}
bool arrayIsSorted(int *a, int size)
{
	for (int idx = 0; idx < size - 1; idx++)
		if (a[idx] > a[idx + 1])//没有排序好
			return false;
	return true;//排序好了
}
bool sortIsValid(int *&ans, int size, int *source)
{
	//一个严谨判断是否排序好的算法
	if (arrayIsSorted(ans, size) == false)
		return false;
	int idx = 0;
	while (idx < size)
	{
		int equalsize = 1;
		while (idx + equalsize < size)//判断是否超过最大个数
		{
			if (ans[idx] == ans[idx + equalsize])
				equalsize++;
			else break;
		}
		
		int numcount = 0;
		for (int i = 0; i < size; i++)
			if (source[i] == ans[idx])
				numcount++;
		if (numcount != equalsize)
			return false;

		idx += equalsize;
	}
	return true;
}
int main()
{
	cout << "**\t\t排序算法比较\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t1 --- 冒泡排序\t\t**" << endl;
	cout << "**\t\t2 --- 选择排序\t\t**" << endl;
	cout << "**\t\t3 --- 直接插入排序\t**" << endl;
	cout << "**\t\t4 --- 希尔排序\t\t**" << endl;
	cout << "**\t\t5 --- 快速排序\t\t**" << endl;
	cout << "**\t\t6 --- 堆排序\t\t**" << endl;
	cout << "**\t\t7 --- 归并排序\t\t**" << endl;
	cout << "**\t\t8 --- 桶排序\t\t**" << endl;
	cout << "**\t\t9 --- 基数排序\t\t**" << endl;
	cout << "**\t\t0 --- 退出程序\t\t**" << endl;
	cout << "==========================================" << endl;

	cout << endl << "请输入要产生的随机数的个数：";
	int size;
	cin >> size;
	while (size < 1)
	{
		cerr << "请输入随机数个数！" << endl;
		cin.clear();
		cin.ignore();
		cin >> size;
	}

	int *source=numProducting(size);
	int swaptime,*ans=NULL;
	clock_t time;

	while (1)
	{
		cout << endl << "请选择排序算法：\t";
		char operation;
		cin >> operation;

		switch (operation)
		{
		case '1':
			bubbleSort(source,size,ans,swaptime,time);
			break;
		case '2':
			selectSort(source,size,ans,swaptime,time);
			break;
		case '3':
			insertSort(source,size,ans,swaptime,time);
			break;
		case '4':
			shellSort(source,size,ans,swaptime,time);
			break;
		case '5':
			quickSort(source,size,ans,swaptime,time);
			break;
		case '6':
			heapSort(source,size,ans,swaptime,time);
			break;
		case '7':
			mergeSort(source,size,ans,swaptime,time);
			break;
		case '8':
			radixSort(source,size,ans,swaptime,time);
			break;
		default:
			return 0;
		}

		cout<<"排序所用时间:"<<time<<"ms."<<endl;
		cout<<"交换次数:"<<swaptime<<endl;
		if(sortIsValid(ans,size,source))
			cout<<"排序成功！"<<endl;
		else
			cout<<"排序未成功"<<endl;

		delete[] ans;
		ans=NULL;
 	}
}