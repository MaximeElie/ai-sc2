#include "Builder.h"

Builder::Builder(Bot* bot) {
    this->bot = bot;
}

void Builder::addBuildOrder(UnitTypeID unitType, AbilityID, ability) {
    buildOrders.push( { unitType, ability } );
}

void Builder::build() {
    if (buildOrders.empty())
        return;

    UnitTypeID unit_type = buildOrders.front().unit_type;
    AbilityID ability = buildOrders.front().ability;
    std::cout << ability << std::endl;

    Unit unit;
    if (!GetRandomUnit(unit, Observation(), unit_type))
        return;

    Point2D pos;

    if (unit_type == UNIT_TYPEID::PROTOSS_PROBE) {
        if (ability == ABILITY_ID::BUILD_PYLON) {
            bool retry = true;
            while (retry) {
                float rx = GetRandomScalar();
                float ry = GetRandomScalar();

                pos = Point2D(unit.pos.x + rx * 15.0f, unit.pos.y + ry * 15.0f);

                if (Query()->Placement(ability, pos, unit))
                    retry = false;
            }

            pylons.push_back(pos);
        }
        else if (ability == ABILITY_ID::BUILD_ASSIMILATOR) {
            Units vespens = Observation()->GetUnits(IsUnit(UNIT_TYPEID::NEUTRAL_VESPENEGEYSER));
            Unit vespenSelected = vespens.front();
            for (Unit vespen : vespens) {
                if (Distance2D(vespen.pos, unit.pos) < Distance2D(vespenSelected.pos, unit.pos))
                    vespenSelected = vespen;
            }

            pos = vespenSelected.pos;
        }
        else {
            bool retry = true;
            while (retry) {
                float rx = GetRandomScalar();
                float ry = GetRandomScalar();

                pos = Point2D(pylons.front().x + rx * 6.5f, pylons.front().y + ry * 6.5f);

                if (Query()->Placement(ability, pos, unit))
                    retry = false;
            }
        }
    }

    if (&pos != nullptr)
        Actions()->Uni
        Actions()->UnitCommand(unit, ability, pos);
    else
        Actions()->UnitCommand(unit, ability);

    //buildOrders.pop();
}