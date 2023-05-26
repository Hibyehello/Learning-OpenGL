#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_tex_coord;

uniform sampler2D u_texture;

void main() {
	vec4 texColor = texture(u_texture, v_tex_coord);
	color = texColor;
	color = vec4(1.0);
}
