// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAME3020_OzcanHakan : ModuleRules
{
	public GAME3020_OzcanHakan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "ApplicationCore" });
	}
}
