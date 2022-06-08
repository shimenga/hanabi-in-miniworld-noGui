#include "AutoClicker.h"

AutoClicker::AutoClicker() : AbstractModule("AutoClicker", Category::Combat) {

	EventManager::getInstance().reg(Event::EventRenderOverlay, MakeHandler(this, &AutoClicker::onRenderOverlay));
}

AutoClicker* AutoClicker::getInstance() {
	static AutoClicker* inst = new AutoClicker();
	return inst;
}

void AutoClicker::onEnabled() {
	this->cpsTimer.reset();
}

void AutoClicker::onDisabled() {
	
}

void AutoClicker::onRenderOverlay() {
	ToggleCheck;
	IngameCheck;
	if (ClickGui::getInstance()->getToggle()) return;
	if (GetForegroundWindow() != Client::wndGame) return;

#ifdef _DEBUG
	ImGui::Begin("AutoClicker");

	ImGui::SliderInt("CPS", &(this->cps), 0, 15);

	ImGui::End();
#endif

	if (Client::rendererIO->MouseDownDuration[ImGuiMouseButton_Middle] > 0) {
	
		if (this->cpsTimer.elapsed(1000 / this->cps)) {
			Simulator::mlclick(20);
			this->cpsTimer.reset();
		}

	}

}
