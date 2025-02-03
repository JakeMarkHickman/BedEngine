#!/bin/bash

#TODO: this will need to be a build tool in editor

#Build Path
buildPath="build"                           # The path to build to

#Locations
Dependencies="BedEngine/Dependencies"
Source="BedEngine/Source"
    Bed="$Source/Bed"
        App="$Bed/App"
        Game="$Bed/Game"
        Math="$Bed/Math"
        Tools="$Bed/Tools"
    Graphics="$Source/Graphics"
    Inclusions="$Source/Inclusions"
    Platforms="$Source/Platforms"

#Output
GameOutputFile="Playground"                     # No extention as we will set it after we know what OS we are building for
EngineOutputFile="BedEngine.dll"            # The engine will always be a dynamic lib

#Includes
GameIncludes="-I$Source -I$Inclusions -I$Dependencies/nlohmann"
EngineIncludes="-I$Source -I$Inclusions -I$Dependencies/GLFW/include
                -I$Dependencies/GLEW/include -I$Dependencies/stb_image
                -I$Dependencies/glm -I$Dependencies/nlohmann"

#Libarys
GameLibs="$buildPath/BedEngine.lib"             # Libs for the game
EngineLibs=""                               # Libs for the engine

#flags
GameFlags="-fuse-ld=lld-link"                   # Flags for the game
EngineFlags=""                              # Flags for the engine

#Preprocessor Definitions
GamePredef="-std=c++17 -Wno-c++17-extensions"                                   # Definitions for the game
EnginePredef="-std=c++17 -Wno-c++17-extensions -DBED_BUILD_DLL"             # Definitions for the engine

#CPPs
GraphicsCpp="$Graphics/VertexBuffer.cpp $Graphics/IndexBuffer.cpp
            $Graphics/VertexArray.cpp $Graphics/Renderer.cpp
            $Graphics/Shader.cpp $Graphics/GraphicVariables.cpp
            $Graphics/Texture.cpp $Graphics/StorageBuffer.cpp"

OpenGLCpp="$Graphics/OpenGL/OpenRenderer.cpp $Graphics/OpenGL/OpenShader.cpp"

VulkanCpp=""

DirectXCpp=""

MetalCpp=""

ToolsCpp="$Tools/FileLoader.cpp $Tools/StringSearcher.cpp $Tools/Memory/MemoryPool.cpp"

GameObjectsCpp="$Game/World/GameObjects/Mesh/Mesh.cpp $Game/World/World.cpp"

EcsCpps="$Bed/ECS/ComponentManager.cpp $Bed/ECS/EntityManager.cpp"

MathCpp="$Math/Matrix/Matrix3x3.cpp"

EngineCpp="$App/Application.cpp $Dependencies/stb_image/stb_image.cpp
            $App/DeltaTime.cpp
            $GraphicsCpp
            $ToolsCpp 
            $GameObjectsCpp
            $EcsCpps
            $MathCpp
            $OpenGLCpp
            $VulkanCpp
            $DirectXCpp
            $MetalCpp"

GameCpp="Playground/Source/App.cpp"


#Check what system is being used

if [[ "$uname" == "Linux" ]]; then           # This checks if the version is Linux
    echo Linux is currently unsupported

    # Set Variables
    GamePredef="$GamePredef -DBED_LINUX_PLATFORM"
    EnginePredef="$EnginePredef -DBED_LINUX_PLATFORM"
    outputFile="$outputFile.elf"

elif [[ "$uname" == "Darwin" ]]; then

    echo Mac is currently unsupported

    # Set Variables
    GamePredef="$GamePredef -DBED_MAC_PLATFORM"
    EnginePredef="$EnginePredef -DBED_MAC_PLATFORM"
    GameOutputFile="$GameOutputFile.app"

else

    echo Building for Windows...

    # Set Variables
    EngineLibs="$EngineLibs -luser32 BedEngine/Dependencies/GLFW/glfw3_mt.lib -lopengl32 -lUser32 -lGdi32 -lShell32 BedEngine/Dependencies/GLEW/lib/Release/x64/glew32s.lib"
    GamePredef="$GamePredef -DBED_WINDOWS_PLATFORM"
    
    EnginePredef="$EnginePredef -DBED_WINDOWS_PLATFORM -DGLEW_STATIC"
    GameOutputFile="$GameOutputFile.exe"

fi

# Build the Engine 
echo Building Engine DLL...
clang++ -shared $EngineIncludes $EngineLibs $EngineFlags $EnginePredef -o"$buildPath/$EngineOutputFile" $EngineCpp

# Build the Game
echo Building Game...
clang++ $GameIncludes $GameLibs $GameFlags $GamePredef -o"$buildPath/$GameOutputFile" $GameCpp