#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "simulation.h"
#include "parsecmd.h"
#include "defines.h"
#include "parse_callback.h"
#include "graph.h"
#include "allegro_start_shutdown.h"
#define DIRTYFILE "dirtyfile.png"
#define CLEANFILE "cleanfile.png"
#define BOTFILE "botfile.png"
#define MUSICFILE "pacman_chomp.wav"
#define MUSICFILE2 "pacman_lose.wav"
#define FONTFILE "pacfont.ttf"
typedef struct
{
	unsigned int fil;
	unsigned int col;
	unsigned int bots_num;
	unsigned int mode;

}userData;

using namespace std;
int main(int argc, char **argv)
{
	userData * userinfo=NULL;
	userData user;
	userinfo = &user;// ok, me tiraba problemas y al parecer esto lo arreglo
	userinfo->col = 10;
	userinfo->fil = 10;
	userinfo->bots_num = 2;
	userinfo->mode = 1;
	ALLEGRO_SAMPLE * music = NULL;
	ALLEGRO_DISPLAY * display=NULL;
	ALLEGRO_FONT * font=NULL;
	pCallback pfun = input_check;

	if (parseCmdLine(argc, argv,pfun,(void *) userinfo))
	{
		if(allegro_startup())
		{
			if ((display = al_create_display(display_width, display_height))!= NULL)
			{
				srand(time(NULL));
				//hacer main
				int ticks;
				if (userinfo->mode == 1)
				{
					music = al_load_sample(MUSICFILE);
					font = al_load_font(FONTFILE, 40, 0);
					al_play_sample(music, 2.75, 0, 1.125, ALLEGRO_PLAYMODE_LOOP, NULL);
					simulation s(userinfo->fil,userinfo->col,DIRTYFILE,userinfo->bots_num,CLEANFILE,BOTFILE,display_width,display_height,userinfo->mode);
						ticks = s.run();
					al_stop_samples();
					music = al_load_sample(MUSICFILE2);
					al_play_sample(music, 2.75, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_text(font, al_map_rgb(255, 255, 255), display_width/8, display_height/2, 0, "La cantidad de ticks fue: ");
					al_draw_textf(font, al_map_rgb(0,255, 0), display_width/2, display_height* 2/ 3, 0, "%d", ticks);
					al_flip_display();
					al_rest(5.0);

						
				}
				else if (userinfo->mode==2)
				{
					 double tickmedio[MAX_BOTS];
					tickmedio[0] = 0;
					tickmedio[1] = 1;
					for (int i = 1; (i < MAX_BOTS) && (abs(tickmedio[i] - tickmedio[i - 1]) > 0.1); i++)
					{
						 double sum = 0.0;
						for (int a = 0; a < max_sims; a++)
						{
							simulation s( userinfo->fil,userinfo->col, DIRTYFILE, i, CLEANFILE, BOTFILE, display_width, display_height,userinfo->mode);

							sum += s.run();
						//	printf("Ya termine con %d simulaciones\n", a);
						}
						printf("Ya termine con %d bots\n", i);
						tickmedio[i] = sum / max_sims;
					}
					graphbar(tickmedio);
				}
	
				al_destroy_display(display);
				allegro_shut_down();

			}
			else
			{
				cout << "Couldnt start display" << endl;
				allegro_shut_down();
			}
		}
		else
		{
			cout << "Couldnt start allegro" << endl;
		}
	}
	else
	{
		cout << "input invalid" << endl;		//mensaje de error de parseo
	}
	return 0;
}
