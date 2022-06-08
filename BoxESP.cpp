#include "BoxESP.h"

BoxESP::BoxESP() : AbstractModule("BoxESP", Category::Render) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &BoxESP::onRenderOverlay));
}

BoxESP* BoxESP::getInstance() {
	static BoxESP* inst = new BoxESP();
	return inst;
}

void BoxESP::onEnabled() {

}

void BoxESP::onDisabled() {

}

void BoxESP::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;

	Vec3 ePos;
	Vec2 eScPos;
	Vec3 eHeadPos;
	Vec2 view;
	Vec4 camera;

	Vec3 bp1;
	Vec2 bp1Sc;
	Vec3 bp2;
	Vec2 bp2Sc;
	Vec3 bp3;
	Vec2 bp3Sc;
	Vec3 bp4;
	Vec2 bp4Sc;

	Vec3 tp1;
	Vec2 tp1Sc;
	Vec3 tp2;
	Vec2 tp2Sc;
	Vec3 tp3;
	Vec2 tp3Sc;
	Vec3 tp4;
	Vec2 tp4Sc;

	Vec3 sightStartPos;
	Vec3 sightEndPos;
	Vec2 sightStartScPos;
	Vec2 sightEndScPos;

	for (SDK::ClientPlayer* p : Game::playerInWorld) {
		
		ePos.x = p->actorBody->entity->posX;
		ePos.y = p->actorBody->entity->posY;
		ePos.z = p->actorBody->entity->posZ;
		
		eHeadPos.x = p->actorBody->entity->posX;
		eHeadPos.y = p->actorBody->entity->posY + this->headOffset;
		eHeadPos.z = p->actorBody->entity->posZ;

		sightStartPos.x = p->actorBody->entity->posX;
		sightStartPos.y = p->actorBody->entity->posY + this->sightXOffset;
		sightStartPos.z = p->actorBody->entity->posZ;

		view = Game::getGameViewSize();
		view.x *= 0.5f;
		view.y *= 0.5f;

		bool canDraw = true;
		bp1 = this->rotatePointYaw(ePos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 45);
		bp2 = this->rotatePointYaw(ePos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 135);
		bp3 = this->rotatePointYaw(ePos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 225);
		bp4 = this->rotatePointYaw(ePos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 315);
		tp1 = this->rotatePointYaw(eHeadPos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 45);
		tp2 = this->rotatePointYaw(eHeadPos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 135);
		tp3 = this->rotatePointYaw(eHeadPos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 225);
		tp4 = this->rotatePointYaw(eHeadPos, this->radius, (0 - (p->playerLocoMotion->yaw)) + 315);
		Vec3 sightYaw = this->rotatePointYaw(sightStartPos, this->sightLength, 0 - (p->playerLocoMotion->yaw) - 90);
		Vec3 sightPitch = this->rotatePointPitch(sightStartPos, this->sightLength, 0 - (p->playerLocoMotion->pitch));
		sightEndPos.x = sightYaw.x;
		sightEndPos.y = sightPitch.y;
		sightEndPos.z = sightYaw.z;

		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &bp1, &view, &bp1Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &bp2, &view, &bp2Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &bp3, &view, &bp3Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &bp4, &view, &bp4Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &tp1, &view, &tp1Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &tp2, &view, &tp2Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &tp3, &view, &tp3Sc);
		if (!canDraw) continue;
		canDraw = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &tp4, &view, &tp4Sc);
		if (!canDraw) continue;
		Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &sightStartPos, &view, &sightStartScPos);
		bool canDrawSight = Utility::worldToScreen(Game::theUIRenderer->matrixLevel1->matrixLevel2->matrix, &sightEndPos, &view, &sightEndScPos);

		ImDrawList* dl = ImGui::GetForegroundDrawList();

		if (TeamCheck && Game::thePlayer->isSameTeam(p->playerTeamComponent->team)) {
		
			// 3D Rect
			dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp2Sc.x, bp2Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(bp1Sc.x, bp1Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp2Sc.x, tp2Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(18, 255, 18, 245), 1.5f);

			// Sight Line
			if (canDrawSight) {
				dl->AddLine(ImVec2(sightStartScPos.x, sightStartScPos.y), ImVec2(sightEndScPos.x, sightEndScPos.y), IM_COL32(18, 255, 18, 245), 1.5f);
				dl->AddCircleFilled(ImVec2(sightStartScPos.x, sightStartScPos.y), 3, IM_COL32(18, 255, 18, 245));
				dl->AddCircleFilled(ImVec2(sightEndScPos.x, sightEndScPos.y), 3, IM_COL32(18, 255, 18, 245));
			}

		}
		else {		

			// 3D Rect
			dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(bp2Sc.x, bp2Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(bp3Sc.x, bp3Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(bp4Sc.x, bp4Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(bp1Sc.x, bp1Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp1Sc.x, tp1Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp2Sc.x, tp2Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp3Sc.x, tp3Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(tp4Sc.x, tp4Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp1Sc.x, bp1Sc.y), ImVec2(tp1Sc.x, tp1Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp2Sc.x, bp2Sc.y), ImVec2(tp2Sc.x, tp2Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp3Sc.x, bp3Sc.y), ImVec2(tp3Sc.x, tp3Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);
			dl->AddLine(ImVec2(bp4Sc.x, bp4Sc.y), ImVec2(tp4Sc.x, tp4Sc.y), IM_COL32(255, 18, 18, 245), 1.5f);

			// Sight Line
			if (canDrawSight) {
				dl->AddLine(ImVec2(sightStartScPos.x, sightStartScPos.y), ImVec2(sightEndScPos.x, sightEndScPos.y), IM_COL32(255, 18, 18, 245), 1.5f);
				dl->AddCircleFilled(ImVec2(sightStartScPos.x, sightStartScPos.y), 3, IM_COL32(255, 18, 18, 245));
				dl->AddCircleFilled(ImVec2(sightEndScPos.x, sightEndScPos.y), 2.7f, IM_COL32(255, 18, 18, 245));
			}

		}

		

	}

}

Vec3 BoxESP::rotatePointYaw(Vec3 opc, float radius, float angle) {
		
	float rad = (3.14159f / 180) * angle;

	Vec3 res;
	res.x = opc.x + cosf(rad) * radius;
	res.y = opc.y;
	res.z = opc.z + sinf(rad) * radius;

	return res;
}

Vec3 BoxESP::rotatePointPitch(Vec3 opc, float radius, float angle) {

	float rad = (3.14159f / 180) * angle;

	Vec3 res;
	res.x = opc.x;
	res.y = opc.y + sinf(rad) * radius;
	res.z = opc.z;

	return res;
}
