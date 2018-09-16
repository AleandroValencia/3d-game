#include "GraphicsComponent.h"

void GraphicsComponent::SetTexture(std::string _filePath)
{
	SDL_Surface* image = IMG_Load(_filePath.c_str());

	if (image == nullptr)
	{
		printf("Error: Could not find texture path: %s\n", _filePath.c_str());
	}
	else
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		textureSet = true;

#if _DEBUG
		printf("fileName %s loaded!\n", _filePath.c_str());
#endif
	}
}
