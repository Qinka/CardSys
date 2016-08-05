#include "stdafx.h"
#include "Burn.h"
#include "Picker.h"
#include "Holder.h"
#include "Card.h"
using namespace std;

CHolder::CHolder(std::string id)
{
	_itemid = id;
	auto picker = CPicker(id + ".holder");
	_sex = *((char*)picker[0]);
	_times = *((unsigned long long*)picker[1]);
	_name = string((char*)picker[2]);
	_type = string((char*)picker[3]);
	_belong = string((char*)picker[4]);
}

CHolder::CHolder(std::string id, std::string name, std::string typ, std::string belong, char sex):_itemid(id),_name(name),_type(typ),_belong(belong),_sex(sex),_times(0)
{
	burning();
}

CHolder::~CHolder()
{
	burning();
}

std::string CHolder::getName() const
{
	return _name;
}

std::string CHolder::getType() const
{
	return _type;
}

std::string CHolder::getBelonged() const
{
	return _belong;
}

std::string CHolder::getItemId() const
{
	return std::string();
}

char CHolder::getSex() const
{
	return _sex;
}

unsigned long long CHolder::getTimes() const
{
	return _times;
}

bool CHolder::pay()
{
		_times++;
	burning();
	return true;
}

void CHolder::burning()
{
	size_t sizes[6] = { 0,sizeof(char),sizeof(unsigned long long),_name.length()+1,_type.length()+1,_belong.length()+1};
	{
		auto cur = begin(sizes);
		cur++;
		while (cur != end(sizes))
		{
			*cur += *(cur - 1);
			cur++;
		}
	}
	auto tmpbuf = new char[*(end(sizes) - 1)];
	auto bufcur = tmpbuf;
	*bufcur = _sex;
	++bufcur;
	*((unsigned long long*)bufcur) = _times;
	bufcur += sizeof(unsigned long long);
	_name.copy(bufcur, _name.length());
	bufcur += _name.length();
	*bufcur = '\0';bufcur++;
	_type.copy(bufcur, _type.length());
	bufcur += _type.length();
	*bufcur = '\0';bufcur++;
	_belong.copy(bufcur, _belong.length());
	bufcur += _belong.length();
	*bufcur = '\0';
	CBurn::brunIt(tmpbuf, *(end(sizes) - 1),sizes, 5, _itemid + ".holder");
	delete[] tmpbuf;
}
