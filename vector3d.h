#pragma once

#include<cmath>
#include<limits>
#include<stdexcept>
#include <array>
#include <algorithm>
#include <iterator>
#include <utility>
#include <tuple>

constexpr double EPSILON = std::numeric_limits<double>::epsilon(); // машинный ноль

/*ограничение от переполнени¤ дабла
* маск степент дабла 308, у нас беретс¤ скал¤рное произовденеи от векторного,
* (е70 * e70 * e70 * e70)<308
*/
const double COORD_LIMIT = 1e70; 

class Vector3D
{
public:

	Vector3D() = default;
	Vector3D(double x, double y, double z);
	bool operator == (const Vector3D& v) const; 
	bool operator != (const Vector3D& v) const;
	const Vector3D operator - (const Vector3D& v) const;
	const Vector3D operator + (const Vector3D& v) const;
	const Vector3D operator * (double number) const;
	double CalculateScalarProd(const Vector3D& v);// —кал¤рное произведенеи
	double CalculateLength();  // норма вектора
	Vector3D CalculateCrossProd(const Vector3D& v); //векторное произведение
	bool CheckLimits();

private:	

	double X;
	double Y;
	double Z;
};

class Segment3D
{
public:
	Segment3D() = default;
	Segment3D(const Vector3D& v, const Vector3D& u);
	Vector3D Directional_Vector() const; // направл¤ющий вектор отрезка
	bool IsPointOn(const Vector3D& v) const; // ф-ци¤ проверки что точка лежит на отрезке
	Vector3D GetStart() const { // дл¤ инкапсул¤ции
		return start;
	}
	Vector3D GetEnd() const { // дл¤ инкапсул¤ции
		return end;
	}

private:
	Vector3D start;
	Vector3D end;

};

std::pair <Vector3D, Vector3D>  CalculateLinkVector(const Segment3D& segment_u, const Segment3D& segment_v);

/*
* ‘ункци¤ поиска точки пересечени¤ двух сегментов
* @param segment_v первый сегмент дл¤ которго мы ищем точку пересечени¤
* @param segment_u первый сегмент дл¤ которго мы ищем точку пересечени¤
* @return Vector3D точку пересечени¤, или бросает исключение std::logic_error если если еЄ нет или это множество точек
*/
Vector3D Intersect(const Segment3D& segment_v, const Segment3D& segment_u); //можно было сделать  через std::optional<Vector3D> и возврощать  std::nullopt если пересечени¤ нет


