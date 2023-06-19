// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "VitalValeInstance.h"


UVitalValeInstance::UVitalValeInstance(const FObjectInitializer& ObjectInitializer)
{
	NetMg = nullptr;
}

void UVitalValeInstance::SetNetworkMg(UNetworkManager* UNetMg)
{
	this->NetMg = UNetMg;
}

UNetworkManager* UVitalValeInstance::GetNetworkMg()
{
	if (NetMg != nullptr) return NetMg;
	else return nullptr;
}
