/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: m_vertexShader_2.vert
Purpose:   standard shader
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

 #version 330 core
   layout (location = 0) in vec3 aPos;
   layout (location = 1) in vec3 aNormal;

   out VS_OUT {
      vec3 normal;
   } vs_out;
   out vec3 outColor;

   uniform mat4 model;   
   uniform mat4 view;
   uniform mat4 projection;
   
    void main()
    {
      mat3 normalMatrix = mat3(transpose(inverse(view * model)));
      vs_out.normal = vec3(projection * vec4(normalMatrix * aPos, 0.0));
      gl_Position = projection * view * model * vec4(aPos, 1.0);
      outColor = vec3(1.0, 0.0, 0.0);
   }