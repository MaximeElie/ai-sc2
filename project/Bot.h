#pragma once

#include <sc2api/sc2_api.h>

#include <iostream>
#include <queue>
#include <vector>

using namespace sc2;

struct buildOrder {
	UnitTypeID unit_type;
	AbilityID ability;
};

class Bot : public Agent {

public:
	void build();
	void manageProbe();
	void macro();
	void micro();
	virtual void OnStep() final;
	virtual void OnGameStart() final;

private:
	std::queue<buildOrder> buildOrders;
	std::vector<Point2D> pylons;

};
