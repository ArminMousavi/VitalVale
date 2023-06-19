#include "PlayOutEnterGame.h"

void UPlayOutEnterGame::ConstructPacket()
{
	SetPacketID(1);
}

FString UPlayOutEnterGame::JSerialize()
{
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember("PacketID", GetPacketID(), doc.GetAllocator());
	doc.AddMember("PlayerID", PlayerID, doc.GetAllocator());
	doc.AddMember("RoomID", RoomID, doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return FString(buffer.GetString());
	
}
