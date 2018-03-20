

#define display_width 800.0
#define display_height 600.0
#define SUCIO 0
#define LIMPIO 1

#define max_sims 3 //Claramente tengo memory leaks ya que no pude resolver el tema con el destructor de floor que no me deja usarlo
#define MAX_BOTS 10 //no se elijan ustedes
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
// si falta un parametro sera definido asi.

