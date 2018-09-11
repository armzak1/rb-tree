#pragma once
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////
//				 *****class RBSearchTree*****                      //
/////////////////////////////////////////////////////////////////////
enum Color {
	RED,
	BLACK
};

struct Node {
	int		key_;
	Color	color_;
	Node*	parent_;
	Node*	llink_;
	Node*	rlink_;
	Node(int key = int(), Color color = BLACK, Node* parent = 0, Node* llink = 0, Node* rlink = 0) :
		key_(key), color_(color), parent_(parent), llink_(llink), rlink_(rlink) {}
};

class RBtree {
private:
	//***** AUXILIARY FUNCTIONS *****
	void   clear(Node* tree);
	void   print(const Node* tree, int indent = 0)const;

	//***** BALANCING METHODDS *****   
	void leftRotate(Node* p);
	void rightRotate(Node* p);
	void balancingAfterInsertion(Node* p);
	void balancingAfterRemoval(Node* p);

public:
	//***** PUBLIC METHODDS *****   
	/*1*/	RBtree() :tree_(&NIL_) {}
	/*2*/	~RBtree() { clear(tree_); }

	//Accessors
	/*3*/	bool	empty()const { return tree_ == &NIL_; }
	/*4*/	void	print()const { cout << endl << "- - - - - - - - - -" << endl << endl; print(tree_); }
	/*5*/	Node*	search(int elem)const;

	//Modifiers
	/*6*/	void	insert(Node* node);
	/*7*/	void	remove(Node* node);

private:
	Node	NIL_;
	Node*	tree_;
};

