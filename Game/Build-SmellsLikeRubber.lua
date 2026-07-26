project "SmellsLikeRubber"
  kind "WindowedApp"
  language "C++"
  cppdialect "C++23"

  targetdir ("../bin/%{cfg.buildcfg}")
  objdir ("../bin/Intermediates/%{cfg.buildcfg}")

  files 
  {
    "src/**.cpp", 
    "src/**.cxx",
    "src/**.c",

    "src/**.hpp", 
    "src/**.hxx", 
    "src/**.h",
  }

  includedirs 
  {
    "src",

	  "../vendor/SlateEngine/Slate/include",
  }

  links
  {
    "SlateEngine",
  }

  filter "system:windows"
    systemversion "latest"
    buildoptions { "/Zc:preprocessor" }

  filter "configurations:Debug"
    defines "SLR_DEBUG"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    defines "SLR_RELEASE"
    runtime "Release"
    optimize "on"

  filter "configurations:Dist"
    defines "SLR_DIST"
    runtime "Release"
    optimize "full"
  filter{}
