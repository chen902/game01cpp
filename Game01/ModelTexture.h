#pragma once
class ModelTexture
{
public:
	ModelTexture(unsigned int textureID);
	~ModelTexture();

	void setShineDamper(float shine) { this->shineDamper = shine; };
	void setReflectivity(float reflectivity) { this->reflectivity = reflectivity; };

	unsigned int getTextureID() const { return textureID; };

private:
	unsigned int textureID;
	float shineDamper;
	float reflectivity;

};

