/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name:  m_fragmentShader2.frag
Purpose: fragment shader file without the lights
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

 #version 330 core
   out vec4 FragColor;
   in vec3 outColor;
   
   void main()
   {
       FragColor = vec4(outColor, 1.0);
   }