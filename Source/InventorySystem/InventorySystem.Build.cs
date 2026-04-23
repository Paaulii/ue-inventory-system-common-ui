using UnrealBuildTool;

public class InventorySystem : ModuleRules
{
	public InventorySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivateDependencyModuleNames.AddRange(
		[
			"Core",
			"CoreUObject",
			"GameplayTags",
			"EnhancedInput",
			"Inventory",
			"UISystem",
		]);
	}
}