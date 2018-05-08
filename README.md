# isis-nexus-json-cpp

Create a JSON description for ISIS NeXus files in C++.
Dependencies are managed by Conan which can be installed using `pip`. Then the following Conan remote must be added:
```
conan remote add <LOCAL_NAME> https://api.bintray.com/conan/vthiery/conan-packages
```
where <LOCAL_NAME> must be substituted by a locally unique name.

You should then be able to go ahead and build using `CMake` in the usual way for your platform.
For example on Linux:
```
mkdir build
cd build
cmake ..
make
```
and then run with
```
./bin/nexus_json-cmake
