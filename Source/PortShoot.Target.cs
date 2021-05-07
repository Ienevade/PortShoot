

using UnrealBuildTool;
using System.Collections.Generic;

public class PortShootTarget : TargetRules
{
	public PortShootTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "PortShoot" } );
	}
}
