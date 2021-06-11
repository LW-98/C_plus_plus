/////////////////////////
////// NOT MY CODE //////
/////////////////////////

#include <iostream>
#include <vector>
#include "IntMod.h"
#include "Poly.h"
using namespace std;

int main() {

	IntMod<8> n = -6;
	IntMod<8> m;
	m = 3; // implicit conversion thanks to value constructor
	cout << "n=" << n << endl;
	cout << "m=" << m << endl;
	cout << "n+m=" << n + m << endl;
	cout << "n*m=" << n * m << endl;
	n = 7 + n; // again, implicit conversion
	cout << "n+7=" << n << endl;
	m = m * m;
	cout << "m*m=" << m << endl;
	cout << std::boolalpha << (n==7) << endl;

	IntMod<10> z = 3;
	cout << z.inverse() << endl;
	z = 4;
	try {
		cout << z.inverse() << endl;
	}
	catch(const std::domain_error& e) {
		cerr << e.what() << endl;
	}

	Polynomial<int> zero;
	cout << "Default polynomial:" << zero << endl;
	cout << zero.degree() << endl;

	Polynomial<int> p({0,0,0,1});
	cout << p << endl;
	Polynomial<int> q({-1,-1,-1,-1});
	p = p + q;
	cout << p << endl;
	cout << p.getCoef(3) << " " << p.getCoef(0) << endl;

	Polynomial<float> pp({0.1,-1.2,3.14});
	Polynomial<float> qq({-0.1,1.2,3.14});
	cout << pp << endl;
	pp = pp + qq;
	cout << pp << endl;
	cout << pp.degree() << endl;
	cout << pp.getCoef(1) << endl;

	Polynomial< IntMod<8> > mm({5,4,7});
	Polynomial< IntMod<8> > nn({3,3,3});
	cout << mm << endl;
	Polynomial< IntMod<8> > oo = mm + nn;
	cout << oo << endl;
	cout << oo.degree() << endl;
	cout << oo.getCoef(2) << endl;
}

