#pragma once
#include <exception>
#include <string>

#define Stringify(expr) #expr;

class ValueException : public std::exception
{
private:
	std::string m_typename;
public:
	ValueException(std::string a_typename);
	std::string message();
};

