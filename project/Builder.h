#include <queue>
#include <vector>

#include "Bot.h"

struct buildOrder {
	UnitTypeID unit_type;
	AbilityID ability;
};

class Builder {

public:
    Builder(Bot* bot);
    void addBuildOrder(UnitTypeID unitType, AbilityID, ability);
    void build();

private:
    Bot* bot;
    std::queue<buildOrder> buildOrders;
	std::vector<Point2D> pylons;
}