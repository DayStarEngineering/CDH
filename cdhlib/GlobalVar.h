#ifndef GLOBAL_VAR_H     // Prevent duplicate definition
#define GLOBAL_VAR_H

#include <stdio.h>

using namespace std;

int setGV(const char* fname, int value);
int getGV(const char* fname);

#endif

