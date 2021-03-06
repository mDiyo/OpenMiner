#------------------------------------------------------------------------------
# CMakeLists.txt
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

project(openminer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2")

if (WIN32)
	set(WIN_LIBRARIES_PATH "C:/Libraries")
endif ()

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
set(DEBUG_GCC_FLAGS -g -Og -Wall -Wextra -Wfatal-errors -Wno-variadic-macros)
set(RELEASE_GCC_FLAGS -O3)
set(RELWITHDEB_GCC_FLAGS -g -O3 -Wall -Wextra -Wfatal-errors -Wno-variadic-macros)

set(CMAKE_CXX_STANDARD 14)

#------------------------------------------------------------------------------
# Setting default build type
#------------------------------------------------------------------------------
set(DEFAULT_BUILD_TYPE RelWithDebInfo)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)

	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - Lua
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/lua)
endif ()

find_package(Lua REQUIRED)

if(NOT LUA_FOUND)
	message(FATAL_ERROR "Lua is needed to build the project. Please install it correctly.")
endif()

include_directories(${LUA_INCLUDE_DIR})
link_directories(${LUA_LIBRARY_DIRS})

#------------------------------------------------------------------------------
# - gamekit
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/gamekit)
endif ()

find_package(GameKit REQUIRED)

if(NOT GAMEKIT_FOUND)
	message(FATAL_ERROR "gamekit is needed to build the project. Please install it correctly.")
endif()

include_directories(${GAMEKIT_INCLUDE_DIR})

#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/tinyxml2)
endif ()

find_package(TinyXml2 REQUIRED)

if(NOT TINYXML2_FOUND)
	message(FATAL_ERROR "tinyxml2 is needed to build the project. Please install it correctly.")
endif()

include_directories(${TINYXML2_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - OpenGL
#------------------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE "LEGACY")

if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/glm)
endif ()

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

if(NOT GLM_FOUND)
	message(FATAL_ERROR "glm not found!")
endif(NOT GLM_FOUND)

include_directories(${GLM_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - SDL2, SDL2_image, SDL2_mixer
#------------------------------------------------------------------------------
if (MSVC)
	set(SDL2_PATH       ${WIN_LIBRARIES_PATH}/SDL2       CACHE BOOL "" FORCE)
	set(SDL2_IMAGE_PATH ${WIN_LIBRARIES_PATH}/SDL2_image CACHE BOOL "" FORCE)
	set(SDL2_MIXER_PATH ${WIN_LIBRARIES_PATH}/SDL2_mixer CACHE BOOL "" FORCE)
	set(SDL2_TTF_PATH   ${WIN_LIBRARIES_PATH}/SDL2_ttf   CACHE BOOL "" FORCE)
elseif (WIN32)
	set(SDL2_PATH       ${WIN_LIBRARIES_PATH}/SDL2/i686-w64-mingw32       CACHE BOOL "" FORCE)
	set(SDL2_IMAGE_PATH ${WIN_LIBRARIES_PATH}/SDL2_image/i686-w64-mingw32 CACHE BOOL "" FORCE)
	set(SDL2_MIXER_PATH ${WIN_LIBRARIES_PATH}/SDL2_mixer/i686-w64-mingw32 CACHE BOOL "" FORCE)
	set(SDL2_TTF_PATH   ${WIN_LIBRARIES_PATH}/SDL2_ttf/i686-w64-mingw32   CACHE BOOL "" FORCE)
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 not found!")
endif(NOT SDL2_FOUND)

if(NOT SDL2_IMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image not found!")
endif(NOT SDL2_IMAGE_FOUND)

if(NOT SDL2_MIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer not found!")
endif(NOT SDL2_MIXER_FOUND)

if(NOT SDL2_TTF_FOUND)
	message(FATAL_ERROR "SDL2_ttf not found!")
endif(NOT SDL2_TTF_FOUND)

include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - SFML network
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/SFML)
endif ()

if (MINGW)
	set(SFML_STATIC_LIBRARIES TRUE)
endif ()

find_package(SFML COMPONENTS system network)

if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML is needed to build the project. Please install it correctly.")
endif()

include_directories(${SFML_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - GLEW
#------------------------------------------------------------------------------
if (WIN32)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WIN_LIBRARIES_PATH}/glew)

	find_package(GLEW REQUIRED)

	if(NOT GLEW_FOUND)
		message(FATAL_ERROR "GLEW not found!")
	endif(NOT GLEW_FOUND)

	include_directories(${GLEW_INCLUDE_DIRS})
endif ()

#------------------------------------------------------------------------------
# Subdirectories
#------------------------------------------------------------------------------
add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
