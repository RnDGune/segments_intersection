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

/*ограничение от переполнения дабла
* маск степень дабла 308, у нас берется скал¤рное произовденеи от векторного,
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

	// функция для вычесления скалярного произведнеия
	double CalculateScalarProd(const Vector3D& v);
	// функция для вычесления длины вектора произведнеия
	double CalculateLength();  
	// функция для вычесления скалярного произведнеия
	Vector3D CalculateCrossProd(const Vector3D& v); 
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

	/*функция вычесления направлющего вектора 
	* @return Vector3D end - start
	*/
	Vector3D Directional_Vector() const; 
	/*функция проверяет лежит ли точка на отркзке
	* @param 'v' вектор задающий точку
	* @return bool  true если лежит, и false если нет
	*/
	bool IsPointOn(const Vector3D& v) const; 
	Vector3D GetStart() const { // для инкапсул¤ции
		return start;
	}
	Vector3D GetEnd() const { // для инкапсул¤ции
		return end;
	}

private:
	Vector3D start;
	Vector3D end;

};

/*
* вспомогательная функция для поиска начального вектора соеденяющего отрезки.
* позволяет отрабатыват ситуации когда две крайние точки сегментов близки, а две других удалены на
* растояние порядка std::numeric_limits<double>::max(). 
* в теущей реализации можно заменить на просто start-start или end-end , поскольку от переполнения дабла 
* защищает жесткое ограничение вхождных координат
* @param segment_u первый сегмент для которго мы ищем точку пересечения
* @param segment_v первый сегмент для которго мы ищем точку пересечения
* @return pair <Vector3D, Vector3D> , первый член самый короткий вектор, второй член
* начальная точка найденого вектора
*/
std::pair <Vector3D, Vector3D>  CalculateLinkVector(const Segment3D& segment_u, const Segment3D& segment_v);

/*
* функция поиска точки пересечения двух сегментов
* @param segment_v первый сегмент для которго мы ищем точку пересечения
* @param segment_u первый сегмент для которго мы ищем точку пересечения
* @return Vector3D точку пересечени¤, или бросает исключение std::logic_error если если еЄ нет или это множество точек
*/
Vector3D Intersect(const Segment3D& segment_v, const Segment3D& segment_u); //можно было сделать  через std::optional<Vector3D> и возвращать  std::nullopt если пересечений нет


