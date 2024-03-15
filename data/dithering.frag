#version 330 core

in vec2 TexCoord;
flat in int TexIndex;

out vec4 FragColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;
uniform sampler2D Texture7;
uniform sampler2D Texture8;
uniform sampler2D Texture9;
uniform sampler2D Texture10;
uniform sampler2D Texture11;
uniform sampler2D Texture12;
uniform sampler2D Texture13;
uniform sampler2D Texture14;
uniform sampler2D Texture15;
uniform vec2 u_Resolution;

void main()
{
	vec2 resolution = u_Resolution;
	float screenWidth = resolution.x;
	float screenHeight = resolution.y;

	const mat4 ditherMatrix = mat4(
			1.0,  9.0,  3.0, 11.0,
			13.0, 5.0, 15.0,  7.0,
			4.0, 12.0,  2.0, 10.0,
			16.0, 8.0, 14.0,  6.0
			);
 
	int x = int(gl_FragCoord.x) % 4;
	int y = int(gl_FragCoord.y) % 4;
	float ditherValue = ditherMatrix[x][y] / 16.0;

    vec4 outColor = vec4(1.0, 0.0, 0.0, 1.0);
    switch (int(TexIndex)) {
        case 0: outColor = texture(Texture0, TexCoord); break;
        case 1: outColor = texture(Texture1, TexCoord); break;
        case 2: outColor = texture(Texture2, TexCoord); break;
        case 3: outColor = texture(Texture3, TexCoord); break;
        case 4: outColor = texture(Texture4, TexCoord); break;
        case 5: outColor = texture(Texture5, TexCoord); break;
        case 6: outColor = texture(Texture6, TexCoord); break;
        case 7: outColor = texture(Texture7, TexCoord); break;
        case 8: outColor = texture(Texture8, TexCoord); break;
        case 9: outColor = texture(Texture9, TexCoord); break;
        case 10: outColor = texture(Texture10, TexCoord); break;
        case 11: outColor = texture(Texture11, TexCoord); break;
        case 12: outColor = texture(Texture12, TexCoord); break;
        case 13: outColor = texture(Texture13, TexCoord); break;
        case 14: outColor = texture(Texture14, TexCoord); break;
        case 15: outColor = texture(Texture15, TexCoord); break;
        default: outColor = vec4(1.0, 0.0, 0.0, 1.0); break;
    }
	vec4 ogColor = outColor;

	if (outColor.r < ditherValue && outColor.r > 0.3)
		outColor.r = 0.9;
	else if (outColor.r < ditherValue && outColor.r < 0.15)
		outColor.r = 0.25;
	else
		outColor.r = 0.4;

	if (outColor.g < ditherValue && outColor.g > 0.3)
		outColor.g = 0.9;
	else if (outColor.g < ditherValue && outColor.g < 0.15)
		outColor.g = 0.1;
	else
		outColor.g = 0.;

	if (outColor.b < ditherValue && outColor.b > 0.3)
		outColor.b = 0.29;
	else if (outColor.b < ditherValue && outColor.b < 0.15)
		outColor.b = 0.20;
	else
		outColor.b = 0.7;

	FragColor = outColor;
}
