#include "Platform.h"


Platform::Platform()
{
}

void Platform::SetPosition(float a_x, float a_y){
	XPos = a_x;
	YPos = a_y;
}
void Platform::SetWidth(float a_width){
	width = a_width;
}
float Platform::GetWidth(){
	return width;
}
void Platform::SetHeight(float a_height){
	height = a_height;
}
float Platform::GetHeight(){
	return height;
}
void Platform::SetX(float a_x){
	XPos = a_x;
}
float Platform::GetX(){
	return XPos;
}
void Platform::SetY(float a_y){
	YPos = a_y;
}
float Platform::GetY(){
	return YPos;
}

Platform::~Platform()
{
}
