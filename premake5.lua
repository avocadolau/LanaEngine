workspace "Lanna"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lanna/vendor/GLFW/include"
IncludeDir["Glad"] = "Lanna/vendor/Glad/include"
IncludeDir["ImGui"] = "Lanna/vendor/imgui"

include "Lanna/vendor/GLFW"
include "Lanna/vendor/Glad"
include "Lanna/vendor/imgui"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
        "Glad",
        "ImGui",
		"opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
            "LN_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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
        "Lanna/src"
    }

    links
    {
        "Lanna"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS"
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