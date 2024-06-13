// 정점 좌표
#version 330 core // 사용할 버젼의 파일을 명시적으로 컴파일러에게 알려준다
layout (location = 0) in vec3 aPos;


void main() {
  // gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
  // gl_Position = vec4(0.5, 0.5, 0.0, 1.0);
  gl_Position = vec4(aPos, 1.0); // aPos로부터 정점데이터를 받는다
}