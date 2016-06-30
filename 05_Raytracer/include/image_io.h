
#include "tiny_vec.h"
#include "mat.h"
#include <cstdio>
#include <cstdlib>
#include <string>


inline void write16bit(int n, FILE* fp) 
{ 
  unsigned char bytes[] = { (unsigned char)(n % 256), (unsigned char)(n / 256) };
  fwrite(bytes, 2, sizeof(unsigned char),fp);
}


inline bool write_tga( mat<tiny_vec<unsigned char,3> >& img, const std::string& filename) 
{
	FILE *fp =fopen(filename.c_str(),"wb");
	if(fp)
	{

		// fixed header values for the subset of TGA we use for writing
	   unsigned char TGAHeaderColor[12] = 
	  { 0,// 0 ID length = no id
		0,// 1 color map type = no color map
		2,// 2 image type = uncompressed true color
		0, 0, 0, 0, 0,// color map spec = empty
		0, 0,  // x origin of image 
		0, 0   // y origin of image
	  };
	
	   fwrite(TGAHeaderColor, 12, sizeof(unsigned char),fp);
 
	  write16bit(img.w(),fp);  
	  write16bit(img.h(),fp);  
 
 
	   putc(24,fp); 
	   putc(0x00,fp);
	   unsigned char r,g,b;
	   for(int y = (int)img.h()-1; y >= 0; y--)
		   for(int x = 0; x < (int)img.w(); x++)
		   {
			   r = img(x,y)[0];
			   g = img(x,y)[1];
			   b = img(x,y)[2];
			 
   
			   fwrite((void*)&b,1 , sizeof(char),fp);
			   fwrite((void*)&g,1 , sizeof(char),fp);
			   fwrite((void*)&r,1 , sizeof(char),fp);
			  

		   }


	   fclose(fp);
	   return true;
	}
	return false;
}


inline bool write_bmp(const mat<tiny_vec<unsigned char,3> >& img, const std::string& filename)
{
	
    unsigned short width = (unsigned short) img.w();
	unsigned short height = (unsigned short) img.h();
	const unsigned char* data = (const unsigned char*)img.begin();
	
	FILE* fp = fopen(filename.c_str(), "wb");
	if (!fp) 
	{
		std::cerr << "can't open file for writing: "<< filename<<"\n";

		return false;
	}
	
	bool success = fp != 0;
	if (success) 
	{
		static unsigned char bmp_header[54] = 
		{
			66,  77,  90,   0,   0,   0,   0,   0,   0,   0,  54,   0,   0,   0,  40,   0,   0,   0,   4,   1,   0,   0,   3,   0,   0,   0,   1,   0,  24,   0,   0,   0,   0,   0,  36,   0,   0,   0, 196,  14,   0,   0, 196,  14,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 
		};

		((unsigned short*)bmp_header)[9]  = width;
		((unsigned short*)bmp_header)[11] = height;
		bool success = fwrite(bmp_header, 1, 54, fp) == 54;
		if (success) 
		{
			 int bytes_per_line = width*3;
			data += (height-1)*bytes_per_line;
			for (unsigned short y = 0; success && y < height; ++y) 
			{
				for (unsigned short x = 0; x < width; ++x, data += 3)
				{
					
					unsigned char col[3] = { data[2], data[1], data[0] };
					if (!(success = fwrite(col, 1, 3, fp) == 3) )
						break;
				}
				data -= 2*bytes_per_line;
		

			}
		}
		if(!success)
			std::cerr<< "could not write bmp header\n";
		fclose(fp);
		return success;

	}
	return success;
}
