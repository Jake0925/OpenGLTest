#include "program.h"

ProgramUPtr Program::Create(
    const std::vector<ShaderPtr>& shaders) 
    {
        auto program = ProgramUPtr(new Program());
        if (!program->Link(shaders)) // 링크실패시
            return nullptr;
        return std::move(program); // 메모리를 해제하지 않고 전달
    }


bool Program::Link(const std::vector<ShaderPtr>& shaders) 
{
    m_program = glCreateProgram();
    for (auto& shader: shaders) // iterator 반복문
        glAttachShader(m_program, shader->Get()); // shader->Get() -> shader의 ID를 가져온다
    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success); // 상태체크, program에 대한 정수형 정보를 얻어옴

    // 실패시 에러메세지
    if (!success) 
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to link program: {}", infoLog);
        return false;
    }

    return true;
}

void Program::Use() const {
    glUseProgram(m_program);
}


// 소멸자
Program::~Program() {
    if (m_program) 
    {
        glDeleteProgram(m_program);
    }
}


/* shared_ptr 설명 03-03
void test()
{
    std::shared_ptr<int> a  = std::shared_ptr<int>(new int);
    {
        std::shared_ptr<int> b = a; // a와 b는 같은 메모리를 공동으로 사용한다 
        *b += 1;
    } // b는 }(스코프)를 벗어나면 사라져서 레퍼런스 카운팅은 2에서 1로 변하지만 0이 아니므로 new int 메모리는 사라지지 않는다
} a의 메모리가 사라지면서 레퍼런스 카운팅이 0이 되면서 new int의 메모리도 해제 된다

*/

/* unique_ptr -> shared_ptr로 변환
    ShaderPtr shader = Shader::CreateFromFile()
*/