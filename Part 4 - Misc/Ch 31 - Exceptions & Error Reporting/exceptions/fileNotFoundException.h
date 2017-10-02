#pragma once
#include "exception.h"

class FileNotFoundException : public Exception
{
public:
	FileNotFoundException(int errorCode, const std::string& details) 
							: _errorCode(errorCode), _details(details)
	{}

	virtual ~FileNotFoundException()
	{}

	int getErrorCode()  const override
	{
		return _errorCode;
	}

	std::string getErrorReport() const override
	{
		return _details;
	}

private:
	int _errorCode;
	std::string _details;
};