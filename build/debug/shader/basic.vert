#version 110

attribute vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}