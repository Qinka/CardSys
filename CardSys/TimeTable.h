#pragma once
#include<string>
class CTimeTable
{
public:
	CTimeTable();
	CTimeTable(std::string);
	CTimeTable(std::string,std::string);
	~CTimeTable();
	void burning();
	int check();
protected:
	friend class CCar;
	std::string _name;
	std::string timeable;
	std::string acu;
};

