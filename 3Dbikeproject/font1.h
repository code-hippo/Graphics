


#ifndef TEXT_3D_H_INCLUDED
#define TEXT_3D_H_INCLUDED

#include <string>

void t3dInit();

void t3dCleanup();

void t3dDraw2D(std::string str,
			   int hAlign, int vAlign,
			   float lineHeight = 1.5f);
class T3DLoadException {
	private:
		std::string message0;
	public:
		T3DLoadException(std::string message1);
		std::string message() const;
};

#endif
