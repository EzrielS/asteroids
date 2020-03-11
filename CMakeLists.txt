cmake_minimum_required(VERSION 3.6)

add_subdirectory(SDL2)

project(ASTEROID_PRG_AV LANGUAGES CXX)

function(COMPILATION)
    cmake_parse_arguments( COMPILATION_PREFIX "USE_SDL" "EXEC" "SRC" ${ARGN})
    add_executable(${COMPILATION_PREFIX_EXEC} "")
    target_sources(${COMPILATION_PREFIX_EXEC} PRIVATE ${COMPILATION_PREFIX_SRC})
    target_include_directories(${COMPILATION_PREFIX_EXEC} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}})
    set_target_properties(${COMPILATION_PREFIX_EXEC} PROPERTIES CXX_STANDARD 17)
    if (${COMPILATION_PREFIX_USE_SDL})
        target_link_libraries(${COMPILATION_PREFIX_EXEC} PRIVATE SDL2main SDL2-static)
    endif()
endfunction()




# ajouter les sources ici

set(SRC_FILES_ASTEROID
    main.cpp)

# fonction de compilation
# syntaxe ( EXEC nom_executable SRC sources  [USE_SDL] )

compilation(EXEC asteroid SRC ${SRC_FILES_ASTEROID}  USE_SDL)

