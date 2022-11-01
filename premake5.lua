workspace "Lanna"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Lanna/vendor/GLFW/include"
IncludeDirs["ImGui"] = "Lanna/vendor/imgui"
IncludeDirs["Glew"] = "Lanna/vendor/Glew/include/GL"
IncludeDirs["JSON"] = "Lanna/vendor/rapidjson"
IncludeDirs["MathGeoLib"] = "Lanna/vendor/MathGeoLib"
IncludeDirs["PCG"] = "Lanna/vendor/PCG/include"
IncludeDirs["assimp"] = "Lanna/vendor/assimp/include"
IncludeDirs["stb"] = "Lanna/vendor/stb"
IncludeDirs["glm"] = "Lanna/vendor/glm/glm"
IncludeDirs["Optick"] = "Lanna/vendor/Optick/include"


include "Lanna/vendor/GLFW"
include "Lanna/vendor/imgui"
include "Lanna/vendor/Optick"

project "Lanna"
    location "Lanna"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lnpch.h"
	pchsource "Lanna/src/lnpch.cpp"

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
        "%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/rapidjson",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.MathGeoLib}",
        "%{IncludeDirs.Glew}",
        "%{IncludeDirs.PCG}",
        "%{IncludeDirs.assimp}",
        "%{IncludeDirs.stb}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.Optick}"
	}

	links 
	{ 
		"GLFW",
        "ImGui",
        "Lanna/vendor/Glew/lib/glew32.lib",
		"opengl32.lib",
        "Optick",
        "Lanna/vendor/assimp/lib/x64/release/assimp-vc143-mt.lib"

    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
            "LN_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"),
            ("{COPY} %{cfg.buildtarget.relpath} ../Editor")
		}

    debugdir "$(SolutionDir)/Editor"

    filter "configurations:Debug"
        defines
		{ 
			"LN_DEBUG",
			"LN_ENABLE_ASSERTS"
		}
        runtime "Debug"
        symbols "On"


    filter "configurations:Release"
        defines "LN_RELEASE"
        runtime "Release"
        optimize "On"

       

    filter "configurations:Dist"
        defines "LN_DIST"
        runtime "Release"
        optimize "On"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"

    }

    includedirs
    {
        "Lanna/vendor/spdlog/include",
        "Lanna/vendor/rapidjson",
        "Lanna/vendor/imgui",
        "Lanna/src",
        "Lanna/vendor/Glew/include/GL",
        "Lanna/vendor/glm/glm",
        "%{IncludeDirs.Optick}",
        "Lanna/vendor/assimp/include",
        "Lanna/vendor/stb",
        "Lanna/vendor/PCG/include"
    }

    links
    {
        "Lanna",
        "ImGui",
        "Optick"
    }

    debugdir "$(SolutionDir)/Editor"

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS"
        }
        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Editor")
		}

    filter "configurations:Debug"
        defines "LN_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        runtime "Release"
        optimize "On"