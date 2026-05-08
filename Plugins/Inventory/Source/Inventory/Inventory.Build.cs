using UnrealBuildTool;

public class Inventory : ModuleRules
{
	public Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
		[
			"GameplayAbilities",
			"UISystem"
		]);
			
		
		PrivateDependencyModuleNames.AddRange(
		[
			"CoreUObject",
			"Engine",
			"Core",
			"EnhancedInput",
			"ModelViewViewModel",
			"UISystem",
			"UMG",
			"CommonUI",
			"GameplayTags",
		]);
	}
}
