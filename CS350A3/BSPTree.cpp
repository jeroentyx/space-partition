/* Start Header -------------------------------------------------------
Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: BSPTree.cpp
Purpose: Helper function to build BSPTree
Language: MSVC C++
Platform: VS2019, Windows
Project: cs350A3
Author: Jeroen Tan , yixujeroen.tan
Creation date: 8/10/2022
End Header --------------------------------------------------------*/

#include "BSPTree.h"

#define MAX_DEPTH 8
#define MIN_LEAF_SIZE 300

BSPNode* BuildBSPTree(std::vector<Triangle>& polygons, std::vector<Model*>& mod, int depth,
	std::vector<int>& obj_index, std::vector<std::vector<unsigned>>& obj_indices)
{
	//using leaf storing

	//using random to randomize different colors
	float r = (rand() % 100) / 100.f;
	float g = (rand() % 100) / 100.f;
	float b = (rand() % 100) / 100.f;

	glm::vec3 color(r, g, b);

	//Return NULL Tree if there are no polygons
	if (polygons.empty()) return NULL;

	//Get number of polygons in the input vector
	int numPolygons = polygons.size();

	//if criterion for a leaf is matched, create a leaf node 
	//from the remaining polygon 
	if (depth <= 0 || numPolygons <= MIN_LEAF_SIZE)
		return new BSPNode(polygons);

	BSPNode* pNode = new BSPNode(polygons);

	//Select the best possible partitioning plane based on the input geometry
	Plane splitPlane = PickSplittingPlane(polygons);
	std::vector<Triangle> frontList, backList;
	std::vector<int> front_obj_index, back_obj_index;
	std::vector<std::vector<unsigned>> front_obj_indices, back_obj_indices;

	//Test each polygon against the dividing plane, adding them
	//to the front list, back list or both as appropriate
	for (int i = 0; i < numPolygons; i++)
	{
		mod[obj_index[i]]->bsptree_color[obj_indices[i][0]] = color;
		mod[obj_index[i]]->bsptree_color[obj_indices[i][1]] = color;
		mod[obj_index[i]]->bsptree_color[obj_indices[i][2]] = color;
		Triangle poly = polygons[i];
		switch (ClassifyPolygonToPlane(poly, splitPlane))
		{
		case COPLANAR_WITH_PLANE:
			//what's done in this case depends on what type of tree is being built
			//for a node-storing tree, the polygon is stored inside
			//the node at this level. As for here, a leaf storing tree in this assignment3
			//coplanar polygon are send to either side of the plane. In this case, 
			//to the front side by falling through to the next case
			break;
		case IN_FRONT_OF_PLANE:
			frontList.push_back(poly);
			front_obj_index.push_back(obj_index[i]);
			front_obj_indices.push_back(obj_indices[i]);
			break;
		case BEHIND_PLANE:
			backList.push_back(poly);
			back_obj_index.push_back(obj_index[i]);
			back_obj_indices.push_back(obj_indices[i]);
			break;
		case STRADDLING_PLANE:
			//	Split polygon to plane and send a part to each side of the plane
			frontList.push_back(poly);
			backList.push_back(poly);
			front_obj_index.push_back(obj_index[i]);
			back_obj_index.push_back(obj_index[i]);
			front_obj_indices.push_back(obj_indices[i]);
			back_obj_indices.push_back(obj_indices[i]);
			break;
		}
	}
	//	 Recursively build child subtrees and return new tree root combining them
	pNode->m_front = BuildBSPTree(frontList, mod, depth - 1, front_obj_index, front_obj_indices);
	pNode->m_back = BuildBSPTree(backList, mod, depth - 1, back_obj_index, back_obj_indices);
	return pNode;
}

//Given a vector of polygons, attempts to compute a good splitting plane
Plane PickSplittingPlane(std::vector<Triangle>& polygons)
{
	//Blend factor for optimizing for balance or split ( should be tweaked) - book
	const float K = 0.8f;

	//Variables for tracking best splitting plane seen so far
	Plane bestPlane;
	float bestScore = FLT_MAX;

	//Try the plane for each polygon as a dividing plane
	for (unsigned int i = 0; i < polygons.size(); i++) {
		int numInFront = 0, numBehind = 0, numStraddling = 0;
		Plane plane = GetPlaneFromPolygon(polygons[i]);

		//Test against all other polygon
		for (unsigned int j = 0; j < polygons.size(); j++)
		{
			//Ignore testing again self
			if (i == j) continue;

			//Keep standing count of the various poly-plane relationships
			switch (ClassifyPolygonToPlane(polygons[j], plane))
			{
			case COPLANAR_WITH_PLANE:
				//Coplanar polygons treated as being in front of the plane
				break;
			case IN_FRONT_OF_PLANE:
				numInFront++;
				break;
			case BEHIND_PLANE:
				numBehind++;
				break;
			case STRADDLING_PLANE:
				numStraddling++;
				break;
			}
		}

		//Compute score as a weighted combination ( based on K , with k in range) 
		// 0...1 between balance and split ( lower score is better ) 
		float score = K * numStraddling + (1.0f - K) * glm::abs(numInFront - numBehind);
		if (score < bestScore) {
			bestScore = score;
			bestPlane = plane;
		}
	}
	return bestPlane;
}

//Function to classify point p to a plane thickened by a given thickness epsilon
int ClassifyPointToPlane(glm::vec3 p, Plane plane)
{
	//compute the signed distance of the point from plane
	float dist = glm::dot(plane.n, p) - plane.d;
	float epsilon = std::numeric_limits<float>::epsilon();
	float PLANE_THICKNESS_EPSILON = epsilon;

	//Classify p based on the signed distane
	if (dist > PLANE_THICKNESS_EPSILON)
		return POINT_IN_FRONT_OF_PLANE;
	if (dist < -PLANE_THICKNESS_EPSILON)
		return POINT_BEHIND_PLANE;
	return POINT_ON_PLANE;
}

//Referenced from Chapter 8 BSP Tree Hierachy
//Return value specifying whether the polygon "poly" lies in front of 
//behind of, on, or straddles on the plane 'Plane'
int ClassifyPolygonToPlane(Triangle poly, Plane plane)
{
	int numInFront = 0, numBehind = 0;
	int numVerts = 3;
	for (int i = 0; i < numVerts; i++)
	{
		glm::vec3 p = poly.pt[i];
		switch (ClassifyPointToPlane(p, plane))
		{
		case POINT_IN_FRONT_OF_PLANE:
			numInFront++;
			break;
		case POINT_BEHIND_PLANE:
			numBehind++;
			break;
		}
	}

	//if vertices is on both side of the plane, the polygon is straddling
	if (numBehind != 0 && numInFront != 0)
		return STRADDLING_PLANE;

	//if one of more vertices in front of the plane and no vertices behind the 
	// plane , the polygon lies in front of the plane
	if (numInFront != 0)
		return IN_FRONT_OF_PLANE;

	//The polygon lies behind the plane if no vertices is in front of the plane
	if (numBehind != 0)
		return BEHIND_PLANE;

	//All vertices lies on the plane so the polygon is coplanar with the plane
	return COPLANAR_WITH_PLANE;
}

Plane GetPlaneFromPolygon(Triangle poly)
{
	Plane p;
	p.n = glm::normalize(glm::cross(poly.pt[1] - poly.pt[0], poly.pt[2] - poly.pt[0]));
	p.d = glm::dot(p.n, poly.pt[0]);
	return p;
}


