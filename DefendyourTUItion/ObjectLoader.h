#pragma once
#include "MainHeaders.h"

namespace ObjectLoader
{
	struct coordinate{
		float x, y, z;
		coordinate(float a, float b, float c)
			: x(a), y(b), z(c) { }
	};

	struct face{
		int facenum;
		bool four;
		int faces[4];
		face(int facen, int f1, int f2, int f3)
			: facenum(facen)
		{
			faces[0] = f1;
			faces[1] = f2;
			faces[2] = f3;
			four = false;
		}

		face(int facen, int f1, int f2, int f3, int f4)
			: facenum(facen)
		{
			faces[0] = f1;
			faces[1] = f2;
			faces[2] = f3;
			faces[3] = f4;
			four = true;
		}
	};

	class ObjectLoader
	{
	public:
		ObjectLoader();
		~ObjectLoader();
		
		
		
		void loadObject(const char* filename);
	private:
		int load(const char* filename);
		void init(const char* filename);
		void display();

		int cube;
		float angle;
	};
}