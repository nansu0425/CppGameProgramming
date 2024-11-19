#include <conio.h>
#include <assert.h>

constexpr size_t g_sizeBuf = 50;

void printInt(int i);
void inputInt(char* ptrBaseBuf);
int convertIntToStr(int i, char* ptrBaseBuf);
int convertStrToInt(const char* ptrBaseBuf);
void printFibonacci(int nth);

int main()
{
	char buf[g_sizeBuf];

	inputInt(buf);
	printFibonacci(convertStrToInt(buf));

	return 0;
}

void printInt(int i)
{
	char buf[g_sizeBuf];
	int lenStr = convertIntToStr(i, buf);

	for (int idxBuf = 0; idxBuf < lenStr - 1; ++idxBuf)
	{
		assert(('0' <= buf[idxBuf]) &&
			   (buf[idxBuf] <= '9'));

		_putch(buf[idxBuf]);
	}
}

void inputInt(char* ptrBaseBuf)
{
	int idxBuf = 0;

	for (; idxBuf < g_sizeBuf - 1; ++idxBuf)
	{
		const char ch = _getch();
		_putch(ch);

		// 숫자가 아니면 더 이상 입력받지 않는다
		if ((ch < '0') ||
			(ch > '9'))
		{
			break;
		}

		ptrBaseBuf[idxBuf] = ch;
	}

	ptrBaseBuf[idxBuf] = '\0';
	_putch('\n');
}

int convertIntToStr(int i, char* ptrBaseBuf)
{
	if (i == 0)
	{
		ptrBaseBuf[0] = '0';
		ptrBaseBuf[1] = '\0';

		return 2;
	}

	int numDigits = 0;
	int copyI = i;

	while (copyI != 0)
	{
		++numDigits;
		copyI /= 10;
	}

	assert(numDigits < g_sizeBuf);

	for (int idxBuf = numDigits - 1; idxBuf >= 0; --idxBuf)
	{
		// 일의 자리 숫자를 아스키 코드로 변환
		ptrBaseBuf[idxBuf] = i % 10 + '0';
		i /= 10;
	}

	ptrBaseBuf[numDigits] = '\0';

	return numDigits + 1;
}

int convertStrToInt(const char* ptrBaseBuf)
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

void printFibonacci(int nth)
{
	assert(nth > 0);

	if (nth > 0)
	{
		_putch('0');
		_putch(' ');
	}

	if (nth > 1)
	{
		_putch('1');
		_putch(' ');
	}

	if (nth < 3)
	{
		return;
	}

	int* ptrTableFibo = new int[nth];
	ptrTableFibo[0] = 0;
	ptrTableFibo[1] = 1;

	for (int idxTable = 2; idxTable < nth; ++idxTable)
	{
		ptrTableFibo[idxTable] = ptrTableFibo[idxTable - 1] + ptrTableFibo[idxTable - 2];
		printInt(ptrTableFibo[idxTable]);
		_putch(' ');
	}

	delete[] ptrTableFibo;
}
