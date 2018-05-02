#include <iostream>
#include <algorithm>
#include "tree.h"
#include "n_gram.h"
using namespace std;

// g++ *.cpp -std=c++11 -lboost_system -lboost_filesystem

int main() {
	N_gram a("training/");

	a.print_each_char();

	/*
	shared_ptr<Tree> b(new Tree('b'));// = new Tree('b');
	shared_ptr<Tree> c(new Tree('c'));// = new Tree('c');
	shared_ptr<Tree> d(new Tree('c'));// = new Tree();

	//d -> lhs = b;
	d -> add_left(b);
	d -> add_right(b);

	cout << *b << endl;
	cout << *c << endl;

	cout << *d << endl;
	*/

	//delete d;
	//*c = *b;
	//c -> lhs = b;
	//delete b;
	//cout << *c << endl;
	//delete c;

	return 0;
}