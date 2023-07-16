cmake_minimum_required(VERSION 3.7)

file(GLOB V_GLOB LIST_DIRECTORIES true "*")
foreach(item ${V_GLOB})
	string(REGEX MATCH "template$" is_template ${item})
	
	if(IS_DIRECTORY ${item} AND NOT is_template)
		add_subdirectory(${item})
	endif()
endforeach()