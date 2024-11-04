#ifndef MESH_CLASS_H
#define MECH_CLASS_H

#include <string>
#include <vector>

#include "shaders_VAO.h"
#include "shaders_EBO.h"
#include "camera_class.h"
#include "textures_class.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);
};
#endif