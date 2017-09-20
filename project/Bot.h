#pragma once

#include <sc2api/sc2_api.h>
#include <iostream>

#include "Builder.h"

using namespace sc2;

class Bot : public Agent {

public:
	Bot();

private:
	Builder builder;

	void manageProbe();
	void macro();
	void micro();
	virtual void OnStep() final;
	virtual void OnGameStart() final;

};
