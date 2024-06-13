#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename,  GLenum shaderType) 
{
  auto shader = ShaderUPtr(new Shader());
  if (!shader->LoadFile(filename, shaderType))
    return nullptr; // 만약 로드가 실패한경우 함수를 벗어난면 ShaderUPtr의 메모리는 소멸된다
  return std::move(shader); //std::unique_ptr의경우 함수를 벗어나면 메모리가 소멸되지만 move를 사용하여 소멸하지않고 메모리를 전달할수 있다
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) 
{
  auto result = LoadTextFile(filename);
  if (!result.has_value()) // 파일안에 값이 있는지 여부 확인
    return false;

  auto& code = result.value();
  const char* codePtr = code.c_str(); // c타입의 포인터 전달
  int32_t codeLength = (int32_t)code.length(); // int32_t = int, uint8_t = unsigned char

  // create and compile shader
  m_shader = glCreateShader(shaderType); // shader 오브젝트 생성
  glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); // 소스코드입력   두번째인자 - 코드갯수
  glCompileShader(m_shader);  // shader 컴파일


  // check compile error
  int success = 0;
  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); // 컴파일 상태 조회
  if (!success) 
  {
    char infoLog[1024];
    glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog); // 에러로그 가져오기
    SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
    SPDLOG_ERROR("reason: {}", infoLog); // 컴파일 실패시 에러로그 
    return false;
  }
  return true;
}

// 소멸자
Shader::~Shader()
{
    if(m_shader)
    {
        glDeleteShader(m_shader); // shader object 제거
    }
}


