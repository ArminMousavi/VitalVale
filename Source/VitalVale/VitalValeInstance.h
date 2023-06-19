// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/UObjectGlobals.h"
#include "Network/NetworkManager.h"
#include "VitalValeInstance.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UVitalValeInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UVitalValeInstance(const FObjectInitializer& ObjectInitializer);
	
	void SetNetworkMg(UNetworkManager* UNetMg);
	UNetworkManager* GetNetworkMg();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
	UNetworkManager* NetMg;
	
};
