/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name:	m_octree.vert
Purpose: use for the drawing of the octree
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);
	color = aColor;
}