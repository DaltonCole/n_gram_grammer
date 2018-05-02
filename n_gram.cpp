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
					for(auto c : line) {
						baby_trees.push_back(shared_ptr<Tree>(new Tree(c)));
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

	// For each string
	for(auto s : all_strings) {
		// Create vector of soon to be full trees
		vector<shared_ptr<Tree> > baby_trees;

		// For each character
		for(auto c : s) {
			// Add a root node
			baby_trees.push_back(shared_ptr<Tree>(new Tree(c)));
		}

		// Add soon to be trees to the forest
		this -> forest.push_back(baby_trees);
	}
}

void N_gram::print_each_char() const {
	for(auto t : forest) {
		for(auto baby_t : t) {
			cout << baby_t;
		}
		cout << endl;
	}

	return;
}