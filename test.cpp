#include "HashTable.h"
#include <iostream>

#include <string>
using std::string;

int main(int argc, char **argv) {
	HashTable<string> stringTable;
	string str1("abc");
	string str2("def");
	stringTable.AddElement(str1);
	stringTable.AddElement(str2);
	cout << "Testing " << str1 << ": result=" << stringTable.IsElementInHashTable(str1) << endl;
	stringTable.DumpHashTable();

	HashTable<int> intTable;
	int a=10;
	int b=5;
	int c=100000;
	intTable.AddElement(a);
	intTable.AddElement(a);
	intTable.AddElement(b);
	intTable.AddElement(c);
	cout << "Testing " << a << ": result=" << intTable.IsElementInHashTable(a) << endl;
	intTable.DumpHashTable();

	return 0;
}
