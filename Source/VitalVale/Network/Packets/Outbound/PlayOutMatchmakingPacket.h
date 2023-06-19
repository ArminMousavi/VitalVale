// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "../PacketBase.h"
#include "Serialization/Archive.h"

/**
 * 
 */
class VITALVALE_API UPlayOutMatchmakingPacket : public UPacketBase
{

public:
	
	int PlayerID = 32323;
	int PacketID = 2;

	void ConstructPacket();

	void Serialize(FArchive& Archive);

    FString JSerialize() override;
	
};
