#include "Snake.h"
#include "Keyboard.h"
#include "FrameTimer.h"

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

Snake::Snake(Grid& grid, const PosGrid& pos, float periodMove, const FrameTimer& frameTimer)
	: m_grid(grid)
	, m_pos(pos)
	, m_periodMove(periodMove)
	, m_frameTimer(frameTimer)
{
	m_segments.emplace_front(m_pos, s_head);
	grid.SetColorCell(m_pos, s_head);
	grid.SetTypeOccupied(m_pos, ObjectType::SNAKE);
}

void Snake::Move(Food& food)
{
	if (m_isStop || !IsMoveTriggered())
	{
		return;
	}

	if (!IsOutGrid())
	{
		m_isStop = true;
		return;
	}

	bool growed = false;

	if (!m_segmentsGrow.empty())
	{
		growed = true;
		IncludeSegmentGrow();
		DecreasePeriodMove(15.0f);
	}

	auto next = m_segments.begin();
	auto cur = next;
	++next;

	if (!growed)
	{
		m_grid.SetTypeOccupied((*cur).GetPos(), ObjectType::NONE);
	}

	if (IsCollision())
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

	if (m_grid.GetTypeOccupied(m_pos) == ObjectType::FOOD)
	{
		food.Respawn();
		Grow();
	}

	m_grid.SetTypeOccupied(m_pos, ObjectType::SNAKE);
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
	if (m_sumDeltaTime < m_periodMove)
	{
		m_sumDeltaTime += m_frameTimer.GetSecondsDeltaTime();
		return false;
	}

	m_sumDeltaTime = 0.0f;
	
	return true;
}

void Snake::IncludeSegmentGrow()
{
	Segment& segIncluded = m_segmentsGrow.front();
	segIncluded.SetPos(m_segments.front().GetPos());

	m_segments.emplace_front(segIncluded);
	m_segmentsGrow.pop();
}

void Snake::Grow()
{
	static int s_idxNextColorBody = 0;
	static int s_diffIdx = 1;

	m_segmentsGrow.emplace(s_colorsBody[s_idxNextColorBody]);
	s_idxNextColorBody += s_diffIdx;

	if (s_idxNextColorBody == s_numColorsBody - 1)
	{
		s_diffIdx = -1;
	}
	else if (s_idxNextColorBody == 0)
	{
		s_diffIdx = 1;
	}
}

void Snake::DecreasePeriodMove(float percentage)
{
	m_periodMove *= 1.0f - percentage / 100.0f;
}

bool Snake::IsOutGrid() const
{
	PosGrid next = m_pos + m_delta;

	return ((0 <= next.row) && 
			(next.row < m_grid.s_lenRow) &&
			(0 <= next.col) &&
			(next.col < m_grid.s_lenCol));
}

bool Snake::IsCollision() const
{
	const ObjectType nextPos = m_grid.GetTypeOccupied(m_pos + m_delta);

	return ((nextPos == ObjectType::SNAKE) ||
			(nextPos == ObjectType::OBSTACLE) ||
			(nextPos == ObjectType::WALL));
}
