#pragma once
#include<string>
class CHolder
{
public:
	CHolder(std::string id);
	CHolder(std::string id, std::string name, std::string typ, std::string belong, char sex);
	~CHolder();
	std::string getName()const;
	std::string getType() const;
	std::string getBelonged() const;
	std::string getItemId() const;
	char getSex() const;
	unsigned long long getTimes() const;
	bool pay();
protected:
	std::string _name;
	char _sex; // 0 male,1 famale
	std::string _type;
	std::string _belong;
	std::string _itemid;
	unsigned long long _times;
	void burning();
};

