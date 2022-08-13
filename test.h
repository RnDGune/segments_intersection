#pragma once

#include <cassert>

#include "vector3d.h" // в этом хэдере лежат классы векторов, сегментов и функция пересечения 

// юнит-тесты  

void Test() {
	{
		Vector3D start_V(5, 5, 5);
		Vector3D end_V(10, 5, 5);
		Vector3D start_U(5, -5, -5);
		Vector3D end_U(10, -5, -5);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Parallel segment test passed" << std::endl;
		}
	}
	{
		Vector3D start_V(5, 5, 5);
		Vector3D end_V(10, 5, 5);
		Vector3D start_U(5, 5, 5);
		Vector3D end_U(10, 5, 5);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Same segment test passed" << std::endl;
		}
	}
	{
		Vector3D start_V(5, 5, 5);
		Vector3D end_V(10, 5, 5);
		Vector3D start_U(0, 5, 0);
		Vector3D end_U(0, 10, 0);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Disjoint segment test passed" << std::endl;
		}
	}
	{
		Vector3D start_V(0, 0, 0);
		Vector3D end_V(0, 0, 0);
		Vector3D start_U(5, 5, 5);
		Vector3D end_U(5, 5, 5);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Zero norm segment test passed" << std::endl;
		}
	}
	{
		Vector3D start_V(5, 10, 0);
		Vector3D end_V(20, 10, 0);
		Vector3D start_U(10, 0, 0);
		Vector3D end_U(10, 20, 0);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		Vector3D intersec_calc = Intersect(U, V);
		Vector3D intersec_real(10, 10, 0);
		assert(intersec_calc == intersec_real, "Wrong intersect point");
		std::cout << "Intersecting segment test passed" << std::endl;
	}

	{
		Vector3D start_V(5, 10, 0);
		Vector3D end_V(20, 10, 0);
		Vector3D start_U(25, 0, 0);
		Vector3D end_U(25, 20, 0);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);

		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Intersecting on continuation lines test passed" << std::endl;
		}
	}

	{
		Vector3D start_V(0, 0, 0);
		Vector3D end_V(10, 0, 0);
		Vector3D start_U(10, 0, 0);
		Vector3D end_U(20, 0, 0);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);

		Vector3D intersec_calc = Intersect(U, V);
		Vector3D intersec_real(10, 0, 0);
		assert(intersec_calc == intersec_real, "Wrong intersect point");
		std::cout << "Intersecting in edge point segment test passed" << std::endl;

	}
	{
		Vector3D start_V(0, 0, 0);
		Vector3D end_V(10, 0, 0);
		Vector3D start_U(10, 0, 0);
		Vector3D end_U(5, 0, 0);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Overlap segments  test passed" << std::endl;
		}

	}
	{
		Vector3D start_V(5, 5, 5);
		Vector3D end_V(5, 5, 5);
		Vector3D start_U(5, 5, 5);
		Vector3D end_U(5, 5, 5);
		Segment3D V(start_V, end_V);
		Segment3D U(start_U, end_U);
		try {
			Intersect(U, V);
		}
		catch (std::logic_error) {
			std::cout << "Point segment test passed" << std::endl;
		}
	}

}

