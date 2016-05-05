workspace "T4Loader"
    location "build"
    configurations { "Debug", "Release" }
    filter { "configurations:Debug" }
      targetdir "debug"

    filter { "configurations:Release" }
      targetdir "release"

	project "T4Loader"
	  kind "StaticLib"
	  language "C++"
	  files {"include/**.h", "src/**.cpp" }
	  includedirs {"include"}

	  filter { "configurations:Debug" }
        defines { "DEBUG" }
        flags { "Symbols" }

      filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

      configuration {"linux"} 
    	buildoptions {"-std=c++11"}
