cmake_minimum_required(VERSION 3.21)
project(HelloWorld VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

find_package(CLI11 CONFIG REQUIRED)

# ```
# find_package(spdlog CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
# ```
# This does not work. spdlog is not compatible with Cmake 4.x

if(NOT VCPKG_TARGET_TRIPLET)
    file(GLOB _vcpkg_triplets LIST_DIRECTORIES true "${CMAKE_BINARY_DIR}/vcpkg_installed/*")
    list(FILTER _vcpkg_triplets EXCLUDE REGEX "/vcpkg$")
    list(GET _vcpkg_triplets 0 _vcpkg_triplet_dir)
    get_filename_component(VCPKG_TARGET_TRIPLET "${_vcpkg_triplet_dir}" NAME)
endif()
set(VCPKG_INSTALLED "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}")

add_executable(${PROJECT_NAME} src/main.cpp)

# Manual spdlog/fmt workaround requires us to set include- and library directories manually
target_include_directories(${PROJECT_NAME} PRIVATE "${VCPKG_INSTALLED}/include")
target_link_directories(${PROJECT_NAME} PRIVATE 
    "$<IF:$<CONFIG:Debug>,${VCPKG_INSTALLED}/debug/lib,${VCPKG_INSTALLED}/lib>"
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    CLI11::CLI11 
    "$<$<CONFIG:Debug>:spdlogd>"
    "$<$<CONFIG:Debug>:fmtd>"
    "$<$<NOT:$<CONFIG:Debug>>:spdlog>"
    "$<$<NOT:$<CONFIG:Debug>>:fmt>"
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)