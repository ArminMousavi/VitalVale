// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "../PacketBase.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class VITALVALE_API UPlayOutPosRot : public UPacketBase
{
public:
	int PlayerID = 386;
	int RoomID = 15;

	float xpos, ypos, zpos;
	float xrot, yrot, zrot;

	void ConstructPacket(float xp, float yp, float zp, float xr, float yr, float zr);

	FString JSerialize() override;
};
