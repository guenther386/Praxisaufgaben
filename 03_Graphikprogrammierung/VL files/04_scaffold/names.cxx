#include <iostream>

using namespace std;

int version = 1;

namespace cgv {
	int version = 2;
	namespace media {
		namespace image {
			// access to parent namespace
			int image_version = version;
			int nr_images = 0;
			class reader;
			class writer;
		}
		namespace video {
			// access to root namespace
			int image_version = ::version;
			int nr_videos = 0;
			class reader;
			class writer;
		}
	}
}

//continue definition of cgv
namespace cgv {
	namespace render {
		class context;
		namespace gl {
			// overwrites context in parent
			class context;
		}
	}
	using media::image::nr_images;
	using media::video::nr_videos;
}

// use only the context class
using cgv::render::context;
// use the whole image namespace
using namespace cgv::media::image;

void namespace_test()
{
	// symbol known through using namespace 
	cout << nr_images << " = " 
	// symbol known through using inside cgv
	     << cgv::nr_images << " = " 
	// global path to symbol
		 << cgv::media::image::nr_images;
}