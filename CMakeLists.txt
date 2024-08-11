cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전 설정
project(MyVectorProject VERSION 1.0)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 기본 빌드 타입 설정 (Debug, Release, RelWithDebInfo, MinSizeRel 중 선택)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 빌드 출력 디렉터리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# GLM 라이브러리 위치 설정
if(DEFINED ENV{GLM_DIR})
    include_directories($ENV{GLM_DIR})
else()
    message(FATAL_ERROR "GLM_DIR 환경 변수가 설정되어 있지 않습니다.")
endif()

# 헤더 파일 디렉터리 추가
include_directories(${PROJECT_SOURCE_DIR}/include)

# 소스 파일을 자동으로 수집
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 실행 파일 추가 (이름을 프로젝트와 연관된 이름으로 변경)
add_executable(MyVectorProjectExec ${SOURCES})

# 로그 폴더를 미리 생성
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/log)

# 로그 폴더 설정 (필요시)
target_compile_definitions(MyVectorProjectExec PRIVATE LOG_DIR="${PROJECT_SOURCE_DIR}/log")
