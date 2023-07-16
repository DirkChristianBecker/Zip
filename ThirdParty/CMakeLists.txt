cmake_minimum_required(VERSION 3.7)

add_subdirectory(Platform)

######### Keep libraries inside a separate folder. ########
set_target_properties(Platform PROPERTIES FOLDER ${LIBS_FOLDER_NAME})
