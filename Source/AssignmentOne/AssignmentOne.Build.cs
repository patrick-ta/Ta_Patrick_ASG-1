using UnrealBuildTool;

public class AssignmentOne : ModuleRules
{
	public AssignmentOne(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.Add(ModuleDirectory);
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "EnhancedInput" });
    }
}
