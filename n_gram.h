#ifndef N_GRAM_H
#define N_GRAM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <boost/filesystem.hpp>
#include "tree.h"

namespace fs = boost::filesystem;
using namespace std;

struct pair_hash;

class N_gram {
	public:
		N_gram();
		N_gram(string s); // Directory name
		N_gram(vector<string> s);

		pair<shared_ptr<Tree>, shared_ptr<Tree> > most_frequent() const;

		void print_each_char() const;
		void print_each_addr() const;

	private:
		vector<vector<shared_ptr<Tree> > > forest;
};

// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

#endif