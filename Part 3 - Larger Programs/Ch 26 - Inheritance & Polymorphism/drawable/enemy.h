#pragma once
#include "drawable.h"

class Enemy : public Drawable
{
public:
	virtual void drawOverridable();
	virtual void draw();
};