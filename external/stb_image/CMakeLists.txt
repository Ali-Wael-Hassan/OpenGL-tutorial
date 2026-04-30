# Define the library name
project(stb_image)

# Add the source file
add_library(stb_image STATIC src/stb_image.cpp)

# Tell the library where its own headers are
target_include_directories(stb_image PUBLIC include)