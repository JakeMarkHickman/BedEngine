# TODO: make the directory use linking
# TODO: determine between engine build

#!/bin/bash

includes="-IBedEngine/Source"
engineincludes="-IBedEngine/Platforms"

if [[ "$uname" == "Linux" ]]; then
    echo "not currently supported for linux"
    outputFile=TesterGame.bin


elif [[ "$uname" == "Darwin" ]]; then
    echo "not currently supported for mac"
else
    echo "Running on windows"
    outputFile=TesterGame.exe

    Platform="BED_WINDOWS_PLATFORM"

    clang++ -D BED_WINDOWS_PLATFORM -D BED_BUILD_DLL $engineincludes -g BedEngine/Source/Bed/App/Application.cpp -luser32 -shared -o build/BedEngine.dll # Builds the entrypoint for 
fi

echo "building .exe"
clang++ -D $Platform $includes -fuse-ld=lld-link -o build/$outputFile TesterGame/Source/App.cpp build/BedEngine.lib