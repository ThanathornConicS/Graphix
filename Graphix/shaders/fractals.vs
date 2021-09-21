#version 330 core

attribute vec3 pos;

uniform float systemTime;
uniform vec2 systemResolution;
uniform lowp vec3 camera_pos;
uniform lowp vec2 mouse_delta;

varying float vSystemTime
varying vec2 vSystemResolution;
varying lowp vec3 vCamera_pos;
varying lowp vec2 vMouse_delta;

void main()
{
    vSystemTime = systemTime;
    vSystemResolution = systemResolution;
    vCamera_pos = camera_pos;
    vMouse_delta = mouse_delta;
    gl_Position = vec4(pos, 1);
}