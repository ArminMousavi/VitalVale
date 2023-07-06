// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class VitalVale : ModuleRules
{
	public VitalVale(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Sockets", "Networking", "UMG", "Slate", "SlateCore" });

        
        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.Add("ThirdParty/rapidjson/include");

        PublicIncludePaths.Add("C:\\Users\\Frixy\\Documents\\Kharazmi\\VitalVale\\Source\\ThirdParty\\include");

        //PublicAdditionalLibraries.Add("ThirdParty/capnproto/src/capnp/Debug/capnp.lib");
        PublicAdditionalLibraries.Add("C:\\Users\\Frixy\\Documents\\Kharazmi\\VitalVale\\Source\\ThirdParty\\lib\\flatbuffers.lib");
        //PublicAdditionalLibraries.Add("C:\\Users\\Frixy\\Documents\\Unreal Projects\\VitalVale\\Source\\ThirdParty\\lib\\libprotobuf.lib");
        //PublicAdditionalLibraries.Add("C:\\Users\\Frixy\\Documents\\Unreal Projects\\VitalVale\\Source\\ThirdParty\\capnproto\\src\\kj\\Debug\\kj-async.lib");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
