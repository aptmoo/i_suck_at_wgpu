project "GLFW"
    kind "StaticLib"
    language "C"
    targetdir "../lib/"
    staticruntime "off"

    files 
    {
        "glfw/src/**.c", "glfw/src/**.h",
        "glfw/include/**.h"
    }

    includedirs
    {
        "./",
        "glfw/include/",
    }

    links
    {
        
    }

    defines
    {
        
    }

    targetdir ("../lib/")
    objdir ("../Intermediates/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { "_GLFW_WIN32" }

    filter "system:linux"
        defines { "_GLFW_X11" }
        libdirs { "/usr/lib", "../lib", }
        links { "dl", "m", "pthread" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"