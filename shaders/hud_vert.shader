#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uTranslate;
uniform float uAspectRatio;  // height / width，修正非正方形视口的拉伸

void main()
{
    vec2 pos = aPos;
    pos.x *= uAspectRatio;
    gl_Position = vec4(pos + uTranslate, 0.0, 1.0);
}
