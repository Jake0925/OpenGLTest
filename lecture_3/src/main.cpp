#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "context.h"


// 윈도우 창크기의 변화가 있는경우 콜백
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height); // 윈도우크기가 변하는 경우 사이즈 메세지 출력
    glViewport(0, 0, width, height); // 그림을그릴 위치 및 홤ㄴ설정
}


// 키보드 콜랙
void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  // ESC키를 누르는경우 종료
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char** argv) {
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");


    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) // 초기화 실패시 아래 내용실행
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw 윈도우 생성
    // 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, // CmakeLixt에 선언되어있다 
      nullptr, nullptr);
    if (!window) // window 생성 실패시
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }

    // 텍스트 설정
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // glfwGetProcAddress- 프로세스주소를 얻어온다, gladLoadGLLoader - opengl함수를 얻어온
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    // // 여기서부터 Opengl 함수를 호출하여 사용할수 있다 ****************************
    auto glVersion = glGetString(GL_VERSION); // 버젼확인
    // SPDLOG_INFO("OpenGL context version: {}", glVersion);


    // context 초기화
    auto context = Context::Create();
    if (!context) {
    SPDLOG_ERROR("failed to create context");
    glfwTerminate();
    return -1;
    }


    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange); // 윈도우 콜백
    glfwSetKeyCallback(window, OnKeyEvent); // 키보드 콜백


    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {    
        // render
        context->Render();
        glfwSwapBuffers(window); // 더블버퍼링, 프레임버퍼2개를준비함(front/back)
        glfwPollEvents(); // 1/60초 간격으로 이벤트를 실행 및 감지, 이것이 없이는경우 루프가 너무빨리돌아 멈춘화면처럼 보인다
    }
    context.reset(); // context 메모리 해제 (또는 context = nullPtr를 사용해도 된다)

    glfwTerminate();
    return 0;
}



// #include <spdlog/spdlog.h>

// int main(int argc, const char** argv) {
//     SPDLOG_INFO("Hello, test!");
//     return 0;
// }

// #include <iostream>

// int main(int argc, const char** argv)
// {
//     std::cout<<"hello, opengl"<< std::endl;

//     return 0;
// }


