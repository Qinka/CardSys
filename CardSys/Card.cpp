#include "stdafx.h"
#include "Card.h"
#include "Burn.h"
#include "Picker.h"

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
}

bool CCard::pay()
{
	auto x = true;
	switch (type)
	{
	case 'l'://����
		if (freetimes > 1)
		{
			--freetimes;
			display();
		}
		else if (freetimes == 1)
		{
			--freetimes;
			cout << "���һ����ѣ��´��շ�" << endl;
		}
		else if (balance >5)
		{
			balance -= 2;
			display();
		}
		else if (balance > 2)
		{
			balance -= 2;
			cout << "���ֵ" << endl;
			display();
		}
		else
		{
			cout << "�޷��˳�" << endl;
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
		}
		else if (balance > 2)
		{
			balance -= 2;
			cout << "���ֵ" << endl;
			display();
		}
		else
		{
			cout << "�޷��˳�" << endl;
			x = false;
		}
		this->buring();
		return x;
		break;
	case 't':
		this->buring();
		display();
		return x;
		break;
	default:
		cout << "�޷��˳�" << endl;
		x = false;
	}
	return x;
}

CCard::~CCard()
{
}

void CCard::display()
{
	cout << "��ӭ�˳�" << endl;
	cout << "��ӭ " << name << endl;
	cout << "������" << balance << endl;
	if (type == 't')
		cout << "ʣ�������" << freetimes << endl;
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
}
