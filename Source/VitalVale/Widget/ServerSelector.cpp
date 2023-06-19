// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "ServerSelector.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widget.h"
#include "Components/ScrollBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "ServerWidget.h"

void UServerSelector::MenuSetup()
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
		}
		else return;

		UServerObject* ServerObject = NewObject<UServerObject>();
		ServerObject->SetServerName("1");
		ServerObject->SetServerAddress(TEXT("127.0.0.1"));
		Servers.Add(ServerObject);

		UServerObject* ServerObject2 = NewObject<UServerObject>();
		ServerObject2->SetServerName("2");
		Servers.Add(ServerObject2);

		UServerObject* ServerObject3 = NewObject<UServerObject>();
		ServerObject3->SetServerName("3");
		Servers.Add(ServerObject3);

		UServerObject* ServerObject4 = NewObject<UServerObject>();
		ServerObject4->SetServerName("4");
		Servers.Add(ServerObject4);

		UE_LOG(LogTemp, Warning, TEXT("%i"), Servers.Num());


		UScrollBox* ServerScroll = Cast<UScrollBox>(WidgetTree->FindWidget(TEXT("ServerScroll")));

		for (UServerObject* Server : Servers)
		{

			UServerWidget* ServerWidget = CreateWidget<UServerWidget>(PlayerController, LoadClass<UServerWidget>(nullptr, TEXT("/Game/Assets/Widgets/Menu/Child/WBP_ServerWidget.WBP_ServerWidget_C")));
			if (IsValid(ServerWidget) && IsValid(ServerScroll))
			{
				if (!ensureMsgf(this != nullptr, TEXT("Called with null this pointer")))
				{
					return;
				}
				if (Server) {
					ServerWidget->SetServerName(FString::Printf(TEXT("سرور %s"), *Server->GetServerName()));
					ServerWidget->SetServerAddress(*Server->GetServerAddress());

					ServerScroll->AddChild(ServerWidget);

					UE_LOG(LogTemp, Warning, TEXT("ServerWidget is valid."));
				}


			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("ServerWidget or SeverScroll isn't valid."));
			}
		}

	}

}

bool UServerSelector::Initialize()
{
	if (!Super::Initialize()) return false;

	return true;
}
