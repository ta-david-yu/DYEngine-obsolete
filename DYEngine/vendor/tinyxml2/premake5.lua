project "tinyxml2"
    kind "StaticLib"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/tinyxml2.h",
        "src/tinyxml2.cpp"
    }
    
    includedirs
    {
        "include"
    }
    
	filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        
    filter { "system:windows", "configurations:Release" }
    buildoptions "/MT"
