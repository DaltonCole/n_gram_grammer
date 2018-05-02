#include "n_gram.h"

N_gram::N_gram() {}


// NOTE IGNORES NEW LINE CHARACTERS
N_gram::N_gram(string dir_path) {
	// Path
	fs::path p(dir_path);

	// Make sure input was a path
	if(!exists(p) || !is_directory(p)) {
		cerr << p << " is not a path" << endl;
	} else {
		// Create iterator to go through each file
		fs::recursive_directory_iterator begin(p), end;
		vector<fs::directory_entry> v(begin, end);

		// Maps character to corresponding root node
		unordered_map<char, shared_ptr<Tree>> same_value;

		// Go through each file
		for(auto& f: v) {
			string line;
			// Open File
			ifstream ifs(f.path().string().c_str());

			// If file is open
			if(ifs) {
				// Create vector of soon to be full trees
				vector<shared_ptr<Tree> > baby_trees;
				// Get each line in the file
				while(getline(ifs, line)) {
					// For each character
					for(auto c : line) {
						// Add a root node
						if(same_value[c] == nullptr) {
							baby_trees.push_back(shared_ptr<Tree>(new Tree(c)));
							same_value[c] = baby_trees[baby_trees.size() - 1];
						} else {
							baby_trees.push_back(same_value[c]);
						}
					}
				}

				// Add soon to be trees to the forest
				this -> forest.push_back(baby_trees);
			} else {
				cerr << "Couldn't open " << f.path().string() << " for reading\n";
			}
		}
	}
	
}

N_gram::N_gram(vector<string> all_strings) {
	// Maps character to corresponding root node
	unordered_map<char, shared_ptr<Tree>> same_value;

	// For each string
	for(auto s : all_strings) {
		// Create vector of soon to be full trees
		vector<shared_ptr<Tree> > baby_trees;

		// For each character
		for(auto c : s) {
			// Add a root node
			if(same_value[c] == nullptr) {
				baby_trees.push_back(shared_ptr<Tree>(new Tree(c)));
				same_value[c] = baby_trees[baby_trees.size() - 1];
			} else {
				baby_trees.push_back(same_value[c]);
			}
		}

		// Add soon to be trees to the forest
		this -> forest.push_back(baby_trees);
	}
}

pair<shared_ptr<Tree>, shared_ptr<Tree> > N_gram::most_frequent() const {
	// Create two_gram map of occurences
	unordered_map<pair<shared_ptr<Tree>, shared_ptr<Tree> >, int, pair_hash> two_gram;
	// Most frequently occuring pair
	pair<shared_ptr<Tree>, shared_ptr<Tree> > highest_occurence;
	int times_occured = -100;

	// For each tree in the forest
	for(auto t : this -> forest) {
		// For each pair of consecutive baby trees
		for(int i = 0; i < t.size() - 1; i++) {
			for(int j = i + 1; j < t.size(); j++) {
				// Increment pair count
				two_gram[pair<shared_ptr<Tree>, shared_ptr<Tree> >(t[i], t[j])]++;

				// If new most frequently occuring node, update most frequntly occuring node variable
				if(two_gram[pair<shared_ptr<Tree>, shared_ptr<Tree> >(t[i], t[j])] > times_occured) {
					times_occured = two_gram[pair<shared_ptr<Tree>, shared_ptr<Tree> >(t[i], t[j])];
					// NOTE CAN BE MADE MUCH FASTER BY USING POINTERS INSTEAD OF THE CONSTRUCTOR!
					highest_occurence = pair<shared_ptr<Tree>, shared_ptr<Tree> >(t[i], t[j]);
				}
			}
		}
	}

	return highest_occurence;
}


void N_gram::print_each_char() const {
	// For each tree in a forest
	for(auto t : forest) {
		// Print each baby tree. When finished, there should only be one baby tree, which is a full tree
		for(auto baby_t : t) {
			cout << *baby_t << " ";
		}
		cout << endl;
	}

	return;
}

void N_gram::print_each_addr() const {
	// For each tree in a forest
	for(auto t : forest) {
		// Print each baby tree. When finished, there should only be one baby tree, which is a full tree
		for(auto baby_t : t) {
			cout << baby_t << " ";
		}
		cout << endl;
	}

	return;
}