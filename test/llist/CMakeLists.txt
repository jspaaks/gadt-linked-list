set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
if (APPLE)
    list(APPEND CMAKE_INSTALL_RPATH @loader_path/../lib)
elseif(UNIX)
    list(APPEND CMAKE_INSTALL_RPATH $ORIGIN/../lib)
endif()

add_executable(tgt_exe_test_llist)

set_property(TARGET tgt_exe_test_llist PROPERTY OUTPUT_NAME test_llist)

target_compile_definitions(
    tgt_exe_test_llist
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

target_compile_features(
    tgt_exe_test_llist
    PRIVATE
        c_std_23
)

target_compile_options(
    tgt_exe_test_llist
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Release>:-Werror>
)

target_include_directories(
    tgt_exe_test_llist
    PRIVATE
        ${PROJECT_ROOT}/include
)

target_link_libraries(
    tgt_exe_test_llist
    PRIVATE
        criterion
        tgt_lib_llist
)

target_sources(
    tgt_exe_test_llist
    PRIVATE
        ${PROJECT_ROOT}/test/llist/test_llist__append.c
        ${PROJECT_ROOT}/test/llist/test_llist__create.c
        ${PROJECT_ROOT}/test/llist/test_llist__delete.c
        ${PROJECT_ROOT}/test/llist/test_llist__destroy.c
        ${PROJECT_ROOT}/test/llist/test_llist__get_length.c
        ${PROJECT_ROOT}/test/llist/test_llist__insert.c
        ${PROJECT_ROOT}/test/llist/test_llist__prepend.c
)

install(TARGETS tgt_exe_test_llist)
