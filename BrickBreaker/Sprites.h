#pragma once

/////////////////////////////////////////Forward Declarations/////////////////////////////////////////

class Graphics;
struct Vector;

/////////////////////////////////////////Method Declarations/////////////////////////////////////////

namespace BrickBreaker
{
	/*---------------*
	 *    Sprites    *
	 *---------------*/

	class Sprites
	{
	public:
		static void				DrawBall(const Vector& position, Graphics& gfx);
	};
}
