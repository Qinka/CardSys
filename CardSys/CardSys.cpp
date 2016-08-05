// CardSys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Card.h"
#include"Holder.h"
#include "Car.h"
#include "CardOpt.h"
using namespace std;

int main(int argc,char** argv)
{
	CCardOpt::argc = argc;
	CCardOpt::argv = argv;
	try
	{
		false >> cmdFunc(CCardOpt::addCard) >> cmdFunc(CCardOpt::delCard) >> [&]() {
			if (argc < 1) throw "ee";
			else if (argv[1] == string("pay"))
			{
				string id, car,stop;
				cin >> car >> id >> stop;
				CCar c = CCar(car);
				auto x = c.AddAMan(id,stop);
			}
			else if (argv[1] == string("card-show"))
			{
				string id;
				cin >> id;
				CCard card = CCard(id);
				card.display();
			}
			else if (argv[1] == string("add-car"))
			{
				string p, t, d, ti;
				int m;
				cin >> p >> t >> m >> d >> ti;
				CCar(p, t, m, d, ti).burning();
			}
			else if (argv[1] == string("add-time"))
			{
				string id, stop,in,out;
				vector<string>s, t;
				cin >> id ;
				while (cin >> stop >> in >> out)
				{
					s.push_back(stop);
					t.push_back(in);
					t.push_back(out);
				}
				CStop rt = CStop(id, { s }, { t });
				rt.burning();
			}
			else if (argv[1] == string("car-in"))
			{
				string id, time;
				cin >> id >> time;
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
			else if (argv[1] == string("car-check"))
			{
				string id;
				auto i = 0, count = 0;
				while (cin >> id)
				{
					CCar car = CCar(id);
					i += car.Check();
					count++;
				}
				cout << i*1.0 / count << endl;
			}
			else if (argv[1] == string("holder-show"))
			{
				string id;
				cin >> id;
				auto item = CHolder(id);
				cout << "Id: " << item.getItemId() << endl
					<< "Name: " << item.getName() << endl
					<< "Position: " << item.getType() << endl
					<< "Belong to: " << item.getBelonged() << endl
					<< "Sex: " << (item.getSex() ? "Female" : "Male") << endl
					<< "Times: " << item.getTimes() << endl;
			}
			else if (argv[1] == string("holder-add"))
			{
				string id, name, typ, belong;
				int sex;
				cin >> id >> name >> typ >> belong >> sex;
				CHolder(id, name, typ, belong, sex);
			}
			else cout << ">>" << endl;
			return true;
		};
	}
	catch (string x)
	{
		cout << x << endl;
	}
    return 0;
}

