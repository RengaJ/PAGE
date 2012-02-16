#ifndef __PAGE_WINDOW_H
#define __PAGE_WINDOW_H

#include "page_graphics.h"
#include <vector>

namespace PAGE
{

	class WindowContext
	{
		public:
			WindowContext();
			void initialize(int h, int w);

		private:
			int height;
			int width;
			std::vector<GraphicsContext> contexts;
	};

}

#endif /* __PAGE_WINDOW_H */
