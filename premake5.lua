workspace "DYEngine"
	architecture "x86_64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "DYEngine"
	location "DYEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/include/**.h"
	}

	includedirs
	{
		"%{prj.name}/include",
		"%{prj.name}/include/vendor"
	}
    
    libdirs 
    {
		"%{prj.name}/lib/%{cfg.architecture}"
    }
    
	links { "glfw3" }
   
	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.10240.0"

		defines
		{
			"DYE_PLATFORM_WINDOWS",
			"DYE_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "DYE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DYE_DEBUG"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/include/**.h"
	}

	includedirs
	{
		"DYEngine/include",
		"DYEngine/include/vendor"
	}

	links
	{
		"DYEngine"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.10240.0"

		defines
		{
			"DYE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DYE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DYE_DEBUG"
		optimize "On"
        