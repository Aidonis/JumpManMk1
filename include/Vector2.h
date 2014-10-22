#ifndef _VECTOR2_H_
#define _VECTOR2_H_

struct Vector2
{
	float x, y;

	Vector2(){
		x = 0;
		y = 0;
	}

	Vector2(float a_x, float a_y){
		x = a_x;
		y = a_y;
	}
};

#endif