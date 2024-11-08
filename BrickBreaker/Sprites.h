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
		static void				DrawGameOver(const Vector& position, Graphics& gfx);
		static void				DrawPoo(const Vector& position, Graphics& gfx);
	};
}
