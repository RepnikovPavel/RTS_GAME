// Copyright Epic Games, Inc. All Rights Reserved.

using System.Collections.Generic;
using System.IO;
using System.Security.Permissions;
using UnrealBuildTool;

public class RTS : ModuleRules
{
	private string opencv_version = "450";
	private string opencv_dir_name = "OpenCV/OpenCV_450";
	private string opencv_libs_dir_name = "build/x64/vc15/lib";
	private string opencv_bins_dir_name = "build/x64/vc15/bin";
	private string opencv_includes_dir_name = "build/include";
	private string[] opencv_libs = 

	public RTS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject",
			"Engine", "InputCore","UMG"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		RuntimeDependencies.Add("$(BinaryOutputDir)/sqlite3.dll",
			Path.Combine(ModuleDirectory, "external_bin", "sqlite3.dll"));

		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "external_bin",
			"sqlite3.lib"));

		PublicDelayLoadDLLs.Add("sqlite3.dll");
	}
	
	private string ThirdPartyPath
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
		}
	}

	public bool Load_opencv(ReadOnlyTargetRules Target)
	{
		// TODO: add checking for library availability by expected path
		// [tutorial](https://www.youtube.com/watch?v=YOidIl2kTD0)
		string BaseLibDir = Path.Combine(ThirdPartyPath, opencv_dir_name);
		string LibsDir = Path.Combine(BaseLibDir, opencv_libs_dir_name);
		string BinsDir = Path.Combine(BaseLibDir, opencv_bins_dir_name);
		string IncludesDir = Path.Combine(BinsDir, opencv_includes_dir_name);
		PublicIncludePaths.Add(IncludesDir);
		PublicAdditionalLibraries.Add();
		return false;
	}
	
}
