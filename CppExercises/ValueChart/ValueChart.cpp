#include "ValueChart.h"
#include "StringUtils.h"

#include <cassert>
#include <fstream>

void ValueChart::load()
{
	std::ifstream ifs(s_nameFile);

	if (!ifs.good())
	{
		StringUtils::print("Failed to load\n");
		return;
	}

	m_idxLast = -1;

	while (true)
	{
		char name[s_sizeBuf] = {};
		int value = 0;

		// 파일에서 name, value 쌍을 읽는다
		ifs.getline(name, s_sizeBuf);
		ifs >> value;

		// 정상적인 입력인지 확인
		if (!ifs.good())
		{
			break;
		}

		++m_idxLast;
		int idxName = 0;

		// 파일에서 읽은 name 복사
		while (name[idxName] != '\0')
		{
			m_names[m_idxLast][idxName] = name[idxName];
			++idxName;
		}

		m_names[m_idxLast][idxName] = '\0';

		// 파일에서 읽은 value 복사
		m_values[m_idxLast] = value;
	}

	assert(ifs.eof());
	StringUtils::print("Successfully loaded\n");
}

void ValueChart::save()
{
	std::ofstream ofs(s_nameFile);

	if (!ofs.good())
	{
		StringUtils::print("Failed to save\n");
	}

	for (int idxValues = 0; idxValues <= m_idxLast; ++idxValues)
	{
		ofs << m_names[idxValues] << "\n" << m_values[idxValues] << "\n";
	}

	ofs.close();
	StringUtils::print("Successfully saved\n");
}

void ValueChart::add()
{
	assert(m_idxLast < s_maxNumValues - 1);
	++m_idxLast;

	// name을 입력받는다
	StringUtils::print("Enter name: ");
	StringUtils::inputLine();
	StringUtils::write(m_names[m_idxLast], s_sizeBuf);

	// value를 입력받는다
	StringUtils::print("Enter value: ");
	StringUtils::inputLine();
	m_values[m_idxLast] = StringUtils::convertStr2Int(StringUtils::getPtrBuf());
}

void ValueChart::print()
{
	StringUtils::print("\n\tValue Chart\n");
	StringUtils::print("\t-----------\n\n");

	for (int idxValues = 0; idxValues <= m_idxLast; ++idxValues)
	{
		StringUtils::print(m_names[idxValues]);
		StringUtils::print("\t|");

		for (int count = 0; count < m_values[idxValues]; ++count)
		{
			_putch('=');
		}

		_putch('\n');
	}
}
