#pragma once

struct Vec2 {
	float x;
	float y;

	constexpr Vec2() : x(0.0f), y(0.0f) {}
	constexpr Vec2(float _x, float _y) : x(_x), y(_y) {}
};

struct Vec3 {
	float x;
	float y;
	float z;

	constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	constexpr Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Vec4 {
	float x;
	float y;
	float z;
	float w;

	constexpr Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	constexpr Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};


