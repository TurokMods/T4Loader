solution "T4Loader"
  location "build"
  configurations { "Debug", "Release" }
  filter { "configurations:Debug" }
    targetdir "debug"

  filter { "configurations:Release" }
    targetdir "release"

  project "Test"
    kind "ConsoleApp"
    language "C++"
    files { "test.cpp" }
    links { "T4Loader" }
    includedirs {"include"}

    filter { "configurations:Debug" }
      defines { "DEBUG" }
      flags { "Symbols" }

    filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"

    configuration {"linux"} 
      buildoptions {"-std=c++11"}

  project "T4Loader"
    kind "SharedLib"
    language "C++"
    files { "include/**.h", "src/**.cpp" }
    includedirs { "include" }

    filter { "configurations:Debug" }
      defines { "DEBUG" }
      flags { "Symbols" }

    filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"

    configuration { "linux" } 
      buildoptions { "-std=c++11" }
