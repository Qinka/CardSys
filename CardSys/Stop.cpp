#include "stdafx.h"
#include "Stop.h"
#include "Picker.h"
#include "Burn.h"

using namespace std;


CStop::CStop(std::string id):_id(id)
{
	auto picker = CPicker(id + ".stop");
	size_t ss[3] = { 0,0,0 };
	ss[0] = *((size_t*)(picker[0]));
	size_t * x = (size_t*)picker[0];

	ss[1] = *((size_t*)(picker[1]));
	ss[2] = *((size_t*)(picker[2]));
	auto nextstr = [](char* i)
	{
		while (*i != '\0')
		{
			++i;
		}
		return ++i;
	};
	auto make = [&](size_t size,void* ptr)
	{
		auto rt = vector<string>(size);
		for (auto item : rt)
		{
			item = string((char*)ptr);
			ptr = nextstr((char*)ptr);
		}
		return rt;
	};
	_stops = make(ss[0], picker[3]);
	_time = make(ss[1], picker[4]);
	_rtime = make(ss[2], picker[5]);
}

CStop::CStop(std::string id, std::vector<std::string> stop, std::vector<std::string> time):_stops(stop),_time(time),_rtime(),_id(id)
{
	if (_stops.size() * 2 != _time.size())
		throw "error";
}

string CStop::in(string time)
{
	if (_time.size() > _rtime.size())
	{
		_rtime.push_back(time);
		burning();
		return _stops[_rtime.size()/2 - 1];
	}
	else cout << "老司机，车往哪里开？";
	throw "error";
	return "";
}

void CStop::out(string time)
{
	if (_time.size() > _rtime.size())
	{
		_rtime.push_back(time);
		burning();
		return;
	}
	else cout << "老司机，车往哪里开？";
	throw "error";
	return;
}

void CStop::burning()
{
	auto csize = [](vector<string> vs)
	{
		size_t sum = 0;
		for (auto item : vs)
		{
			sum += item.length() + 1;
		}
		if (vs.size() == 0)
			sum += 1;
		return sum;
	};
	auto bs = { csize(_stops),csize(_time),csize(_rtime) };
	size_t ss[] = { _stops.size(),_time.size(),_rtime.size() };
	auto buf_size = sizeof(size_t) * 3 + [&]() {auto sum = 0;for (auto item : bs) { sum += item; }return sum;}();
	char * const buf = new char[buf_size];
	size_t* sbuf = (size_t*)buf;
	for (auto item : ss)
	{
		*sbuf = item;
		++sbuf;
	}
	typedef char* charP;
	auto make = [](vector<string> vs,charP& ibuf)
	{
		for (auto item : vs)
		{
			item.copy(ibuf, item.length() + 2);
			ibuf += item.length();
			*ibuf = '\0';
			++ibuf;
		}
		if (vs.size() == 0)
		{
			*ibuf = '\0';
			++ibuf;
		}

		return;
	};
	charP strbuf = (char *)sbuf;
	make(_stops, strbuf);
	make(_time, strbuf);
	make(_rtime, strbuf);
	size_t ssize[7];
	{
		ssize[0] = 0;
		auto i = 1;
		for (auto item : ss)
		{
			ssize[i] = sizeof(item);
			++i;
		}
		for (auto item : bs)
		{
			ssize[i] = item;
			++i;
		}
	}
	for (auto item = begin(ssize) + 1;item != end(ssize);++item)
	{
		*item += *(item - 1);
	}
	CBurn::brunIt(buf, buf_size, ssize, 6, _id+".stop");
	delete[] buf;
}


CStop::~CStop()
{
}
