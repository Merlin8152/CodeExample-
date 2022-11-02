// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;


public class PZ_SkillTreeEditor : ModuleRules
{
	public PZ_SkillTreeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;


		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Public")
				// ... add public include paths required here ...
			}
			);
				
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Private")
				// ... add other private include paths required here ...
			}
			);
			
		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"PZ_SkillTree",

				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Kismet", // add to use FWorkflowCentricApplication
				"InputCore", // add to use SListView
				"UnrealEd",
				"AssetTools",
				"GraphEditor",
				"EditorStyle",
				"ToolMenus",
				"ApplicationCore",
				"Projects", // IPluginManager
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
