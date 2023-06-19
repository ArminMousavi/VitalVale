// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class VITALVALE_API UPacketBase
{

public:

	void SetPacketID(int pId);
	int GetPacketID();

	virtual FString JSerialize() = 0;

private:

	int PacketID = 0;
	
};
