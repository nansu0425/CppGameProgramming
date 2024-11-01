﻿#include "Sprites.h"
#include "Vector.h"
#include "Graphics.h"

/////////////////////////////////////////Method Definitions/////////////////////////////////////////

namespace BrickBreaker
{
	/*---------------*
	 *    Sprites    *
	 *---------------*/

	void Sprites::DrawBall(const Vector& position, Graphics& gfx)
	{
		const int x = static_cast<int>(position.x);
		const int y = static_cast<int>(position.y);

		gfx.PutPixel(5 + x, 0 + y, 48, 48, 48);
		gfx.PutPixel(6 + x, 0 + y, 48, 48, 48);
		gfx.PutPixel(7 + x, 0 + y, 48, 48, 48);
		gfx.PutPixel(8 + x, 0 + y, 48, 48, 48);
		gfx.PutPixel(3 + x, 1 + y, 48, 48, 48);
		gfx.PutPixel(4 + x, 1 + y, 48, 48, 48);
		gfx.PutPixel(5 + x, 1 + y, 248, 224, 96);
		gfx.PutPixel(6 + x, 1 + y, 248, 200, 72);
		gfx.PutPixel(7 + x, 1 + y, 200, 168, 72);
		gfx.PutPixel(8 + x, 1 + y, 248, 200, 72);
		gfx.PutPixel(9 + x, 1 + y, 48, 48, 48);
		gfx.PutPixel(10 + x, 1 + y, 48, 48, 48);
		gfx.PutPixel(2 + x, 2 + y, 48, 48, 48);
		gfx.PutPixel(3 + x, 2 + y, 248, 224, 96);
		gfx.PutPixel(4 + x, 2 + y, 248, 224, 96);
		gfx.PutPixel(5 + x, 2 + y, 248, 224, 96);
		gfx.PutPixel(6 + x, 2 + y, 248, 224, 96);
		gfx.PutPixel(7 + x, 2 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 2 + y, 200, 168, 72);
		gfx.PutPixel(9 + x, 2 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 2 + y, 248, 200, 72);
		gfx.PutPixel(11 + x, 2 + y, 48, 48, 48);
		gfx.PutPixel(1 + x, 3 + y, 48, 48, 48);
		gfx.PutPixel(2 + x, 3 + y, 248, 224, 96);
		gfx.PutPixel(3 + x, 3 + y, 248, 224, 96);
		gfx.PutPixel(4 + x, 3 + y, 248, 248, 248);
		gfx.PutPixel(5 + x, 3 + y, 248, 248, 248);
		gfx.PutPixel(6 + x, 3 + y, 248, 224, 96);
		gfx.PutPixel(7 + x, 3 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 3 + y, 248, 200, 72);
		gfx.PutPixel(9 + x, 3 + y, 152, 112, 16);
		gfx.PutPixel(10 + x, 3 + y, 200, 168, 72);
		gfx.PutPixel(11 + x, 3 + y, 200, 168, 72);
		gfx.PutPixel(12 + x, 3 + y, 48, 48, 48);
		gfx.PutPixel(1 + x, 4 + y, 48, 48, 48);
		gfx.PutPixel(2 + x, 4 + y, 248, 224, 96);
		gfx.PutPixel(3 + x, 4 + y, 248, 224, 96);
		gfx.PutPixel(4 + x, 4 + y, 248, 248, 248);
		gfx.PutPixel(5 + x, 4 + y, 248, 248, 248);
		gfx.PutPixel(6 + x, 4 + y, 248, 224, 96);
		gfx.PutPixel(7 + x, 4 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 4 + y, 248, 200, 72);
		gfx.PutPixel(9 + x, 4 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 4 + y, 152, 112, 16);
		gfx.PutPixel(11 + x, 4 + y, 152, 112, 16);
		gfx.PutPixel(12 + x, 4 + y, 48, 48, 48);
		gfx.PutPixel(0 + x, 5 + y, 48, 48, 48);
		gfx.PutPixel(1 + x, 5 + y, 248, 200, 72);
		gfx.PutPixel(2 + x, 5 + y, 248, 224, 96);
		gfx.PutPixel(3 + x, 5 + y, 248, 224, 96);
		gfx.PutPixel(4 + x, 5 + y, 248, 224, 96);
		gfx.PutPixel(5 + x, 5 + y, 248, 224, 96);
		gfx.PutPixel(6 + x, 5 + y, 248, 224, 96);
		gfx.PutPixel(7 + x, 5 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 5 + y, 248, 200, 72);
		gfx.PutPixel(9 + x, 5 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 5 + y, 152, 112, 16);
		gfx.PutPixel(11 + x, 5 + y, 152, 112, 16);
		gfx.PutPixel(12 + x, 5 + y, 200, 168, 72);
		gfx.PutPixel(13 + x, 5 + y, 48, 48, 48);
		gfx.PutPixel(0 + x, 6 + y, 48, 48, 48);
		gfx.PutPixel(1 + x, 6 + y, 248, 200, 72);
		gfx.PutPixel(2 + x, 6 + y, 248, 200, 72);
		gfx.PutPixel(3 + x, 6 + y, 248, 224, 96);
		gfx.PutPixel(4 + x, 6 + y, 248, 224, 96);
		gfx.PutPixel(5 + x, 6 + y, 248, 224, 96);
		gfx.PutPixel(6 + x, 6 + y, 248, 200, 72);
		gfx.PutPixel(7 + x, 6 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 6 + y, 248, 200, 72);
		gfx.PutPixel(9 + x, 6 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 6 + y, 152, 112, 16);
		gfx.PutPixel(11 + x, 6 + y, 152, 112, 16);
		gfx.PutPixel(12 + x, 6 + y, 152, 112, 16);
		gfx.PutPixel(13 + x, 6 + y, 48, 48, 48);
		gfx.PutPixel(0 + x, 7 + y, 48, 48, 48);
		gfx.PutPixel(1 + x, 7 + y, 200, 168, 72);
		gfx.PutPixel(2 + x, 7 + y, 248, 200, 72);
		gfx.PutPixel(3 + x, 7 + y, 248, 200, 72);
		gfx.PutPixel(4 + x, 7 + y, 248, 200, 72);
		gfx.PutPixel(5 + x, 7 + y, 248, 200, 72);
		gfx.PutPixel(6 + x, 7 + y, 248, 248, 248);
		gfx.PutPixel(7 + x, 7 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 7 + y, 200, 168, 72);
		gfx.PutPixel(9 + x, 7 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 7 + y, 152, 112, 16);
		gfx.PutPixel(11 + x, 7 + y, 152, 112, 16);
		gfx.PutPixel(12 + x, 7 + y, 152, 112, 16);
		gfx.PutPixel(13 + x, 7 + y, 48, 48, 48);
		gfx.PutPixel(0 + x, 8 + y, 128, 88, 0);
		gfx.PutPixel(1 + x, 8 + y, 200, 168, 72);
		gfx.PutPixel(2 + x, 8 + y, 200, 168, 72);
		gfx.PutPixel(3 + x, 8 + y, 248, 200, 72);
		gfx.PutPixel(4 + x, 8 + y, 248, 200, 72);
		gfx.PutPixel(5 + x, 8 + y, 248, 200, 72);
		gfx.PutPixel(6 + x, 8 + y, 248, 200, 72);
		gfx.PutPixel(7 + x, 8 + y, 200, 168, 72);
		gfx.PutPixel(8 + x, 8 + y, 200, 168, 72);
		gfx.PutPixel(9 + x, 8 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 8 + y, 152, 112, 16);
		gfx.PutPixel(11 + x, 8 + y, 152, 112, 16);
		gfx.PutPixel(12 + x, 8 + y, 200, 168, 72);
		gfx.PutPixel(13 + x, 8 + y, 128, 88, 0);
		gfx.PutPixel(1 + x, 9 + y, 152, 112, 16);
		gfx.PutPixel(2 + x, 9 + y, 152, 112, 16);
		gfx.PutPixel(3 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(4 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(5 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(6 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(7 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(8 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(9 + x, 9 + y, 152, 112, 16);
		gfx.PutPixel(10 + x, 9 + y, 152, 112, 16);
		gfx.PutPixel(11 + x, 9 + y, 200, 168, 72);
		gfx.PutPixel(12 + x, 9 + y, 192, 152, 56);
		gfx.PutPixel(1 + x, 10 + y, 128, 88, 0);
		gfx.PutPixel(2 + x, 10 + y, 248, 200, 72);
		gfx.PutPixel(3 + x, 10 + y, 152, 112, 16);
		gfx.PutPixel(4 + x, 10 + y, 152, 112, 16);
		gfx.PutPixel(5 + x, 10 + y, 200, 168, 72);
		gfx.PutPixel(6 + x, 10 + y, 152, 112, 16);
		gfx.PutPixel(7 + x, 10 + y, 200, 168, 72);
		gfx.PutPixel(8 + x, 10 + y, 152, 112, 16);
		gfx.PutPixel(9 + x, 10 + y, 152, 112, 16);
		gfx.PutPixel(10 + x, 10 + y, 200, 168, 72);
		gfx.PutPixel(11 + x, 10 + y, 248, 200, 72);
		gfx.PutPixel(12 + x, 10 + y, 128, 88, 0);
		gfx.PutPixel(2 + x, 11 + y, 48, 48, 48);
		gfx.PutPixel(3 + x, 11 + y, 248, 200, 72);
		gfx.PutPixel(4 + x, 11 + y, 200, 168, 72);
		gfx.PutPixel(5 + x, 11 + y, 152, 112, 16);
		gfx.PutPixel(6 + x, 11 + y, 152, 112, 16);
		gfx.PutPixel(7 + x, 11 + y, 152, 112, 16);
		gfx.PutPixel(8 + x, 11 + y, 152, 112, 16);
		gfx.PutPixel(9 + x, 11 + y, 200, 168, 72);
		gfx.PutPixel(10 + x, 11 + y, 248, 200, 72);
		gfx.PutPixel(11 + x, 11 + y, 48, 48, 48);
		gfx.PutPixel(3 + x, 12 + y, 48, 48, 48);
		gfx.PutPixel(4 + x, 12 + y, 152, 112, 16);
		gfx.PutPixel(5 + x, 12 + y, 248, 200, 72);
		gfx.PutPixel(6 + x, 12 + y, 248, 200, 72);
		gfx.PutPixel(7 + x, 12 + y, 248, 200, 72);
		gfx.PutPixel(8 + x, 12 + y, 248, 200, 72);
		gfx.PutPixel(9 + x, 12 + y, 152, 112, 16);
		gfx.PutPixel(10 + x, 12 + y, 48, 48, 48);
		gfx.PutPixel(5 + x, 13 + y, 48, 48, 48);
		gfx.PutPixel(6 + x, 13 + y, 48, 48, 48);
		gfx.PutPixel(7 + x, 13 + y, 48, 48, 48);
		gfx.PutPixel(8 + x, 13 + y, 48, 48, 48);
	}
}
