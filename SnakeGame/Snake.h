#pragma once

#include "Grid.h"
#include "Food.h"

#include <forward_list>
#include <queue>
#include <random>

class FrameTimer;

class Snake
{
public:
	enum class Direction
	{
		LEFT,
		UP,
		RIGHT,
		DOWN,
	};

private:
	class Segment
	{
	public:
		Segment(Color color)
			: m_color(color)
		{}

		Segment(const PosGrid& pos, Color color)
			: m_pos(pos)
			, m_color(color)
		{}

		void		Move(Grid& grid, const Segment& next);
		void		Move(Grid& grid, const PosGrid& delta);
		void		Draw(const Grid& grid) const;

		PosGrid		GetPos() const { return m_pos; }
		void		SetPos(const PosGrid& pos) { m_pos = pos; }

	private:
		PosGrid		m_pos;
		Color		m_color;
	};

	using ListSegments		= std::forward_list<Segment>;
	using QueueSegments		= std::queue<Segment>;

public:
	Snake(Grid& grid, const PosGrid& pos, float periodMove, const FrameTimer& frameTimer);

	void	Move(Food& food);
	void	Draw() const;
	void	SetDirection(Direction direction);
	void	Grow();
	bool	IsStop() const { return m_isStop; }

private:
	bool	IsMoveTriggered();
	void	IncludeSegmentGrow();
	void	DecreasePeriodMove(float percentage);
	bool	IsOutGrid() const;
	bool	IsCollision() const;

private:
	Grid&				m_grid;
	PosGrid				m_pos;
	PosGrid				m_delta;
	ListSegments		m_segments;
	QueueSegments		m_segmentsGrow;
	const FrameTimer&	m_frameTimer;
	float				m_periodMove;
	float				m_sumDeltaTime = 0.0f;
	bool				m_isStop = false;

	static constexpr Color		s_head = Colors::Yellow;
	static constexpr int		s_numColorsBody = 4;
	static constexpr Color		s_colorsBody[s_numColorsBody] =
	{
		{10, 100, 32},
		{10, 130, 48},
		{18, 160, 48},
		{10, 130, 48},
	};
};
