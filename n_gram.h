#ifndef N_GRAM_H
#define N_GRAM_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include "tree.h"

namespace fs = boost::filesystem;
using namespace std;

class N_gram {
	public:
		N_gram();
		N_gram(string s); // Directory name
		N_gram(vector<string> s);

		void print_each_char() const;

	private:
		vector<vector<shared_ptr<Tree> > > forest;
};

#endif