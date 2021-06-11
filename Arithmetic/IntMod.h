#ifndef __INTMOD_H_
#define __INTMOD_H_

#include <iostream>
using std::ostream;
using std::cout;

template<int n>
class IntMod {

public:

	// Default constructor
	IntMod() {
	  value = 0;
	}

	// Value constructor. Accepts any (positive or negative) integer
	// not necessarily within [0..n-1]
	IntMod(int v) {
	  value = v;
	}

	// Returns the value of this IntMod as an integer, in
	// the range 0..n-1
	int toInt() const {
	  return (n + (value % n)) % n;
	}

	// Overloaded + operator for adding two IntMods
	friend IntMod operator+(const IntMod& lhs, const IntMod& rhs) {
	  int tempNum = lhs.toInt() + rhs.toInt();
	  IntMod<n> temp(tempNum);
	  return temp;
	}

	// Overloaded * operator for multiplying two IntMods
	friend IntMod operator*(const IntMod& lhs, const IntMod& rhs) {
	  int tempNum = lhs.toInt() * rhs.toInt();
	  IntMod<n> temp(tempNum);
	  return temp;

	}

	// Overloaded == operator for comparing two IntMods
	friend bool operator==(const IntMod& lhs, const IntMod& rhs) {
	  if (lhs.toInt() == rhs.toInt())
	    return true;
	  else
	    return false;
	}

	// Return the multiplicative inverse of the current number mod n
	// An inverse of a number x, modulo n, is a number y such that
	// x*y mod n == 1.
	// If the inverse does not exist, throw a std::domain_error exception.
	IntMod inverse() {
	  for (int i = 1; i < n; i++) {
	    if ((n + ((value*i) % n)) % n == 1) {
	      IntMod<n> temp(i);
	      return temp;
	    }
	  }
	  throw std::domain_error("Inverse does not exist");
	}

	// Overloaded << operator, printing the IntMod like an integer
	friend ostream& operator<<(ostream& os, const IntMod& p) {
	  os << p.toInt();
	  return os;
	}

private:
  int value;
};

#endif /* __INTMOD_H_ */
