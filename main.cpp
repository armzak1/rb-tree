// RB-trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RBtree.h"

int main()
{
	RBtree s;

	Node* n1 = new Node(1);
	Node* n2 = new Node(2);
	Node* n3 = new Node(3);
	Node* n4 = new Node(4);
	Node* n5 = new Node(5);
	Node* n6 = new Node(6);
	Node* n7 = new Node(7);
	Node* n8 = new Node(8);
	Node* n9 = new Node(9);
	Node* n10 = new Node(10);

	cout << endl << "*****   INSERTIONS: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10   *****" << endl << endl;
	s.insert(n1);	s.print();
	s.insert(n2);	s.print();
	s.insert(n3);	s.print();
	s.insert(n4);	s.print();
	s.insert(n5);	s.print();
	s.insert(n6);	s.print();
	s.insert(n7);	s.print();
	s.insert(n8);	s.print();
	s.insert(n9);	s.print();
	s.insert(n10);	s.print();

	cout << endl << endl << "*****   DELETIONS: 1, 3, 5, 7, 9  *****" << endl << endl;
	s.remove(n1); s.print();
	s.remove(n3); s.print();
	s.remove(n5); s.print();
	s.remove(n7); s.print();
	s.remove(n9); s.print();
	
	return 0;
}


