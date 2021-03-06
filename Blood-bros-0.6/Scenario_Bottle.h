#ifndef __SCENARIO_BOTTLE_H__
#define __SCENARIO_BOTTLE_H__

#include "Scenario_elem.h"
#include "p2Point.h"


enum bottles{

	BLUE_WIDE,
	BLUE_NARROW,
	ORANGE

};

class Scenario_Bottle : public Scenario_elem
{
private:

	Animation idle;

	p2Point<int> orig_pos;


public:

	Scenario_Bottle(int x, int y);

};

#endif