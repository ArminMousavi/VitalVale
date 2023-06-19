// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerSelector.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

	UPROPERTY(EditAnywhere)
	UServerSelector* ServerSelector;


protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	UFUNCTION()
	void OnStartButtonClicked();
	
	UFUNCTION()
	void OnSettingsButtonClicked();
};
