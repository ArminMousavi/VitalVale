// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "GameNetHandler.h"
#include "NetworkManager.h"
#include "rapidjson/istreamwrapper.h"
#include "Serialization/ArrayWriter.h"
#include "rapidjson/document.h"

UGameNetHandler::UGameNetHandler()
{
	UE_LOG(LogTemp, Warning, TEXT("GameNetHandler Initialized."));
}

UGameNetHandler::~UGameNetHandler()
{

}




//
// Called when a Packet has been received from server.
// 
// PacketID -> ID of the received Packet, indicates the type of packet.
// DeserializedPacket -> Deserialized Packet data.
// ReceivedData -> Raw JSONString of Received Packet Data.
//
void UGameNetHandler::ProcessPacket(int PacketID, const FString& RecivedData)
{

	UE_LOG(LogTemp, Warning, TEXT("%s"), *RecivedData);
	rapidjson::Document doc;
	doc.Parse(TCHAR_TO_UTF8(*RecivedData));
	switch (PacketID)
	{
	case 1:
		// Packet EnterGame Request();
		UE_LOG(LogTemp, Warning, TEXT("You can join: %s"), doc["canJoin"].GetBool() ? TEXT("yes") : TEXT("NO"));
		break;
	default:
		break;
	}

}

//
// Set the Network Manager Instance
// 
// networkManager -> the Instance of Network Manager class.
// 
void UGameNetHandler::SetNetworkManager(UNetworkManager* networkManager)
{
	this->NetworkManager = networkManager;
}

UNetworkManager* UGameNetHandler::GetNetworkManager()
{
	return this->NetworkManager;
}
