#include "tree.h"

Tree::Tree() {
	// Set each branch to nullptr
	lhs = nullptr;
	rhs = nullptr;
}

Tree::Tree(char v) {
	// Set each branch to nullptr
	lhs = nullptr;
	rhs = nullptr;
	// Set root value
	value = v;
}

Tree::Tree(char v, shared_ptr<Tree> l, shared_ptr<Tree> r) {
	// set root value and each branch
	value = v;
	lhs = l;
	rhs = r;
}

Tree::~Tree() {
	// Set branches to null (shared ptr automatically deletes itself if needed)
	lhs = nullptr;
	rhs = nullptr;
}

shared_ptr<Tree> Tree::clone(const shared_ptr<Tree> t) {
	// If at end of branch, return null
	if(t == nullptr) {
		return nullptr;
	} else {
		// Recursively make a new node
		return shared_ptr<Tree> (new Tree(t -> value, clone(t -> lhs), clone(t -> rhs)));
	}
}

Tree::Tree(const Tree& other) {
	this -> lhs = clone(other.lhs);
	this -> rhs = clone(other.rhs);
	this -> value = other.value;
}

const Tree& Tree::operator=(const Tree& other) {
	if(this != &other) {
		// Shared ptr handles deletion
		this -> lhs = clone(other.lhs);
		this -> rhs = clone(other.rhs);
		this -> value = other.value;
	}
}

Tree::Tree(Tree&& other) {
	lhs = other.lhs;
	rhs = other.rhs;
	value = other.value;

	lhs = nullptr;
	rhs = nullptr;
}

Tree& Tree::operator=(Tree&& other) {
	if(this != &other) {
		// Release current tree's resources
		if(lhs != nullptr) {
			///delete lhs;
		}
		if(rhs != nullptr) {
			///delete rhs;
		}
		lhs = other.lhs;
		rhs = other.rhs;
		value = other.value;

		other.lhs = nullptr;
		other.rhs = nullptr;
	}
}

ostream &operator<<(ostream &os, Tree t) {
	// If left branch, recursively go down that
	if(t.lhs != nullptr) {
		os << *t.lhs;
	}
	// If right branch, recursively go down that
	if(t.rhs != nullptr) {
		os << *t.rhs;
	}

	// If leaf node, print the value
	if(t.lhs == nullptr && t.rhs == nullptr) {
		os << t.value;
	}

	return os;
}

void Tree::add_left(shared_ptr<Tree> l) {
	if(lhs != nullptr) {
		throw "LEFT HAND SIDE ALREADY EXISTS!"; 
	}
	lhs = l;

	return;
}

void Tree::add_right(shared_ptr<Tree> r) {
	if(rhs != nullptr) {
		throw "RIGHT HAND SIDE ALREADY EXISTS!"; 
	}
	rhs = r;

	return;
}