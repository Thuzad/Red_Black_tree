#include<iostream>
#include"redblackTree.h"
using namespace std;

rbTree::rbTree() {
	root = Nil = NULL;
	size = 0;
}

rbTree::~rbTree() {
	Empty(root);
	delete Nil;
	root = Nil = NULL;
}

void rbTree::InitRoot() {
	root = new Node(-1);
	Nil = new Node(-1);
	root->color = BLACK;
	Nil->color = BLACK;
	root->parent = Nil;
}

void LeftRotate(Node *pNode) {
	Node *ParentNode = pNode->parent;
	Node *RightNode = pNode->right;
	pNode->right = RightNode->left;
	RightNode->left->parent = pNode;
	RightNode->left = pNode;
	pNode->parent = RightNode;

	if(pNode == ParentNode->left) {
		ParentNode->left = RightNode;
		RightNode->parent = ParentNode;
	}
	else if(pNode == ParentNode->right) {
		ParentNode->right = RightNode;
		RightNode->parent = ParentNode;
	}
	else {
		if(ParentNode == Nil) {
			RightNode->parent = Nil;
			root = RightNode;
		}
	}
}

bool rbTree::Insert(int k) {
	Node *NewNode = new Node(k);
	NewNode->left = Nil;
	NewNode->right = Nil;
	Node *RNode = root;
	Node *NNode = Nil;
	while
