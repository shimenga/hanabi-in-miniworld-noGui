#pragma once
#include <vector>
#include "Notification.h"
#include "EventManager.h"
#include "ImGuiHeader.h"
#include "Utility.h"

class NotificationManager {

public:

	static NotificationManager& getInstance();

	void makeNotification(std::string text, Type type);
	void addNotification(Notification n);
	void render();

	void setIcon(IDirect3DTexture9* info, IDirect3DTexture9* err, IDirect3DTexture9* succ, IDirect3DTexture9* warn);

	NotificationManager(const NotificationManager&) = delete;
	NotificationManager(NotificationManager&&) = delete;
	NotificationManager& operator=(NotificationManager&) = delete;

private:

	clock_t cleanInterval;

	IDirect3DTexture9* iconInfo;
	IDirect3DTexture9* iconErr;
	IDirect3DTexture9* iconSucc;
	IDirect3DTexture9* iconWarn;

	float startX;
	float startY;

	std::vector<Notification> notifications;
	TimerUtil cleanTimer;

	void clearNotifications();

	NotificationManager();
	~NotificationManager() = default;

};

