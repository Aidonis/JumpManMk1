#include "Platform.h"


Platform::Platform()
{
}

void Platform::SetSize(float a_width, float a_height){
	width = a_width;
	height = a_height;
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

void Platform::SetSpriteID(unsigned int a_spriteID){
	spriteID = a_spriteID;
}
unsigned int  Platform::GetSpriteID(){
	return spriteID;
}

float Platform::GetTop(){
	return YPos + (height / 2);
}
float Platform::GetBottom(){
	return YPos - (height / 2);
}
float Platform::GetLeft(){
	return XPos - (width / 2);
}
float Platform::GetRight(){
	return XPos + (width / 2);
}

Platform::~Platform()
{
}
