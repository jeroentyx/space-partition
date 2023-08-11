/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Light.h
Purpose: Function declaration for the Light functions
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#pragma once
#include "glm/glm.hpp"
#include "Shader.h"

class Light
{
public:
	//constructor
	Light() :m_Color(glm::vec3(0, 0, 0)), maxBrightness(), radius() {};
	//destructor
	~Light() {}

	//Set the number of lightSphere max as 1
	int m_SphereMax = 1;

	glm::vec3 m_Color;
	glm::vec3 position[16] = { glm::vec3(0.0f,0.0f,0.0f), //sphere1
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
										 glm::vec3(0.0f,0.0f,0.0f), 
	};

	glm::vec3 lightColor[16] = {
										 glm::vec3(1.0f,0.0f,0.6f),
										 glm::vec3(0.0f,0.7f,0.7f),
										 glm::vec3(0.5f,0.5f,0.5f),
										 glm::vec3(0.2f,0.2f,0.5f),
										 glm::vec3(0.7f,0.7f,0.0f),
										 glm::vec3(0.7f,0.0f,0.0f),
										 glm::vec3(0.3f,0.3f,0.8f),
										 glm::vec3(0.3f,0.8f,0.3f),
										 glm::vec3(0.8f,0.3f,0.3f),
										 glm::vec3(0.7f,0.0f,0.7f),
										 glm::vec3(0.2f,0.2f,0.2f),
										 glm::vec3(0.1f,0.5f,0.7f),
										 glm::vec3(0.7f,0.5f,0.1f),
										 glm::vec3(0.9f,0.1f,0.9f),
										 glm::vec3(0.2f,0.4f,0.8f),
										 glm::vec3(0.8f,0.4f,0.2f),
	};

	glm::vec3 ambient[16] = { glm::vec3(0.15f,0.15f,0.15f),	//sphere1
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere2
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere3
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere4
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere5
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere6
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere7
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere8
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere9
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere10
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere11
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere12
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere13
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere14
										 glm::vec3(0.15f,0.15f,0.15f),	//sphere15
										 glm::vec3(0.15f,0.15f,0.15f)	//sphere16
	};

	glm::vec3 diffuse[16] = { glm::vec3(0.2f,0.2f,0.2f),	//sphere1
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere2
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere3
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere4
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere5
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere6
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere7
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere8
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere9
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere10
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere11
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere12
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere13
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere14
									 glm::vec3(0.2f,0.2f,0.2f),	//sphere15
									 glm::vec3(0.2f,0.2f,0.2f)	//sphere16
	};

	glm::vec3 specular[16] = { glm::vec3(1.0f, 1.0f, 1.0f),	//sphere1
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere2
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere3
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere4
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere5
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere6
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere7
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere8
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere9
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere10
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere11
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere12
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere13
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere14
									 glm::vec3(1.0f, 1.0f, 1.0f),	//sphere15
									 glm::vec3(1.0f, 1.0f, 1.0f)	//sphere16
	};

	float inner_angle[16] = { 7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f,
							  7.5f, 7.5f, 7.5f, 7.5f, 7.5f, 7.5f,
							  7.5f, 7.5f, 7.5f, 7.5f
	};

	float outer_angle[16] = { 15.5f,15.5f,15.5f,15.5f,15.5f,15.5f,
							  15.5f,15.5f,15.5f,15.5f,15.5f,15.5f,
							  15.5f,15.5f,15.5f,15.5f
	};

	float falloff[16] = { 1.f, 1.f, 1.f, 1.f, 1.f,
						 1.f, 1.f, 1.f, 1.f, 1.f,
						 1.f, 1.f, 1.f, 1.f, 1.f, 1.f
	};


	float linear = 0.7f;
	float quadratic = 1.8f;
	float constant = 1.0f;
	float maxBrightness[16];

	int lightType = 0;
	float radius[16];

	void Update(Shader* shader)
	{
		shader->SetVec3("FragColor", m_Color);
		shader->SetInt("sphere_max", m_SphereMax);
		shader->SetInt("LightType", lightType);

		//Updating the lightSphere uniforms (use UBO should be faster but lack of time - jeroen)
		for (int i = 0; i < 16; i++)
		{
			maxBrightness[i] = std::fmaxf(std::fmaxf(lightColor[i].r, lightColor[i].g), lightColor[i].b);
			radius[i] = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness[i]))) / (2.0f * quadratic);

			std::string num = std::to_string(i);

			if (lightType == 0)//PointLight
			{
				shader->SetVec3("lightColor[" + num + "]", lightColor[i]);
				shader->SetVec3("pointLights[" + num + "].position", position[i]);
				shader->SetVec3("pointLights[" + num + "].ambient", ambient[i]);
				shader->SetVec3("pointLights[" + num + "].diffuse", diffuse[i]);
				shader->SetVec3("pointLights[" + num + "].specular", specular[i]);
				shader->SetFloat("pointLights[" + num + "].constant", constant);
				shader->SetFloat("pointLights[" + num + "].linear", linear);
				shader->SetFloat("pointLights[" + num + "].quadratic", quadratic);
				shader->SetFloat("pointLights[" + num + "].Radius", radius[i]);
			}
			else if (lightType == 1) //Direction Light
			{
				shader->SetVec3("lightColor[" + num + "]", lightColor[i]);
				shader->SetVec3("dirLight[" + num + "].position", position[i]);
				shader->SetVec3("dirLight[" + num + "].direction", position[i]);
				shader->SetVec3("dirLight[" + num + "].ambient", ambient[i]);
				shader->SetVec3("dirLight[" + num + "].diffuse", diffuse[i]);
				shader->SetVec3("dirLight[" + num + "].specular", specular[i]);
			}
			else if (lightType == 2) //Spot Light
			{
				shader->SetVec3("spotLight[" + num + "].position", position[i]);
				shader->SetVec3("spotLight[" + num + "].direction", -position[i]);
				shader->SetVec3("spotLight[" + num + "].ambient", ambient[i]);
				shader->SetVec3("spotLight[" + num + "].diffuse", diffuse[i]);
				shader->SetVec3("spotLight[" + num + "].specular", specular[i]);
				shader->SetFloat("spotLight[" + num + "].constant", constant);
				shader->SetFloat("spotLight[" + num + "].linear", linear);
				shader->SetFloat("spotLight[" + num + "].quadratic", quadratic);
				shader->SetFloat("spotLight[" + num + "].cutOff", glm::cos(glm::radians(inner_angle[i])));
				shader->SetFloat("spotLight[" + num + "].outerCutOff", glm::cos(glm::radians(outer_angle[i])));
				shader->SetFloat("spotLight[" + num + "].falloff", falloff[i]);
				shader->SetFloat("spotLight[" + num + "].Radius", radius[i]);
			}
		}
	}
};