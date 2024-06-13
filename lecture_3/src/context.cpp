#include "context.h"

ContextUPtr Context::Create() {
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}



bool Context::Init() {  
    // 사각형 좌표
    float vertices[] = 
    {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, // top left
    };

    // 인덱스
    uint32_t indices[] = 
    { // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // VAO
    glGenVertexArrays(1, &m_vertexArrayObject); // array object를 1개 생성
    glBindVertexArray(m_vertexArrayObject); // 바인딩
    


    // VBO
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float)*12);    
    // glGenBuffers(1, &m_vertexBuffer); // 정점, 색상, 텍스처등의 정보를 담은 새로운 buffer object를 1개 만든다
    // glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // VBO와 m_vertextBuffer를 연결(바인드), GL_ARRAY_BUFFER-사용할 buffer object는 vertext data를 저장할 용도임을 알려줌
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);  // 지정된 buffer에 데이터를 복사한다
    //                                                                             // GL_STATIC_DRAW- GPU버퍼에 vertex데이터를 셋팅하고 다시는 값을변경하지 않을것을 의미
    //                                                                             // cf) 변경하고 싶은경우 GL_DYNAMIC_DRAW을 사용, 한번만사용하고 데이터를 버릴경우 GL_STREAM_DRAW
    //                                                                             // vertices의 자료형이 float이고 정점이 9개이므로 sizeof(float) *9, vertices를 입력한다
    //                                                                             // m_vertextBuffer에 vertices의 정보를 넘겨준다

    // VAO
    glEnableVertexAttribArray(0); // 정점 attribute중 0번의 attribute를 사용할것이다, 이 0은 simple.vs 에서 loacation =0을 의미한다
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);  // vertice가 어떻게 구성되어 잇는지 설명한다
                                                                            // 0번 attribute는 float형태의 값이 3개인 nomalize(0~1사이의값)할필요없고(GL_FALSE), 
                                                                            //stride 즉 다음좌표의값을 확인하기위해서는 sizeof(float)*3만큼의 메모리위치를 건너띄면되고
                                                                            //옵셋은 0이다

    // index번호 호출을 위함
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(float)*6);
	// glGenBuffers(1, &m_indexBuffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6,  indices, GL_STATIC_DRAW);

    // vertex, fragment
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER); //로드파일
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER); //로드파일
    if (!vertShader || !fragShader) // 둘중하나라도 초기화에 실패한 경우
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    // program
    m_program = Program::Create({fragShader, vertShader});
    if (!m_program) // 초기화에 실패한 경우
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.1f, 0.2f, 0.3f, 0.0f); // 화면을 무슨색으로 지울지 설정
    
    // uint32_t vao = 0;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    return true;
}

void Context::Render() {
    glClear(GL_COLOR_BUFFER_BIT); // 실제로 지우는 역할

    // 그림그리는 코드
    m_program->Use(); //glUseProgram(m_program->Get());
    // glDrawArrays(GL_TRIANGLES, 0, 3); // 삼각형그리기 (어떤타입으로 그릴것인지, VAO에서 정점배열중 몇번째점부터 그리것인지, 몇개의 정점을 그릴것인지)
    // glDrawArrays(GL_TRIANGLES, 0, 6); // 사각형그리기, 두개의삼각형을 붙여서 사각형형태를만든다
    // glDrawArrays(GL_LINE_STRIP, 0, 3); // 라인그리기 (어떤타입으로 그릴것인지, VAO에서 정점배열중 몇번째점부터 그리것인지, 몇개의 정점을 그릴것인지)
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 인덱스번호를 호출하여 사각형을 그린다
}

// void Context::Render()
// {
//     glClear(GL_COLOR_BUFFER_BIT);  // 실제로 지우는 역할

//     // 그림그리는 코드
//     glUseProgram(m_program->Get());
//     glDrawArrays(GL_POINTS, 0, 1);
// }