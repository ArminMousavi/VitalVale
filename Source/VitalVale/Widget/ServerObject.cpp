// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "ServerObject.h"


UServerObject::UServerObject(const FString& ServerName, const FString& ServerAddress,int ServerLoad)
{
	this->ServerName = ServerName;
	this->ServerAddress = ServerAddress;
	this->ServerLoad = ServerLoad;
}

UServerObject::UServerObject()
{
	this->ServerName = TEXT("ناشناخته");
	this->ServerAddress = ServerAddress;
	this->ServerLoad = 100;
}
