#!/bin/bash

#Build Path
buildPath="build"                           # The path to build to

#Output
outputFile="Playground"                     # No extention as we will set it after we know what OS we are building for
engineOutputFile="BedEngine.dll"            # The engine will always be a dynamic lib

#Includes
includes="-IBedEngine/Source -IBedEngine/Source/Inclusions"
engineIncludes="-IBedEngine/Source -IBedEngine/Source/Inclusions -IBedEngine/Dependencies/GLFW/include -IBedEngine/Dependencies/GLEW/include -IBedEngine/Dependencies/stb_image -IBedEngine/Dependencies/glm"

#Libarys
libs="$buildPath/BedEngine.lib"             # Libs for the game
engineLibs=""                               # Libs for the engine

#flags
flags="-fuse-ld=lld-link"                   # Flags for the game
engineFlags=""                              # Flags for the engine

#Preprocessor Definitions
predef="-std=c++17 -Wno-c++17-extensions"                                   # Definitions for the game
enginePredef="-std=c++17 -Wno-c++17-extensions -DBED_BUILD_DLL"             # Definitions for the engine

#BuildEntry
entry="Playground/Source/App.cpp"
engineEntry="BedEngine/Source/Bed/App/Application.cpp"

#ExtraCpps
cpp=""
enginecpp=" BedEngine/Source/Graphics/VertexBuffer.cpp BedEngine/Source/Graphics/IndexBuffer.cpp
            BedEngine/Source/Graphics/VertexArray.cpp BedEngine/Source/Graphics/Renderer.cpp BedEngine/Source/Graphics/Shader.cpp
            BedEngine/Source/Graphics/OpenGL/OpenRenderer.cpp BedEngine/Source/Graphics/OpenGL/OpenShader.cpp
            BedEngine/Source/Graphics/Texture.cpp BedEngine/Dependencies/stb_image/stb_image.cpp 
            BedEngine/Source/Bed/Tools/FileLoader.cpp BedEngine/Source/Bed/Tools/StringSearcher.cpp
            BedEngine/Source/Bed/Game/World/GameObjects/ECS/ECS.cpp BedEngine/Source/Bed/Game/World/GameObjects/Mesh/Mesh.cpp
            BedEngine/Source/Bed/Game/World/GameObjects/Components/CameraComponent.cpp
            BedEngine/Source/Bed/Game/World/GameObjects/Components/RenderComponent.cpp BedEngine/Source/Bed/Game/World/GameObjects/Components/VelocityComponent.cpp
            BedEngine/Source/Bed/Math/Matrix/Matrix3x3.cpp"


#Check what system is being used

if [[ "$uname" == "Linux" ]]; then           # This checks if the version is Linux
    echo Linux is currently unsupported

    # Set Variables
    predef="$predef -DBED_LINUX_PLATFORM"
    enginePredef="$enginePredef -DBED_LINUX_PLATFORM"
    outputFile="$outputFile.elf"

elif [[ "$uname" == "Darwin" ]]; then

    echo Mac is currently unsupported

    # Set Variables
    predef="$predef -DBED_MAC_PLATFORM"
    enginePredef="$enginePredef -DBED_MAC_PLATFORM"
    outputFile="$outputFile.app"

else

    echo Building for Windows...

    # Set Variables
    engineLibs="$engineLibs -luser32 BedEngine/Dependencies/GLFW/glfw3_mt.lib -lopengl32 -lUser32 -lGdi32 -lShell32 BedEngine/Dependencies/GLEW/lib/Release/x64/glew32s.lib"
    predef="$predef -DBED_WINDOWS_PLATFORM"
    
    enginePredef="$enginePredef -DBED_WINDOWS_PLATFORM -DGLEW_STATIC"
    outputFile="$outputFile.exe"

fi

# Build the Engine 
echo Building Engine DLL...
clang++ -shared $engineIncludes $engineLibs $engineFlags $enginePredef -o"$buildPath/$engineOutputFile" $engineEntry $enginecpp

# Build the Game
echo Building Game...
clang++ $includes $libs $flags $predef -o"$buildPath/$outputFile" $entry $cpp