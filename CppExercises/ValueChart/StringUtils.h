#pragma once

#include <conio.h>

class StringUtils
{
private:
	static constexpr int	s_sizeBuf = 1024;

public:
	static void				print(const char* ptrBaseBuf);
	static void				print(int data);
	static void				printLine();
	static void				inputLine();
	static const char*		getPtrBuf();

private:
	static int				convertInt2Str(int data);
	static int				convertStr2Int(const char* ptrBaseBuf);

private:
	static char				s_buf[s_sizeBuf];
};
