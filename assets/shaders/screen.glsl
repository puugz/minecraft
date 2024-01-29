#version 330 core
#type vertex

layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_texcoord;

out vec2 v_texcoord;

void main()
{
    v_texcoord = a_texcoord;
    gl_Position = vec4(a_pos, 0.0, 1.0);
}

#type fragment

out vec4 frag_color;

in vec2 v_texcoord;

uniform sampler2D screen_tex;

void main()
{
    frag_color = texture(screen_tex, v_texcoord);
}
