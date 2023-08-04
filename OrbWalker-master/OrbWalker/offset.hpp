#pragma once

#include <cstdint>

struct Offset {
	uintptr_t oGameTime;
	uintptr_t oLocalPlayer;
	uintptr_t oViewProjMatrices;
	uintptr_t oHeroList;
	uintptr_t oTurretList;
	//uintptr_t oInhibitorList;
	uintptr_t oMinionList;
	uintptr_t oChatClient;
	uintptr_t oHudInstance;

	uintptr_t oPrintChat;
	uintptr_t oIssueOrder;
	uintptr_t oAttackDelay;
	uintptr_t oAttackCastDelay;
	uintptr_t oIsAlive;
	uintptr_t oBonusRadius;
};

extern Offset offset;
void InitOffset();