# Compilation
CMake requires `build` directory in Project Root
```
mkdir build
cd build
```

Configure and Build Project for the first time
```
cmake ..
cmake --build .
```
On Windows it will build in debug by default. To build in release you need to use this command
```
cmake --build . --config Release
```

# Running and recompiling changes
after you build the first time go into the build folder and find the .exe in the bin folder somewhere and then run it
```
cd build/bin
./Particle_Life.exe
```

if something in the code is changed go back into the build folder and build again and then run it ... then continue this loop
```
cd ..
cmake --build .
cd bin
./Particle_Life.exe
```

# Demo

![til](./utils/Artificial-Life.gif)