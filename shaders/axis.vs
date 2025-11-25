#version 330 core

layout(location = 0) in vec3 aPos; // vertex pos
uniform mat4 uProjection; // projection matrix

void main() {
	gl_Position = uProjection * vec4(aPos, 1.0);
}
