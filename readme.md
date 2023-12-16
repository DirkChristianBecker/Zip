## Zip
Zip is a C++-Wrapper around the [link](https://github.com/richgel999/miniz.git) Miniz-library. It is in its early stage and currently only supports reading and extraction of zip files.

## Usage
Zip is supposed to be added as a submodule via Git and build via cmake. You can add it to your project like this:

```cmd
git submodule add https://github.com/DirkChristianBecker/Zip.git
```

Then add the project to your cmake build and link against your binary.
```cmake
add_subdirectory(Zip)
target_link_libraries(${your_binary_name} Zip)
```
