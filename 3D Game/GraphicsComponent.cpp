#include "GraphicsComponent.h"

void GraphicsComponent::SetTexture(GLuint _texture)
{
	////** load texture
	//glGenTextures(1, &m_texture);
	//glBindTexture(GL_TEXTURE_2D, m_texture);

	//// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	////** loadImage and create texture
	//// Load image, create texture and generate mipmaps
	//int width, height;
	//unsigned char* image = SOIL_load_image(texFileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	////glBindTexture(GL_TEXTURE_2D, 0);

	//printf("fileName %s \n", texFileName.c_str());

	////textureSet = true;
}
