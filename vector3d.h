#pragma once

#include<cmath>
#include<limits>
#include<stdexcept>
#include <array>
#include <algorithm>
#include <iterator>

constexpr double EPSILON = std::numeric_limits<double>::epsilon(); // �������� ����

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

	double CalculateScalarProd(const Vector3D& v);// ��������� ������������
	double CalculateLength();  // ����� �������
	Vector3D CalculateCrossProd(const Vector3D& v); //��������� ������������

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

	Vector3D Directional_Vector() const; // ������������ ������ �������
	bool IsPointOn(const Vector3D& v) const; // �-��� �������� ��� ����� ����� �� �������
	Vector3D GetStart() const { // ��� ������������
		return start;
	}
	Vector3D GetEnd() const { // ��� ������������
		return end;
	}

private:
	Vector3D start;
	Vector3D end;

};

std::pair <Vector3D, Vector3D>  CalculateLinkVector(const Segment3D& segment_u, const Segment3D& segment_v);

/*
* ������� ������ ����� ����������� ���� ���������
* @param segment_v ������ ������� ��� ������� �� ���� ����� �����������
* @param segment_u ������ ������� ��� ������� �� ���� ����� �����������
* @return Vector3D ����� �����������, ��� ������� ���������� std::logic_error ���� ���� � ��� ��� ��� ��������� �����
*/
Vector3D Intersect(const Segment3D& segment_v, const Segment3D& segment_u); //����� ���� �������  ����� std::optional<Vector3D> � ����������  std::nullopt ���� ����������� ���


