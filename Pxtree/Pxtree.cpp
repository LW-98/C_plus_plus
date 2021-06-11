#include "Pxtree.h"
#include <iostream>

using namespace std;

// Constructor
Pxtree::Pxtree() {
  c_ = '\0';
  count_ = 0;
  leftmostChild_ = nullptr;
  nextSibling_ = nullptr;
}

// Destructor
Pxtree::~Pxtree() {
  //deleteRecursively();
}

// Own copy method so I can use recursion
void Pxtree::copyValues(const Pxtree& other) {
  // Copy the int and char values
  c_ = other.c_;
  count_ = other.count_;

  // Check if there is a child/sibling to recursively copy the Pxtree pointers
  if (other.leftmostChild_ != nullptr) {
    leftmostChild_ = new Pxtree();
    leftmostChild_->copyValues(*other.leftmostChild_);
  }
  if (other.nextSibling_ != nullptr) {
    nextSibling_ = new Pxtree();
    nextSibling_->copyValues(*other.nextSibling_);
  }
}

// Copy constructor
Pxtree::Pxtree(const Pxtree& other)  {
  copyValues(other);
}

// Copy assignment
Pxtree& Pxtree::operator=(const Pxtree& other) {
  if (&other == this)
    return *this;
  copyValues(other);
  return *this;
}

int Pxtree::count(string s) const {

	if (c_ == '\0') { // special case: the root
		if (leftmostChild_ == nullptr) return 0;
		else return leftmostChild_->count(s); // just pass it down
	}
	else if (c_ == s[0]) { // the char at this node matches the first char of the string

		// the string s ends here
		if (s.length() == 1) return count_;

		// more char from s need to be matched, but no children
		else if (leftmostChild_ == nullptr) return 0;

		// recursively pass the remaining part of s to the child to handle
		else return leftmostChild_->count(s.erase(0,1));
	}
	else { // the char at this node doesn't match

		// just pass it to the next sibling, if none then there is no match
		if (nextSibling_ == nullptr) return 0;
		else return nextSibling_->count(s);
	}
}

void Pxtree::add(string s) {
  // Temporary tree
  Pxtree* t = new Pxtree();
  if (s.length() == 1)
    ++(t->count_);

  // Special case root
  if (c_ == '\0') {
    t->c_ = s[0];
    if (leftmostChild_ == nullptr) {
      leftmostChild_ = t;
      if (s.length() != 1)
	leftmostChild_->add(s);
    } else {
      leftmostChild_->add(s);
      }
  } else if (c_ == s[0]) {
    t->c_ = s[1];
    if (s.length() == 1) {
      ++count_;
    } else if (leftmostChild_ == nullptr) {
      leftmostChild_ = t;
      leftmostChild_->add(s.erase(0, 1));
    } else {
      leftmostChild_->add(s.erase(0, 1));
    }
  } else {
    t->c_ = s[0];
    if (nextSibling_ == nullptr) {
      nextSibling_ = t;
      if (s.length() != 1)
	nextSibling_->add(s);
    } else {
      nextSibling_->add(s);
    }
  }
  t = nullptr;
}

void Pxtree::remove(string s) {
  // Check to make sure string is non-empty
  if (count(s) == 0)
    return;

  // Special case root
  if (c_ == '\0') {
    leftmostChild_->remove(s);
  } else {
    // If value is the same as the first character in string, go down that subtree. Otherwise go to sibling
    if (c_ == s[0]) {
      // If string is length 1 that means we have found the last character and we can return
      if (s.length() == 1) {
	--count_;
	return;
      }
      if (leftmostChild_ == nullptr) {
	--count_;
      } else
	leftmostChild_->remove(s.erase(0,1));
    } else {
      nextSibling_->remove(s);
    }
  }
}

// spacesNum is the depth of the tree, i.e. first level, spacesNum == 0
string Pxtree::printTree(int spacesNum) const {
  string spaces = "";
  string value{c_};

  // Add the required amount of spaces depending on the level of the tree we are at (spacesNum)
  for (int i = 0; i < spacesNum; i++) {
    spaces += "  ";
  }
  // Special case root
  if (c_ == '\0')
    if (leftmostChild_ == nullptr)
      return "";
    else
      return leftmostChild_->printTree(0);
  if (leftmostChild_ == nullptr)
    if (nextSibling_ == nullptr)
      return (spaces + value + " " + to_string(count_));
    else
      return (spaces + value + " " + to_string(count_) + "\n" + nextSibling_->printTree(spacesNum));
  else {
    if (nextSibling_ != nullptr)
      return (spaces + value + " " + to_string(count_) + "\n" + leftmostChild_->printTree(spacesNum + 1)) + ("\n" + nextSibling_->printTree(spacesNum));
    else
      return (spaces + value + " " + to_string(count_) + "\n" + leftmostChild_->printTree(spacesNum + 1));
  }
}

string Pxtree::print() const {
  // A value is needed to track the level of the tree
  return printTree(0);
}

string Pxtree::autoComplete(string s) const {
  if (count(s) == 0)
    return s;

  if (c_ == '\0') {
    return leftmostChild_->autoComplete(s);
  } else if (c_ == s[0]) {
    int max = findMaxCount();
    return findCount("", max);
  } else {
    return nextSibling_->autoComplete(s);
  }
}

