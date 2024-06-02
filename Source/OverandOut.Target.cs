// 1011Blueprints.

using UnrealBuildTool;
using System.Collections.Generic;

public class OverandOutTarget : TargetRules
{
	public OverandOutTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "OverandOut" } );
	}
}
