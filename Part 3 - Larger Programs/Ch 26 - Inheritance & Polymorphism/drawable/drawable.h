#pragma once

class Drawable
{
public:
	void drawNonOverrridable();		// Inheriting classes can use this method, but it cannot be overwritten.
	virtual void drawOverridable();	// This virtual method can be overwritten in inheriting classes, but that is not required.
	virtual void draw() = 0;		// This is a pure virtual method. This must be defined in any inheriting classes.
};
