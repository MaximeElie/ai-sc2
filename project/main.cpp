#include "Bot.h"

int main(int argc, char* argv[]) {
	Coordinator coordinator;
	coordinator.LoadSettings(argc, argv);

	Bot bot;
	coordinator.SetParticipants({
		CreateParticipant(Race::Protoss, &bot),
		CreateComputer(Race::Zerg)
	});

	coordinator.SetRealtime(true);
	coordinator.LaunchStarcraft();
	coordinator.StartGame(sc2::kMapBelShirVestigeLE);

	while (coordinator.Update());
	return 0;
}
