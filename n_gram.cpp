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
			// Create string buffer
			stringstream buffer;

			// If file is open
			if(ifs) {
				// Create vector of soon to be full trees
				vector<shared_ptr<Tree> > baby_trees;

				// Read in entire file as a buffer
				buffer << ifs.rdbuf();
				
				// For each character in the buffer
				for(const auto& c : buffer.str()) {
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
	for(const auto& s : all_strings) {
		// Create vector of soon to be full trees
		vector<shared_ptr<Tree> > baby_trees;

		// For each character
		for(const auto& c : s) {
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
	// Current pair we are looking at
	pair<shared_ptr<Tree>, shared_ptr<Tree> > current_pair;
	// Most frequently occuring pair
	pair<shared_ptr<Tree>, shared_ptr<Tree> > highest_occurence;
	int times_occured = -100;
	int count;

	// For each tree in the forest
	for(const auto& t : this -> forest) {
		// For each pair of consecutive baby trees
		for(int i = 0; i < t.size() - 1; i++) {
			// Increment pair count
			two_gram[pair<shared_ptr<Tree>, shared_ptr<Tree> >(t[i], t[i+1])]++;
		}
	}

	for(const auto& set : two_gram) {
		count = set.second;

		// If new most frequently occuring node, update most frequntly occuring node variable
		if(count > times_occured) {
			times_occured = count;
			highest_occurence = set.first;
		}
	}

	return highest_occurence;
}

void N_gram::combine_trees(pair<shared_ptr<Tree>, shared_ptr<Tree> > set) {
	// Make new tree node out of set pair
	shared_ptr<Tree> new_node(new Tree(set.first, set.second));

	for(auto& t : this -> forest) {
		for(int i = 0; i < t.size() - 1; i++) {
			if(t[i] == set.first && t[i+1] == set.second) {
				t[i] = new_node;
				t.erase(t.begin() + i + 1);
			}
		}
	}

	return;
}

void N_gram::make_forest() {
	while(!all_trees_made()) {
		auto set = most_frequent();
		/*
		if(set.first -> lhs == nullptr && set.first -> lhs == nullptr) {
			cout << set.first -> value;
		} else {
			cout << set.first;
		}
		cout << " ";
		if(set.second -> lhs == nullptr && set.second -> lhs == nullptr) {
			cout << set.second -> value;
		} else {
			cout << set.second;
		}
		cout << endl;
		*/
		combine_trees(set);
	}

	return;
}

bool N_gram::all_trees_made() const {
	for(const auto& t : this -> forest) {
		if(t.size() != 1) {
			return false;
		}
	}

	return true;
}

void N_gram::print_each_char() const {
	// For each tree in a forest
	for(const auto& t : forest) {
		// Print each baby tree. When finished, there should only be one baby tree, which is a full tree
		for(const auto& baby_t : t) {
			cout << *baby_t << " ";
		}
		cout << endl << "--------------" << endl;
	}

	return;
}

void N_gram::print_each_addr() const {
	// For each tree in a forest
	for(const auto& t : forest) {
		// Print each baby tree. When finished, there should only be one baby tree, which is a full tree
		for(const auto& baby_t : t) {
			cout << baby_t << " ";
		}
		cout << endl;
	}

	return;
}

void N_gram::print_grammar_rules() const {
	// Start symbol
	cout << "START -> ";
	for(const auto& t : forest) {
		for(const auto& baby_t : t) {
			cout << baby_t << " | ";
		}
	}
	cout << endl;

	for(const auto& t : forest) {
		for(const auto& baby_t : t) {
			baby_t -> recurive_rule_print();
		}
	}

	return;

	// Sub-symbolts
}