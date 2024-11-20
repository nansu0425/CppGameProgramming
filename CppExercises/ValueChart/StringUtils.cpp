#include "StringUtils.h"

#include <cassert>

char StringUtils::s_buf[StringUtils::s_sizeBuf] = {};

void StringUtils::print(const char* ptrBaseBuf)
{
	int idxBuf = 0;

	while (ptrBaseBuf[idxBuf] != '\0')
	{
		_putch(ptrBaseBuf[idxBuf]);
		++idxBuf;
	}
}

void StringUtils::print(int data)
{
	int lenStr = convertInt2Str(data);

	for (int idxBuf = 0; idxBuf < lenStr - 1; ++idxBuf)
	{
		assert(('0' <= s_buf[idxBuf]) &&
			   (s_buf[idxBuf] <= '9'));

		_putch(s_buf[idxBuf]);
	}
}

void StringUtils::printLine()
{
	print(s_buf);
	_putch('\n');
}

void StringUtils::inputLine()
{
	int idxBuf = 0;

	for (; idxBuf < s_sizeBuf - 1; ++idxBuf)
	{
		const char ch = _getch();
		_putch(ch);

		// CR 입력 받으면 입력 종료
		if (ch == '\r')
		{
			break;
		}

		s_buf[idxBuf] = ch;
	}

	s_buf[idxBuf] = '\0';
	_putch('\n');
}

const char* StringUtils::getPtrBuf()
{
	return s_buf;
}

int StringUtils::convertInt2Str(int data)
{
	if (data == 0)
	{
		s_buf[0] = '0';
		s_buf[1] = '\0';

		return 2;
	}

	int numDigits = 0;
	int copyData = data;

	while (copyData != 0)
	{
		++numDigits;
		copyData /= 10;
	}

	assert(numDigits < s_sizeBuf);

	for (int idxBuf = numDigits - 1; idxBuf >= 0; --idxBuf)
	{
		// 일의 자리 숫자를 아스키 코드로 변환
		s_buf[idxBuf] = data % 10 + '0';
		data /= 10;
	}

	s_buf[numDigits] = '\0';

	return numDigits + 1;
}

int StringUtils::convertStr2Int(const char* ptrBaseBuf)
{
	int numDigits = 0;

	// 수의 자릿수를 구한다
	while (('0' <= ptrBaseBuf[numDigits]) &&
		   (ptrBaseBuf[numDigits] <= '9'))
	{
		++numDigits;
	}
	--numDigits;

	int result = 0;
	int powTen = 1;

	for (int idxBuf = numDigits; idxBuf >= 0; --idxBuf)
	{
		result += (ptrBaseBuf[idxBuf] - '0') * powTen;
		powTen *= 10;
	}

	return result;
}
