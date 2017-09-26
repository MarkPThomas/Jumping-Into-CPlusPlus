#pragma once
class Comparable
{
public:
	virtual ~Comparable();
	virtual int compare(Comparable& other) = 0;
};