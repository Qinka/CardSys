#include "stdafx.h"
#include "Picker.h"
#include "Burn.h"
#include "Car.h"
#include "Card.h"
#include "Holder.h"
using namespace std;

CCar::CCar(std::string plate)
{
	_plate = plate;
	CPicker data = CPicker(plate + ".car");
	_type = string((char*)(data[0]));
	_max = *(int*)(data[1]);
	auto _now_size = *(size_t*)(data[4]);
	auto make = [](char* buf, size_t s)
	{
		vector<cmap> rt = vector<cmap>(s);
		for (auto item : rt)
		{
			string _id_ = string(buf);
			buf += _id_.length() + 1;
			string _stop_ = string(buf);
			buf += _stop_.length() + 1;
			rt.push_back(cmap(_id_, _stop_));
		}
		return rt;
	};
	_now = make((char*)(data[5]),_now_size);
	_driver = string((char*)(data[2]));
	_time_table_name = string((char*)(data[3]));
	_time_table = CStop(_time_table_name);
}
CCar::CCar(std::string plate, std::string type, int max, std::string driver, std::string time_table_name)
	:_plate(plate),_type(type),_max(max),_driver(driver),_time_table_name(time_table_name),_time_table(time_table_name),_now(vector<cmap>())
{}
void CCar::burning()
{
	auto cmapsize = [&]()
	{
		size_t sum = 0;
		string _id_, _stop_;
		for (auto item : _now)
		{
			tie(_id_, _stop_) = item;
			sum += _id_.length() + _stop_.length() + 2;
		}
		return sum;
	}();
	size_t sizes[6] = { 0,_type.length() + 1,sizeof(int),_driver.length() + 1,_time_table_name.length() + 1 ,cmapsize};
	size_t it = sizeof(char)*(_time_table_name.length() + _type.length() + _driver.length() + 3) + sizeof(int) * 2+cmapsize;
	char * tmpbuf = new char[it];
	sizes[1] += sizes[0];
	sizes[2] += sizes[1];
	sizes[3] += sizes[2];
	sizes[4] += sizes[3];
	sizes[5] += sizes[4];
	strcpy(&tmpbuf[sizes[0]], _type.c_str());
	*(int*)&tmpbuf[sizes[1]] = _max;
	strcpy(&tmpbuf[sizes[2]], _driver.c_str());
	strcpy(&tmpbuf[sizes[3]], _time_table_name.c_str());
	*(int*)&tmpbuf[sizes[4]] = _now.size();
	auto make = [&](char *buf)
	{
		for (auto item : _now)
		{
			string l, r;
			tie(l, r) = item;
			l.copy(buf, l.length() + 2);
			buf += l.length();
			*buf = '\0';
			++buf;
			r.copy(buf, r.length() + 2);
			buf += r.length();
			*buf = '\0';
			++buf;
		}
		return;
	};
	make(&tmpbuf[sizes[5]]);
	CBurn::brunIt(tmpbuf, it, sizes, 5, _plate + ".car");
	delete[] tmpbuf;
}

void CCar::in(string time)
{
	auto stop_name = _time_table.in(time);
	for (auto item=_now.begin();item !=_now.end();++item)
	{
		string l,r;
		tie(l, r) = *item;
		if (r == stop_name)
		{
			_now.erase(item);
			auto man = CCard(l);
			cout << "请" << man.getHolder() << "下车" << endl;
			cout << man.getHolder() << "被踹下了车😂！" << endl;
		}
	}
	_time_table.burning();
}

void CCar::go(string time)
{
	_time_table.out(time);
	_time_table.burning();
}

void CCar::ar(string time)
{
	_time_table.out(time);
	_time_table.burning();
}

int CCar::Check()
{
	return _time_table.check();
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
	return _now.size();
}

string CCar::GetDriver() const
{
	return _driver;
}

string CCar::GetWhen() const
{
	return string();
}

bool CCar::AddAMan(string id,string stop)
{
	cout << "当前人数：" << _now.size() << endl;
	if (_max > _now.size())
	{
		auto man = CCard(id);
		if (man.pay())
		{
			_now.push_back(cmap(id, stop));
			burning();
			return true;
		}
	}
	else
		cout << "坐满了" << endl;
	return false;
}

string CCar::GetTimeTable() const
{
	return _time_table_name;
}


