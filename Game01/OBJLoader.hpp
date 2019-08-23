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

		std::getline(file, line);
		std::string header = line.substr(0, 2);

		std::string* values = nullptr;
		std::string* faces = nullptr;

		// read vertices
		while (header != "f ") {
			values = Utilities::split(' ', line.substr(2, line.length()));
			if (header == "v ") {
				vertices.push_back(glm::vec3(std::stof(values[0]), std::stof(values[1]), std::stof(values[2])));
			}
			else if (header == "vt") {

			}
			else if (header == "vn") {

			}

			std::getline(file, line);
			header = line.substr(0, 2);
		}

		delete[] values;

		std::string* vertex1 = nullptr;
		std::string* vertex2 = nullptr;
		std::string* vertex3 = nullptr;

		do {
			// "[2/3/4, 4/5/6, 1/2/3]"
			faces = Utilities::split(' ', line.substr(2, line.length()));
			
			vertex1 = Utilities::split('/', faces[0]);
			vertex2 = Utilities::split('/', faces[1]);
			vertex3 = Utilities::split('/', faces[2]);

			indices.push_back(std::stoi(vertex1[0]) - 1);
			indices.push_back(std::stoi(vertex2[0]) - 1);
			indices.push_back(std::stoi(vertex3[0]) - 1);

			delete[] vertex1;
			delete[] vertex2;
			delete[] vertex3;
			delete[] faces;

		} while (std::getline(file, line) && line.substr(0, 2) == "f ");

		float* vertices_arr = new float[vertices.size() * 3];

		for (size_t i = 0; i < vertices.size(); ++i) {
			vertices_arr[i * 3] = vertices.at(i).x;
			vertices_arr[i * 3 + 1] = vertices.at(i).y;
			vertices_arr[i * 3 + 2] = vertices.at(i).z;
		}

		unsigned int* indices_arr = new unsigned int[indices.size()];

		for (size_t i = 0; i < indices.size(); ++i) {
			indices_arr[i] = indices.at(i);
		}

		RawModel& r = loader.loadToVAO(indices_arr, sizeof(unsigned int)*indices.size(), vertices_arr, sizeof(float)*vertices.size()*3);

		delete[] vertices_arr;
		delete[] indices_arr;

		return r;
	}

	static void proccessVertex(std::string* currentVertex, std::vector<int>& indices)
	{


	}
};