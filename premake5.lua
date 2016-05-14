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
    files { "Src/TestApp/**.h", "Src/TestApp/**.cpp" }
    links { "T4Loader" }
    includedirs { "Src" }

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
    files { "Src/T4Loader/**.h", "Src/T4Loader/**.cpp" }
    includedirs { "include" }

    filter { "configurations:Debug" }
      defines { "DEBUG" }
      flags { "Symbols" }

    filter { "configurations:Release" }
      defines { "NDEBUG" }
      optimize "On"

    configuration { "linux" } 
      buildoptions { "-std=c++11" }
