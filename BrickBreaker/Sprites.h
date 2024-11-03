#pragma once

class Graphics;
struct Vector;

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
