#ifndef PXTREE_H_
#define PXTREE_H_

#include <string>
using std::string;

class Pxtree
{
public:
	// Constructor. Constructs an empty Pxtree. Root node contains the special character '\0'
	Pxtree();

	// Destructor
	~Pxtree();

	// Copy constructor
	Pxtree(const Pxtree &other);

	// Copy assignment
	Pxtree &operator=(const Pxtree &other);

	// Return the count associated with the string s. If the string is
	// not in the tree, return 0.
	int count(string s) const;

	// Add the string s to the tree if it is not already represented in the tree.
	void add(string s);

	// Remove string s from tree
	void remove(string s);

	// Print out the tree
	string print() const;

	// Return the string with the highest count that ends in the subtree
	// rooted at s, including s itself.
	string autoComplete(string s) const;

	// This "compacts" the tree by removing any leaves with a count of 0.
	void compact();

	int findMaxCount() const;
	int isEmptyLeaf();
	string printTree(int spacesNum) const;
	string findCount(string answer, int count) const;
	bool hasEmptyLeaves() const;
	void copyValues(const Pxtree &other);
	void recursiveCompact();
	void deleteRecursively();

private:
	char c_;				// Character associated with this node
	int count_;				// Count associated with this node
	Pxtree *leftmostChild_; // Pointer to leftmost child
	Pxtree *nextSibling_;	// Pointer to sibling immediately to the right
};

#endif
