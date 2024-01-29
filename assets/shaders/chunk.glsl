#version 330 core
#type vertex

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texcoord;

out vec2 v_texcoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    v_texcoord = a_texcoord;
    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);
}

#type fragment

out vec4 frag_color;

in vec2 v_texcoord;

uniform sampler2D tex;

void main()
{
    vec4 col = texture(tex, v_texcoord);
    if (col.a < 0.1) discard;

    frag_color = col;
}
