# TODO: make the directory use linking
# TODO: determine between engine build

#!/bin/bash

includes="-IBedEngine/Source"

if [[ "$uname" == "Linux" ]]; then
    echo "not currently supported for linux"
elif [[ "$uname" == "Darwin" ]]; then
    echo "not currently supported for mac"
else
    echo "Running on windows"
    outputFile=TesterGame.exe
    Platform="BED_WINDOWS_PLATFORM"

<<<<<<< Updated upstream
    clang++ -D BED_WINDOWS_PLATFORM -D BED_BUILD_DLL -g BedEngine/Source/Bed/App/Application.cpp -shared -o build/BedEngine.dll
=======
    clang++ -D BED_WINDOWS_PLATFORM -D BED_BUILD_DLL -g BedEngine/Source/Bed/App/Application.cpp -shared -o build/BedEngine.dll # Builds the entrypoint for 
>>>>>>> Stashed changes

fi

echo "building .exe"
<<<<<<< Updated upstream
clang++ -D BED_WINDOWS_PLATFORM $includes TesterGame/Source/App.cpp -o build/$outputFile 
=======
#clang++ -D BED_WINDOWS_PLATFORM $includes TesterGame/Source/App.cpp -o build/$outputFile 
clang++ -D $Platform $includes -fuse-ld=lld-link -o build/$outputFile TesterGame/Source/App.cpp -lgdi32 -luser32 build/BedEngine.lib
>>>>>>> Stashed changes
