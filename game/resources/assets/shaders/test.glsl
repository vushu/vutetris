#type vertex
#version 300 es
precision highp float;
in vec3 aPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
}

#type fragment
#version 300 es
precision highp float;
//precision mediump int;
out vec4 FragColor;

void main () {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
