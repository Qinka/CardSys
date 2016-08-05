#include "stdafx.h"
#include "Picker.h"
using namespace std;


CPicker::CPicker(std::string filename)
{
	{
		ifstream tmp("." + filename + ".lock");
		if (tmp.is_open())
		{
			tmp.close();
			throw "locked";
		}
	}
	ifstream read(filename);
	if (!read.is_open()) throw "no such a file";
	char tmp[16];
	read.read(tmp, sizeof(size_t));
	_sizeOfPtr = *(size_t*)tmp;
	read.read(tmp, sizeof(size_t));
	_bufsize = *(size_t*)tmp;
	_ptrForPtrs = new size_t[_sizeOfPtr];
	read.read((char*)(_ptrForPtrs), sizeof(size_t)*_sizeOfPtr); // Æ½Ì¨ÒÀÀµ
	buf = new char[_bufsize];
	auto x = _bufsize;
	auto buftmp = buf;
	while (x > 0)
	{
		read.read(buftmp, 1);
		--x;
		buftmp++;
	}
	read.close();
}

CPicker::~CPicker()
{
	delete[] _ptrForPtrs;
	delete[] buf;
}

void * CPicker::operator[](unsigned index)
{
	return &(buf[_ptrForPtrs[index]]);
}
