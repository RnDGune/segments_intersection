#include "vector3d.h"


Vector3D::Vector3D(double x, double y, double z) :
	X(x),
	Y(y),
	Z(z)
{
};

bool Vector3D::operator== (const Vector3D& v) const {
	if (std::abs(X - v.X) < EPSILON && std::abs(Y - v.Y) < EPSILON && std::abs(Z - v.Z) < EPSILON) {
		return true;
	}
	return false;
};

bool Vector3D::operator!= (const Vector3D& v) const {
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

bool Vector3D::CheckLimits() {
	if (std::abs(X) > COORD_LIMIT || std::abs(Y) > COORD_LIMIT || std::abs(Z) > COORD_LIMIT) {
		throw std::invalid_argument("Coordinates are beyond of limits");
	}
	return true;
}

Segment3D::Segment3D(const Vector3D& v, const Vector3D& u) {
	start = v;
	end = u;
};

Vector3D Segment3D::Directional_Vector() const { // направляющий вектор отрезка
	return end - start;
}

bool Segment3D::IsPointOn(const Vector3D& v) const { // ф-ция проверки что точка лежит на отрезке
	if (v == start || v == end) {
		return true;
	}
	Vector3D v_start = v - start;
	Vector3D v_end = v - end;	
	if (v_start.CalculateScalarProd(v_end) > EPSILON) {
		return false;
	}
	return true;
};


std::pair <Vector3D, Vector3D> CalculateLinkVector(const Segment3D& segment_v, const Segment3D& segment_u) {
	Vector3D st_st = segment_u.GetStart() - segment_v.GetStart();
	Vector3D en_st = segment_u.GetEnd() - segment_v.GetStart();
	Vector3D st_en = segment_u.GetStart() - segment_v.GetEnd();
	Vector3D en_en = segment_u.GetEnd() - segment_v.GetEnd();		
	double st_st_lng = st_st.CalculateLength();
	double en_st_lng = en_st.CalculateLength();
	double st_en_lng = st_en.CalculateLength();
	double en_en_lng = en_en.CalculateLength();
	std::array<std::tuple<double, Vector3D*, Vector3D>, 4> lng = { std::make_tuple(st_st_lng,&st_st,segment_v.GetStart()) ,std::make_tuple(en_st_lng,&en_st,segment_v.GetStart()),std::make_tuple(st_en_lng,&st_en, segment_v.GetEnd()) ,std::make_tuple(en_en_lng,&en_en,segment_v.GetEnd()) };
	auto min_lng = std::min_element(lng.begin(), lng.end(), [](std::tuple<double, Vector3D*, Vector3D> lhs, std::tuple<double, Vector3D*, Vector3D>rhs) {
		return (std::get<0>(lhs) < std::get<0>(rhs)); });
	std::tuple<double, Vector3D*, Vector3D> tuple_min_vec = *min_lng;
	if (std::isinf(std::get<0>(tuple_min_vec))) {
		throw std::logic_error("Disjoint segments");
	}
	return std::make_pair(*std::get<1>(tuple_min_vec), std::get<2>(tuple_min_vec));
}

Vector3D Intersect(const Segment3D& segment_v, const Segment3D& segment_u) {

	segment_v.GetStart().CheckLimits();
	segment_u.GetStart().CheckLimits();
	segment_v.GetEnd().CheckLimits();
	segment_u.GetEnd().CheckLimits();
	Vector3D v_direct_vec = segment_v.Directional_Vector();
	Vector3D u_direct_vec = segment_u.Directional_Vector();
	auto link_vec = CalculateLinkVector(segment_v, segment_u);
	Vector3D u_link_cross_vec = u_direct_vec.CalculateCrossProd(link_vec.first);
	Vector3D u_v_croos_vec = u_direct_vec.CalculateCrossProd(v_direct_vec);
	if (u_v_croos_vec.CalculateLength() < EPSILON) {
		if (v_direct_vec.CalculateLength() < EPSILON && segment_u.IsPointOn(segment_v.GetEnd())) {
			return segment_v.GetStart();
		}
		if (u_direct_vec.CalculateLength() < EPSILON && segment_v.IsPointOn(segment_u.GetEnd())) {
			return segment_u.GetStart();
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
	if (u_v_croos_vec.CalculateScalarProd(link_vec.first) > EPSILON) {
		throw std::logic_error("Disjoint segment");
	}
	// порядок умножения скаляра на вектор важен, определил только оператор вектор*скаляр
	Vector3D intersec_point = link_vec.second + v_direct_vec *
		((u_link_cross_vec.CalculateScalarProd(u_v_croos_vec) / (u_v_croos_vec.CalculateLength()) * u_v_croos_vec.CalculateLength())); 
	if (!segment_v.IsPointOn(intersec_point) || !segment_u.IsPointOn(intersec_point)) { // проверка что точка лежит на обоих отрезках
		throw std::logic_error("Intersecting on continuation lines");
	}
	return intersec_point;
}
