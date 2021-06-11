/////////////////////////
////// NOT MY CODE //////
/////////////////////////

#include <iostream>
#include "Pxtree.h"

using namespace std;

int main() {

	Pxtree t;
	cout << "--- Some adds ---\n";
	t.add("baby");
	t.add("ban");
	t.add("bank");
	t.add("bad");
	t.add("dad");
	cout << t.print() << endl;

	cout << "--- add and remove ---\n";
	t.add("ban");
	t.add("c");
	t.remove("baby");
	cout << t.print() << endl;

	cout << "--- count ---\n";
	cout << t.count("ban") << endl;
	cout << t.count("bank") << endl;
	cout << t.count("ba") << endl;

	cout << "--- copy con, copy asg ---" << endl;
	Pxtree u(t);
	cout << u.print() << endl << endl;
	Pxtree v;
	v = t;
	cout << v.print() << endl;

	cout << "--- autoComplete ---\n";
	cout << t.autoComplete("ba") << endl;
	cout << t.autoComplete("d") << endl;
	cout << t.autoComplete("z") << endl;

	cout << "--- compact ---\n";
	t.compact();
	cout << t.print() << endl;

}
