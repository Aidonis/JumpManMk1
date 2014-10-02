#include "AIE.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Initialise(800, 600, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));


	//Game Loop
	do
	{
		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}
