cmake_minimum_required(VERSION 3.10)

# Set project name
project("OpenGLProject")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
# Define source and content directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(CONTENT_DIR "${CMAKE_SOURCE_DIR}/Content")

# Include all .cpp and .c files from src directory
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.c")

# Include directories for headers
include_directories(${SRC_DIR})
include_directories(${INCLUDE_DIR})

# Add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES}
        ${SRC_DIR}/glad.c
)

# Find OpenGL
find_package(OpenGL REQUIRED)
if (NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Find GLFW
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw glm::glm)

set(CONTENT_SUBDIRS Models Shaders Textures Images)

add_custom_target(always_copy_files ALL
        COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/timestamp"
)

# Platform-specific settings for building app or exe
if (APPLE)
    # Create .app bundle on macOS
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_GUI_IDENTIFIER com.example.openglproject
            MACOSX_BUNDLE_BUNDLE_NAME "OpenGLProject"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist"
    )
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa" "-framework OpenGL" "-framework IOKit")

    # Copy Content files (Models, Shaders, Images, Textures) to .app bundle's Resources folder
    foreach(SUBDIR ${CONTENT_SUBDIRS})
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CONTENT_DIR}/${SUBDIR}"  # Source subdirectory
                "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources/Content/${SUBDIR}"  # Destination
                DEPENDS always_copy_files ${SUBDIR}

        )
    endforeach()

else ()
    # For other platforms (Windows, Linux): Copy Content files to binary directory
    foreach(SUBDIR ${CONTENT_SUBDIRS})
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CONTENT_DIR}/${SUBDIR}"
                "${CMAKE_BINARY_DIR}/bin/Content/${SUBDIR}"
                DEPENDS always_copy_files ${SHADER_FILES}
        )
    endforeach()
endif ()

# Set output directories for both platforms
set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
