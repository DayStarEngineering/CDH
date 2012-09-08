#include "GlobalVar.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string fname = "/home/daystar/test";
	for( int i = 0; i < 10; i++ )
	{
		if(setGV(fname.c_str(),i) == -1)
			cerr << " well " << endl;
		cout << "got: " << getGV(fname.c_str()) << endl;
	}
}
