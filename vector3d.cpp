
#include "vector3d.h"

Vector3D::Vector3D(double x, double y, double z) :
	X(x),
	Y(y),
	Z(z)
{
};

bool Vector3D::operator== (const Vector3D& v) {
	if (std::abs(X - v.X) < EPSILON && std::abs(Y - v.Y) < EPSILON && std::abs(Z - v.Z) < EPSILON) {
		return true;
	}
	return false;
};

bool Vector3D::operator!= (const Vector3D& v) {
	return !(*this == v);
};

const Vector3D Vector3D::operator- (const Vector3D& v) const {
	double x = X - v.X;
	double y = Y - v.Y;
	double z = Z - v.Z;
	Vector3D result(x, y, z);
	return result;
};

const Vector3D Vector3D::operator+ (const Vector3D& v) const {
	double x = X + v.X;
	double y = Y + v.Y;
	double z = Z + v.Z;
	Vector3D result(x, y, z);
	return result;
};

const Vector3D Vector3D::operator* (double number) const {
	double x = X * number;
	double y = Y * number;
	double z = Z * number;
	Vector3D result(x, y, z);
	return result;
};

double Vector3D::CalculateScalarProd(const Vector3D& v) { //скалярное произведение
	return v.X * X + v.Y * Y + v.Z * Z;
};

double Vector3D::CalculateLength() { // норма вектора
	double norm = X * X + Y * Y + Z * Z;
	return std::sqrt(norm);
};

Vector3D Vector3D::CalculateCrossProd(const Vector3D& v) { //векторное произведение
	double cross_x = Y * v.Z - Z * v.Y;
	double cross_y = Z * v.X - X * v.Z;
	double cross_z = X * v.Y - Y * v.X;
	Vector3D cross_vec(cross_x, cross_y, cross_z);
	return cross_vec;
};

Segment3D::Segment3D(const Vector3D& v, const Vector3D& u) {
	start = v;
	end = u;
};

Vector3D Segment3D::Directional_Vector() const { // направляющий вектор отрезка
	return end - start;
}

bool Segment3D::IsPointOn(const Vector3D& v) const { // ф-ция проверки что точка лежит на отрезке
	Vector3D v_start = v - start;
	Vector3D v_end = v - end;
	if (v_start.CalculateScalarProd(v_end) > EPSILON) {
		return false;
	}
	return true;
};

/*
* Функция поиска точки пересечения двух сегментов
* @param segment_v первый сегмент для которго мы ищем точку пересечения
* @param segment_u первый сегмент для которго мы ищем точку пересечения
* @return Vector3D точку пересечения, или бросает исключение std::logic_error если если её нет или это множество точек
* можно было сделать  через возврат std::optional<Vector3D> и возвращать std::nullopt если пересечения нет
*/
Vector3D Intersect(const Segment3D& segment_v, const Segment3D& segment_u) {
	Vector3D v_direct_vec = segment_v.Directional_Vector();
	Vector3D u_direct_vec = segment_u.Directional_Vector();
	Vector3D link_vec = segment_u.GetStart() - segment_v.GetStart();
	/* можно получить переполнение при очень далеких точках старта отрезков, это можно улучшить
	*  добавив функцию которая будет возвращать самый короткий вектор из четверки:
	*	segment_u.GetStart() - segment_v.GetStart();
	*	segment_u.GetEnd() - segment_v.GetEnd();
	*	segment_u.GetStart() - segment_v.GetEnd();
	*	segment_v.GetStart() - segment_u.GetEnd()
	*  и уже его класть в link_vec;
	*/
	Vector3D fg = u_direct_vec.CalculateCrossProd(link_vec);
	Vector3D fe = u_direct_vec.CalculateCrossProd(v_direct_vec);
	if (fe.CalculateLength() < EPSILON) {
		if (v_direct_vec.CalculateLength() < EPSILON && segment_u.IsPointOn(v_direct_vec)) {
			return v_direct_vec;
		}
		if (u_direct_vec.CalculateLength() < EPSILON && segment_v.IsPointOn(u_direct_vec)) {
			return u_direct_vec;
		}
		if (segment_v.GetEnd() == segment_u.GetEnd()) {
			if (segment_u.IsPointOn(segment_v.GetStart()) || segment_v.IsPointOn(segment_u.GetStart())) {
				throw std::logic_error("Overlap segments");
			}
			else {
				return segment_v.GetEnd();
			}
		}
		if (segment_v.GetStart() == segment_u.GetStart()) {
			if (segment_u.IsPointOn(segment_v.GetEnd()) || segment_v.IsPointOn(segment_u.GetEnd())) {
				throw std::logic_error("Overlap segments");
			}
			else {
				return segment_v.GetStart();
			}
		}
		if (segment_v.GetEnd() == segment_u.GetStart()) {
			if (segment_v.IsPointOn(segment_u.GetEnd()) || segment_u.IsPointOn(segment_v.GetStart())) {
				throw std::logic_error("Overlap segments");
			}
			else {
				return segment_v.GetEnd();
			}
		}
		if (segment_v.GetStart() == segment_u.GetEnd()) {
			if (segment_v.IsPointOn(segment_u.GetStart()) || segment_u.IsPointOn(segment_v.GetEnd())) {
				throw std::logic_error("Overlap segments");
			}
			else {
				return segment_v.GetStart();
			}
		}
		throw std::logic_error("Parallel segment");
	}
	if (fe.CalculateScalarProd(link_vec) > EPSILON) {
		throw std::logic_error("Disjoint segment");
	}
	Vector3D intersec_point = segment_v.GetStart() + v_direct_vec * (fg.CalculateScalarProd(fe) / (fe.CalculateLength() * fe.CalculateLength())); // порядок умножения скаляра на вектор важен, определил только оператор вектор*скаляр
	if (!segment_v.IsPointOn(intersec_point) || !segment_u.IsPointOn(intersec_point)) { // проверка что точка лежит на обоих отрезках
		throw std::logic_error("Intersecting on continuation lines");
	}
	return intersec_point;
}
