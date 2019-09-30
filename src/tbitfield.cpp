// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

const int TELEM_BIT_SIZE = sizeof(TELEM) * 8;

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "Error: illegal length";
	BitLen = len;
	MemLen = (BitLen - 1) / TELEM_BIT_SIZE + 1;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > BitLen) || (n < 0))
		throw "Error: illegal n";
	return n / TELEM_BIT_SIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > BitLen) || (n < 0))
		throw "Error: illegal n";
	return 1 << (n % TELEM_BIT_SIZE);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int index = GetMemIndex(n);
	pMem[index] = pMem[index] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int index = GetMemIndex(n);
	pMem[index] = pMem[index] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;

	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;

	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;

	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int blen, mlen;
	if (BitLen < bf.BitLen)
	{
		blen = bf.BitLen;
		mlen = bf.MemLen;
	}
	else
	{
		blen = BitLen;
		mlen = MemLen;
	}

	TBitField tmp(blen);

	for (int i = 0; i < mlen; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];

	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int blen, mlen;
	if (BitLen < bf.BitLen)
	{
		blen = bf.BitLen;
		mlen = bf.MemLen;
	}
	else
	{
		blen = BitLen;
		mlen = MemLen;
	}
		
	TBitField tmp(blen);

	for (int i = 0; i < mlen; i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];

	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);

	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];

	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string tmp;
	istr >> tmp;
	size_t len = tmp.length();
	TBitField out(len);

	for (int i = 0; i < len; i++)
		if (tmp[i] == '1')
			out.SetBit(i);
		else
			out.ClrBit(i);
	bf = out;

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		ostr << bf.GetBit(i);

	return ostr;
}
