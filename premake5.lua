workspace "Brain-Matrix"
	architecture "x86_64"
	startproject "Brain-Matrix-Test"

	configurations
	{
		"Debug",
		"Release",
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["openCL"] = "Brain-Matrix/vendor/AMD/include"
IncludeDir["openCL_LIB"] = "Brain-Matrix/vendor/AMD/lib/x86_64"

project "Brain-Matrix"
	location "Brain-Matrix"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{prj.name}/lib")
	objdir ("%{prj.name}/lib-int")

	files
	{
		"%{prj.name}/include/**.cpp",
		"%{prj.name}/include/**.h",
		"%{prj.name}/include/**.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{IncludeDir.openCL}"
	}
	libdirs
	{
		"%{IncludeDir.openCL_LIB}",
	}
	links
	{ 
		"OpenCL.lib" 
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "Brain-Matrix-Test"
	location "Brain-Matrix-Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{prj.name}/bin")
	objdir ("%{prj.name}/bin-int")

	files
	{
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.h",
		"%{prj.name}/**.hpp",
	}

	includedirs
	{
		"Brain-Matrix/include",
	}

	links
	{
		"Brain-Matrix"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"