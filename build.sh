#!/bin/bash

#TODO: this will need to be a build tool in editor

#Build Path
buildPath="build"                           # The path to build to
StaticBuild=true

SharedDependencies="-IPillowMath/include"

#TODO: THIS IS THE PHYSICS ENGINE LIB BUILD

Dependencies="MattressPhysicsEngine/Dependencies"
Source="MattressPhysicsEngine/Source"

Includes="$SharedDependencies -I$Source"
Cpps="$Source/PhysicsWorld.cpp"
Flags="-std=c++20 -Wno-c++20-extensions"
Predef=""
OutputFile=""

if $StaticBuild; then
    echo Physics Building Static
    mkdir -p "$buildPath/Static/obj"

    PhysicsbuildPath="$buildPath/Static"
    OutputFile="Mattress.lib"
    Libs=""
    Flags="$Flags -c"

    for cpp in $Cpps; do
        objname=$(basename "$cpp" .cpp).o
        clang++ $Includes $Libs $Flags $Predef "$cpp" -o "$PhysicsbuildPath/obj/$objname"
    done

    llvm-ar rcs "$PhysicsbuildPath/$OutputFile" "$PhysicsbuildPath/obj/"*.o
fi


#TODO: THIS IS THE GAME ENGINE AND GAME
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
EngineOutputFile=""                # The engine will always be a dynamic lib

#Includes
GameIncludes=" $SharedDependencies -I$Source -I$Inclusions -I$Dependencies/nlohmann -I$Dependencies/glm -I$Dependencies/GLEW/include -I$Dependencies/GLFW/include -I$Dependencies/MetaStuff/include -IMattressPhysicsEngine/Source"
EngineIncludes=" $SharedDependencies -I$Source -I$Inclusions -I$Dependencies/GLFW/include
                -I$Dependencies/GLEW/include -I$Dependencies/stb_image
                -I$Dependencies/glm -I$Dependencies/nlohmann -I$Dependencies/MetaStuff/include
                -IMattressPhysicsEngine/Source"

#Libarys
GameLibs=""             # Libs for the game
EngineLibs="$buildPath/Static/Mattress.lib"                               # Libs for the engine

#flags
GameFlags="-fuse-ld=lld-link -std=c++20 -Wno-c++20-extensions"                      # Flags for the game
EngineFlags="-fuse-ld=lld-link -std=c++20 -Wno-c++20-extensions"                                      # Flags for the engine

#Preprocessor Definitions
GamePredef=""                                                                       # Definitions for the game
EnginePredef=""                                                                     # Definitions for the engine

#CPPs
GraphicsCpp="$Graphics/VertexBuffer.cpp $Graphics/IndexBuffer.cpp
            $Graphics/VertexArray.cpp $Graphics/ShaderAsset.cpp 
            $Graphics/GraphicVariables.cpp $Graphics/InstanceArray.cpp
            $Graphics/StorageBuffer.cpp $Graphics/InstanceBuffer.cpp"

OpenGLCpp="$Graphics/OpenGL/OpenRenderer.cpp $Graphics/OpenGL/OpenShader.cpp $Graphics/OpenGL/OpenTexture.cpp"

VulkanCpp=""

DirectXCpp=""

MetalCpp=""

ToolsCpp="$Tools/FileLoader.cpp $Tools/StringSearcher.cpp $Tools/Memory/MemoryPool.cpp"

GameObjectsCpp="$Game/Game.cpp $Game/GameObjects/Mesh/Mesh.cpp $Game/GameObjects/Physics/Collision/Collision.cpp"

EcsCpps="$Bed/ECS/ECS.cpp $Bed/ECS/ComponentManager.cpp $Bed/ECS/EntityManager.cpp $Bed/ECS/World.cpp"

MathCpp="$Math/Matrix/Matrix3x3.cpp"

PlatformSpecficCpps=""

EngineCpp="$App/Application.cpp $Dependencies/stb_image/stb_image.cpp
            $App/Time.cpp
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

    PlatformSpecficCpps=""

    # Set Variables
    GamePredef="$GamePredef -DBED_LINUX_PLATFORM"
    EnginePredef="$EnginePredef -DBED_LINUX_PLATFORM"
    outputFile="$outputFile.elf"

elif [[ "$uname" == "Darwin" ]]; then

    echo Mac is currently unsupported

    PlatformSpecficCpps=""

    # Set Variables
    GamePredef="$GamePredef -DBED_MAC_PLATFORM"
    EnginePredef="$EnginePredef -DBED_MAC_PLATFORM"
    GameOutputFile="$GameOutputFile.app"

else

    echo Building for Windows...

    PlatformSpecficCpps=$Platforms/Windows/GLFWWindow.cpp

    # Set Variables
    EngineLibs="$EngineLibs BedEngine/Dependencies/GLFW/glfw3_mt.lib -lopengl32 -luser32 -lkernel32 -lgdi32 -lwinmm -lshell32 -lBedEngine/Dependencies/GLEW/lib/Release/x64/glew32s.lib"
    GamePredef="$GamePredef -DBED_WINDOWS_PLATFORM"

    GameFlags="$GameFlags -Wl,/subsystem:console"
    
    EnginePredef="$EnginePredef -DBED_WINDOWS_PLATFORM -DGLEW_STATIC -DGLFW_STATIC"
    GameOutputFile="$GameOutputFile.exe"

fi

# Build the Engine
if $StaticBuild; then
    echo Building Static
    mkdir -p "$buildPath/Static/obj"

    buildPath="$buildPath/Static"

    GameLibs="-DGLFW_STATIC $EngineLibs"
    GamePredef="$EnginePredef"

    EngineLibs=""
    EnginePredef="$EnginePredef"
    EngineOutputFile="BedEngine.lib"
    EngineFlags="$EngineFlags -c"

    for cpp in $EngineCpp $PlatformSpecficCpps; do
        objname=$(basename "$cpp" .cpp).o
        clang++ $EngineIncludes $EngineLibs $EngineFlags $EnginePredef "$cpp" -o "$buildPath/obj/$objname"
    done

    llvm-ar rcs "$buildPath/$EngineOutputFile" "$buildPath/obj/"*.o
else
    echo Building Dynamic
    mkdir -p "$buildPath/Dynamic"

    buildPath="$buildPath/Dynamic"

    EngineLibs="$EngineLibs $buildPath/Mattress.lib"
    EnginePredef="$EnginePredef -DBED_BUILD_DLL -DENGINE_DLL"
    GamePredef="$GamePredef -DENGINE_DLL"
    EngineOutputFile="BedEngine.dll"
    EngineFlags="$EngineFlags -shared"

    clang++ $EngineIncludes $EngineLibs $EngineFlags $EnginePredef -o"$buildPath/$EngineOutputFile" $EngineCpp $PlatformSpecficCpps
fi

GameLibs="$GameLibs $buildPath/BedEngine.lib"

# Build the Game
echo Building Game...
clang++ $GameIncludes $GameLibs $GameFlags $GamePredef -o"$buildPath/$GameOutputFile" $GameCpp