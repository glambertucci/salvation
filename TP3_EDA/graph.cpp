#include "defines.h"
#include "graph.h"
#include <algorithm>
#define BACKGROUND "background.png"
#define ROOF  550
#define GROUND 150
#define WIDTH 700
using namespace std;
void graphbar( double * ticks_medio)
{
	ALLEGRO_BITMAP * bitmap = NULL;
	bitmap = al_load_bitmap(BACKGROUND);
	al_draw_bitmap(bitmap, 0, 0, 0);
	double * highest_tick = max_element(ticks_medio+1, ticks_medio+MAX_BOTS);
	
	for (int i = 1; i < MAX_BOTS; i++)
	{
		printf(" tick %d es %lf\n", i, ticks_medio[i]);
		al_draw_filled_circle( (i* WIDTH / MAX_BOTS)+10, ROOF - (ticks_medio[i] * ROOF / *highest_tick) , 5, al_map_rgb(255, 0, 0));
	}
	printf("La mayor cantidad de ticks es %lf\n", *highest_tick);
	al_flip_display();
	al_rest(5.0);
	getchar();
}