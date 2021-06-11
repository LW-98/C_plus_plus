/////////////////////////
////// NOT MY CODE //////
/////////////////////////

#include <iostream>
#include <fstream>
#include "Student.h"
using namespace std;

int main() {

	Student* a = new BScStudentOld("alice");
	Student* b = new BScStudentNew("bob");
	Student* c = new MScStudent("carol");

	a->addModule("CO2001", 50);
	a->addModule("CO2006", 50);
	a->addModule("CO2008", 50);
	a->addModule("CO2011", 50);
	a->addModule("CO2012", 50);
	a->addModule("CO2015", 50);
	a->addModule("CO2016", 50);
	a->addModule("CO2017", 50);
	a->addModule("CO3101", 70);
	a->addModule("CO3102", 70);
	a->addModule("CO3105", 70);
	a->addModule("CO3002", 70);
	a->addModule("CO3099", 50);
	a->addModule("CO3201", 70);

	// should use dynamic_cast but wouldn't compile until you
	// implement virtualness correctly!
	cout << static_cast<BScStudentOld*>(a)->y2cwa() << endl;
	cout << static_cast<BScStudentOld*>(a)->y3cwa() << endl;
	cout << a->cwa() << endl;
	cout << a->calcDegClass() << endl;

	b->addModule("CO2FAK", 39.99);
	b->addModule("CO3FAK", 0);
	b->updateMark("CO3FAK", 99.99);
	cout << b->cwa() << endl;
	cout << b->calcDegClass() << endl;

	ifstream fin("teststudent3.txt");
	fin >> (*c);
	cout << c->cwa() << endl;
	cout << c->calcDegClass() << endl;
	cout << *c << endl;
}
