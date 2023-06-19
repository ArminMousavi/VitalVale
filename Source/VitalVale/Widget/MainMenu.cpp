// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Layout/Margin.h"
#include "../Network/NetworkManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"

void UMainMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController) {
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}


}

bool UMainMenu::Initialize()
{

	if (!Super::Initialize()) return false;

	if (StartButton && SettingsButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartButtonClicked);
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenu::OnSettingsButtonClicked);
	}

	return true;
}

void UMainMenu::OnStartButtonClicked()
{
	StartButton->SetIsEnabled(false);

	if (StartButton)
	{
		this->RemoveFromViewport();
	}

	UWorld* World = GetWorld();

	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!PlayerController) return;

	ServerSelector = CreateWidget<UServerSelector>(PlayerController, LoadClass<UServerSelector>(nullptr, TEXT("/Game/Assets/Widgets/Menu/WBP_ServerSelector.WBP_ServerSelector_C")));

	if (IsValid(ServerSelector))
	{
		ServerSelector->MenuSetup();
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

/*void UMainMenu::OnStartButtonClicked()
{
	UNetworkManager* NetworkManager = NewObject<UNetworkManager>();


	GameLoadingW = CreateWidget<UGameLoading>(PlayerController, LoadClass<UGameLoading>(nullptr, TEXT("/Game/Assets/Widgets/Menu/WBP_LoadingGame.WBP_LoadingGame_C")));
	if (IsValid(GameLoadingW)) {
		GameLoadingW->MenuSetup();

		NetworkManager->UpdateGameLoadingInstance(GameLoadingW);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Purple,
				GetWorld()->GetMapName()
			);
		}
	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Purple,
				FString(TEXT("GameLoadingW is nullptr BOOOOOOOOOOIIIIIIIIIIII"))
			);
		}
	}
	
}*/

void UMainMenu::OnSettingsButtonClicked()
{

}

