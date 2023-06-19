// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "ServerWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ServerRoomList.h"


bool UServerWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (ServerButton)
	{
		ServerButton->OnClicked.AddDynamic(this, &UServerWidget::OnServerButtonClicked);
	}

	return true;
}

void UServerWidget::OnServerButtonClicked()
{
	UWorld* World = GetWorld();

	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!PlayerController) return;

	UServerRoomList* ServerRoomList = CreateWidget<UServerRoomList>(PlayerController, LoadClass<UServerRoomList>(nullptr, TEXT("/Game/Assets/Widgets/Menu/WBP_ServerRoomList.WBP_ServerRoomList_C")));

	if (IsValid(ServerRoomList))
	{
		ServerRoomList->MenuSetup();

		ServerRoomList->SetServerName(this->ServerName);
		ServerRoomList->SetServerAddress(this->ServerAddress);
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Purple,
				FString(TEXT("ServerSelector is nullptr."))
			);
		}
	}
}

void UServerWidget::SetServerName(const FString& InServerName)
{
	if (!ensureMsgf(this != nullptr, TEXT("UServerWidget::SetServerName called with null this pointer")))
	{
		return;
	}

	if (ServerNameText)
	{
		ServerNameText->SetText(FText::FromString(InServerName));
		this->ServerName = InServerName;
	}
}

void UServerWidget::SetServerAddress(const FString& InServerAddress)
{
	this->ServerAddress = InServerAddress;
}
