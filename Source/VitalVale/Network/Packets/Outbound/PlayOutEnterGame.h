#pragma once

#include "CoreMinimal.h"
#include "../PacketBase.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class VITALVALE_API UPlayOutEnterGame : public UPacketBase
{
public:
	int PlayerID = 231;
	int RoomID = 0;

	void ConstructPacket();

	FString JSerialize() override;
};
