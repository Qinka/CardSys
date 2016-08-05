#pragma once
#include "Card.h"
#include <functional>
#include <string>

class CCardOpt
{
public:
	CCardOpt();
	~CCardOpt();
static	bool addCard();
static	bool delCard();
static	int argc;
static	char** argv;
};

typedef std::function<bool()> cmdFunc;
bool operator >> (bool is, cmdFunc item);