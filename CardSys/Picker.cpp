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
	read.read((char*)(_ptrForPtrs), sizeof(size_t)*_sizeOfPtr); // ∆ΩÃ®“¿¿µ
	buf = new char[_bufsize];
	read.read(buf, _bufsize);
	read.close();
}

CPicker::~CPicker()
{
	delete[] buf;
}

void * CPicker::operator[](unsigned index)
{
	return &(buf[_ptrForPtrs[index]]);
}
