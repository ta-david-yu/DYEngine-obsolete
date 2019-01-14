workspace "DYEngine"
	configurations { "Debug", "Release" }
    platforms { "x86", "x86_64" }
    startproject "Sandbox"
    defines { "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_DEPRECATE" }
    
-- architecture specification 
filter "platforms:x86"
    architecture "x86"
    
filter "platforms:x86_64"
    architecture "x86_64"

-- build output directory
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "DYEngine/vendor/GLFW/include"
IncludeDir["glad"] = "DYEngine/vendor/glad/include"
IncludeDir["tinyxml2"] = "DYEngine/vendor/tinyxml2/include"

include "DYEngine/vendor/GLFW"
include "DYEngine/vendor/glad"
include "DYEngine/vendor/tinyxml2"

project "DYEngine"
	location "DYEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}
    
	includedirs
	{
		"%{prj.name}/include",
		"%{prj.name}/vendor/include",
        
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.tinyxml2}"
	}
    
    links
    {
        "GLFW",
        "glad",
        "tinyxml2",
        "opengl32.lib"
    }
   
	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"DYE_PLATFORM_WINDOWS",
			"DYE_BUILD_DLL",
            "DYE_ENABLE_ASSERT",
            
            "GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
    
	filter "configurations:Debug"
		defines "DYE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "DYE_DEBUG"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include",
        
		"DYEngine/include",
		"DYEngine/vendor/include",
        
        "DYEngine/vendor/glad/include"
	}

	links
	{
		"DYEngine"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"DYE_PLATFORM_WINDOWS",
            "DYE_ENABLE_ASSERT"
		}
        
	filter "configurations:Debug"
		defines { "DYE_DEBUG" }
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines { "DYE_DEBUG" }
		buildoptions "/MD"
		optimize "On"
        