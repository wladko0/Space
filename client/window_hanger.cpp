#include "main.h"

void init_form_hanger()
{
	int i,j,k;

	hanger.backround = NULL;
	hanger.temp_backround = SDL_CreateRGBSurface ( SDL_HWSURFACE, 800, 600, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
	hanger.visible = 0;
	for ( i=0;i<5;i++ )
	{
		hanger.button[i].x = 92;
		hanger.button[i].y = 109 + ( i * 77 );
		hanger.button[i].w = 305;
		hanger.button[i].h = 73;
		hanger.button[i + 5].x = 402;
		hanger.button[i + 5].y = 109 + ( i * 77 );
		hanger.button[i + 5].w = 305;
		hanger.button[i + 5].h = 73;
	}
	hanger.button[10].x = 201;
	hanger.button[10].y = 515;
	hanger.button[10].w = 125;
	hanger.button[10].h = 37;
	hanger.button[11].x = 342;
	hanger.button[11].y = 515;
	hanger.button[11].w = 300;
	hanger.button[11].h = 37;
	hanger.button[12].x = 655;
	hanger.button[12].y = 515;
	hanger.button[12].w = 60;
	hanger.button[12].h = 25;
	for ( i=0;i<10;i++ )
	{
		hanger.ship[i].name[0] = '\0';
		hanger.ship[i].server_id = -1;
		hanger.ship[i].type = -1;
		hanger.ship[i].kind = -1;
	}
}

void load_hanger()
{
	if ( !hanger.backround )
	{
		hanger.backround = IMG_Load ( "graphics/hangerback.jpg" );
		hanger.selection = IMG_Load ( "graphics/selection.png" );
		hanger.buynew = IMG_Load ( "graphics/buynew.png" );
		hanger.takeselected = IMG_Load ( "graphics/takeselected.png" );
		hanger.redraw = 1;
	}

	if ( hanger.redraw ) redraw_hanger();

	set_forms_invisible();
	hanger.visible = 1;
	SDL_BlitSurface ( hanger.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void redraw_hanger()
{
	int i, empty_slot = 0;
	char temp_filename[200], temp_str[21], temp_line[200];
	SDL_Rect img_location, text_location[3];

	//bring back original to our temp
	SDL_BlitSurface ( hanger.backround, NULL, hanger.temp_backround, NULL );

	for ( i=0;i<10;i++ )
	{
		//check if have ship
		if ( hanger.ship[i].server_id < 0 || hanger.ship[i].type < 0 || hanger.ship[i].kind < 0 )
		{
			//used below
			empty_slot = 1;
			continue;
		}

		//load and draw ship image
		if ( i<5 )
		{
			img_location.x = 104;
			img_location.y = 120 + ( i * 77 );
		}
		else
		{
			img_location.x = 414;
			img_location.y = 120 + ( ( i-5 ) * 77 );
		}

		if ( load_fship ( hanger.ship[i].server_id, hanger.ship[i].type, hanger.ship[i].kind, 0, server[hanger.ship[i].server_id].ship[hanger.ship[i].type].name ) )
			SDL_BlitSurface ( server[hanger.ship[i].server_id].ship[hanger.ship[i].type].fship_img[hanger.ship[i].kind][0], NULL, hanger.temp_backround, &img_location );
		else
			SDL_BlitSurface ( hanger.no_fship[hanger.ship[i].kind][0], NULL, hanger.temp_backround, &img_location );

		//write text
		if ( i<5 )
		{
			text_location[0].x = text_location[1].x = text_location[2].x = 175;
			text_location[0].y = 118 + ( i * 77 );
			text_location[1].y = 135 + ( i * 77 );
			text_location[2].y = 152 + ( i * 77 );
		}
		else
		{
			text_location[0].x = text_location[1].x = text_location[2].x = 485;
			text_location[0].y = 118 + ( ( i-5 ) * 77 );
			text_location[1].y = 135 + ( ( i-5 ) * 77 );
			text_location[2].y = 152 + ( ( i-5 ) * 77 );
		}

		sprintf ( temp_line,"%s %s", server[hanger.ship[i].server_id].ship[hanger.ship[i].type].name, ship_name ( hanger.ship[i].kind, temp_str ) );
		draw_raw_label ( hanger.temp_backround, temp_line, text_location[0], 255, 255, 255 );
		sprintf ( temp_line,"Hull:%d/%d Cargo:%d/%d", hanger.ship[i].hull, hanger.ship[i].hull_max, hanger.ship[i].cargo, hanger.ship[i].cargo_max );
		draw_raw_label ( hanger.temp_backround, temp_line, text_location[1], 255, 255, 255 );
		//if ( hanger.ship[i].has_weapons )
		//	sprintf ( temp_line,"Rng:%d Spd:%d Shld:%d Armed", hanger.ship[i].range, hanger.ship[i].speed, hanger.ship[i].shield );
		//else
		//	sprintf ( temp_line,"Rng:%d Spd:%d Shld:%d Empty", hanger.ship[i].range, hanger.ship[i].speed, hanger.ship[i].shield );
		sprintf ( temp_line,"Rng:%d Spd:%d Shld:%d Rf:%d", hanger.ship[i].range, hanger.ship[i].speed, hanger.ship[i].shield, hanger.ship[i].ref );
		draw_raw_label ( hanger.temp_backround, temp_line, text_location[2], 255, 255, 255 );
	}

	//draw the selection box
	if ( game.ship_sel<5 )
	{
		img_location.x = 85;
		img_location.y = 101 + ( game.ship_sel * 78 );
	}
	else
	{
		img_location.x = 395;
		img_location.y = 101 + ( ( game.ship_sel-5 ) * 78 );
	}
	SDL_BlitSurface ( hanger.selection, NULL, hanger.temp_backround, &img_location );


	//draw buy new ship if there is an empty slot
	if ( empty_slot )
	{
		img_location.x = 204;
		img_location.y = 519;
		SDL_BlitSurface ( hanger.buynew, NULL, hanger.temp_backround, &img_location );
	}

	//draw take selected... if there is a ship selected
	if ( game.ship[game.ship_sel].server_id > -1 && game.ship[game.ship_sel].type > -1 && game.ship[game.ship_sel].kind > -1 )
	{
		img_location.x = 343;
		img_location.y = 519;
		SDL_BlitSurface ( hanger.takeselected, NULL, hanger.temp_backround, &img_location );
	}

	hanger.redraw = 0;
}

void button_hanger ( int x, int y )
{
	int i, j;

	for ( i=0;i<13;i++ )
		if ( x >= hanger.button[i].x && x <= hanger.button[i].x + hanger.button[i].w && y >= hanger.button[i].y && y <= hanger.button[i].y + hanger.button[i].h )
			break;

	if ( i == 13 ) return;

	switch ( i )
	{
		case 10: //buy new
			//send server command to switch to empty hanger spot
			for ( j=0;j<10;j++ ) //find empty slot
				if ( hanger.ship[j].server_id < 0 || hanger.ship[j].type < 0 || hanger.ship[j].kind < 0 )
					break;

			if ( j==10 ) //if no empty slot
				break;

			load_shop();

			if ( game.ship[game.ship_sel].server_id > -1 && game.ship[game.ship_sel].type > -1 && game.ship[game.ship_sel].kind > -1 )
				select_ship ( j ); //if we already have a ship selected, then choose the first empty slot
			break;
		case 11: //edit selected
			if ( game.ship[game.ship_sel].server_id > -1 && game.ship[game.ship_sel].type > -1 && game.ship[game.ship_sel].kind > -1 )
				load_shop();
			break;
		case 12: //leave
			if ( game.home_id == game.server_id && game.home_planet == planet.last_planet )
			{
				switch ( server[game.server_id].planet[planet.last_planet].home_class )
				{
					default:
					case 1:
						load_gen_home();
						break;
					case 2:
						load_velic_home();
						break;
				}
			}
			else //not home planet
			{
				load_planet ( planet.last_planet );
			}
			break;
		default:
			select_ship ( i ); //because all others are ship cells
			break;
	}
}
