using UnrealBuildTool;

public class UISystem : ModuleRules
{
	public UISystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
		[
			"Core",
			"UMG",
			"GameplayTags",
			"CommonUI",
			"ModelViewViewModel",
		]);

		PrivateDependencyModuleNames.AddRange(
		[
			"CoreUObject",
			"Engine",
			"Slate",
		]);
	}
}
