#include "stdafx.h"
#include "RBtree.h"

void
RBtree::clear(Node* tree)
{
	//if (tree->llink_ == 0) return;

	//clear(tree->llink_);
	//clear(tree->rlink_);
	//delete tree;
	cout << "DESTRUCTOR CALLED";
}


void
RBtree::print(const Node* tree, int indent)const
{
	if (tree->llink_ == 0) return;

	print(tree->rlink_, indent + 5);

	for (int i = 0; i<indent; i++) cout << ' ';
	cout << tree->key_;
	if (tree->color_ == BLACK)
		cout << 'B' << endl;
	else
		cout << 'R' << endl;
	print(tree->llink_, indent + 5);
}

////////////////////////////////////////////////////////////////////////
//          *****BALANCING METHODS: Implementation*****               //
////////////////////////////////////////////////////////////////////////
void
RBtree::leftRotate(Node* p)
{
	Node* p1 = p->rlink_;
	p->rlink_ = p1->llink_;
	if (p1->llink_ != &NIL_)
		p1->llink_->parent_ = p;
	if (p->parent_ == &NIL_)
	{
		tree_ = p1;
	}
	else
		(p == p->parent_->llink_) ? p->parent_->llink_ = p1 : p->parent_->rlink_ = p1;
	p1->llink_ = p;
	p1->parent_ = p->parent_;
	p->parent_ = p1;
	p = p1;
	//cout << "\n ROOT PARENT IS: " << tree_->parent_;
}

void
RBtree::rightRotate(Node* p)
{
	Node* p1 = p->llink_;
	p->llink_ = p1->rlink_;
	p1->rlink_->parent_ = p;
	if (p->parent_ == &NIL_)
		tree_ = p1;
	else
		(p == p->parent_->llink_) ? p->parent_->llink_ = p1 : p->parent_->rlink_ = p1;
	p1->rlink_ = p;
	p1->parent_ = p->parent_;
	p->parent_ = p1;
	p = p1;
}

void
RBtree::balancingAfterInsertion(Node* z)
{
	int i = 1;
	while (z->parent_ != &NIL_ && z->parent_->color_ == RED)
	{
		//cout << "IN WHILE:" << i++ << " IS PARENT NULL"<< (z->parent_ == 0);
		if (z->parent_ == z->parent_->parent_->llink_)
		{
			Node* y = z->parent_->parent_->rlink_;
			if (y->color_ == RED)
			{
				z->parent_->color_ = BLACK;
				y->color_ = BLACK;
				z->parent_->parent_->color_ = RED;
				z = z->parent_->parent_;
			}
			else
			{
				if (z == z->parent_->rlink_)
				{
					z = z->parent_;
					leftRotate(z);
				}
				z->parent_->color_ = BLACK;
				z->parent_->parent_->color_ = RED;
				rightRotate(z->parent_->parent_);
			}
		}
		else
		{
			Node* y = z->parent_->parent_->llink_;
			if (y->color_ == RED)
			{
				z->parent_->color_ = BLACK;
				y->color_ = BLACK;
				z->parent_->parent_->color_ = RED;
				z = z->parent_->parent_;
				//cout<<"\n PARENT KEY IS "<<z->parent_->key_;
			}
			else
			{
				if (z == z->parent_->llink_)
				{
					z = z->parent_;
					rightRotate(z);
				}
				z->parent_->color_ = BLACK;
				z->parent_->parent_->color_ = RED;
				leftRotate(z->parent_->parent_);
			}
		}
	}
	tree_->color_ = BLACK;
}

void
RBtree::balancingAfterRemoval(Node* x)
{
	while (x != tree_ && x->color_ == BLACK)
	{
		if (x == x->parent_->llink_)
		{
			Node* w = x->parent_->rlink_;
			if (w->color_ == RED)
			{
				w->color_ = BLACK;
				x->parent_->color_ = RED;
				leftRotate(x->parent_);
				w = x->parent_->rlink_;
			}
			if (w->llink_->color_ == BLACK && w->rlink_->color_ == BLACK)
			{
				w->color_ = RED;
				x = x->parent_;
			}
			else
			{
				if (w->rlink_->color_ == BLACK)
				{
					w->llink_->color_ = BLACK;
					w->color_ = RED;
					rightRotate(w);
					w = x->parent_->rlink_;
				}
				w->color_ = x->parent_->color_;
				x->parent_->color_ = BLACK;
				w->rlink_->color_ = BLACK;
				leftRotate(x->parent_);
				x = tree_;
			}
		}
		else
		{
			Node* w = x->parent_->llink_;
			if (w->color_ == RED)
			{
				w->color_ = BLACK;
				x->parent_->color_ = RED;
				rightRotate(x->parent_);
				w = x->parent_->llink_;
			}
			if (w->llink_->color_ == BLACK && w->rlink_->color_ == BLACK)
			{
				w->color_ = RED;
				x = x->parent_;
			}
			else
			{
				if (w->llink_->color_ = BLACK)
				{
					w->rlink_->color_ = BLACK;
					w->color_ = RED;
					leftRotate(w);
					w = x->parent_->llink_;
				}
				w->color_ = x->parent_->color_;
				x->parent_->color_ = BLACK;
				w->llink_->color_ = BLACK;
				rightRotate(x->parent_);
				x = tree_;
			}
		}
	}
	x->color_ = BLACK;
}

//PUBLIC METHODS
Node*
RBtree::search(int elem)const
{
	Node * current = tree_;
	while (current != &NIL_)
	{
		if (current->key_ == elem)
			return current;
		if (elem >= current->key_)
			current = current->rlink_;
		else
			current = current->llink_;
	}
	return 0;
}

void
RBtree::insert(Node* node)
{
	Node* current = tree_, *prev = &NIL_;
	int key = node->key_;
	while (current != &NIL_)
	{
		if (current->key_ == key) return; //isertion is not done
		prev = current;
		(key<current->key_) ? current = current->llink_ : current = current->rlink_;
	}

	node->color_ = RED, node->parent_ = prev, node->llink_ = node->rlink_ = &NIL_;

	if (tree_ == &NIL_)
	{
		tree_ = node;
		node->color_ = BLACK;
		return;
	}

	(key<prev->key_) ? prev->llink_ = node : prev->rlink_ = node;

	balancingAfterInsertion(node);
}

void
RBtree::remove(Node* node)
{
	Color color = node->color_;
	Node* next;
	if (node->llink_ != &NIL_&& node->rlink_ != &NIL_) {
		for (next = node->rlink_; next->llink_ != &NIL_; next = next->llink_)
			;

		node->key_ = next->key_;//rewriting info
		color = next->color_;
		node = next;
	}

	if (node->llink_ == &NIL_) {
		next = node->rlink_;
		if (node->parent_ != &NIL_)
			if (node == node->parent_->llink_)
				node->parent_->llink_ = next;
			else
				node->parent_->rlink_ = next;
		else
		{
			tree_ = next; tree_->parent_ = &NIL_;
		}

		next->parent_ = node->parent_;
		delete node;
		if (color == BLACK)
			balancingAfterRemoval(next);
		return;
	}

	//node->rlink_==&NIL_	
	next = node->llink_;
	if (node->parent_ != &NIL_)
		if (node == node->parent_->llink_)
			node->parent_->llink_ = next;
		else
			node->parent_->rlink_ = next;
	else
	{
		tree_ = next; tree_->parent_ = &NIL_;
	}

	next->parent_ = node->parent_;
	delete node;
	if (color == BLACK)
		balancingAfterRemoval(next);
}
