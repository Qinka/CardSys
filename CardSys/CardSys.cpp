// CardSys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Card.h"
#include "Car.h"
using namespace std;

int main(int argc,char** argv)
{
	try
	{
		if (argc < 1) throw "ee";
		else if (argv[1] == string("add-man"))
		{
			int b, f;
			char t;
			string id, n;
			cin >> id >> t >> b >> f >> n;
			CCard(id, t, b, f, n).buring();
		}
		else if (argv[1] == string("pay"))
		{
			string id, car;
			cin >> car >> id;
			CCar c = CCar(car);
			c.AddAMan(id);
		}
		else if (argv[1] == string("show-men"))
		{
			string id;
			cin >> id;
			CCard card = CCard(id);
			card.display();
		}
		else if (argv[1] == string("add-car"))
		{
			string p, t, d, t;
			int m;
			cin >> p >> t >> m >> d >> t;
			CCar(p, t, m, d, t).burning();
		}
		else if (argv[1] == string("add-time"))
		{
			string id, tb;
			CTimeTable rt = CTimeTable(id, tb);
			rt.burning();
		}
		else if (argv[1] == string("car-in"))
		{
			string id,time;
			cin >> id>>time;
			CCar car = CCar(id);
			car.in(time);
		}
		else if (argv[1] == string("car-go"))
		{
			string id, time;
			cin >> id >> time;
			CCar car = CCar(id);
			car.go(time);
		}
		else if (argv[1] == string("car-ar"))
		{
			string id, time;
			cin >> id >> time;
			CCar car = CCar(id);
			car.ar(time);
		}
		else cout << ">>" << endl;
	}
	catch (string x)
	{
		cout << x << endl;
	}
    return 0;
}

