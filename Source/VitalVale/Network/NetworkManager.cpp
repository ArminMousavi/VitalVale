
// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "NetworkManager.h"
#include "Templates/SharedPointer.h"
#include "Misc/CString.h"
#include "HAL/Runnable.h"
#include "PacketPipeline.h"
#include "Components/WidgetComponent.h"
#include "GameNetHandler.h"
#include "Packets/PacketBase.h"
#include "HAL/UnrealMemory.h"
#include "Serialization/BufferArchive.h"
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/flexbuffers.h>

UNetworkManager::UNetworkManager()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Network Manager Initialized."));
	}

	// Create a UDP socket
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("MySocket"), true);

	// Connect to the server
	FString Address = TEXT("127.0.0.1");
	int32 Port = 57612;

	FIPv4Address IP;
	FIPv4Address::Parse(Address, IP);
	TSharedPtr<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	RemoteAddress->SetIp(IP.Value);
	RemoteAddress->SetPort(Port);
	Socket->Connect(*RemoteAddress);

	// Listen to UDP Packets
	if (Socket != nullptr) {
		flexbuffers::Builder fbb;
		fbb.Vector([&]() {
			fbb.Int(0);
			fbb.Int(1402);
		});

		fbb.Finish();

		const std::vector<uint8_t>& serializedData = fbb.GetBuffer();

		int32 bytesSent = 0;

		if (Socket->Send(serializedData.data(), serializedData.size(), bytesSent))
		{
			if (bytesSent > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Bytes Sent to Server: %i"), bytesSent);
			}
		}

/*		PlayOutRoomList* Packet;
		Packet->set_id(12);
		Packet->set_id(14);

		std::string Serialized;
		Packet->SerializeToString(&Serialized);


		int32 SentBytes = 0;
		if (Socket->Send(reinterpret_cast<const uint8*>(Serialized.c_str()), Serialized.size(), SentBytes))
		{
			if (SentBytes > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Bytes Sent to Server: %i"), SentBytes);
			}
		}

		delete &Packet;*/
		

		/*TArray<uint8> OutCompressedData;

		TArray<uint8> SerializedData;
		FMemoryWriter MemoryWriter(SerializedData);
		Packet->Serialize(MemoryWriter);

		const int32 CompressedBufferSize = LZ4_compressBound(SerializedData.Num());
		OutCompressedData.SetNumUninitialized(CompressedBufferSize);
		int32 CompressedSize = LZ4_compress_HC(reinterpret_cast<const char*>(SerializedData.GetData()), reinterpret_cast<char*>(OutCompressedData.GetData()), SerializedData.Num(), CompressedBufferSize, LZ4HC_CLEVEL_DEFAULT);

		if (CompressedSize > 0)
		{
			OutCompressedData.SetNum(CompressedSize);
			UE_LOG(LogTemp, Warning, TEXT("Packet Compression Successfull."));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Packet Compression Unsuccessfull."));
		}

		int32 BytesSent = 0;
		int32 TotalBytesToSend = OutCompressedData.Num();
		const int32 BufferSize = 1024;
		while (BytesSent < TotalBytesToSend)
		{
			int32 BytesLeft = TotalBytesToSend - BytesSent;
			int32 BytesToSend = FMath::Min(BytesLeft, BufferSize);
			if (Socket->Send(reinterpret_cast<const uint8*>(OutCompressedData.GetData()), BytesToSend, BytesSent))
			{
				BytesSent += BytesToSend;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Sending Packet Failed."));

			}

		}

		UE_LOG(LogTemp, Warning, TEXT("Bytes Sent to Server: %i"), BytesSent);*/
		


		/*		PacketMatchmaking packet;
				packet.set_packetid(0);
				packet.set_playerid(1386);

				std::string serialized;
				packet.SerializeToString(&serialized);

				int32 SentBytes;
				Socket->Send(reinterpret_cast<const uint8*>(serialized.c_str()), serialized.size(), SentBytes); // Send the prefixed data
				//UE_LOG(LogTemp, Warning, TEXT("Sent %i bytes to the Server."), SentBytes);
				//delete &packet;

				UDPSocketListener();
				UE_LOG(LogTemp, Warning, TEXT("Socket isn't nullptr."));
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Sock is nullptr"));
			}	*/
	}
}

void UNetworkManager::SendPacket(const FString& PacketData)
{
	if (Socket != nullptr)
	{
		const char* data = TCHAR_TO_UTF8(*PacketData);
		int32 DataSize = FCString::Strlen(ANSI_TO_TCHAR(data));;

		int32 Length = FMath::Min(DataSize, 2048 - 4); // MAX_PACKET_LENGTH is the maximum allowed packet length, excluding the length field
		char* Buffer = new char[Length + 4];
		*(int32*)Buffer = Length; // Write the length to the first 4 bytes

		FMemory::Memcpy(Buffer + 4, data, Length); // Copy the data to the remaining bytes
		int32 SentBytes;
		Socket->Send((uint8*)Buffer, Length + 4, SentBytes); // Send the prefixed data
		delete[] Buffer; // Free the buffer
		UE_LOG(LogTemp, Warning, TEXT("DataSize : %i"), DataSize);



	}
}

UNetworkManager::~UNetworkManager()
{
}


void UNetworkManager::UpdateRoomListInstance(UServerRoomList* InServerRoomList)
{
	this->ServerRoomList = InServerRoomList;
}

void UNetworkManager::UpdateMenuRooms(rapidjson::Value& InGameSessions)
{
	this->ServerRoomList->SetGameSessions(InGameSessions);
}

void UNetworkManager::UDPSocketListener()
{
	if (!Socket) return;

	FRunnableThread* Thread = FRunnableThread::Create(new FPacketPipeline(Socket, this), TEXT("PacketPipelineThread"));
}



UGameNetHandler* UNetworkManager::GetGameNetHandler()
{
	return this->NetHandler;
}




