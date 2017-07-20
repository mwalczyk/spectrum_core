#version 450
#extension GL_ARB_separate_shader_objects : enable

layout (set = 0, binding = 0) uniform uniform_buffer_object
{
	mat4 model;
	mat4 view;
	mat4 projection;
} ubo;

// Vertex shader inputs
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;

// Vertex shader outputs
out gl_PerVertex
{
	vec4 gl_Position;
};

layout (location = 0) out vec2 vs_texcoord;

void main()
{
	vs_texcoord = texcoord;
  gl_Position = ubo.projection * ubo.view * ubo.model * vec4(position, 1.0);
}
