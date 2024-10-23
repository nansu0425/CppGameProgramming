#include "Snake.h"
#include "Keyboard.h"

void Snake::Segment::Move(Grid& grid, const Segment& next)
{
	m_pos = next.m_pos;
	grid.SetColorCell(m_pos, m_color);
}

void Snake::Segment::Move(Grid& grid, const PosGrid& delta)
{
	m_pos = m_pos + delta;
	grid.SetColorCell(m_pos, m_color);
}

void Snake::Segment::Draw(const Grid& grid) const
{
	grid.Draw(m_pos);
}

Snake::Snake(Grid& grid, const PosGrid& pos, int periodMove)
	: m_grid(grid)
	, m_pos(pos)
	, m_periodMove(periodMove)
{
	m_segments.emplace_front(m_pos, s_head);
	grid.SetColorCell(m_pos, s_head);
	grid.SetCellIsOccupied(m_pos, true);
}

void Snake::Move()
{
	if (m_isStop || !IsMoveTriggered())
	{
		return;
	}

	if (!IsNextMoveValid())
	{
		m_isStop = true;
		return;
	}

	if (!m_segmentsGrow.empty())
	{
		IncludeSegmentGrow();
		IncreaseSpeed(2);
	}

	auto next = m_segments.begin();
	auto cur = next;
	++next;

	m_grid.SetCellIsOccupied((*cur).GetPos(), false);

	if (IsCollisionBody())
	{
		m_isStop = true;
		return;
	}

	while (next != m_segments.end())
	{
		(*cur).Move(m_grid, *next);
		
		++cur;
		++next;
	}

	(*cur).Move(m_grid, m_delta);
	m_pos = m_pos + m_delta;
	m_grid.SetCellIsOccupied(m_pos, true);
}

void Snake::Draw() const
{
	for (const Segment& seg : m_segments)
	{
		m_grid.Draw(seg.GetPos());
	}
}

void Snake::SetDirection(Direction direction)
{
	switch (direction)
	{
	case Snake::Direction::LEFT:
		m_delta = {0, -1};
		break;
	case Snake::Direction::UP:
		m_delta = {-1, 0};
		break;
	case Snake::Direction::RIGHT:
		m_delta = {0, 1};
		break;
	case Snake::Direction::DOWN:
		m_delta = {1, 0};
		break;
	default:
		break;
	}
}

bool Snake::IsMoveTriggered()
{
	if (m_counterMove < m_periodMove)
	{
		++m_counterMove;
		return false;
	}

	m_counterMove = 0;
	
	return true;
}

void Snake::IncludeSegmentGrow()
{
	m_segments.emplace_front(m_segmentsGrow.front());
	m_segmentsGrow.pop();
}

void Snake::Grow()
{
	m_segmentsGrow.emplace(s_body);
}

void Snake::IncreaseSpeed(int period)
{
	m_periodMove -= period;
}

bool Snake::IsNextMoveValid() const
{
	PosGrid next = m_pos + m_delta;

	return ((0 <= next.row) && 
			(next.row < m_grid.m_lenRow) &&
			(0 <= next.col) &&
			(next.col < m_grid.m_lenCol));
}

bool Snake::IsCollisionBody() const
{
	return m_grid.IsCellOccupied(m_pos + m_delta);
}
