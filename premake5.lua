workspace "Lanna"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lanna"
    location "Lanna"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"

    }

    includedirs
    {
        "Lanna/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines
        {
            "LN_PLATFORM_WINDOWS",
            "LN_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "LN_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines
        {
            "LN_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "LN_DEBUG"
        symbols "On"

    filter "configurations:Release"
    filter "configurations:Release"
        defines "LN_RELEASE"
        optimize "On"

    filter "configurations:Debug"
        defines "LN_DIST"
        optimize "On"