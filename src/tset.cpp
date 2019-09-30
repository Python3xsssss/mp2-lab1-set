// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;

	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField != s.BitField)
		return 0;

	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField == s.BitField)
		return 0;

	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField tmp = BitField | s.BitField;

	TSet out(tmp);
	return out;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp = *this;

	tmp.InsElem(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp = *this;

	tmp.DelElem(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField tmp = BitField & s.BitField;

	TSet out(tmp);
	return out;
}

TSet TSet::operator~(void) // дополнение
{
	TBitField tmp = ~BitField;

	TSet out(tmp);
	return out;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	TBitField tmp(s.GetMaxPower());

	istr >> tmp;

	TSet out(tmp);
	s = out;

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int len = s.GetMaxPower();
	for (int i = 0; i < len; i++)
		ostr << s.IsMember(i);

	return ostr;
}