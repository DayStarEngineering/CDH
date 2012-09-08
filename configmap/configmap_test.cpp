#include <iostream>
#include "configmap.h"

int main(int argc,char *argv[])
{
	configmap m;
	configmap::const_iterator i;
	pair<configmap::const_iterator,configmap::const_iterator> p;
	if (argc<2) exit(1);
	m.readfile(argv[1]);
	for (i=m.begin();i!=m.end();i++)
		cout << i->first << '=' << i->second << endl;
}

