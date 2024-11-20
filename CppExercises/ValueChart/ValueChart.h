#pragma once

class ValueChart
{
public:
	void load();
	void save();
	void add();
	void print();

private:
	static constexpr char s_nameFile[] = "ValueChart";
	static constexpr int s_sizeBuf = 256;
	static constexpr int s_maxNumValues = 100;

	int	m_idxLast = -1;
	char m_names[s_maxNumValues][s_sizeBuf] = {};
	int m_values[s_maxNumValues] = {};
};
