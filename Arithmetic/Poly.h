#include <iostream>
#include <vector>
#include <deque>
using std::ostream;
using std::vector;
using std::deque;

// Templated class for a polynomial, with coefficients of type T
// The type T is assumed to have a zero element 0
// Furthermore T is assumed to have implemented:
//   the + operator;
//   the == operator;
//   the << operator.
template<typename T>
class Polynomial {
public:
  
	// Default constructor. Constructs the polynomial "0"
	Polynomial() {
	  degreeNum = 0;
	  poly.push_front(0);
	}

	// Value constructor. Constructs a polynomial based on the vector
	// of coefficients, in descending order of exponents.
	// For example, if coef contains {0,6,8,9,4}, then it constructs
	// the polynomial 6x^3 + 8x^2 + 9x + 4
	Polynomial(vector<T> other) {
	  degreeNum = other.size() - 1;
	  // 'check' makes sure the first number is > 0
	  bool check = true;
	  for (int i = 0; i < other.size(); i++) {
	    // if 'check' is true, that means we are yet to get a number greater than 0
	    // if 'check' wasn't here, that would mean every 0 would get omitted, instead of just the first ones.
	    if (other[i] == 0 && check) {
	      degreeNum--;
	      continue;
	    }
	    // Once we get a number > 0, that means 0's are now allowed
	    check = false;
	    poly.push_front(other[i]);
	  }
	}

	// Return the degree of the polynomial.
	int degree() const {
	  return degreeNum;
	}

	// Return the coefficient of the x^i term. If i is negative or
	// larger than the degree, 0 is returned.
	T getCoef(int i) const {
	  if (i < 0 || i > degreeNum)
	    return 0;
	  else
	    return poly[i];
	 }

	// Addition of two polynomials
	Polynomial operator+(const Polynomial& other) const {
	  Polynomial<T> temp;
	  int max;
	  if (poly.size() > other.poly.size())
	    max = poly.size();
	  else
	    max = other.poly.size();
	  for (int i = max - 1; i >= 0; i--) {
	    temp.poly.push_front(poly[i] + other.poly[i]);
	    
	  }
	  
	  Polynomial<T> newPoly(temp);
	  for (int i = 0; i < newPoly.poly.size(); i++) {
	    std::cout << newPoly.poly[i] << ":" << getCoef(i);
	  }
	  std::cout << "\n" << newPoly.degreeNum << std::endl;;
	  return newPoly;
	}

  deque<T> getPoly() {
    return poly;
  }

	// Print the polynomial, in descending order of coefficients and
	// with the usual "x^..." terms.
	friend ostream& operator<<(ostream& os, const Polynomial<T>& p) {
	  for (int i = p.poly.size() - 1; i >= 0; i--) {
	    if (!(p.poly[i] == 0)) {
	      if (!(p.poly[i] == 1))
		os << p.poly[i];
	      if (i != 0)
		if (i == 1)
		  os << "x" << " + ";
		else
		  os << "x^" << i << " + ";
	    }
	  }
	  return os;
	}

private:
  int degreeNum;
  deque<T> poly;
};
