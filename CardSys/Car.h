#pragma once
#include<tuple>
#include <string>
#include "Stop.h"


typedef std::tuple<std::string, std::string> cmap;

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
	bool AddAMan(std::string id,std::string stop);
	std::string GetTimeTable() const;
	void burning();
	void in(std::string);
	void go(std::string);
	void ar(std::string);
	int Check();
protected:
	std::string _plate;
	std::string _type;
	int _max;
	std::vector<cmap> _now;
	std::string _driver;
	std::string _when;
	CStop _time_table;
	std::string _time_table_name;
};

