#include "Team.h"

Team::Team() : AbstractModule("Team", Category::World) {

}

Team* Team::getInstance() {
	static Team* inst = new Team();
	return inst;
}

void Team::onEnabled() {

}

void Team::onDisabled() {

}

