#include "stdafx.h"
#include "Card.h"
#include "Burn.h"
#include "Picker.h"
#include "Holder.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

CCard::CCard(std::string id)
{
	cardid = id;
	CPicker data = CPicker(id+".card");
	type = *(char*)(data[0]);
	balance = *(int*)(data[1]);
	freetimes = *(int*)(data[2]);
	strcpy(name, (char*)data[3]);
	holder = cardid.substr(0, cardid.find('.'));
}

bool CCard::pay()
{
	auto x = true;
	switch (type)
	{
	case 'l'://限制
		if (freetimes > 1)
		{
			--freetimes;
			display();
			{
				auto h = CHolder(holder);
				h.pay();
			}
		}
		else if (freetimes == 1)
		{
			--freetimes;
			cout << "最后一次免费，下次收费" << endl;
			display();
			{
				auto h = CHolder(holder);
				h.pay();
			}
		}
		else if (balance >5)
		{
			balance -= 2;
			display();
			{
				auto h = CHolder(holder);
				h.pay();
			}
		}
		else if (balance > 2)
		{
			balance -= 2;
			cout << "请充值" << endl;
			display();
			{
				auto h = CHolder(holder);
				h.pay();
			}
		}
		else
		{
			cout << "无法乘车" << endl;
			x = false;
		}
		this->buring();
		return x;
		break;
	case 's':
		if (balance >5)
		{
			balance -= 2;
			display();
			{
				auto h = CHolder(holder);
				h.pay();
			}
		}
		else if (balance > 2)
		{
			balance -= 2;
			cout << "请充值" << endl;
			display();
			{
				auto h = CHolder(holder);
				h.pay();
			}
		}
		else
		{
			cout << "无法乘车" << endl;
			x = false;
		}
		this->buring();
		return x;
		break;
	case 't':
		this->buring();
		display();
		{
			auto h = CHolder(holder);
			h.pay();
		}
		return x;
		break;
	default:
		cout << "无法乘车" << endl;
		x = false;
	}
	return x;
}

CCard::~CCard()
{
}

void CCard::display()
{
	cout << "欢迎乘车" << endl;
	cout << "欢迎 " << name << endl;
	cout << "卡内余额：" << balance << endl;
	if (type == 'l')
		cout << "剩余次数：" << freetimes << endl;
}

void CCard::buring()
{
	size_t sizes[4];
	size_t it = sizeof(char) * 65 + sizeof(int) * 2;
	char * tmpbuf = new char[it];
	tmpbuf[0] = type;
	*(int*)&tmpbuf[0+sizeof(char)] = balance;
	*(int*)&tmpbuf[sizeof(char) + sizeof(int)] = freetimes;

	strcpy(&tmpbuf[sizeof(char) + sizeof(int) * 2], name);
	sizes[0] = 0;
	sizes[1] = sizes[0] + sizeof(char);
	sizes[2] = sizes[1] + sizeof(int);
	sizes[3] = sizes[2] + sizeof(int);
	CBurn::brunIt(tmpbuf, it, sizes, 4, cardid + ".card");
	delete[] tmpbuf;
}

CCard::CCard(std::string c, char t, int b , int f, std::string n)
{
	cardid = c;
	type = t;
	balance = b;
	freetimes = f;
	strcpy(name, n.c_str());
	holder = cardid.substr(0, cardid.find('.'));
}

std::string CCard::getHolder() const
{
	return holder;
}
