cmake_minimum_required(VERSION 3.10)
project(C_Playground C)


# Compile the TestRunner
file(GLOB_RECURSE TESTLIB_SOURCES "deps/*.c")









# Tell CMake where to look for headers
include_directories(
    Collections
    deps/testlib
)



# Automatically find all .c files under Collections, including subdirectories, excluding those starting with '_'
file(GLOB_RECURSE TESTLIB_SOURCES "Collections/*.c")

# Filter out files starting with '_'
set(FILTERED_TESTLIB_SOURCES "")
foreach(file ${TESTLIB_SOURCES})
    get_filename_component(file_name ${file} NAME)
    if(NOT file_name MATCHES "^_.*")
        list(APPEND FILTERED_TESTLIB_SOURCES ${file})
    endif()
endforeach()

# Conditionally create the library if there are valid source files
if(FILTERED_TESTLIB_SOURCES)
    add_library(Collections STATIC ${FILTERED_TESTLIB_SOURCES})
else()
    message(STATUS "No valid source files found for Collections library. Skipping library creation.")
endif()

# Automatically find all .c files under Tests/Vector, excluding those starting with '_'
file(GLOB_RECURSE TEST_SOURCES "Tests/*.c")
message(STATUS "Found source files: ${TEST_SOURCES}")

# Filter out files starting with '_'
set(FILTERED_TEST_SOURCES "")
foreach(file ${TEST_SOURCES})
    get_filename_component(file_name ${file} NAME)
    if(NOT file_name MATCHES "^_.*")
        list(APPEND FILTERED_TEST_SOURCES ${file})
    endif()
endforeach()

# For each test file, create a separate executable
foreach(test_file ${FILTERED_TEST_SOURCES})
    # Get the filename without path and without extension
    get_filename_component(test_name ${test_file} NAME_WE)

    # Get the last directory in the path to make the name more readable
    get_filename_component(test_dir ${test_file} DIRECTORY)
    get_filename_component(test_dir_name ${test_dir} NAME)  # Extract just the last directory
    set(executable_name "${test_dir_name}_${test_name}")

    # Create executable with a unique name based on its folder
    add_executable(${executable_name} ${test_file})

    # Link the executable with the library if it was created
    if(FILTERED_TESTLIB_SOURCES)
        target_link_libraries(${executable_name} PRIVATE Collections)
    endif()

    # Add compilation arguments
    target_compile_options(${executable_name} PRIVATE -D_GNU_SOURCE)
    target_compile_options(${executable_name} PRIVATE -lpthread)

    # Set C standard
    set_property(TARGET ${executable_name} PROPERTY C_STANDARD 17)

    # Specify the output directory for the executable
    set_target_properties(${executable_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    )
endforeach()
