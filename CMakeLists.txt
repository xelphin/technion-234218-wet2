cmake_minimum_required(VERSION 3.0.0)
project(technion-234218-wet2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(technion_234218_wet2
        Hash.h
        UnionFind.h
        NodeList.h
        Player.h
        Player.cpp
        Team.h
        Team.cpp
        wet2util.h
        worldcup23a2.h
        worldcup23a2.cpp
        main23a2.cpp
        )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
