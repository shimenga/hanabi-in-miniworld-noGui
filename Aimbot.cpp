#include "Aimbot.h"

Aimbot::Aimbot() : AbstractModule("Aimbot", Category::Combat) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &Aimbot::onRenderOverlay));
}

Aimbot* Aimbot::getInstance() {
	static Aimbot* inst = new Aimbot();
	return inst;
}

void Aimbot::onEnabled() {

}

void Aimbot::onDisabled() {

}

void Aimbot::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	std::stable_sort(Game::playerInWorld.begin(), Game::playerInWorld.end(), AimbotDisSorter());
	std::stable_sort(Game::playerInWorld.begin(), Game::playerInWorld.end(), AimbotScreenDisSorter());

	SDK::ClientPlayer* e = nullptr;

	Vec2 view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	float closestScDis = this->aimRange;
	for (SDK::ClientPlayer* p : Game::playerInWorld) {

		if (TeamCheck && Game::thePlayer->isSameTeam(p->playerTeamComponent->team)) continue;
		
		Vec3 ePos = { p->actorBody->entity->posX, p->actorBody->entity->posY + this->headOffset, p->actorBody->entity->posZ };
		Vec2 eScPos;

		Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &ePos, &view, &eScPos);
		
		float scDis = Utility::getDistance2D(view, eScPos);
		if (scDis < closestScDis) {
			e = p;
			closestScDis = scDis;
		}

	}

	if (e == nullptr) {
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(view.x, view.y), this->aimRange, IM_COL32(0, 255, 0, 240));
		return;
	}
	else {
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(view.x, view.y), this->aimRange, IM_COL32(255, 0, 0, 240));
	}

	Vec3 ePos = { e->actorBody->entity->posX, e->actorBody->entity->posY + this->headOffset, e->actorBody->entity->posZ };
	Vec2 eScPos;
		
	Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &ePos, &view, &eScPos);

	ImGui::GetForegroundDrawList()->AddLine(ImVec2(view.x, view.y), ImVec2(eScPos.x, eScPos.y), IM_COL32(255, 0, 0, 230));

	if (ImGui::IsKeyDown(ImGuiKey_C)) {
		
		Vec3 lpCamPos = Game::thePlayer->getCameraPosition();
		Vec2 angle = Utility::calcAimAngle(&lpCamPos, &ePos);
		Game::thePlayer->setYaw(angle.x);
		Game::thePlayer->setPitch(angle.y);
	}
}

bool AimbotDisSorter::operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2) {
	
	Vec3 p1Pos = { p1->actorBody->entity->posX, p1->actorBody->entity->posY, p1->actorBody->entity->posZ };
	Vec3 p2Pos = { p2->actorBody->entity->posX, p2->actorBody->entity->posY, p2->actorBody->entity->posZ };

	return Utility::getDistance3D(Game::thePlayer->getPosition(), p1Pos) < Utility::getDistance3D(Game::thePlayer->getPosition(), p2Pos);
}

bool AimbotScreenDisSorter::operator()(SDK::ClientPlayer* p1, SDK::ClientPlayer* p2) {

	Vec3 p1Pos = { p1->actorBody->entity->posX, p1->actorBody->entity->posY, p1->actorBody->entity->posZ };
	Vec3 p2Pos = { p2->actorBody->entity->posX, p2->actorBody->entity->posY, p2->actorBody->entity->posZ };
	Vec2 p1ScPos;
	Vec2 p2ScPos;

	Vec2 view = Game::getGameViewSize();
	view.x *= 0.5f;
	view.y *= 0.5f;

	Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &p1Pos, &view, &p1ScPos);
	Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &p2Pos, &view, &p2ScPos);

	return Utility::getDistance2D(view, p1ScPos) < Utility::getDistance2D(view, p2ScPos);
}

