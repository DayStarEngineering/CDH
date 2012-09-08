#ifndef H_CONFIGMAP
#define H_CONFIGMAP

#include <iostream>
#include <map>
#include <string>
#include "tinystr.h"
#include "tinyxml.h"

using namespace std;

class configmap : public multimap<string,string>
{
	public:
		string operator[](string);
		void readfile(const char*);
		void dump();
};

#endif
