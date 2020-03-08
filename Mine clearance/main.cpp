#include <iostream>
#include "Mine_clearance.h"

using namespace std;

int main(void)
{
	
	while (true) {
		Mine_clearance game;
		game.setting(game.draw_start());
		game.start_game();
	}
	

	return 0;
}