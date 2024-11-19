#include <fstream>
#include <conio.h>
#include <cassert>

void print(const char* ptrBaseStr);
bool isIfsGood(const std::ifstream& ifs);
void print(int dataInt);
int convertInt2Str(int dataInt, char* ptrBaseBuf);

constexpr int g_sizeBuf = 20;

int main()
{
	std::ifstream ifs("Input.txt");
	
	if (!isIfsGood(ifs))
	{
		return -1;
	}
	_putch('\n');

	ifs.seekg(0, std::ios_base::end);
	const int lenFile = static_cast<int>(ifs.tellg());

	print("File Size: ");
	print(lenFile);
	_putch('\n');

	ifs.seekg(std::ios_base::beg);
	_putch('\n');

	// Text.txt 파일의 텍스트를 콘솔에 출력
	while (true)
	{
		char ch = ifs.get();

		if (!ifs.good())
		{
			_putch('\n');
			break;
		}

		_putch(ch);
	}

	isIfsGood(ifs);

	std::ofstream ofs("Output.txt");

	// 콘솔에 입력한 텍스트를 Output.txt에 기록
	while (true)
	{
		char ch = _getch();
		_putch(ch);

		if (ch == '\r')
		{
			ofs.put(ch);
			break;
		}

		ofs.put(ch);
	}
	_putch('\n');

	ifs.close();
	ofs.close();

	// 바이너리 데이터를 Binary 파일에 기록
	std::ofstream ofsBin("Binary", std::ios::binary);

	const int binaryWritten = 0x12345678;

	ofsBin.write(reinterpret_cast<const char*>(&binaryWritten), sizeof(binaryWritten));
	ofsBin.close();

	// Binary 파일의 바이너리 데이터를 읽는다
	std::ifstream ifsBin("Binary", std::ios::binary);
	
	int binaryRead = 0;

	ifsBin.read(reinterpret_cast<char*>(&binaryRead), sizeof(binaryRead));
	ifsBin.close();

	// 텍스트 데이터를 Text 파일에 기록
	std::ofstream ofsText("Text");
	
	const char textWritten[g_sizeBuf] = "abcd\nef ed\n";

	ofsText << textWritten;
	ofsText.close();

	// Text 파일의 텍스트 데이터를 읽는다
	std::ifstream ifsText("Text");

	char textRead[g_sizeBuf];

	ifsText >> textRead;
	ifsText.close();

	return 0;
}

void print(const char* ptrBaseStr)
{
	int idxStr = 0;

	while (ptrBaseStr[idxStr] != '\0')
	{
		_putch(ptrBaseStr[idxStr]);
		++idxStr;
	}
}

bool isIfsGood(const std::ifstream& ifs)
{
	if (ifs.good())
	{
		print("no error has occurred\n");
		return true;
	}

	if (ifs.eof())
	{
		print("end-of-file has been reached\n");
	}
	else if (ifs.fail())
	{
		print("an error has occurred\n");
	}
	else if (ifs.bad())
	{
		print("a non-recoverable error has occurred\n");
	}

	return false;
}

void print(int dataInt)
{
	char buf[g_sizeBuf];
	int lenStr = convertInt2Str(dataInt, buf);

	for (int idxBuf = 0; idxBuf < lenStr - 1; ++idxBuf)
	{
		assert(('0' <= buf[idxBuf]) &&
			   (buf[idxBuf] <= '9'));

		_putch(buf[idxBuf]);
	}
}

int convertInt2Str(int dataInt, char* ptrBaseBuf)
{
	if (dataInt == 0)
	{
		ptrBaseBuf[0] = '0';
		ptrBaseBuf[1] = '\0';

		return 2;
	}

	int numDigits = 0;
	int copyDataInt = dataInt;

	while (copyDataInt != 0)
	{
		++numDigits;
		copyDataInt /= 10;
	}

	assert(numDigits < g_sizeBuf);

	for (int idxBuf = numDigits - 1; idxBuf >= 0; --idxBuf)
	{
		// 일의 자리 숫자를 아스키 코드로 변환
		ptrBaseBuf[idxBuf] = dataInt % 10 + '0';
		dataInt /= 10;
	}

	ptrBaseBuf[numDigits] = '\0';

	return numDigits + 1;
}
