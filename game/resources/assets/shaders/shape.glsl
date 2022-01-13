#type vertex
#version 300 es
precision highp float;
precision highp int;
in vec3 aPos;
in vec4 aColor;
uniform mat4 uMvp;

out vec4 fColor;

void main() {
    fColor = aColor;
    gl_Position = uMvp * vec4(aPos, 1.0);
}

#type fragment
#version 300 es
precision highp float;
precision highp int;
in vec4 fColor;

out vec4 color;

void main () {
    color = fColor;
}

