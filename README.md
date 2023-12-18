# NierE_AllToBeNice

Use opengl write Nier E hack game. Just for fun.

## Sources

```shell
git clone https://github.com/MinghaoHe/NierE_AllToBeNice.git
```

## Building

```shell
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_BUILD_NIER_E_AIRPLANE=1

cmake --build . --config Release
..\bin\Release\NierE_AllToBeNice.exe

or 

cmake --build . --config Debug
..\bin\Debug\NierE_AllToBeNice.exe

```

