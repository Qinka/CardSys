#include "stdafx.h"
#include "Burn.h"
using namespace std;

CBurn::CBurn()
{
}


CBurn::~CBurn()
{
}

void CBurn::brunIt(char* buf, size_t bufsize, size_t* sizes,size_t s2s, std::string filename)
{
	{
		ifstream tmp("." + filename+".lock");
		if (tmp.is_open())
		{
			tmp.close();
			throw "locked";
		}
		else
		{
			ofstream t("." + filename + ".lock");
			t.close();
		}
	}
	ofstream write(filename);
	if (!write.is_open()) throw "open failed";
	write.write((char*)&s2s, sizeof(size_t));
	write.write((char*)&bufsize, sizeof(size_t));
	write.write((char*)sizes, sizeof(size_t)*s2s);
	write.write(buf, bufsize);
	write.close();
	{
		remove(("." + filename + ".lock").c_str());
	}
}
