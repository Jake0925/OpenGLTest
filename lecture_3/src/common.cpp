#include "common.h"
#include <fstream>
#include <sstream>


// 파일로딩 
std::optional<std::string> LoadTextFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) // 파일이 열렸는지 여부 확인
    {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {};
    }
    std::stringstream text;
    text << fin.rdbuf(); // 파일안의 내용을 모두 stringstream으로 text에 가져온다
    return text.str(); // str형으로 변환
}