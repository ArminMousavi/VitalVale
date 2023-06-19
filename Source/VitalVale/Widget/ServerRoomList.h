// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "rapidjson/document.h"
#include "ServerRoomList.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UServerRoomList : public UUserWidget
{
	GENERATED_BODY()

public:

	void MenuSetup();

	void SetServerName(const FString& InServerName);

	void SetServerAddress(const FString& InServerAddress);

	void SetGameSessions(rapidjson::Value& InGameSessions);

protected:

	virtual bool Initialize() override;

private:

	FString ServerAddress;

	rapidjson::Value GameSessions;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;
	
};
