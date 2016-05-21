#include "stdafx.h"
#include "Picker.h"
#include "Burn.h"
#include "Car.h"
#include "Card.h"
using namespace std;

CCar::CCar(std::string plate)
{
	_plate = plate;
	CPicker data = CPicker(plate + ".car");
	_type = string((char*)(data[0]));
	_max = *(char*)(data[1]);
	_now = *(char*)(data[4]);
	_driver = string((char*)(data[2]));
	_time_table_name = string((char*)(data[3]));
	_time_table = CTimeTable(_time_table_name);
}
CCar::CCar(std::string plate, std::string type, int max, std::string driver, std::string time_table_name)
	:_plate(plate),_type(type),_max(max),_driver(driver),_time_table_name(time_table_name),_time_table(CTimeTable(_time_table_name))
{
	_now = 0;
}
void CCar::burning()
{
	size_t sizes[5] = { 0,_type.length() + 1,sizeof(int),_driver.length() + 1,_time_table_name.length() + 1 };
	size_t it = sizeof(char)*(_time_table_name.length() + _type.length() + _driver.length() + 3) + sizeof(int) * 2;
	char * tmpbuf = new char[it];
	sizes[1] += sizes[0];
	sizes[2] += sizes[1];
	sizes[3] += sizes[2];
	sizes[4] += sizes[3];
	strcpy(&tmpbuf[sizes[0]], _plate.c_str());
	*(int*)&tmpbuf[sizes[1]] = _max;
	strcpy(&tmpbuf[sizes[2]], _driver.c_str());
	strcpy(&tmpbuf[sizes[3]], _time_table_name.c_str());
	*(int*)&tmpbuf[sizes[4]] = _now;
	CBurn::brunIt(tmpbuf, it, sizes, 4, _plate + ".car");
}

void CCar::in(string time)
{
	_time_table.acu += time;
	_time_table.burning();
}

void CCar::go(string time)
{
	_time_table.acu += time;
	_time_table.burning();
}

void CCar::ar(string time)
{
	_time_table.acu += time;
	_time_table.burning();
}


CCar::~CCar()
{
}

string CCar::GetPlate() const
{
	return _plate;
}

string CCar::GetType() const
{
	return _type;
}

int CCar::GetMax() const
{
	return _max;
}

int CCar::GetNow() const
{
	return _now;
}

string CCar::GetDriver() const
{
	return _driver;
}

string CCar::GetWhen() const
{
	return string();
}

bool CCar::AddAMan(string id)
{
	if (_max > _now)
	{
		auto man = CCard(id);
		if (man.pay())
		{
			_now++;
			burning();
			return true;
		}
	}
	return false;
}

string CCar::GetTimeTable() const
{
	return _time_table_name;
}


