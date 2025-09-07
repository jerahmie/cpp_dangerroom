#version 460

#ifdef GL_ES
precision mediump float;
#endif

layout (location = 0) out vec4 FragColor;

layout(std140, set = 3, binding = 0) uniform UniformBlock {
	float u_time;
};

void main() {
    FragColor = vec4(1.0,0.0,1.0,1.0);
}
