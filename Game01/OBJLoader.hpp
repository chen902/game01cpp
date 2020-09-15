#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "RawModel.h"
#include "Loader.h"
#include "Utilities.hpp"



class OBJLoader {
public:
	static RawModel& loadObjModel(const std::string& filename, Loader& loader)
	{
		std::ifstream file;
		file.open(filename.c_str(), std::ios::in);

		std::string line; 

		std::vector <glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;

		std::getline(file, line);
		std::string header = line.substr(0, 2);

		std::string* values = nullptr;
		std::string* faces = nullptr;

		// read vertices
		while (header != "f ") {
			size_t i = line.find(" ");
			values = Utilities::split(' ', line.substr(i+1, line.length()));
			if (header == "v ") {
				vertices.push_back(glm::vec3(std::stof(values[0]), std::stof(values[1]), std::stof(values[2])));
			}
			else if (header == "vt") {
				textures.push_back(glm::vec2(std::stof(values[0]), std::stof(values[1])));
			}
			else if (header == "vn") {
				normals.push_back(glm::vec3(std::stof(values[0]), std::stof(values[1]), std::stof(values[2])));
			}

			std::getline(file, line);
			header = line.substr(0, 2);
			
			delete[] values;
		}

		//delete[] values;

		float* textures_arr = new float[vertices.size() * 2];
		float* normals_arr = new float[vertices.size() * 3];

		while (line != "" && !file.eof()) {
			if (header != "f ") {
				std::getline(file, line);
				header = line.substr(0, 2);
				continue;
			}

			size_t i = line.find(" ");
			values = Utilities::split(' ', line.substr(i + 1, line.length()));

			std::string* v1 = Utilities::split('/', values[0]);
			std::string* v2 = Utilities::split('/', values[1]);
			std::string* v3 = Utilities::split('/', values[2]);

			proccessVertex(v1, indices, textures, normals, textures_arr, normals_arr);
			proccessVertex(v2, indices, textures, normals, textures_arr, normals_arr);
			proccessVertex(v3, indices, textures, normals, textures_arr, normals_arr);

			std::getline(file, line);
			header = line.substr(0, 2);
			
			delete[] values;
		}

		file.close();

		float* vertices_arr = new float[vertices.size() * 3];

		for (size_t i = 0; i < vertices.size(); ++i) {
			glm::vec3 currentVertex = vertices.at(i);
			vertices_arr[i * 3] = currentVertex.x;
			vertices_arr[i * 3 + 1] = currentVertex.y;
			vertices_arr[i * 3 + 2] = currentVertex.z;
		}

		unsigned int* indices_arr = new unsigned int[indices.size()];

		for (size_t i = 0; i < indices.size(); ++i) {
			indices_arr[i] = indices.at(i);
		}

		RawModel& r = loader.loadToVAO(
			indices_arr, sizeof(unsigned int)*indices.size(), 
			vertices_arr, sizeof(float)*vertices.size()*3, 
			textures_arr, sizeof(float)*textures.size()*2,
			normals_arr, sizeof(float)*normals.size()*3);

		delete[] vertices_arr;
		delete[] indices_arr;

		return r;
	}

	static void proccessVertex(std::string* currentVertex, std::vector<unsigned int>& indices, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, float* texture_arr, float* normal_arr)
	{
		int currentVertexIndex = std::stoi(currentVertex[0]) - 1;
		indices.push_back(currentVertexIndex);
		
		glm::vec2 currentTexture = textures.at(std::stoi(currentVertex[1]) - 1);
		texture_arr[currentVertexIndex * 2] = currentTexture.x;
		texture_arr[currentVertexIndex * 2 + 1] = currentTexture.y;

		glm::vec3 currentNormal = normals.at(std::stoi(currentVertex[2]) - 1);
		normal_arr[currentVertexIndex * 3] = currentNormal.x;
		normal_arr[currentVertexIndex * 3 + 1] = currentNormal.y;
		normal_arr[currentVertexIndex * 3 + 2] = currentNormal.z;
	}
};