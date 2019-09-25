#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
};

in vec3 Normal;
in vec2 TexCoords;

uniform Material material;

void main() {
    FragColor = texture(material.diffuse, TexCoords);
}
