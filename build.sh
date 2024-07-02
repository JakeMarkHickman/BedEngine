# TODO: make the directory use linking
# TODO: determine between engine build

#!/bin/bash

includes="-IBedEngine"

if [[ "$uname" == "Linux" ]]; then
    echo "not currently supported for linux"
elif [[ "$uname" == "Darwin" ]]; then
    echo "not currently supported for mac"
else
    echo "Running on windows"
    outputFile=TesterGame.exe
    Platform="-BED_WINDOWS_PLATFORM"

    clang++ -D BED_WINDOWS_PLATFORM -D BED_BUILD_DLL -g BedEngine/Source/Bed/App/Application.cpp -shared -o build/BedEngine.dll

fi

echo "building .exe"
clang++ -D BED_WINDOWS_PLATFORM $includes TesterGame/Source/App.cpp -o build/$outputFile 