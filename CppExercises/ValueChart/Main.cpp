#include "StringUtils.h"
#include "ValueChart.h"

int main()
{
	ValueChart valueChart;

	while (true)
	{
		StringUtils::print("(l)oad (s)ave (a)dd (q)uit or (p)rint?\n");
		StringUtils::inputLine();

		// 두 글자 이상 입력
		if (StringUtils::getPtrBuf()[1] != '\0')
		{
			StringUtils::print("Invalid input: ");
			StringUtils::printLine();

			continue;
		}

		switch (StringUtils::getPtrBuf()[0])
		{
		case 'l':
			valueChart.load();
			break;

		case 's':
			valueChart.save();
			break;

		case 'a':
			valueChart.add();
			break;

		case 'q':
			return 0;

		case 'p':
			valueChart.print();
			break;

		default:
			StringUtils::print("Invalid input: ");
			StringUtils::printLine();

			break;
		}
	}

	return -1;
}
