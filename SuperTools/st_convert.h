#pragma once

BOOL Dec2TextA(LPCSTR lpDecimal, int len, byte *lpOut, int outLen);
BOOL Dec2TextW(LPCWSTR lpDecimal, int len, byte *lpOut, int outLen);

BOOL Hex2TextA(LPCSTR lpHex, int len, byte *lpOut, int outLen);
BOOL Hex2TextW(LPCWSTR lpHex, int len, byte *lpOut, int outLen);

BOOL Text2HexA(byte* lpText, int len, CStringA &szOut);
BOOL Text2HexW(byte* lpText, int len, CStringW &szOut);

BOOL Hex2IntA(LPCSTR lpHex, int &outValue);
BOOL Hex2IntW(LPCWSTR lpHex, int &outValue);

BOOL Hex2FloatA(LPCSTR lpHex, float &outValue);
BOOL Hex2FloatW(LPCWSTR lpHex, float &outValue);

BOOL Hex2DoubleA(LPCSTR lpHex, double &outValue);
BOOL Hex2DoubleW(LPCWSTR lpHex, double &outValue);


