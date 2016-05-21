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
	acu = string((char*)(p[0]));
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
}
