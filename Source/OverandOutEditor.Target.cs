// 1011Blueprints.

using UnrealBuildTool;
using System.Collections.Generic;

public class OverandOutEditorTarget : TargetRules
{
	public OverandOutEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "OverandOut" } );
	}
}
