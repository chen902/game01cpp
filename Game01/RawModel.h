#pragma once
/* Represents a VAO/Model in GPU memory*/
class RawModel
{
public:
	RawModel(const unsigned int& vaoID, const size_t& verticesCount);
	~RawModel();
	
	// getters
	unsigned int getVaoID() const { return vaoID; }
	size_t getVerticesCount() const { return verticesCount; }

private:
	unsigned int vaoID;
	size_t verticesCount;
};

