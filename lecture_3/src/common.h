#ifndef __COMMON_H__  // common.h가 잘못해서 main.cpp에서 여러번 #include하는경우 컴파일 에러가 발생할수 있다
#define __COMMON_H__  // 따라서 #include common.h가 다시 증복선언되는경우 #ifndef __COMMON_H__에 의해 이미 __COMMON_H__이 호출된경우 조건문에의해 재호출시 false가되어 아래문장을 실행하지 않는다
                      // 다른방법으로 #ifdef, #define 대신에 #pragma once를 사용할수 있다  
#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>


// 이름이 너무 기므로 간단하게 사용하기 매크로 선언 
// 우측의 std::unique_ptr<klassName>같은 변수 선언대신 좌측의 klassName ## UPtr를 대신하여 사용할수 있도록함
// '\'는 줄이 이어짐을 의미
// unique_ptr 해당 변수가 함수 밖을 벗어나면 메모리가 자동으로 해제된다
// '##'은 선언한 이름을 붙여주는 것이다
// ex) klassName ## UPtr -> klassNameUPtr
// ex) CLASS_PTR(aaa)로 선언하면 
// class aaa; 
// using aaaUPtr = std::unique_ptr<aaa>; 
// using aaaPtr = std::shared_ptr<aaa>; 
// using aaaWPtr = std::weak_ptr<aaa>;
// 클래스내의 모든것들이 호출된다

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;



std::optional<std::string> LoadTextFile(const std::string& filename); // optional - 메모리를 보호하기 위해 text가 있으면 메모리를 할당하고 없으면 할당하지 않는다

#endif // __COMMON_H__