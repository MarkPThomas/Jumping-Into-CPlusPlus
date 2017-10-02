#pragma once

class Exception
{
public:
	virtual ~Exception() = 0;
	virtual int getErrorCode() const = 0;
	virtual std::string getErrorReport() const = 0;
};

inline Exception::~Exception()
{
	
}


// Consider deriving all exceptions from the following:
// std::exception;