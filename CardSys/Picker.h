#pragma once
#include<string>
class CPicker
{
public:
	CPicker(std::string filename);
	~CPicker();
	void* operator[] (unsigned);
private:
	size_t* _ptrForPtrs;
	size_t _sizeOfPtr;
	size_t _bufsize;
	char *buf;
};

