// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLoading.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UGameLoading : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void MenuSetup();

	UFUNCTION(BlueprintCallable)
	void SetPlayers(const FString& Players);



protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayersText;

};
