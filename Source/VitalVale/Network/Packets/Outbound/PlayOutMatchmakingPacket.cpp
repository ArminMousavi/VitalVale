// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "PlayOutMatchmakingPacket.h"
#include "Serialization/MemoryWriter.h"

void UPlayOutMatchmakingPacket::ConstructPacket()
{
	SetPacketID(0);
}

void UPlayOutMatchmakingPacket::Serialize(FArchive& Archive)
{
	Archive << PacketID;
	Archive << PlayerID;
}

FString UPlayOutMatchmakingPacket::JSerialize()
{
	return FString();
}

