// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Packets/Outbound/PlayOutMatchmakingPacket.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "HAL/Runnable.h"
#include "../Widget/GameLoading.h"
#include "NetworkManager.h"



class FPacketPipeline : public FRunnable
{

public:
	FPacketPipeline(FSocket* InSocket, UNetworkManager* InNetManager) : Socket(InSocket), NetManager(InNetManager)
	{
		Thread = FRunnableThread::Create(this, TEXT("PacketPipelineThread"));
	}

	~FPacketPipeline()
	{
		if (Thread)
		{
			if (Socket != nullptr)
			{
				ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
				Socket = nullptr;
			}
			Thread->Kill(true);
			Thread = nullptr;
			delete Thread;
		}
	}

	virtual bool Init() override
	{
		return true;
	}

	virtual uint32 Run() override
	{
		while (Socket)
		{
				uint32 Size;
				if (Socket->HasPendingData(Size) != NULL && Socket->HasPendingData(Size))
				{
					TArray<uint8> Data;
					Data.SetNumUninitialized(Size);
					int32 BytesRead;
					Socket->Recv(Data.GetData(), Size, BytesRead);
					if (BytesRead > 0)
					{
						UE_LOG(LogTemp, Warning, TEXT("Got Data"));


						
						/*
						PlayOutRoomList RoomListPacket;
						bool bPacketParsed = RoomListPacket.ParseFromArray(Data.GetData(), Data.Num());
						if (bPacketParsed)
						{
							
							UE_LOG(LogTemp, Warning, TEXT("Parsed Packet RoomList: %i"), RoomListPacket.packetid);
						}
						else {
							UE_LOG(LogTemp, Warning, TEXT("Failed to parse packet."));

						}*/
						// Process the received packet data here
						/*FString ReceivedData = FString(UTF8_TO_TCHAR((char*)Data.GetData()));

						rapidjson::Document doc;
						doc.Parse(TCHAR_TO_UTF8(*ReceivedData));

						int PacketID = doc["packetID"].GetInt();


						switch (PacketID)
						{
						case 0:
							UE_LOG(LogTemp, Warning, TEXT("Received Packet %i With SessionID of %i"), PacketID, doc["sessionId"].GetInt());


							if (doc.IsObject())
							{
								//
								// Parsing was successful.
								//

								rapidjson::Value& GameSessions = doc["gameSessions"];
								assert(GameSessions.IsArray());

								if (NetManager)
								{
									NetManager->UpdateMenuRooms(GameSessions);
								}

								/*for (rapidjson::SizeType i = 0; i < GameSessions.Size(); i++)
								{
									rapidjson::Value& Session = GameSessions[i];
									assert(Session.IsObject());


									UE_LOG(LogTemp, Warning, TEXT("Receive: %i %i"), Session["sessionId"].GetInt(), Session["maxPlayers"].GetInt());

								}
							}


							UE_LOG(LogTemp, Warning, TEXT("Received packet matchmaking data: %s"), *ReceivedData);

							break;
						default:
							if (NetManager != nullptr)
								NetManager->GetGameNetHandler()->ProcessPacket(PacketID, ReceivedData);

							break;
						}*/

					}
				}

			FPlatformProcess::Sleep(0.01f);
		}

		return 0;
	}

	virtual void Stop() override
	{
	}
public:

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "PacketReceiveEvent"))
	void PacketReceiveEvent(const FString& event_data);

private:

	UPROPERTY()
	FSocket* Socket;

	UPROPERTY()
	FRunnableThread* Thread;

	UPROPERTY()
	UNetworkManager* NetManager;

};
