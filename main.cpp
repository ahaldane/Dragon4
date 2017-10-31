/******************************************************************************
  Copyright (c) 2014 Ryan Juckett
  http://www.ryanjuckett.com/

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

  3. This notice may not be removed or altered from any source
     distribution.
******************************************************************************/
#include "PrintFloat.h"
#include <float.h>
#include <math.h>
#include <string.h>



//******************************************************************************
//******************************************************************************
static void TestFormat_F32(tC8 * pBuffer, tU32 bufferSize, tPrintFloatFormat format, tS32 precision, tF32 value, const tC8 * pValueStr)
{
	tU32 printLen = PrintFloat32(pBuffer, bufferSize, value, format, precision);
	RJ_ASSERT( pBuffer[printLen] == '\0' );
	RJ_ASSERT( strcmp(pBuffer, pValueStr) == 0 );
}

//******************************************************************************
//******************************************************************************
static void TestFormat_F64(tC8 * pBuffer, tU32 bufferSize, tPrintFloatFormat format, tS32 precision, tF64 value, const tC8 * pValueStr)
{
	tU32 printLen = PrintFloat64(pBuffer, bufferSize, value, format, precision);
	RJ_ASSERT( pBuffer[printLen] == '\0' );
	RJ_ASSERT( strcmp(pBuffer, pValueStr) == 0 );
}

//******************************************************************************
//******************************************************************************
int main()
{
	const tU32 valBuffSize = 2048;
	tC8 valBuff[valBuffSize];

	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, -1,   1.0f,    "1");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, -1,   1.0f,    "1e+000");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, -1,   10.234f, "10.234");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, -1,  -10.234f, "-10.234");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, -1,   10.234f, "1.0234e+001");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, -1,  -10.234f, "-1.0234e+001");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, -1,   1000.0f, "1000");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional,  0,   1.0f,    "1");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific,  0,   1.0f,    "1e+000");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional,  0,   10.234f, "10");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional,  0,  -10.234f, "-10");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific,  0,   10.234f, "1e+001");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific,  0,  -10.234f, "-1e+001");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional,  2,  10.234f,  "10.23");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific,  2,  10.234f,  "1.02e+001");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific,  16,  9.9999999999999995e-008,  "1.0000000000000000e-007");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific,  16,  9.8813129168249309e-324,  "0.9881312916824931e-323");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific,  16,  9.9999999999999694e-311,  "0.9999999999999969e-310");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific,  -1,  9.9999999999999995e-008,  "1e-007");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific,  -1,  9.8813129168249309e-324,  "1e-323");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific,  -1,  9.9999999999999694e-311,  "1e-310");

	// test rounding
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 10, 3.14159265358979323846f, "3.1415927410"); // 3.1415927410 is closest tF32 to PI
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, 10, 3.14159265358979323846f, "3.1415927410e+000");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 10, 3.14159265358979323846,  "3.1415926536");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific, 10, 3.14159265358979323846,  "3.1415926536e+000");

	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 5, 299792458.0f, "299792448.00000"); // 299792448 is closest tF32 to 299792458
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, 5, 299792458.0f, "2.99792e+008");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 5, 299792458.0, "299792458.00000");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific, 5, 299792458.0, "2.99792e+008");
	
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 25, 3.14159265358979323846f, "3.1415927410125732421875000");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 50, 3.14159265358979323846,  "3.14159265358979311599796346854418516159057617187500");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, -1, 3.14159265358979323846,  "3.141592653589793");

	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific, -1, 1e23,  "1e+023");

	// smallest numbers
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 149, powf(0.5, 126 + 23), "0.00000000000000000000000000000000000000000000140129846432481707092372958328991613128026194187651577175706828388979108268586060148663818836212158203125");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 1074, pow(0.5, 1022 + 52), "0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000004940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954457177309266567103559397963987747960107818781263007131903114045278458171678489821036887186360569987307230500063874091535649843873124733972731696151400317153853980741262385655911710266585566867681870395603106249319452715914924553293054565444011274801297099995419319894090804165633245247571478690147267801593552386115501348035264934720193790268107107491703332226844753335720832431936092382893458368060106011506169809753078342277318329247904982524730776375927247874656084778203734469699533647017972677717585125660551199131504891101451037862738167250955837389733598993664809941164205702637090279242767544565229087538682506419718265533447265625");

	// largest numbers
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 0, FLT_MAX, "340282346638528859811704183484516925440");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 0, DBL_MAX, "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368");

	// test trailing zeros
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 3,  1.0f, "1.000");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 3,  1.0f, "1.000");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, 3,  1.0f, "1.000e+000");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific, 3,  1.0f, "1.000e+000");

	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Positional, 3,  1.5f, "1.500");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Positional, 3,  1.5f, "1.500");
	TestFormat_F32(valBuff, valBuffSize, PrintFloatFormat_Scientific, 3,  1.5f, "1.500e+000");
	TestFormat_F64(valBuff, valBuffSize, PrintFloatFormat_Scientific, 3,  1.5f, "1.500e+000");

	// test buffer overflow
	TestFormat_F32(valBuff, 5, PrintFloatFormat_Positional, -1, 1234565789.f,   "1235");
	TestFormat_F32(valBuff, 5, PrintFloatFormat_Positional, -1, 123.4565789f,   "123.");
	TestFormat_F32(valBuff, 5, PrintFloatFormat_Positional, -1, 12.34565789f,   "12.3");
	TestFormat_F32(valBuff, 5, PrintFloatFormat_Positional, -1, 0.1234565789f,  "0.12");
	TestFormat_F32(valBuff, 5, PrintFloatFormat_Positional, -1, -0.1234565789f, "-0.1");

	TestFormat_F32(valBuff, 5, PrintFloatFormat_Scientific, -1, 1234565789.f,  "1.23");
	TestFormat_F32(valBuff, 1, PrintFloatFormat_Scientific, -1, 1234565789.f,  "");
	TestFormat_F32(valBuff, 2, PrintFloatFormat_Scientific, -1, 1234565789.f,  "1");
	TestFormat_F32(valBuff, 3, PrintFloatFormat_Scientific, -1, 1234565789.f,  "1.");
	TestFormat_F32(valBuff, 4, PrintFloatFormat_Scientific, -1, 12.f,          "1.2");
	TestFormat_F32(valBuff, 5, PrintFloatFormat_Scientific, -1, 12.f,          "1.2e");
	TestFormat_F32(valBuff, 6, PrintFloatFormat_Scientific, -1, 12.f,          "1.2e+");
	TestFormat_F32(valBuff, 8, PrintFloatFormat_Scientific, -1, 12.f,          "1.2e+00");
	TestFormat_F32(valBuff, 9, PrintFloatFormat_Scientific, -1, 12.f,          "1.2e+001");
	TestFormat_F32(valBuff, 9, PrintFloatFormat_Scientific, -1, -12.f,         "-1.2e+00");

	// test rounding up trailing 9s
	TestFormat_F32(valBuff, 7, PrintFloatFormat_Positional, -1, 1000.4999f,   "1000.5");
	TestFormat_F32(valBuff, 7, PrintFloatFormat_Positional, -1, 1000.9999f,   "1001");
	TestFormat_F32(valBuff, 7, PrintFloatFormat_Positional, -1,  999.9999f,   "1000");

	return 0;
}

