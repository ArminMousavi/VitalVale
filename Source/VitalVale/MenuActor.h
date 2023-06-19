// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MenuActor.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API AMenuActor : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	
	UFUNCTION(BlueprintCallable, Category = LevelBP)
	void BeginWorldProcessor();
	
};
