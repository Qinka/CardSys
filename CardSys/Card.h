#pragma once
#include<string>
class CCard
{
public:
	CCard(std::string);
	bool pay();
	~CCard();
	void display();
	void buring();
	CCard(std::string,char,int,int,std::string);
private:
	char name[64];
	std::string cardid;
	char type;
	int balance;
	int freetimes;
};

