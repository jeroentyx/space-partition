/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: BSPTree.h
Purpose: function declaration for the BSPTree
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

//BSP Node
struct BSPNode
{
	BSPNode(std::vector<Triangle>& polygons) {
		m_polygons = polygons;
	};
	BSPNode* m_front;
	BSPNode* m_back;
	std::vector<Triangle> m_polygons;
};

struct Plane
{
	glm::vec3 n; // Plane normal. (n.x) = d
	float d; // d = dot(n,p) for a given point p on the plane
};

//clipping of the plane
enum Point_
{
	POINT_IN_FRONT_OF_PLANE,
	POINT_BEHIND_PLANE,
	POINT_ON_PLANE
};

enum Plane_
{
	COPLANAR_WITH_PLANE,
	IN_FRONT_OF_PLANE,
	BEHIND_PLANE,
	STRADDLING_PLANE
};


BSPNode* BuildBSPTree(std::vector<Triangle>& polygons, std::vector<Model*>& mod, int depth,
	std::vector<int>& obj_index, std::vector<std::vector<unsigned>>& obj_indices);
Plane PickSplittingPlane(std::vector<Triangle>& polygons);
Plane GetPlaneFromPolygon(Triangle poly);
int ClassifyPointToPlane(glm::vec3 p, Plane plane);
int ClassifyPolygonToPlane(Triangle poly, Plane plane);


