#pragma once
#include "drawable.h"

class Ship : public Drawable
{
public:
	virtual void drawOverridable();
	virtual void draw();
};
