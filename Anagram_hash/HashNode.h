#ifndef HASH_NODE_H
#define HASH_NODE_H
#include"Node.h"
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;
class HashNode {

public:
	string key;
	Node* anagram;  // val, next
	HashNode* next;
	HashNode();

	HashNode* search(string key);
	void insert(string key, string word);
};


HashNode::HashNode()
{
	this->key = "";
	this->anagram = NULL;
	this->next = NULL;
}



void HashNode::insert(string key, string word)  //////
{
	if (this->key == "")
	{
		this->key = key;
		anagram = new Node(word);
	}
	else
	{
		HashNode* curr = this;
		HashNode* prev = this;
		bool flag = false;
		while (curr != nullptr)
		{
			if (curr->key != key)
			{
				prev = curr;
				curr = curr->next; //
			}
			else
			{
				Node* nnode = new Node(word);
				Node* cur = curr->anagram;
				Node* pre = curr->anagram;
				while (cur != nullptr)
				{
					pre = cur;
					cur = cur->next;
				}
				pre->next = nnode;
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			HashNode* nnode = new HashNode();
			nnode->key = key;
			nnode->anagram = new Node(word);
			prev->next = nnode;
		}
	}
}

HashNode* HashNode::search(string key)
{
	HashNode* node = this;
	while (node != nullptr)
	{
		if (node->key == key)
		{
			return node;
		}
		node = node->next;
	}
	return NULL;
}

#endif