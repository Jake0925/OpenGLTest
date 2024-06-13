#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"

CLASS_PTR(Context)
class Context {
public:
    static ContextUPtr Create();
    void Render();    
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    uint32_t m_vertexArrayObject;   // VAO (vertex array buffer) 각정점은몇byte로구성되었는가등 정점데이터의구조를알려주는오브젝트
    // uint32_t m_vertexBuffer;        // VBO(vertex buffer object, 정점데이터를 담은 버퍼 오브젝트, 정점에대한 다양한테이터를GPU가접근가능한메모리에저장해둔다)를 담아둘 uint32_t형 멤버변수
    // uint32_t m_indexBuffer;         // 인덱스번호정보의 버퍼를 담는다

    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
};

#endif // __CONTEXT_H__