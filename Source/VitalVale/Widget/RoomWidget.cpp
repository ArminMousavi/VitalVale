// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "RoomWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../Network/NetworkManager.h"
#include "../Network/Packets/Outbound/PlayOutEnterGame.h"
#include "../Network/GameNetHandler.h"
#include "../VitalValeInstance.h"
#include "Kismet/GameplayStatics.h"




//
// Called when creating the Widget.
//
void URoomWidget::RoomSetup(const FString& InServerAddress, int InSessionID, const FString& InGameName, const FString& InGameType, const FString& InGameMap, const FString& TextGameStatus, int InCurrentPlayers, int InMaxPlayers, bool InIsStarted)
{
	if (SessionID)
	{
		ServerAddress = InServerAddress;
		GameID = InSessionID;
		GameName = InGameName;
		GameType = InGameType;
		GameMap = InGameMap;
		GameCurrentPlayers = InCurrentPlayers;
		GameMaxPlayers = InMaxPlayers;
		GameIsStarted = InIsStarted;

		// Setting TextBlocks
		SessionID->SetText(FText::FromString(FString::FromInt(GameID)));
		SessionName->SetText(FText::FromString(GameName));
		SessionType->SetText(FText::FromString(GameType));
		SessionMap->SetText(FText::FromString(GameMap));
		SessionPlayers->SetText(FText::FromString(FString::Printf(TEXT("%i / %i"), GameCurrentPlayers, GameMaxPlayers)));
		SessionStatus->SetText(FText::FromString(TextGameStatus));
	}
}

void URoomWidget::OnRoomClicked()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
			15.f,
			FColor::Red,
			TEXT("Room Clicked."));
	}

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr) return;

	SetVisibility(ESlateVisibility::Hidden);
	RemoveFromViewport();
	bIsFocusable = false;

	if (PlayerController) {
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(false);
	}

	UNetworkManager* NetworkManager = NewObject<UNetworkManager>();

	UGameNetHandler* NetHandler = NewObject<UGameNetHandler>();

	UVitalValeInstance* VitalValeInstance = Cast<UVitalValeInstance>(GetGameInstance());
	if (VitalValeInstance)
	{
		VitalValeInstance->SetNetworkMg(NetworkManager);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VitalVale Instance is nullptr"));
	}

	NetHandler->SetNetworkManager(NetworkManager);
	
	UPlayOutEnterGame* PlayOutEnterGame = new UPlayOutEnterGame();
	PlayOutEnterGame->ConstructPacket();
	PlayOutEnterGame->RoomID = this->GameID;
	NetHandler->NetworkManager->SendPacket(PlayOutEnterGame->JSerialize());
	delete PlayOutEnterGame;

	UGameplayStatics::OpenLevel(World, "Lobby");


}

bool URoomWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (SessionButton)
	{
		SessionButton->OnClicked.AddDynamic(this, &URoomWidget::OnRoomClicked);
	}

	return true;
}
