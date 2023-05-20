// Copyright Epic Games, Inc. All Rights Reserved.

using System.Collections.Generic;
using System.IO;
using System.Security.Permissions;
using UnrealBuildTool;

public class RTS : ModuleRules
{
	// private string opencv_version = "450";
	// private string opencv_dir_name = "OpenCV/OpenCV_450";
	// private string opencv_libs_dir_name = "build/x64/vc15/lib";
	// private string opencv_bins_dir_name = "build/x64/vc15/bin";
	// private string opencv_includes_dir_name = "build/include";
	// private string[] opencv_libs = {"opencv_world450.lib"};
	// private string[] opencv_dlls = {"opencv_world450.dll","opencv_videoio_ffmpeg450_64.dll"};
	
	public RTS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		CppStandard = CppStandardVersion.Cpp20;
		
		// WindowsCompiler.  set up compiler y need
		
		
		// WindowsCompiler
		
		// install armadillo 
		// PublicIncludePaths.Add("C:/cpp_libs_source/armadillo/armadillo-12.2.0/include");
		
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject",
			"Engine", "InputCore","UMG","WebSockets"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		// RuntimeDependencies.Add("$(BinaryOutputDir)/sqlite3.dll",
		// 	Path.Combine(ModuleDirectory, "external_bin", "sqlite3.dll"));
		//
		// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "external_bin",
		// 	"sqlite3.lib"));
		//
		// PublicDelayLoadDLLs.Add("sqlite3.dll");
		//
		// Load_opencv();
	}
	
	// private string ThirdPartyPath
	// {
	// 	get
	// 	{
	// 		return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
	// 	}
	// }
	//
	// public bool Load_opencv()
	// {
	// 	// TODO: add checking for library availability by expected path
	// 	// [tutorial](https://www.youtube.com/watch?v=YOidIl2kTD0)
	// 	string BaseLibDir = Path.Combine(ThirdPartyPath, opencv_dir_name);
	// 	string LibsDir = Path.Combine(BaseLibDir, opencv_libs_dir_name);
	// 	string BinsDir = Path.Combine(BaseLibDir, opencv_bins_dir_name);
	// 	string IncludesDir = Path.Combine(BaseLibDir, opencv_includes_dir_name);
	// 	PublicIncludePaths.Add(IncludesDir);
	//
	// 	List<string> FullPathsToLibs = new List<string>();
	// 	for (int i = 0; i < opencv_libs.Length; i++)
	// 	{
	// 		FullPathsToLibs.Add(Path.Combine(LibsDir, opencv_libs[i]));
	// 	}
	//
	// 	List<string> FullPathsToDlls = new List<string>();
	// 	for (int i = 0; i < opencv_dlls.Length; i++)
	// 	{
	// 		FullPathsToDlls.Add(Path.Combine(BinsDir, opencv_dlls[i]));
	// 	}
	// 	
	// 	PublicAdditionalLibraries.AddRange(FullPathsToLibs);
	// 	PublicDelayLoadDLLs.AddRange(opencv_dlls);
	//
	// 	for (int i = 0; i < opencv_dlls.Length; i++)
	// 	{
	// 		RuntimeDependencies.Add(
	// 			InPath: Path.Combine("$(BinaryOutputDir)",opencv_dlls[i]),
	// 			InSourcePath: FullPathsToDlls[i]);
	// 	}
	// 	
	// 	return true;
	// }
	
}
