cmake_minimum_required (VERSION 3.8)
project(Aimbot)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (HEADERS
	""
	)

set(SOURCES 
	"src/main.cpp"
	)


add_executable(Aimbot ${SOURCES} ${HEADERS})
target_include_directories(Aimbot PUBLIC "include")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Aimbot)