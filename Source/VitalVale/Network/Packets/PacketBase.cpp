// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "PacketBase.h"

void UPacketBase::SetPacketID(int pId)
{
	this->PacketID = pId;
}

int UPacketBase::GetPacketID()
{
	return this->PacketID;
}

FString UPacketBase::JSerialize()
{
	return FString();
}
