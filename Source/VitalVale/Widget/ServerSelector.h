 // Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerObject.h"
#include "ServerSelector.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UServerSelector : public UUserWidget
{
	GENERATED_BODY()

public:



public:

	void MenuSetup();

protected:

	virtual bool Initialize() override;

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<UServerObject*> Servers;
	
};
