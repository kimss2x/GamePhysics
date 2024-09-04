cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전 설정
project(GamePhysics VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options(/std:c++17)
endif()

# vcpkg 경로 설정 (환경 변수 사용 또는 절대 경로로 설정)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# 빌드 출력 디렉터리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# GLM 라이브러리 위치 설정
if(DEFINED ENV{GLM_DIR})
    include_directories($ENV{GLM_DIR})
else()
    find_package(GLM REQUIRED)
    if(GLM_FOUND)
        include_directories(${GLM_INCLUDE_DIRS})
    else()
        message(FATAL_ERROR "GLM 라이브러리를 찾을 수 없습니다.")
    endif()
endif()

# uWebSockets 및 libuSockets 라이브러리 경로 설정
# 필요 시 절대 경로 또는 find_package 사용
set(UWEBSOCKETS_INCLUDE_DIR "${VCPKG_ROOT}/installed/x64-windows/include/uwebsockets")
set(UWEBSOCKETS_LIBRARY_DIR "${VCPKG_ROOT}/installed/x64-windows/lib")

# Include 및 Link 경로 설정
include_directories(${UWEBSOCKETS_INCLUDE_DIR})
include_directories(${LIBUSOCKETS_INCLUDE_DIR})
link_directories(${UWEBSOCKETS_LIBRARY_DIR})
link_directories(${LIBUSOCKETS_LIBRARY_DIR})

# 헤더 파일 디렉터리 추가
include_directories(${PROJECT_SOURCE_DIR}/include)

# 소스 파일을 자동으로 수집
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 실행 파일 추가 (이름을 프로젝트와 연관된 이름으로 변경)
add_executable(${PROJECT_NAME} ${SOURCES})

# uWebSockets 및 libuSockets 라이브러리 링크
target_link_libraries(${PROJECT_NAME} uWS uSockets)

# 로그 폴더를 미리 생성
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/log)

# 로그 폴더 설정 (필요시)
target_compile_definitions(${PROJECT_NAME} PRIVATE LOG_DIR="${PROJECT_SOURCE_DIR}/log")
