#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <list>
#include <thread>
#include <chrono>

class Texture;



class ObjModel
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
	};

	std::vector<glm::vec3>	vertices;
	std::vector<glm::vec3>	normals;
	std::vector<glm::vec2>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(const std::string& fileName, const std::string& dirName);
public:
	ObjModel(const std::string& filename, glm::vec3 position);
	ObjModel();
	~ObjModel(void);

	glm::vec3 position;
	glm::mat4 model_matrix;
	glm::vec3 model_position = glm::vec3(0);
	glm::vec3 model_velocity = glm::vec3(0);

	void draw();
};