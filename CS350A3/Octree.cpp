/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Octree.cpp
Purpose:	Helper function to build octree, most of these function is referenced from orange book
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#include "Octree.h"
#include <iostream>

//Preallocates an octree down to a specific depth
OctreeNode* BuildOctree(std::vector<Model*> mod, glm::vec3 center, float halfWidth, int stopdepth)
{
	//Not included in the book, helper for myself to change debug colors
	glm::vec3 color(0);

	//Build the oct tree colors, if it is level 1 , do case 1 colors, otherwise other cases' color
	switch (stopdepth)
	{
	case 1:
		color = glm::vec3(0.5f, 0.2f, 0.1f);
		break;
	case 2:
		color = glm::vec3(1.0f, 1.f, 0.5f);
		break;
	case 3:
		color = glm::vec3(0.5f, 0.6f, 0.3f);
		break;
	case 4:
		color = glm::vec3(1.0f, 0.f, 0.f);
		break;
	case 5:
		color = glm::vec3(0.f, 0.0f, 1.f);
		break;
	case 6:
		color = glm::vec3(1.f, 0.f, 1.0f);
		break;
	case 7:
		color = glm::vec3(1.0f, 1.0f, 0.f);
		break;
	case 8:
		color = glm::vec3(0.0f, 1.0f, 0.f);
		break;
	default:
		break;
	}
	

	int num_tri = GetTriNum(mod, center, halfWidth, color);

	
	if (num_tri < 300 || stopdepth < 0)
	{
		return NULL;
	}

	// Construct and fill in the root of this octree
	OctreeNode *pNode = new OctreeNode;
	pNode->octree_center = center;
	pNode->octree_width = halfWidth;
	pNode->pObjList = NULL;

	//Recursively construct the eight children of the subtree
	glm::vec3 offset;
	float step = halfWidth * 0.5f;
	for (int i = 0; i < 8; i++) {
		offset.x = ((i & 1) ? step : -step);
		offset.y = ((i & 2) ? step : -step);
		offset.z = ((i & 4) ? step : -step);
		pNode->pChild[i] = BuildOctree(mod, center + offset, step, stopdepth - 1);
	}
	return pNode;
}

void OctreeNode::DrawBox(Model* mod, Camera* camera, Shader* shader,
	float aspect, bool isUseBV, bool isUseRotation, int stopdepth) 
{
	mod->position = octree_center;
	mod->scale = glm::vec3(octree_width, octree_width, octree_width);
	
	switch (stopdepth)
	{
	case 1:
		mod->color = glm::vec3(0.5f, 0.2f, 0.1f);
		break;
	case 2:
		mod->color = glm::vec3(1.0f, 1.f, 0.5f);
		break;
	case 3:
		mod->color = glm::vec3(0.5f, 0.6f, 0.3f);
		break;
	case 4:
		mod->color = glm::vec3(1.0f, 0.f, 0.f);
		break;
	case 5:
		mod->color = glm::vec3(0.f, 0.0f, 1.f);
		break;
	case 6:
		mod->color = glm::vec3(1.f, 0.f, 1.0f);
		break;
	case 7:
		mod->color = glm::vec3(1.0f, 1.0f, 0.f);
		break;
	case 8:
		mod->color = glm::vec3(0.0f, 1.0f, 0.f);
		break;
	default:
		break;
	}

	mod->Render(camera, shader, aspect, mod->position, isUseBV, isUseRotation);
	for (int i = 0; i < 8; ++i)
	{
		if (pChild[i])
		{
			pChild[i]->DrawBox(mod, camera, shader, aspect, isUseBV, isUseRotation, stopdepth-1);
		}
	}
}

int GetTriNum(std::vector<Model*> mod, glm::vec3& center, float& halfWidth, glm::vec3 color)
{
	float range = halfWidth;
	int trinum = 0;
	glm::vec3 p1(0), p2(0), p3(0);
	for (unsigned int i = 0; i < mod.size(); i++)
	{
		//Get the number of triangles in the vertices
		for (unsigned int j = 0; j < mod[i]->vertex_indices.size(); j += 3)
		{
			//Using a naive method of using bool state, if all three is true , then it is a triangle
			bool tri1 = false, tri2 = false, tri3 = false;
			p1 = mod[i]->out_vertices[mod[i]->vertex_indices[j]] + mod[i]->position;
			p2 = mod[i]->out_vertices[mod[i]->vertex_indices[j + 1]] + mod[i]->position;
			p3 = mod[i]->out_vertices[mod[i]->vertex_indices[j + 2]] + mod[i]->position;

			if (p1.x <= center.x + range && p1.x >= center.x - range
				&& p1.y <= center.y + range && p1.y >= center.y - range
				&& p1.z <= center.z + range && p1.z >= center.z - range)
			{
				tri1 = true;
				mod[i]->octree_color[mod[i]->vertex_indices[j]] = color;
			}
			if (p2.x <= center.x + range && p2.x >= center.x - range
				&& p2.y <= center.y + range && p2.y >= center.y - range
				&& p2.z <= center.z + range && p2.z >= center.z - range)
			{
				tri2 = true;
				mod[i]->octree_color[mod[i]->vertex_indices[j+1]] = color;
			}
			if (p3.x <= center.x + range && p3.x >= center.x - range
				&& p3.y <= center.y + range && p3.y >= center.y - range
				&& p3.z <= center.z + range && p3.z >= center.z - range)
			{
				tri3 = true;
				mod[i]->octree_color[mod[i]->vertex_indices[j+2]] = color;
			}
			if (tri1 == true && tri2 == true && tri3 == true)
				trinum++;
		}
	}
	return trinum;
}

