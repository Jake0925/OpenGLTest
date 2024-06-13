cmake_minimum_required(VERSION 3.13) # cmake의 버젼이 3.13이상일것을 요

set(PROJECT_NAME first_OpenGL_example) # set는 변수선언 즉 PROJECT_NAME 이라는변수에 "cmake_minimum_example" 대
set(CMAKE_CXX_STANDARD 17) # CMAKE로 시작하는 변수명은 Global변수이다, 17버젼의 c++ 컴파일러를 사용하겠다

set(WINDOW_NAME "First OpenGL Example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})

# 컴파일할 파일들
add_executable(${PROJECT_NAME} 
src/main.cpp
src/common.cpp src/common.h
src/shader.cpp src/shader.h
src/program.cpp src/program.h
src/context.cpp src/context.h
src/buffer.cpp  src/buffer.h
src/vertex_layout.cpp src/vertex_layout.h
)

 
include(Dependency.cmake) # Dependency.cmake 파일 호출


# spdlog라는 라이브러리를 사용하겠 
# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) 


# c++에서의 #define과 같은 역할을 외부에서 한다
target_compile_definitions(${PROJECT_NAME} PUBLIC
  WINDOW_NAME="${WINDOW_NAME}"
  WINDOW_WIDTH=${WINDOW_WIDTH}
  WINDOW_HEIGHT=${WINDOW_HEIGHT}
  )


# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})













