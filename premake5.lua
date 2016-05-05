workspace "T4Loader"
    location "build"
    configurations { "Debug", "Release" }
    filter { "configurations:Debug" }
      targetdir "bin/debug"

    filter { "configurations:Release" }
      targetdir "bin/release"

	project "T4Loader"
	  kind "StaticLib"
	  language "C++"
	  files {"**.h", "**.cpp" }
	  includedirs {"/"}

	  filter { "configurations:Debug" }
        defines { "DEBUG" }
        flags { "Symbols" }

      filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

      configuration {"linux"} 
    	buildoptions {"-std=c++11"}
