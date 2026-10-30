CPU-INF is tiny analog of CPU-Z for x86 and ARM linux.

## Requirements to build:

- cmake 3.21>=

- C++ compiler with C++23 support

- libcpuinfo

- fltk


## Installation (Git + CMake)

1. Clone the repository:

```
git clone https://github.com/Naharashu/cpuinf && cd cpuinf
```

2. Run CMake

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build -j$(nproc)

cmake --install build
```

Done!

## Installation (AUR)

```
yay -S cpuinf-git
```