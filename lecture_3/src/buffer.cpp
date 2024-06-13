#include "buffer.h"

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) 
{
    auto buffer = BufferUPtr(new Buffer());
    if (!buffer->Init(bufferType, usage, data, dataSize))
        return nullptr;
    return std::move(buffer);
}

Buffer::~Buffer() //소멸자
{
    if (m_buffer) {
        glDeleteBuffers(1, &m_buffer); //할당되어있던 버퍼제거
    }
}

void Buffer::Bind() const 
{
    glBindBuffer(m_bufferType, m_buffer); // array버퍼였는지 element버퍼였는지 타입확인후 바인드 버퍼호출
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) 
{
    m_bufferType = bufferType;
    m_usage = usage;
    glGenBuffers(1, &m_buffer);
    Bind();
    glBufferData(m_bufferType, dataSize, data, usage);
    return true;
}