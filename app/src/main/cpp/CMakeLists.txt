cmake_minimum_required(VERSION 3.10.2)

project("cbasiclibrary")

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution)

#Apriltag voodoo
set( lib_build_DIR ${distribution_DIR}/apriltag/build )
file(MAKE_DIRECTORY ${lib_build_DIR})
add_subdirectory(${distribution_DIR}/apriltag lib_build_DIR)

add_library(lib_apriltag SHARED IMPORTED)
set_target_properties(lib_apriltag PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/apriltag/libapriltag.so)
#this doesn't work yet because the cmakelists.txt file in the apriltag library
#don't make an SO file, for some reason there isn't an associated error with this
#End Apriltag voodoo

#we import this library, it is located in the distribution directory
add_library(lib_gperf SHARED IMPORTED)
set_target_properties(lib_gperf PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gperf/lib/${ANDROID_ABI}/libgperf.so)


add_library( native-lib SHARED native-lib.cpp )

#when compiling native-lib.cpp look in these directories for includes
target_include_directories( native-lib PRIVATE
        ${distribution_DIR}/gperf/include
        ${distribution_DIR}/apriltag)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                        apriltag
                        lib_gperf
                        android)