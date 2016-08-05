#include "stdafx.h"
#include "TimeTable.h"
#include "Picker.h"
#include "Burn.h"
using namespace std;

CTimeTable::CTimeTable()
{
}

CTimeTable::CTimeTable(string id)
{
	_name = id;
	CPicker p = CPicker(id + ".timetable");
	timeable = string((char*)(p[0]));
	acu = string((char*)(p[1]));
}

CTimeTable::CTimeTable(string id,string timeb)
{
	_name = id;
	timeable = timeb;
	acu = "";
}


CTimeTable::~CTimeTable()
{
}

void CTimeTable::burning()
{
	size_t sizes[3] = { 0,timeable.length() + 1,acu.length()+1 };
	sizes[1] += sizes[0];
	sizes[2] += sizes[1];
	char *tmpbuf = new char[sizes[2]];
	strcpy(&tmpbuf[sizes[0]], timeable.c_str());
	strcpy(&tmpbuf[sizes[1]], acu.c_str());
	CBurn::brunIt(tmpbuf, sizes[2], sizes, 2, _name + ".timetable");
	delete[] tmpbuf;
}

int CTimeTable::check()
{
	if (acu == timeable)
		return 1;
	else
		return 0;
}
