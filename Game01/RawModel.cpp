#include "RawModel.h"

RawModel::RawModel(const unsigned int & vaoID, const size_t & verticesCount)
{
	this->vaoID = vaoID;
	this->verticesCount = verticesCount;
}

RawModel::~RawModel()
{
}
