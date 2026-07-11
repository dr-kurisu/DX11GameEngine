#pragma once

#include <DX3D/Math/Vec3.h>
#include <cmath>

namespace dx3d {
	class Mat4 {
	public:
		Mat4() = default;

		// Identity matrix
		static Mat4 identity() noexcept {
			Mat4 res{};
			res.m_data[0][0] = 1;
			res.m_data[1][1] = 1;
			res.m_data[2][2] = 1;
			res.m_data[3][3] = 1;
			return res;
		}

		// translation matrix
		static Mat4 translate(const Vec3& translation) noexcept {
			Mat4 res = Mat4::identity();
			res.m_data[3][0] = translation.x;
			res.m_data[3][1] = translation.y;
			res.m_data[3][2] = translation.z;
			return res;
		}

		// scale matrix
		static Mat4 scale(const Vec3& scale) noexcept {
			Mat4 res = Mat4::identity();
			res.m_data[0][0] = scale.x;
			res.m_data[1][1] = scale.y;
			res.m_data[2][2] = scale.z;
			res.m_data[3][3] = 1;
			return res;
		}

		static Mat4 rotateZ(f32 z) noexcept {
			Mat4 res = Mat4::identity();
			res.m_data[0][0] = std::cos(z);
			res.m_data[0][1] = std::sin(z);
			res.m_data[1][0] = -std::sin(z);
			res.m_data[1][1] = std::cos(z);
			return res;
		}

		// this * other
		Mat4 operator *(const Mat4& other) const noexcept {
			Mat4 res{};
			for (auto row = 0u; row < 4u; row++) {
				for (auto k = 0u; k < 4u; k++) {
					auto temp = m_data[row][k];
					for (auto col = 0u; col < 4u; col++) {
						res.m_data[row][col] += temp * other.m_data[k][col];
					}
				}
			}
			return res;
		}

	private:
		f32 m_data[4][4]{};
	};
}