// This method looks through a tree, finds the given count (maxCount) and returns the string that the count represents
// A string (answer) is passed through so it can remember what the answer looks like
string Pxtree::findCount(string answer, int maxCount) const {
  string x = "", y = "";
  string value{c_};

  // If we have found the max count, return the remembered string + the current character
  if (count_ == maxCount) {
    return answer + value;
  }
  else {

    // Recurse over sibling and/or child
    if (leftmostChild_ != nullptr) {
      x = leftmostChild_->findCount(answer + value, maxCount);
    }
    if (nextSibling_ != nullptr) {
      y = nextSibling_->findCount(answer, maxCount);
    }
    if (nextSibling_ == nullptr && leftmostChild_ == nullptr)
      return "";
  }

  // Many strings will come back (through sibling and/or child) so find the biggest and return it
  if (count(x) > count(y))
    return x;
  else
    return y;
}

void Pxtree::compact() {
  // In some cases, there is more than one empty leaf. So if one exists, call recursiveCompact() once. If another exists, it will call it again etc.
  while (hasEmptyLeaves()) {
    recursiveCompact();
  }
}

// This method goes through the tree to find, and remove, exactly one empty leaf.
void Pxtree::recursiveCompact() {
  if (this == nullptr)
    return;

  // Two initial scenarios, root node and not root node
  if (c_ == '\0') {
    if (leftmostChild_ != nullptr) {
      if (leftmostChild_->isEmptyLeaf() == 1) {
	delete leftmostChild_;
	leftmostChild_ = nullptr;
      } else if (leftmostChild_->isEmptyLeaf() == 2) {
	delete leftmostChild_;
	leftmostChild_ = leftmostChild_->nextSibling_;
      } else {
	leftmostChild_->recursiveCompact();
      }
    }
  } else {

    // Two more scenarios, check to see if node has a left child and/or next sibling. If they do, check if it is an empty leaf.

    if (leftmostChild_ != nullptr) {
      // If 1, it is completely empty
      if (leftmostChild_->isEmptyLeaf() == 1) {
	delete leftmostChild_;
	leftmostChild_ = nullptr;
      }
      // If 2 it is empty but has a sibling, so instead of assigning a nullptr, assign its sibling.
      else if (leftmostChild_->isEmptyLeaf() == 2) {
	delete leftmostChild_;
	leftmostChild_ = leftmostChild_->nextSibling_;
      }
      // If 0 (else), it is not empty so recurse.
      else {
	leftmostChild_->recursiveCompact();
      }
    }

    // Same as above, but nextSibling_ instead of leftmostChild_
    if (nextSibling_ != nullptr) {
      if (nextSibling_->isEmptyLeaf() == 1) {
	delete nextSibling_;
        nextSibling_ = nullptr;
      } else if (nextSibling_->isEmptyLeaf() == 2) {
	delete nextSibling_;
        nextSibling_ = nextSibling_->nextSibling_;
      }
      else {
        nextSibling_->recursiveCompact();
      }
    }
  }
}

// Returns a number depending on being an empty leaf
// 0 if leaf is not empty
// 1 if leaf is empty
// 2 if leaf is empty but has next sibling
// 1 & 2 let me know if I need to set the parents leftmostChild_ pointer to nullptr (1) or to sibling (2).
int Pxtree::isEmptyLeaf() {
  if (count_ == 0 && leftmostChild_ == nullptr) {
    if (nextSibling_ == nullptr)
      return 1;
    else
      return 2;
  } else
    return 0;
}

// This method finds the maximum count_ value from the node it was called
int Pxtree::findMaxCount() const {
  if (leftmostChild_ == nullptr) {
    if (nextSibling_ == nullptr)
      return count_;
    else
      return max(nextSibling_->findMaxCount(), count_);
  } else {
    if (nextSibling_ != nullptr) {
      int x = leftmostChild_->findMaxCount();
      int y = nextSibling_->findMaxCount();
      return max(max(x, y), count_);
    } else {
      return max(leftmostChild_->findMaxCount(), count_);
    }
  }
}

// This finds out if the tree still has empty nodes left
bool Pxtree::hasEmptyLeaves() const {
  if (c_ == '\0') {
    if (leftmostChild_ == nullptr)
      return false;
    else
      return leftmostChild_->hasEmptyLeaves();
    // Empty node, return true
  } else if (count_ == 0 && leftmostChild_ == nullptr) {
    return true;
  } else {
    // If not empty and not root node, recursively check child and sibling otherwise return false.
    if (nextSibling_ != nullptr)
      return nextSibling_->hasEmptyLeaves();
    else if (leftmostChild_ != nullptr)
      return leftmostChild_->hasEmptyLeaves();
    else
      return false;
  }
}

void Pxtree::deleteRecursively() {
  if (leftmostChild_ != nullptr) {
    leftmostChild_->deleteRecursively();
    delete leftmostChild_;
    leftmostChild_ = nullptr;
  }
  if (nextSibling_ != nullptr) {
    nextSibling_->deleteRecursively();
    delete nextSibling_;
    nextSibling_ = nullptr;
  }
}