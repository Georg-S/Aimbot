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
set_property(TARGET Aimbot PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_custom_command(TARGET Aimbot 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy 
				   ${CMAKE_SOURCE_DIR}"/config.txt"
				   ${CMAKE_SOURCE_DIR}"/build/debug/config.txt")

add_custom_command(TARGET Aimbot 
					POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy 
					${CMAKE_SOURCE_DIR}"/config.txt"
					${CMAKE_SOURCE_DIR}"/build/Release/config.txt")

add_custom_command(TARGET Aimbot 
					POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy 
					${CMAKE_SOURCE_DIR}"/memoryOffsets.txt"
					${CMAKE_SOURCE_DIR}"/build/debug/memoryOffsets.txt")

add_custom_command(TARGET Aimbot 
					POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy 
					${CMAKE_SOURCE_DIR}"/memoryOffsets.txt"
					${CMAKE_SOURCE_DIR}"/build/Release/memoryOffsets.txt")
