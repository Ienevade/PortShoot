

using UnrealBuildTool;

public class PortShoot : ModuleRules
{
	public PortShoot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] { });


		PublicIncludePaths.AddRange(new string[]
			{
				"PortShoot/Public/Player",
				"PortShoot/Public/Components",
				"PortShoot/Public/Dev",
				"PortShoot/Public/Weapon",
				"PortShoot/Public/UI"});
	// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
