#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <memory>

using namespace std;

class Tree;

ostream &operator<<(ostream &os, Tree t);

class Tree {
	public:
		Tree();
		Tree(char v);
		Tree(char v, shared_ptr<Tree> l, shared_ptr<Tree> r);
		Tree(const Tree& other);
		~Tree();
		shared_ptr<Tree> clone(const shared_ptr<Tree> t);
		const Tree& operator=(const Tree& rhs);
		Tree(Tree&& other);
		Tree& operator=(Tree&& other);

		friend ostream &operator<<(ostream &os, Tree t);

		void add_left(shared_ptr<Tree> l);
		void add_right(shared_ptr<Tree> r);

	//private:
		shared_ptr<Tree> lhs;
		shared_ptr<Tree> rhs;
		char value;
};

#endif