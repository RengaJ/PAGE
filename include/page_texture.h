#ifndef __PAGE_TEXTURE_H
#define __PAGE_TEXTURE_H

#include <GL/glew.h>
#include <GL/glfw.h>

namespace PAGE
{
	class Texture2D
	{
		public:
			enum FileType { PNG = 0, JPEG = 1, BMP = 2, TGA = 3, TIFF = 4 };

			Texture2D();
			Texture2D(const char* name, int length, FileType type);

			~Texture2D();

			void set_format(GLenum frmt);
			void set_filename(const char* name);
			void set_file_type(FileType type);
			void set_uv_wrap(GLenum u_wrap, GLenum v_wrap);
			void set_u_wrap(GLenum u_wrap);
			void set_v_wrap(GLenum v_wrap);
			void set_min_filter(GLenum filter);
			void set_mag_filter(GLenum filter);
			void set_width_height(int w, int h);

			Texture2D& operator=(const Texture2D &texture);

			GLenum Format();
			GLenum UWrap();
			GLenum VWrap();
			GLenum MinFilter();
			GLenum MagFilter();
			FileType ImageType();
			int Height();
			int Width();
			char* Name();

			bool valid();

		private:
			int height;
			int width;
			char* filename;
			FileType fileType;
			GLenum format;
			GLenum wrap_u;
			GLenum wrap_v;
			GLenum min_filter;
			GLenum mag_filter;
	};
}
#endif
