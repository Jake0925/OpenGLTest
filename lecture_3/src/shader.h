#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader); // common.h 에서 호출
// class Shader; 
// using ShaderUPtr = std::unique_ptr<Shader>; 
// using ShaderPtr = std::shared_ptr<Shader>; 
// using ShaderWPtr = std::weak_ptr<Shader>;

class Shader 
{
public:
  static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);

  ~Shader();
  uint32_t Get() const { return m_shader; }    
private:
  Shader() {} // 생성자를 private에 선언함으로서 public의 CreateFromFile함수를 통해서만 생성자를 호출할수 있게 함 3-2
  bool LoadFile(const std::string& filename, GLenum shaderType);
  uint32_t m_shader { 0 };
};

#endif // __SHADER_H__