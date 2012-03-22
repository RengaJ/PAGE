#include "page_texture.h"

#include <stdlib.h>
#include <string.h>

using namespace PAGE;

Texture2D::Texture2D()
{
	filename = NULL;
	format = GL_RGB;
	wrap_u = GL_REPEAT;
	wrap_v = GL_REPEAT;
	min_filter = GL_LINEAR;
	mag_filter = GL_LINEAR;

	width = 64;
	height = 64;
}

Texture2D::Texture2D(const char* name, int length, Texture2D::FileType type)
{
	filename = (char*)malloc(length+1);
	strncpy(filename,name,length);

	filename[length] = '\0';

	fileType = type;

	format = GL_RGB;
	wrap_u = GL_REPEAT;
	wrap_v = GL_REPEAT;
	min_filter = GL_LINEAR;
	mag_filter = GL_LINEAR;

	width = 64;
	height = 64;
}

Texture2D::~Texture2D()
{
	if (filename != NULL)
		free(filename);

	filename = NULL;
}

void Texture2D::set_format(GLenum frmt)
{
	format = frmt;
}

void Texture2D::set_filename(const char* name)
{
	if (filename != NULL)
	{
		free(filename);
		filename = NULL;
	}

	filename = (char*)malloc(strlen(name)+1);
	strncpy(filename,name,strlen(name));

	filename[strlen(name)] = '\0';
}

void Texture2D::set_file_type(Texture2D::FileType type)
{
	fileType = type;
}

void Texture2D::set_uv_wrap(GLenum u_wrap, GLenum v_wrap)
{
	wrap_u = u_wrap;
	wrap_v = v_wrap;
}

void Texture2D::set_min_filter(GLenum filter)
{
	min_filter = filter;
}

void Texture2D::set_mag_filter(GLenum filter)
{
	mag_filter = filter;
}

void Texture2D::set_u_wrap(GLenum u_wrap)
{
	wrap_u = u_wrap;
}

void Texture2D::set_v_wrap(GLenum v_wrap)
{
	wrap_v = v_wrap;
}

void Texture2D::set_width_height(int w, int h)
{
	width = w;
	height = h;
}

GLenum Texture2D::Format()
{
	return format;
}

GLenum Texture2D::UWrap()
{
	return wrap_u;
}

GLenum Texture2D::VWrap()
{
	return wrap_v;
}

GLenum Texture2D::MinFilter()
{
	return min_filter;
}

GLenum Texture2D::MagFilter()
{
	return mag_filter;
}

Texture2D::FileType Texture2D::ImageType()
{
	return fileType;
}

char* Texture2D::Name()
{
	return filename;
}


int Texture2D::Height()
{
	return height;
}

int Texture2D::Width()
{
	return width;
}

Texture2D Texture2D::operator=(const Texture2D &texture)
{
    if (this == &texture)
        return *this;
    height = texture.height;
    width = texture.width;

	if (filename != NULL)
	{
		free(filename);
		filename = NULL;
	}

	filename = (char*)malloc(strlen(texture.filename)+1);
	strncpy(filename,texture.filename,strlen(texture.filename));

	filename[strlen(texture.filename)] = '\0';


    fileType = texture.fileType;
    wrap_u = texture.wrap_u;
    wrap_v = texture.wrap_v;
    min_filter = texture.min_filter;
    mag_filter = texture.mag_filter;

    return *this;
}
