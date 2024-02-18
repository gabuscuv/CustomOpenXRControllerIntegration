// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class CustomOpenXRControllerIntegration : ModuleRules
{
	public CustomOpenXRControllerIntegration(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		string PluginsPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../.."));
		bool bMetaXRPlugin = Directory.Exists(Path.Combine(PluginsPath, "MetaXR"));
		if(bMetaXRPlugin)
		{
			System.Console.WriteLine("[CustomOpenXRControllerIntegration] Detected MetaXR Plugin, Enabling Extensions");
		}
		
		PublicDefinitions.Add("MetaXRExtension="+ (bMetaXRPlugin ? "1" : "0"));

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"XRBase",
				"OpenXRExpansionPlugin",
				"VRExpansionPlugin",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
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
