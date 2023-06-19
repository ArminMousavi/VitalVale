// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "UObject/NoExportTypes.h"
#include "Serialization/ArrayWriter.h"
#include "../Widget/ServerRoomList.h"
#include "GameNetHandler.h"
#include "NetworkManager.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UNetworkManager : public UObject
{
	GENERATED_BODY()

public:
	UNetworkManager();
	~UNetworkManager();


	void UpdateRoomListInstance(UServerRoomList* InServerRoomList);

	void UpdateMenuRooms(rapidjson::Value& InGameSessions);

	void UDPSocketListener();

	void SendPacket(const FString& PacketData);

	UGameNetHandler* GetGameNetHandler();

	FSocket* Socket;
	class UGameNetHandler* NetHandler;

private:
	UWorld* World;
	UServerRoomList* ServerRoomList;
};
