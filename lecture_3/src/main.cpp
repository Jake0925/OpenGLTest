#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

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



    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, // CmakeLixt에 선언되어있다 
      nullptr, nullptr);
    if (!window) // window 생성 실패시
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }


    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // 1/60초 간격으로 이벤트를 실행, 이것이 없이는경우 루프가 너무빨리돌아 멈춘화면처럼 보인다
    }

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


