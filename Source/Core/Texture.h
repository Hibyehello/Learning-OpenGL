#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>
#include "Error.h"

class Texture {
private:
	uint32_t m_renderer_id;
	std::string m_filepath;
	unsigned char* m_local_buffer;
	int m_width, m_height, m_bpp;
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void UnBind() const;

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
};
