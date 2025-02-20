#include "pch.h"
#include <iostream>
using namespace std;
struct linknode
{
	int value;
	linknode *next;
};
class link
{
	linknode *head;
public:
	link() :head(0) {}
	friend istream& operator>>(istream& in, link& me);
	friend ostream& operator<<(ostream& out, link& me);
	link& getIntersection(const link &a, const link &b);
};
istream& operator>>(istream& in, link& me)
{
	me.head = new linknode;
	me.head->value = 0;
	linknode *nodenow = me.head;
	int readin;
	while (1)
	{
		in >> readin;
		if (readin == -1)
			break;
		nodenow->next = new linknode;
		nodenow = nodenow->next;
		nodenow->value = readin;
		me.head->value++;
	}
	nodenow->next = 0;
	return in;
}
ostream& operator<<(ostream& out, link& me)
{
	if (me.head->value == 0)
		out << "NULL" << endl;
	else
	{
		linknode *nodenow = me.head;
		do
		{
			nodenow = nodenow->next;
			out << nodenow->value << ' ';
		}
		while (nodenow->next != 0);
		out << endl;
	}
	return out;
}
link& link::getIntersection(const link &a, const link &b)
{
	linknode *ansNodeNow = this->head = new linknode;
	this->head->value = 0;
	linknode *aNodeNow = a.head->next, *bNodeNow = b.head->next;
	while (aNodeNow != 0 && bNodeNow != 0)
	{
		if (aNodeNow->value == bNodeNow->value)
		{
			ansNodeNow->next = new linknode;
			ansNodeNow = ansNodeNow->next;
			ansNodeNow->value = aNodeNow->value;
			this->head->value++;
			aNodeNow = aNodeNow->next;
			bNodeNow = bNodeNow->next;
		}
		else if (aNodeNow->value < bNodeNow->value)
			aNodeNow = aNodeNow->next;
		else
			bNodeNow = bNodeNow->next;
	}
	ansNodeNow->next = 0;
	return *this;
}
int main()
{
	link s1, s2, s3;
	cin >> s1;
	cin >> s2;
	s3.getIntersection(s1, s2);
	cout << s3;
}