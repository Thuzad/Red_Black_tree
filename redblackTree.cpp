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
	Nil = new Node(-1);
	root = Nil;
	Nil->color = BLACK;
	root->parent = Nil;
}

int rbTree::getSize() {
	return size;
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

void RightRotate(Node *pNode) {
	Node *ParentNode = pNode->parent;
	Node *LeftNode = pNode->left;
	pNode->left = LeftNode->right;
	LeftNode->right->parent = pNode;
	LeftNode->right = pNode;
	pNode->parent = LeftNode;

	if(pNode == ParentNode->left) {
		ParentNode->left = LeftNode;
		LeftNode->parent = ParentNode;
	}
	else if(pNode == ParentNode->right) {
		ParentNode->right = LeftNode;
		LeftNode->parent = ParentNode;
	}
	else {
		if(ParentNode == Nil) {
			LeftNode->parent = Nil;
			root = LeftNode;
		}
	}
}

bool rbTree::Insert(int k) {
	Node *NewNode = new Node(k);
	NewNode->left = Nil;
	NewNode->right = Nil;
	Node *pNode = root;
	Node *pPreNode = Nil;
	while(pNode != Nil) {
		pPreNode = pNode;
		if(k < pNode->key) {
			pNode = pNode->left;
		}
		else if(k > pNode->key) {
			pNode = pNode->right;
		}
		else {
			delete NewNode;
			return false;
		}
	}
	NewNode->parent = pPreNode;
	if(pPreNode == Nil) {
		NewNode->color = BLACK;
		root = NewNode;
	}
	else {
		if(k < pPreNode->key){
			pPreNode->left = NewNode;
		}
		else {
			pPreNode->right = NewNode;
		}
	}
	NewNode->left = Nil;
	NewNode->right = Nil;
	size++;
	Insert_fixup(NewNode);
	return true;
}

void rbTree::Insert_fixup(Node *pNode) {
	Node *uncleNode = NULL;
	while(pNode->parent->color == RED) {
		if(pNode->parent == pNode->parent->parent->left){
			uncleNode = pNode->parent->parent->right;
			if(uncleNode->color == RED) {
				pNode->parent->color = BLACK;
				uncleNode->color = BLACK:
				pNode->parent->parent->color = RED;
				pNode = pNode->parent->parent;
			}
			else {
				if(pNode == pNode->parent->right) {
					pNode = pNode->parent;
					LeftRotate(pNode);
				}
				pNode->parent->color = BLACK;
				pNode->parent->parent->color = RED;
				RightRotate(pNode->parent->parent);
			}
		}
		else {
			uncleNode = pNode->parent->parent->left;
			if(uncleNode->color == RED) {
				pNode->parent->color = BLACK;
				uncleNode->color = BLACK;
				pNode->parent->parent->color = RED;
				pNode = pNode->parent->parent;
			}
			else {
				if(pNode == pNode->parent->left) {
					pNode = pNode->parent;
					RightRotate(pNode);
				}
				pNode->parent->color = BLACK;
				pNode->parent->parent->color = RED;
				LeftRotate(pNode->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

bool rbTree::Delete(int k) {
	Node *pTemp;
	Node *ChildNode;
	Node *pNode, pPreNode;
	if(root == Nil) {
		return false;
	}
	pNode = Search(k);
	if(pNode == NULL) {
		return false;
	}
	pPreNode = pNode->parent;
	if(pNode->left != Nil && pNode->right != Nil) {
		pTemp = pNode->left;
		while(pTemp->right != Nil) {
			pTemp = pTemp->right;
		}
		//swap
		pNode = pTemp->left;
		pNode->parent = pTemp->parent;
		if(pTemp->parent->left == pTemp){
			pTemp->parent->left = pNode;
		}
		else {
			pTemp->parent->right = pNode;
		}
	}
	else if(pNode->left == Nil && pNode->right == Nil) {
		if(pPreNode == Nil) {
			delete root;
			root = Nil;
			size--;
			return true;
		}
		else {
			if(pNode = pPreNode->left) {
				pPreNode->left = Nil;
			}
			else {
				pPreNode->right = Nil;
			}
			ChildNode = Nil;
			ChildNode->parent = pPreNode;
			pTemp = pNode;
		}	
	}
	else {
		if(pNode->left != Nil) {
			ChildNode = pNode->left;
			ChildNode->parent = pPreNode;
		}
		else {
			ChildNode = pNode->right;
			ChildNode->parent = pPreNode;
		}
		if(pNode == pPreNode->left) {
			pPreNode->left = ChildNode;
		}
		else {
			pPreNode->right = ChildNode;
		}
		pTemp = pNode;
	}
	if(pTemp->color == BLACK) {
		Delete_fixup(ChildNode);
	}
	delete pTemp;
	size--;
	return true;
	
}

void rbTree::Delete_fixup(Node *pNode) {

}

/*void Transplant(Node *pNode1, Node *pNode2) {
	if(pNode1->parent == Nil) {
		root = pNode2;
	}
	else if(pNode1 == pNode1->parent->left) {
		pNode1->parent->left = pNode2;
	}
	else {
		pNode1->parent->right = pNode2;
	}
	pNode2->parent = pNode1->parent;
}*/

Node *Search(int k) {

	Node *pNode;
	if(root == Nil) {
		return NULL;
	}

	pNode = root;
	while(pNode != Nil) {
		if(k < pNode->key) {
			pNode = pNode->left;
		}
		else if(k > pNode->key) {
			pNode = pNode->right;
		}
		else {
			return pNode;
		}
	}

	return NULL;
}

void rbTree::Empty(Node *pNode) {
	if(pNode != Nil) {
		Empty(pNode->right);
		Empty(pNode->left);
		delete pNode;
	}
}


