#include "configmap.h"
#include <assert.h>

string configmap::operator[](string key)
{
	configmap::const_iterator i=this->find(key);
	assert (i!=this->end()); // don't reference keys that don't exist!
	return i->second;
}

void configmap::readfile(const char* filename)
{
	TiXmlElement *key;
	TiXmlDocument config(filename);
	if (config.LoadFile())
	{
		key=config.FirstChildElement("configuration")->FirstChildElement();
		while (key)
		{
			if (strcmp(key->Value(),"documentation")!=0)
				this->insert(pair<string,string>(key->Value(),key->GetText()));
			key=key->NextSiblingElement();
		}
	}
}

void configmap::dump()
{
	for (configmap::const_iterator i=this->begin();i!=this->end();i++)
		cout << i->first << '=' << i->second << endl;
}
