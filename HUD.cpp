#include "HUD.h"

HUD::HUD() : AbstractModule("HUD", Category::Render) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &HUD::onRenderOverlay));
}

HUD* HUD::getInstance() {
	static HUD* inst = new HUD();
	return inst;
}

void HUD::onEnabled() {

	this->enabledMods.clear();
}

void HUD::onDisabled() {

	this->enabledMods.clear();
}

void HUD::onRenderOverlay() {
	ToggleCheck;
	// IngameCheck;
	if (ClickGui::getInstance()->getToggle()) return;

	this->enabledMods.clear();
	ModuleManager::getInstance().getModule(true, &(this->enabledMods));
	std::stable_sort(this->enabledMods.begin(), this->enabledMods.end(), EnabledListSorter());

	ImDrawList* dl = ImGui::GetForegroundDrawList();

	static float enabledListX = 0;
	static float enabledListY = 175;
	static float enabledModBgHeight = 25;
	static float enabledModBgSideWidth = 6;
	static float fontScale = 6.5f;
	static float modNameOffsetX = 5;
	static float modNameOffsetY = 4;
	static float modNameFontSize = 15;

/*
#ifdef _DEBUG
	ImGui::Begin("HUD");

	ImGui::SliderFloat("Enabled List X", &enabledListX, 1, Utility::width());
	ImGui::SliderFloat("Enabled List Y", &enabledListY, 1, Utility::height());
	ImGui::SliderFloat("Enabled Mod Background Height", &enabledModBgHeight, 1, 40);
	ImGui::SliderFloat("Enabled Mod Side Width", &enabledModBgSideWidth, 1, 40);
	ImGui::SliderFloat("Font Scale", &fontScale, 1, 50);
	ImGui::SliderFloat("Module Name OffsetX", &modNameOffsetX, 1, 30);
	ImGui::SliderFloat("Module Name OffsetY", &modNameOffsetY, 1, 30);
	ImGui::SliderFloat("Module Name Font Size", &modNameFontSize, 1, 30);

	ImGui::End();
#endif
*/

	// Enabled List
	Block enabledListBlock;
	enabledListBlock.x = enabledListX;
	enabledListBlock.y = enabledListY;
	enabledListBlock.width = 0;
	enabledListBlock.height = 0;

	float curYOffset = 0;
	for (HMOD _Mod : this->enabledMods) {
		AbstractModule* curMod = ToBaseModule(_Mod);
		
		float modNameWidth = Utility::getStringLength(curMod->getName().c_str(), fontScale);
		if (modNameWidth + enabledModBgSideWidth > enabledListBlock.width) enabledListBlock.width = modNameWidth + enabledModBgSideWidth;

		float curModX = enabledListX;
		float curModY = enabledListY + curYOffset;
		dl->AddRectFilled(ImVec2(curModX, curModY), ImVec2(curModX + modNameWidth, curModY + enabledModBgHeight), HanabiColor::EnabledListBackground);
		dl->AddRectFilled(ImVec2(curModX + modNameWidth, curModY), ImVec2(curModX + modNameWidth + enabledModBgSideWidth, curModY + enabledModBgHeight), HanabiColor::EnabledListSmall);
		dl->AddText(Client::defaultFont, modNameFontSize, ImVec2(curModX + modNameOffsetX, curModY + modNameOffsetY), HanabiColor::EnabledListModName, curMod->getName().c_str());

		enabledListBlock.height += enabledModBgHeight;
		curYOffset += enabledModBgHeight;
	}

	if (ClickGui::getInstance()->showBlockBB) Renderer::drawBlockBoundingBox(&enabledListBlock);

}

bool EnabledListSorter::operator()(HMOD m1, HMOD m2) {
	AbstractModule* mod1 = ToBaseModule(m1);
	AbstractModule* mod2 = ToBaseModule(m2);
	return strlen(mod1->getName().c_str()) > strlen(mod2->getName().c_str());
}
