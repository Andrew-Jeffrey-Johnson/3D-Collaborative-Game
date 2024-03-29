#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aOffset;// The position that was being added per instance
//layout (location = 3) in mat4 transform;

out vec2 TexCoord;

uniform mat4 model;// Transformation matrix (same for every instance)
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos+aOffset, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
