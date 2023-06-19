// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void RoomSetup(
		const FString& InServerAddress, int InSessionID, const FString& InGameName, const FString& InGameType, const FString& InGameMap, const FString& TextGameStatus, int InCurrentPlayers, int InMaxPlayers, bool InIsStarted);
protected:

	virtual bool Initialize() override;

private:

	FString ServerAddress;
	int GameID;
	FString GameName;
	FString GameType;
	FString GameMap;
	int GameCurrentPlayers;
	int GameMaxPlayers;
	bool GameIsStarted;

private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SessionID;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionMap;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionPlayers;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SessionStatus;

	UPROPERTY(meta = (BindWidget))
	class UButton* SessionButton;

private:

	UFUNCTION()
	void OnRoomClicked();


};