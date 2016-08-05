#include "stdafx.h"
#include "CardOpt.h"
#include "Holder.h"
using namespace std;

CCardOpt::CCardOpt()
{
}

int CCardOpt::argc = 0;
char ** CCardOpt::argv = nullptr;


bool operator >> (bool is, cmdFunc item)
{
	if (!is) return item();
	else return is;
}

CCardOpt::~CCardOpt()
{
}

bool CCardOpt::addCard()
{
	if (argv[1] == string("card-add"))
	{
		int b, f;
		string id,add;
		cin >> id >> add >> b >> f;
		try
		{
			auto tmp = CHolder(id);
			auto x = 'l';
			if (tmp.getType() == "Stu")
				x = 's';
			else if (tmp.getType() == "Tec")
				x = 't';
			CCard(id+"."+add, x, b, f, tmp.getName()).buring();
		}
		catch (string e)
		{
			cout << "没有此人" << endl;
			return true;
		}
		return true;
	}
	return false;
}

bool CCardOpt::delCard()
{

	if (argv[1] == string("card-del"))
	{
		string id;
		cin >> id;
		remove((id + ".card").c_str());
		return true;
	}
	return false;
}
