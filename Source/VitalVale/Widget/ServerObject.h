// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "ServerObject.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UServerObject : public UObject
{

	GENERATED_BODY()

public:
	UServerObject(const FString& ServerName, const FString& ServerAddress, int ServerLoad);

	UServerObject();
	
private:

	FString ServerName;
	FString ServerAddress;
	int ServerLoad = 0;

public:

	void SetServerName(const FString& InServerName)
	{
		this->ServerName = InServerName;
	}

	FString GetServerName()
	{
		return this->ServerName;
	}

	void SetServerAddress(const FString& InServerAddress)
	{
		this->ServerAddress = InServerAddress;
	}

	FString GetServerAddress()
	{
		return this->ServerAddress;
	}

	void SetServerLoad(int InServerLoad)
	{
		this->ServerLoad = InServerLoad;
	}

	int GetServerLoad()
	{
		return this->ServerLoad;
	}

};
