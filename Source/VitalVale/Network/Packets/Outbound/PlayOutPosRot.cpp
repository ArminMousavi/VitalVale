// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "PlayOutPosRot.h"


void UPlayOutPosRot::ConstructPacket(float xp, float yp, float zp, float xr, float yr, float zr)
{
	SetPacketID(10);

	// Set the position values
	this->xpos = xp;
	this->ypos = yp;
	this->zpos = zp;

	// Set the rotation values
	this->xrot = xr;
	this->yrot = yr;
	this->zrot = zr;
}

FString UPlayOutPosRot::JSerialize()
{
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember("PacketID", GetPacketID(), doc.GetAllocator());
	doc.AddMember("PlayerID", PlayerID, doc.GetAllocator());
	doc.AddMember("RoomID", RoomID, doc.GetAllocator());
	doc.AddMember("XPos", xpos, doc.GetAllocator());
	doc.AddMember("YPos", ypos, doc.GetAllocator());
	doc.AddMember("ZPos", zpos, doc.GetAllocator());
	doc.AddMember("XRot", xrot, doc.GetAllocator());
	doc.AddMember("YRot", yrot, doc.GetAllocator());
	doc.AddMember("ZRot", zrot, doc.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return FString(buffer.GetString());
}
