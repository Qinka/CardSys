#pragma once
#include<string>
#include<vector>
class CStop
{
private:
	std::vector<std::string> _stops;
	std::vector<std::string> _time;
	std::vector<std::string> _rtime;
	std::string _id;
public:
	CStop(std::string id);
	CStop(std::string id, std::vector<std::string> stop, std::vector<std::string> time);
	std::string in(std::string time);
	void out(std::string time);
	int check()const { return 0; }
	CStop() {};
	void burning();
	~CStop();
};

