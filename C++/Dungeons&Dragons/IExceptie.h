#ifndef IEXCEPTIE_H
#define IEXCEPTIE_H
#include <iostream>

class IExceptie
{
public:
	virtual std::string what() = 0;
};

#endif