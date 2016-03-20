#ifdef REDBLACKTREE_H
#define REDBLACKTREE_H

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cassert>
#include"MACRO.h"
using namespace std;

#define RED 1
#define BLACK 0

typedef struct Node {
	int key;
	int color;
	struct Node *parent, *left, *right;
	Node(){}
	Node(int i){
	   key = i;
	   color = RED;
	   parent = NULL;
	   left = NULL;
	   right = NULL;
	}
}rbNode;

class rbTree {
private:
	Node *root;
	Node *Nil;
	int size;
public:
	rbTree();
	virtual ~rbTree();
	void InitRoot();
	bool Insert(int k);
	bool Delete(int k);
	Node *Search(int k);
	int getSize();
private:
	void Insert_fixup(Node *pNode);
	void Delete_fixup(Node *pNode);
	void LeftRotate(Node *pNode);
	void RightRotate(Node *pNode);
	void Swap(Node *pNode1, Node *pNode2);
	void Empty(Node *pNode);
}


#endif
