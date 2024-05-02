cmake_minimum_required(VERSION 3.13) # cmake의 버젼이 3.13이상일것을 요

set(PROJECT_NAME cmake_minimum_example) # set는 변수선언 즉 PROJECT_NAME 이라는변수에 "cmake_minimum_example" 대
set(CMAKE_CXX_STANDARD 17) # CMAKE로 시작하는 변수명은 Global변수이다, 17버젼의 c++ 컴파일러를 사용하겠다

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} lecture_1/main.cpp)

















