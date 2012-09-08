#include "GlobalVar.h"

int setGV(const char* fname, int value)
{
  FILE * pFile;
  if( (pFile = fopen (fname,"wb")) == NULL)
    return -1;
  
  if( fwrite (&value, sizeof(int), 1, pFile ) != 1 )
  {
  	fclose (pFile);
  	return -1;
  }

  fclose (pFile);
  return 0;
}

int getGV(const char* fname)
{
  FILE * pFile;
  int value;
  if((pFile = fopen (fname,"rb")) == NULL)
    return -1;
  
  if( fread (&value, sizeof(int), 1, pFile ) != 1 )
  {
  	fclose (pFile);
  	return -1;
  }
  
  fclose (pFile);
  return value;
}
