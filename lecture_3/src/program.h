// vertex와 gragment shader를 연결한 pipeline program
// 이 프로그램을 이용해서 최종적으로 그림을 그린다

// vertex, fragment 외에 여러개의 shader를 링클할수도 있게함
// shader 인스턴스 인자는 필요하지만 소유할 필요는 없음
// shader 인스턴스는 다른 program인스턴스를 만드는데 재사용할수 있다
// 따라서 shared pointer를 사용 (ShaderPtr)

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program {
public:
    static ProgramUPtr Create(
        const std::vector<ShaderPtr>& shaders);

    ~Program(); // 소멸자
    uint32_t Get() const { return m_program; }
    void Use() const;
private:
    Program() {} // 생성자
    bool Link(const std::vector<ShaderPtr>& shaders); // 초기화함수
    uint32_t m_program { 0 };
};

#endif // __PROGRAM_H__