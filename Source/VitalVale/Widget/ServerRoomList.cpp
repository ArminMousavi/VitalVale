// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "ServerRoomList.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widget.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "../Network/NetworkManager.h"
#include "RoomWidget.h"

void UServerRoomList::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);

			////////////////////////////////////////////////////////////////////
			//                    Multiplayer Things                          //
			////////////////////////////////////////////////////////////////////

			UNetworkManager* NetworkManager = NewObject<UNetworkManager>();

			if (IsValid(NetworkManager))
			{

				NetworkManager->UpdateRoomListInstance(this);
			}
		}
		else return;
	}



}

void UServerRoomList::SetServerName(const FString& InServerName)
{
	if (ServerName)
	{
		ServerName->SetText(FText::FromString(InServerName));
	}
}

void UServerRoomList::SetServerAddress(const FString& InServerAddress)
{
	if (InServerAddress != "")
	{
		this->ServerAddress = InServerAddress;
		UE_LOG(LogTemp, Warning, TEXT("Server Address set to %s"), *InServerAddress);
	}
}

void UServerRoomList::SetGameSessions(rapidjson::Value& InGameSessions)
{

	if (this != nullptr)
	{
		if (!IsInGameThread() && !IsInSlateThread())
		{
			UE_LOG(LogTemp, Error, TEXT("UGameLoading::SetPlayers called from invalid thread!"));
		}

		UWorld* World = GetWorld();
		if (World == nullptr) return;

		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController == nullptr) return;



		this->GameSessions = InGameSessions;
		AsyncTask(ENamedThreads::GameThread, [this, World, PlayerController]() {



			UScrollBox* RoomsBox = Cast<UScrollBox>(WidgetTree->FindWidget(TEXT("RoomsBox")));

			for (rapidjson::SizeType i = 0; i < GameSessions.Size(); i++)
			{
				rapidjson::Value& Session = GameSessions[i];
				assert(Session.IsObject());


				URoomWidget* RoomWidget = CreateWidget<URoomWidget>(PlayerController, LoadClass<URoomWidget>(nullptr, TEXT("/Game/Assets/Widgets/Menu/Child/WBP_RoomWidget.WBP_RoomWidget_C")));

				if (IsValid(RoomsBox) && IsValid(RoomWidget))
				{

					RoomWidget->RoomSetup(ServerAddress, Session["sessionId"].GetInt(), TEXT("بزودی"), TEXT("مبارزه گروهی"), Session["gameMap"].GetString(), TEXT("شروع شده"), Session["currentPlayers"].GetInt(), Session["maxPlayers"].GetInt(), true);

					RoomsBox->AddChild(RoomWidget);

					UE_LOG(LogTemp, Warning, TEXT("%s"), Session["gameMap"].GetString());

				}

			}
			});
	}




}

bool UServerRoomList::Initialize()
{
	if (!Super::Initialize()) return false;

	return true;
}
