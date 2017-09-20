#include "Bot.h"

int CountUnitType(const ObservationInterface* observation, UnitTypeID unit_type) {
	int count = 0;
	Units my_units = observation->GetUnits(Unit::Alliance::Self);
	for (const Unit& unit : my_units) {
		if (unit.unit_type == unit_type)
			++count;
	}

	return count;
}

bool GetRandomUnit(Unit& unit_out, const ObservationInterface* observation, UnitTypeID unit_type) {
	Units my_units = observation->GetUnits(Unit::Alliance::Self);
	std::random_shuffle(my_units.begin(), my_units.end()); // Doesn't work, or doesn't work well.
	for (const Unit& unit : my_units) {
		if (unit.unit_type == unit_type) {
			unit_out = unit;
			return true;
		}
	}
	return false;
}

Builder::Bot() {
	builder = Builder(this);
}

void Bot::manageProbe() {
	Units probes = Observation()->GetUnits(IsUnit(UNIT_TYPEID::PROTOSS_PROBE));
	for (Unit probe : probes) {

		if (probe.orders.empty()) {

			Units mineralFields = Observation()->GetUnits(IsUnit(UNIT_TYPEID::NEUTRAL_MINERALFIELD));
			Unit mineralFieldSelected = mineralFields.front();
			for (Unit mineralField : mineralFields) {
				if (Distance2D(mineralField.pos, probe.pos) < Distance2D(mineralFieldSelected.pos, probe.pos))
					mineralFieldSelected = mineralField;
			}
		}

		Units vespens = Observation()->GetUnits(IsUnit(UNIT_TYPEID::NEUTRAL_VESPENEGEYSER));
		for (Unit vespen : vespens) {
			if (vespen.assigned_harvesters < 3) {
				Actions()->UnitCommand(probe, ABILITY_ID::HARVEST_GATHER, vespen);
			}
		}
	}

	if (Observation()->GetMinerals() >= 50 && Observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::PROTOSS_NEXUS)).front().orders.empty())
		buildOrders.push({ UNIT_TYPEID::PROTOSS_NEXUS, ABILITY_ID::TRAIN_PROBE });
}

void Bot::macro() {

	manageProbe();

	build();
}

void Bot::micro() {

}

void Bot::OnStep() {
	macro();
	micro();
}

void Bot::OnGameStart() {
	buildOrders.push({ UNIT_TYPEID::PROTOSS_PROBE, ABILITY_ID::BUILD_PYLON });
	buildOrders.push({ UNIT_TYPEID::PROTOSS_PROBE, ABILITY_ID::BUILD_GATEWAY });
	buildOrders.push({ UNIT_TYPEID::PROTOSS_PROBE, ABILITY_ID::BUILD_ASSIMILATOR });
	buildOrders.push({ UNIT_TYPEID::PROTOSS_PROBE, ABILITY_ID::BUILD_CYBERNETICSCORE });
	buildOrders.push({ UNIT_TYPEID::PROTOSS_PROBE, ABILITY_ID::BUILD_ASSIMILATOR });
	buildOrders.push({ UNIT_TYPEID::PROTOSS_PROBE, ABILITY_ID::BUILD_PYLON });
}