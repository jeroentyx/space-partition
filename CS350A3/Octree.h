/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Octree.h
Purpose: Function declaration for the Octree function
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <math.h>
#include "Model.h"
#include "Camera.h"
#include "Shader.h"

// Referenced  from Real time collision detection
struct OctreeNode
{
	OctreeNode() {}
	glm::vec3 octree_center; // Center point of octree node (not strictly needed)
	float octree_width; // Half the width of the node volume (not strictly needed)
	OctreeNode* pChild[8]; // Pointers to the eight children nodes
	Model* pObjList; // Linked list of objects contained at this node
	int octree_depth;

	//Helper function to draw the debug boxes
	void DrawBox(Model* mod, Camera* camera, Shader* shader,
		float aspect, bool isUseBV, bool isUseRotation, int stopdepth);
};

struct Object
{
	glm::vec3 center; // Center point for object
	float radius; // Radius of object bounding sphere
	//...
	Model* pNextObject; // Pointer to next object when linked into list
};

//Creating using the top down approach
// 
//Preallocates an octree down to a specific depth
OctreeNode* BuildOctree(std::vector<Model*> mod, glm::vec3 center, float halfWidth, int stopdepth);
int GetTriNum(std::vector<Model*> mod, glm::vec3& center, float& halfWidth, glm::vec3 color);
glm::vec3 GetCenter(std::vector<Model*> mod);
float GetLongest(std::vector<Model*> mod);


