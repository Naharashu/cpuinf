cmake_minimum_required(VERSION 3.21)
project(cpuinf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")



find_package(cpuinfo REQUIRED)
find_package(FLTK REQUIRED)
find_package(PkgConfig REQUIRED)

find_program(MOLD_PATH mold)
find_program(LLD_PATH lld)

if(MOLD_PATH)
    add_link_options("-fuse-ld=mold")
    message(STATUS "Using Mold Linker")
elseif(LLD_PATH)
    add_link_options("-fuse-ld=lld")
    message(STATUS "Using LLD Linker")
endif()


pkg_check_modules(CAIRO REQUIRED cairo)

add_executable(cpuinf main.cpp)

target_compile_options(cpuinf PRIVATE -Wno-writable-strings)


target_include_directories(cpuinf PRIVATE 
    ${FLTK_INCLUDE_DIR}
    ${CAIRO_INCLUDE_DIRS}
)


target_link_libraries(cpuinf PRIVATE 
    cpuinfo::cpuinfo
    ${FLTK_LIBRARIES}
    ${CAIRO_LIBRARIES}
)

install(TARGETS cpuinf
    RUNTIME DESTINATION bin
)