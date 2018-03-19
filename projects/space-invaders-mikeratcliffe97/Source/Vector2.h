#pragma once
struct vector2
{
	// construction
	vector2(float x_, float y_);
	vector2(const vector2& rhs);
	
	// operations
	vector2 operator*(float scalar);
	void normalise();

	float get_x();
	float get_y();

	void x_set(float x_);
	void y_set(float y_);

private:

	// data
	float x = 0;
	float y = 0;
};