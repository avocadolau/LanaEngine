project "Glew"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GL/eglew.h",
		"include/GL/glew.h",
		"include/GL/glxew.h",
		"include/GL/wglew.h",
		"src/glew.c"
	}

	includedirs
	{
		"include/GL"
	}

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"