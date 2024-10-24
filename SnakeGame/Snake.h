#pragma once

#include "Grid.h"
#include "Food.h"

#include <forward_list>
#include <queue>
#include <random>

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
	Snake(Grid& grid, const PosGrid& pos, int periodMove);

	void	Move(Food& food);
	void	Draw() const;
	void	SetDirection(Direction direction);
	void	Grow();
	bool	IsStop() const { return m_isStop; }

private:
	bool	IsMoveTriggered();
	void	IncludeSegmentGrow();
	void	IncreaseSpeed(int period);
	bool	IsOutGrid() const;
	bool	IsCollision() const;

private:
	Grid&			m_grid;
	PosGrid			m_pos;
	PosGrid			m_delta;
	ListSegments	m_segments;
	QueueSegments	m_segmentsGrow;
	int				m_periodMove;
	int				m_counterMove = 0;
	bool			m_isStop = false;

	static constexpr Color		s_head = Colors::Yellow;
	static constexpr Color		s_body = Colors::Green;
};
