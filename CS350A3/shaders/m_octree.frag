/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: m_octree.frag
Purpose: use for drawing the octree
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#version 330 core

out vec4 FragColor;

in vec3 color;

void main()
{
	vec3 result = color;
	FragColor = vec4(color, 1.f);
}