/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name:  m_geometryShader.geom
Purpose:    use for the normals drawing
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

 #version 330 core
   layout (triangles) in;
   layout (line_strip, max_vertices = 6) out;
   
   in VS_OUT {
      vec3 normal;
   } gs_in[];
   out vec3 outColor;
   const float MAGNITUDE = 0.1;

   void GenerateLine(int index)
   {
       gl_Position = gl_in[index].gl_Position;
      outColor = vec3(1.0, 1.0, 0.0);
       EmitVertex();
       gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
      outColor = vec3(1.0, 1.0, 0.0);
       EmitVertex();
       EndPrimitive();
   }
   void main()
   {
      GenerateLine(0); // first vertex normal
       GenerateLine(1); // second vertex normal
       GenerateLine(2); // third vertex normal
   }    