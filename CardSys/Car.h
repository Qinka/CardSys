#pragma once
#include <string>
#include "TimeTable.h"
class CCar
{
public:
	CCar(std::string);
	CCar(std::string, std::string, int,std::string, std::string);
	~CCar();
	std::string GetPlate() const;
	std::string GetType() const;
	int GetMax() const;
	int GetNow() const;
	std::string GetDriver() const;
	std::string GetWhen() const;
	bool AddAMan(std::string id);
	std::string GetTimeTable() const;
	void burning();
	void in(std::string);
	void go(std::string);
	void ar(std::string);
protected:
	std::string _plate;
	std::string _type;
	int _max;
	int _now;
	std::string _driver;
	std::string _when;
	CTimeTable _time_table;
	std::string _time_table_name;
};

