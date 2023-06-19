// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "GameLoading.h"
#include "Components/TextBlock.h"

void UGameLoading::MenuSetup()
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

bool UGameLoading::Initialize()
{
	if (!Super::Initialize()) return false;

	return true;
}

void UGameLoading::SetPlayers(const FString& Players)
{
	if (!ensureMsgf(this != nullptr, TEXT("UGameLoading::SetPlayers called with null this pointer")))
	{
		return;
	}

	if (!IsInGameThread() && !IsInSlateThread())
	{
		UE_LOG(LogTemp, Error, TEXT("UGameLoading::SetPlayers called from invalid thread!"));
	}

	if (PlayersText)
	{
		AsyncTask(ENamedThreads::GameThread, [this, Players]() {
			PlayersText->SetText(FText::FromString(Players));
		});
	}
}