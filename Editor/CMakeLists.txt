cmake_minimum_required (VERSION 3.8)

if(FEATURE_DirectX)
    add_definitions(-DFEATURE_DirectX)
else()
    add_definitions(-DFEATURE_OpenGL)
endif()

add_executable (hs_editor "editor.cpp" "editor.hpp")
target_link_libraries(hs_editor app_engine)
