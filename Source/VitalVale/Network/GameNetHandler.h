// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "GameNetHandler.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UGameNetHandler : public UObject
{
	GENERATED_BODY()

public:

	class UNetworkManager* NetworkManager;

public:
	UGameNetHandler();
	~UGameNetHandler();

	void ProcessPacket(int PacketID, const FString& RecivedData);

	void SetNetworkManager(UNetworkManager* networkManager);
	UNetworkManager* GetNetworkManager();


};