//Get the center position of the Model
glm::vec3 GetCenter(std::vector<Model*> mod)
{
	glm::vec3 mid(0);
	float mod_xMax = -100, mod_xMin = 100, mod_yMin = 100, mod_yMax = -100,
		mod_zMin = 100, mod_zMax = -100;
	float x_dist = 0, y_dist = 0, z_dist = 0;
	float dist = 0;

	for (unsigned int i = 0; i < mod.size(); i++)
	{
		if (mod[i]->position.x > mod_xMax)
		{
			mod_xMax = mod[i]->position.x + mod[i]->aabb().x;
		}
		if (mod[i]->position.x < mod_xMin)
		{
			mod_xMin = mod[i]->position.x - mod[i]->aabb().x;
		}
		if (mod[i]->position.y > mod_yMax)
		{
			mod_yMax = mod[i]->position.y + mod[i]->aabb().y;
		}
		if (mod[i]->position.y < mod_yMin)
		{
			mod_yMin = mod[i]->position.y - mod[i]->aabb().y;
		}
		if (mod[i]->position.z > mod_zMax)
		{
			mod_zMax = mod[i]->position.z + mod[i]->aabb().z;
		}
		if (mod[i]->position.z < mod_zMin)
		{
			mod_zMin = mod[i]->position.z - mod[i]->aabb().z;
		}
	}

	mid = glm::vec3((mod_xMax + mod_xMin), (mod_yMax + mod_yMin), (mod_zMax + mod_zMin))*0.5f;
	x_dist = glm::abs(mod_xMax - mod_xMin);
	y_dist = glm::abs(mod_yMax - mod_yMin);
	z_dist = glm::abs(mod_zMax - mod_zMin);

	if (x_dist > y_dist && x_dist > z_dist)
	{
		dist = x_dist;
	}
	else if (y_dist > x_dist && y_dist > y_dist)
	{
		dist = y_dist;
	}
	else if (z_dist > x_dist && z_dist > y_dist)
	{
		dist = z_dist;
	}

	return mid;
}

float GetLongest(std::vector<Model*> mod)
{
	glm::vec3 mid(0);
	float mod_xMax = -100, mod_xMin = 100, mod_yMin = 100, mod_yMax = -100,
		mod_zMin = 100, mod_zMax = -100;
	float x_dist = 0, y_dist = 0, z_dist = 0;
	float dist = 0;

	for (unsigned int i = 0; i < mod.size(); i++)
	{
		if (mod[i]->position.x > mod_xMax)
		{
			mod_xMax = mod[i]->position.x + mod[i]->aabb().x;
		}
		if (mod[i]->position.x < mod_xMin)
		{
			mod_xMin = mod[i]->position.x - mod[i]->aabb().x;
		}
		if (mod[i]->position.y > mod_yMax)
		{
			mod_yMax = mod[i]->position.y + mod[i]->aabb().y;
		}
		if (mod[i]->position.y < mod_yMin)
		{
			mod_yMin = mod[i]->position.y - mod[i]->aabb().y;
		}
		if (mod[i]->position.z > mod_zMax)
		{
			mod_zMax = mod[i]->position.z + mod[i]->aabb().z;
		}
		if (mod[i]->position.z < mod_zMin)
		{
			mod_zMin = mod[i]->position.z - mod[i]->aabb().z;
		}
	}

	mid = glm::vec3((mod_xMax + mod_xMin), (mod_yMax + mod_yMin), (mod_zMax + mod_zMin))*0.5f;
	x_dist = glm::abs(mod_xMax - mod_xMin);
	y_dist = glm::abs(mod_yMax - mod_yMin);
	z_dist = glm::abs(mod_zMax - mod_zMin);

	if (x_dist > y_dist && x_dist > z_dist)
	{
		dist = x_dist;
	}
	else if (y_dist > x_dist && y_dist > y_dist)
	{
		dist = y_dist;
	}
	else if (z_dist > x_dist && z_dist > y_dist)
	{
		dist = z_dist;
	}

	return dist * 0.5f;
}


