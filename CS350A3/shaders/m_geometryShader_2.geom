/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: m_geometryShader_2
Purpose: use for drawing the vertex normals
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

 #version 330 core
   layout (triangles) in;
   layout (line_strip, max_vertices = 2) out;
   
   in VS_OUT {
      vec3 normal;
   } gs_in[];
   
   const float MAGNITUDE = 0.1;

   out vec3 outColor;

   void main()
   {
      vec3 V0 = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
      vec3 V1 = gl_in[2].gl_Position.xyz - gl_in[1].gl_Position.xyz;
      
      vec3 N = normalize(cross(V0, V1));

      vec4 P = (gl_in[0].gl_Position + gl_in[1].gl_Position
                        + gl_in[2].gl_Position) / 3.0;
      
      gl_Position = P;
      outColor = vec3(0.0, 1.0, 1.0);
      EmitVertex();
      
      gl_Position = P + vec4( N , 0.0 ) * MAGNITUDE;
      outColor = vec3(0.0, 1.0, 1.0);
      EmitVertex();
      EndPrimitive();
	}