// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerWidget.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UServerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetServerName(const FString& InServerName);

	void SetServerAddress(const FString& InServerAddress);

protected:

	virtual bool Initialize() override;

private:

	FString ServerName;

	FString ServerAddress;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton;

	UFUNCTION()
	void OnServerButtonClicked();
	
};
