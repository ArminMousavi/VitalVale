// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "MenuActor.h"
#include "Widget/MainMenu.h"

void AMenuActor::BeginWorldProcessor()
{
	UWorld* World = GetWorld();
	
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			UMainMenu* MainMenu = CreateWidget<UMainMenu>(PlayerController, LoadClass<UMainMenu>(nullptr, TEXT("/Game/Assets/Widgets/Menu/WBP_MainMenu.WBP_MainMenu_C")));

			if (IsValid(MainMenu))
			{
				MainMenu->MenuSetup();
			}
		}
	}
}
