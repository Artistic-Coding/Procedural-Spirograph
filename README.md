# Procedural-Spirograph
A Spirograph generator tool
## Setup
First install [libCinder](https://libcinder.org/docs/guides/)

In CMakeLists go ahead and change line 6, and point the path towards your Cinder library.

Now setup and build the project
```bash
mkdir build && cd build
cmake ..
make -j4
```

You should be able to run the program in /build/Debug/procedural_spirograph/procedural_spirograph

## Arguments
Being a CLI application, the interaction is based on CLI arguments

Head over to the help page to find out its usage
```bash
procedural_spirograph -h
```
