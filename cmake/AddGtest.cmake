
# add_gtest(NAME
#   SOURCES source...
#   [INCLUDES include...]
#   [DEPS dep...]
# )

function(add_gtest NAME)
    cmake_parse_arguments(ADD_GTEST "" "" "SOURCES;INCLUDES;DEPS" ${ARGN})

    add_executable(${NAME} ${ADD_GTEST_SOURCES})
    target_link_libraries(${NAME} CONAN_PKG::gtest ${ADD_GTEST_DEPS})
    target_include_directories(${NAME} PUBLIC ${ADD_GTEST_INCLUDES})

    add_test(NAME ${NAME} COMMAND ${NAME})

    message(STATUS "Added gtest ${NAME}")
endfunction()
