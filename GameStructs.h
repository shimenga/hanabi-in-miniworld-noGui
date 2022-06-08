#pragma once
#include <Windows.h>
#include "Offsets.h"

using Address = unsigned long;
using Pointer = unsigned long;

namespace SDK {

	constexpr int POINTTO_AIR = 0;
	constexpr int POINTTO_BLOCK = 1;
	constexpr int POINTTO_ENTITY = 2;

	constexpr int MODE_CREATIVE = 1;
	constexpr int MODE_ULTIMATE = 2;
	constexpr int MODE_SURVIVE = 3;
	constexpr int MODE_EDIT = 4;
	constexpr int MODE_FUN = 5;

	constexpr int TEAM_NONE = 0;
	constexpr int TEAM_RED = 1;
	constexpr int TEAM_BLUE = 2;
	constexpr int TEAM_GREEN = 3;
	constexpr int TEAM_YELLOW = 4;
	constexpr int TEAM_ORANGE = 5;
	constexpr int TEAM_PURPLE = 6;

	class World
	{
	public:
		char pad_0000[540]; //0x0000
		class WorldManager* worldManager; //0x021C
		char pad_0220[17664]; //0x0220
		class PlayerList_Level1* playerList_Level1; //0x4720
	}; //Size: 0x4724

	class WorldManager
	{
	public:
		char pad_0000[208]; //0x0000
		int mode; //0x00D0
	}; //Size: 0x00D4

	class ClientPlayer
	{
	public:
		char pad_0000[1168]; //0x0000
		class ActorBody* actorBody; //0x0490
		char pad_0494[24]; //0x0494
		int flyState; //0x04AC
		char pad_04B0[20]; //0x04B0
		class PlayerLocoMotion* playerLocoMotion; //0x04C4
		char pad_04C8[4]; //0x04C8
		class PlayerAttribuLua* playerAttribuLua; //0x04CC
		char pad_04D0[192]; //0x04D0
		class PlayerHpProgressComponent* playerHpProgressComponent; //0x0590
		class PlayerTeamComponent* playerTeamComponent; //0x0594
		class PlayerAttackingTargetComponent* playerAttackingTargetComponent; //0x0598
		char pad_059C[360]; //0x059C
		char name[8]; //0x0704
		char pad_070C[720]; //0x070C
		class GameCamera* gameCamera; //0x09DC
		char pad_09E0[100]; //0x09E0
		int crossPointTo; //0x0A44
	}; //Size: 0x0A48

	class PlayerList_Level1
	{
	public:
		char pad_0000[12]; //0x0000
		unsigned long* playerList; //0x000C
		char pad_0010[12]; //0x0010
		int length; //0x001C
	}; //Size: 0x0020

	class ActorBody
	{
	public:
		char pad_0000[528]; //0x0000
		class Entity* entity; //0x0210
	}; //Size: 0x0214

	class Entity
	{
	public:
		char pad_0000[108]; //0x0000
		float posX; //0x006C
		float posY; //0x0070
		float posZ; //0x0074
	}; //Size: 0x0078

	class PlayerAttribuLua
	{
	public:
		char pad_0000[460]; //0x0000
		float currentHealth; //0x01CC
		char pad_01D0[4]; //0x01D0
		float maxHealth; //0x01D4
		char pad_01D8[36]; //0x01D8
		float walkingSpeed; //0x01FC
		float runningSpeed; //0x0200
		float sneakingSpeed; //0x0204
		float swimmingSpeed; //0x0208
		float jumpHeight; //0x020C
		char pad_0210[24]; //0x0210
		float oxygen; //0x0228
		char pad_022C[108]; //0x022C
		float currentHunger; //0x0298
		char pad_029C[8]; //0x029C
		float maxHunger; //0x02A4
	}; //Size: 0x02A8

	class GameCamera
	{
	public:
		char pad_0000[4]; //0x0000
		float yaw; //0x0004
		float pitch; //0x0008
		char pad_000C[44]; //0x000C
		class Camera* camera; //0x0038
		char pad_003C[48]; //0x003C
		float fov; //0x006C
	}; //Size: 0x0070

	class Camera
	{
	public:
		char pad_0000[108]; //0x0000
		float posX; //0x006C
		float posY; //0x0070
		float posZ; //0x0074
	}; //Size: 0x0078

	class UIRenderer
	{
	public:
		char pad_0000[572]; //0x0000
		class Matrix_Level1* matrixLevel1; //0x023C
	}; //Size: 0x0240

	class Matrix_Level1
	{
	public:
		char pad_0000[2252]; //0x0000
		class Matrix_Level2* matrixLevel2; //0x08CC
	}; //Size: 0x08D0

	class Matrix_Level2
	{
	public:
		char pad_0000[56]; //0x0000
		float matrix[4][4]; //0x0038
		float camPosX; //0x0078
		float camPosY; //0x007C
		float camPosZ; //0x0080
	}; //Size: 0x0084

	class PlayerLocoMotion
	{
	public:
		char pad_0000[12]; //0x0000
		float yaw; //0x000C
		float pitch; //0x0010
		char pad_0014[136]; //0x0014
		int onGround; //0x009C
		char pad_00A0[80]; //0x00A0
		int phase; //0x00F0
	}; //Size: 0x00F4

	class PlayerTeamComponent
	{
	public:
		char pad_0000[8]; //0x0000
		int team; //0x0008
	}; //Size: 0x000C

	class PlayerAttackingTargetComponent
	{
	public:
		char pad_0000[4]; //0x0000
	}; //Size: 0x0004

	class PlayerHpProgressComponent
	{
	public:
		char pad_0000[32]; //0x0000
		int team; //0x0020
	}; //Size: 0x0024

	World* getWorld();
	UIRenderer* getUIRenderer();

}
