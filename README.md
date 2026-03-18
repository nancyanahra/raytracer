# raytracer


To build

```shell
# Configure and build release binaries under `build/Release`
$ cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
$ cmake --build build/Release
```

to run

```shell
$ ./build\Release\inOneWeekend > image.ppm
```

view 

```shell
xdg-open image.ppm
```
