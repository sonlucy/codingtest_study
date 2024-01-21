#ifndef NODE_H
#define NODE_H
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;
class Node
{
public:
	string val;
	Node* next;
	Node();
	Node(string val);
};


Node::Node(string val)
{
	this->val = val;
	this->next = NULL;
}

#endif
