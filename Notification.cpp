#include "Notification.h"

Notification::Notification(std::string message, Type msgType) : text(message), type(msgType), start(clock()), end(3500) {}

void Notification::render(IDirect3DTexture9*  icon, int index, float x, float y) {
	 
	ImDrawList* dl = ImGui::GetForegroundDrawList();

	float yOffset = index * 70;

	float bgX = x;
	float bgY = y - yOffset;
	float bgX1 = x + 250;
	float bgY1 = y + 50 - yOffset;

	float iconX = x + 15.5f;
	float iconY = y - yOffset + 13;
	float iconX1 = x + 41;
	float iconY1 = y - yOffset + 38.5f;

	float titleX = x + 55;
	float titleY = y + 17 - yOffset;

	dl->AddRectFilled(ImVec2(bgX, bgY), ImVec2(bgX1, bgY1), HanabiColor::NotificationBackground, 5);
	dl->AddImage(icon, ImVec2(iconX, iconY), ImVec2(iconX1, iconY1));
	dl->AddText(nullptr, 15, ImVec2(titleX, titleY), HanabiColor::NotificationTitle, this->text.c_str());
}

clock_t Notification::getTime() {
	return clock() - this->start;
}

bool Notification::isRendering() {
	return this->getTime() <= this->end;
}

Type Notification::getType() {
	return this->type;
}

std::string Notification::getText() {
	return this->text;
}
