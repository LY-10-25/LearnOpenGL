#version 330 core
//out vec4 FragColor;
//in vec3 ourColor;
//in vec2 TexCoord;
//uniform sampler2D ourTexture;
//void main()
//{
//    FragColor = texture(ourTexture, TexCoord);
//    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
//}

in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix;
void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x*(1),TexCoord.y)), mix);
}