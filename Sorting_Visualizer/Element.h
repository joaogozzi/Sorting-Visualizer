#pragma once
#include <raylib.h>

struct Element
{
	Element()
	{
		value = 0;
		color = WHITE;
	}

	Element(int value)
	{
		this->value = value;
		color = WHITE;
	}

	int value;
	Color color;
};