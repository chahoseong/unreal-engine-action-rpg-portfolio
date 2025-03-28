// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Swordmaster : ModuleRules
{
	public Swordmaster(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {
			"Swordmaster",
		});
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
            "GameplayAbilities",
			"GameplayTasks",
			"GameplayTags",
            "StructUtils",
			"MotionWarping",
			"AIModule",
            "Niagara",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {
			"SkeletalMerging"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
