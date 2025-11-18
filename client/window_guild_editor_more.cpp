#include "main.h"

void init_form_guild_editor_more()
{
	int i, j, k;

	guild_editor_more.backround = NULL;
	guild_editor_more.visible = 0;
	guild_editor_more.button[B_GEM_EXIT].x = 530;
	guild_editor_more.button[B_GEM_EXIT].y = 415;
	guild_editor_more.button[B_GEM_EXIT].w = 63;
	guild_editor_more.button[B_GEM_EXIT].h = 20;
	guild_editor_more.button[B_GEM_SAVE_SETTINGS].x = 217;
	guild_editor_more.button[B_GEM_SAVE_SETTINGS].y = 418;
	guild_editor_more.button[B_GEM_SAVE_SETTINGS].w = 326 - 217;
	guild_editor_more.button[B_GEM_SAVE_SETTINGS].h = 436 - 418;
	guild_editor_more.button[B_GEM_LEFT_DECO].x = 220;
	guild_editor_more.button[B_GEM_LEFT_DECO].y = 296;
	guild_editor_more.button[B_GEM_LEFT_DECO].w = 20;
	guild_editor_more.button[B_GEM_LEFT_DECO].h = 20;
	guild_editor_more.button[B_GEM_RIGHT_DECO].x = 355;
	guild_editor_more.button[B_GEM_RIGHT_DECO].y = 296;
	guild_editor_more.button[B_GEM_RIGHT_DECO].w = 20;
	guild_editor_more.button[B_GEM_RIGHT_DECO].h = 20;
	guild_editor_more.button[B_GEM_TOGGLE_DECO].x = 380;
	guild_editor_more.button[B_GEM_TOGGLE_DECO].y = 296;
	guild_editor_more.button[B_GEM_TOGGLE_DECO].w = 20;
	guild_editor_more.button[B_GEM_TOGGLE_DECO].h = 20;
	guild_editor_more.button[B_GEM_SAVE_DECO_CHANGES].x = 445;
	guild_editor_more.button[B_GEM_SAVE_DECO_CHANGES].y = 295;
	guild_editor_more.button[B_GEM_SAVE_DECO_CHANGES].w = 100;
	guild_editor_more.button[B_GEM_SAVE_DECO_CHANGES].h = 20;
	guild_editor_more.button[B_GEM_MORE_SETTINGS].x = ( 400 - ( 480 / 2 ) ) + 180;
	guild_editor_more.button[B_GEM_MORE_SETTINGS].y = ( 300 - ( 360 / 2 ) ) + 300;
	guild_editor_more.button[B_GEM_MORE_SETTINGS].w = 285 - 180;
	guild_editor_more.button[B_GEM_MORE_SETTINGS].h = 315 - 285;
	for ( i=0;i<3;i++ )
	{
		clear_text_box ( NULL, &guild_editor_more.text_box[i] );
		setup_text_box ( &guild_editor_more.text_box[i] );
		guild_editor_more.text_box[i].max_char = 21;
		guild_editor_more.text_box[i].pass_char = '\0';

		guild_editor_more.text_box[i].location.x = ( 400 - ( 480 / 2 ) ) + 233;
		guild_editor_more.text_box[i].location.y = ( 300 - ( 360 / 2 ) ) + 83 + ( i*14 );
		guild_editor_more.text_box[i].location.w = 420 - 233;
		guild_editor_more.text_box[i].location.h = 20;
	}
	clear_text_box ( NULL, &guild_editor_more.text_box[3] );
	setup_text_box ( &guild_editor_more.text_box[3] );
	guild_editor_more.text_box[3].max_char = 31;
	guild_editor_more.text_box[3].pass_char = '\0';
	guild_editor_more.text_box[3].location.x = 357;
	guild_editor_more.text_box[3].location.y = 267;
	guild_editor_more.text_box[3].location.w = 582 - 357;
	guild_editor_more.text_box[3].location.h = 20;
}

void load_guild_editor_more()
{
	SDL_Rect destination;

	if ( !guild_editor_more.backround )
	{
		guild_editor_more.backround = IMG_Load ( "graphics/guildeditor_more.jpg" );
		guild_editor_more.on[0] = IMG_Load ( "graphics/guild_off.jpg" );
		guild_editor_more.on[1] = IMG_Load ( "graphics/guild_on.jpg" );
		guild_editor_more.sel_left = IMG_Load ( "graphics/seldown.jpg" );
		guild_editor_more.sel_right = IMG_Load ( "graphics/selup.jpg" );
		guild_editor_more.save_settings = IMG_Load ( "graphics/save_settings.jpg" );
	}

	destination.x = 400 - ( 480 / 2 );
	destination.y = 300 - ( 360 / 2 );

	set_forms_invisible();
	guild_editor_more.visible = 1;
	SDL_BlitSurface ( guild_editor_more.backround, NULL, screen, &destination );

	//screen only shit
	guild_editor_more_reset_text_boxes();
	guild_editor_more_draw_deco ( 0 );

	sdl_flip_mutex();
}

void key_guild_editor_more ( int c )
{
	int i;
	const int text_box_max = 4;

	if ( c == 9 ) //tab
	{
		for ( i=0;i<text_box_max;i++ )
			if ( guild_editor_more.text_box[i].selected ) break;

		unselect_text_box ( screen, &guild_editor_more.text_box[i] );

		if ( i>=text_box_max-1 )
			{i=0;}
		else
			{i++;}


		select_text_box ( screen, &guild_editor_more.text_box[i] );
		sdl_flip_mutex();
	}
	else
	{
		for ( i=0;i<text_box_max;i++ )
			if ( guild_editor_more.text_box[i].selected )
			{
				add_text_box ( screen, &guild_editor_more.text_box[i], c );

				if ( i==3 )
					guild_editor_more_draw_save_changes();

				sdl_flip_mutex();
			}
	}
}

void button_guild_editor_more ( int x, int y )
{
	const int button_max = B_GEM_MAX_BUTTONS, text_box_max = 4;
	int i, success = 0, button;

	for ( i=0;i<button_max;i++ )
		if ( x >= guild_editor_more.button[i].x && x <= guild_editor_more.button[i].x + guild_editor_more.button[i].w && y >= guild_editor_more.button[i].y && y <= guild_editor_more.button[i].y + guild_editor_more.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<text_box_max;i++ )
			if ( x >= guild_editor_more.text_box[i].location.x && x <= guild_editor_more.text_box[i].location.x + guild_editor_more.text_box[i].location.w && y >= guild_editor_more.text_box[i].location.y && y <= guild_editor_more.text_box[i].location.y + guild_editor_more.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
		switch ( i )
		{
			case B_GEM_EXIT: //exit
				load_guild_editor();
				break;
			case B_GEM_SAVE_SETTINGS: //save
				guild_editor_more_send_save();
				break;
			case B_GEM_LEFT_DECO: // left deco
				guild_editor_more_previous_deco();
				break;
			case B_GEM_RIGHT_DECO: // right deco
				guild_editor_more_next_deco();
				break;
			case B_GEM_TOGGLE_DECO: // toggle deco
				guild_editor_more_toggle_deco();
				break;
			case B_GEM_SAVE_DECO_CHANGES: //save changes
				if ( !guild_editor_more_deco_changes() ) break;
				guild_editor_more_send_deco_changes();
				break;
			case B_GEM_MORE_SETTINGS:
				load_guild_editor_more2();
				break;
		}
	else
	{
		int k;

		for ( k=0;k<text_box_max;k++ )
			if ( guild_editor_more.text_box[k].selected )
				unselect_text_box ( screen, &guild_editor_more.text_box[k] );

		select_text_box ( screen, &guild_editor_more.text_box[i] );

		sdl_flip_mutex();
	}
}

void guild_editor_more_send_save()
{
	char rtn_str[1000];

	sprintf ( rtn_str, "36,%s,%s,%s",
	          guild_editor_more.text_box[2].message,
	          guild_editor_more.text_box[1].message,
	          guild_editor_more.text_box[0].message );

	send_con_hub ( rtn_str );
}

void guild_editor_more_next_deco()
{
	if ( guild_editor_more.deco_choosen + 1 >= MAX_DECO )
		return;

	guild_editor_more.deco_choosen++;

	guild_editor_more_draw_deco ( guild_editor_more.deco_choosen );

	sdl_flip_mutex();
}

void guild_editor_more_previous_deco()
{
	if ( guild_editor_more.deco_choosen - 1 < 0 )
		return;

	guild_editor_more.deco_choosen--;

	guild_editor_more_draw_deco ( guild_editor_more.deco_choosen );

	sdl_flip_mutex();
}

int guild_editor_more_deco_changes()
{
	int i;

	i = guild_editor_more.deco_choosen;

	//check if on / off is different
	if ( game.guild.deco_activated[i] != guild_editor_more.deco_activated )
		return 1;

	//check if description is different
	if ( strcmp ( guild_editor_more.text_box[3].message, game.guild.deco_name[i] ) )
		return 1;

	//do no changes
	return 0;
}

void guild_editor_more_draw_save_changes()
{
	//now which
	if ( guild_editor_more_deco_changes() )
		SDL_BlitSurface ( guild_editor_more.save_settings, NULL, screen, &guild_editor_more.button[5] );
	else
		SDL_FillRect ( screen, &guild_editor_more.button[5], SDL_MapRGB ( screen->format, 0, 0, 0 ) );
}

void guild_editor_more_send_deco_changes()
{
	char rtn_str[500];

	sprintf ( rtn_str,"46,%d,%s,%d", guild_editor_more.deco_choosen, guild_editor_more.text_box[3].message, guild_editor_more.deco_activated );

	send_con_hub ( rtn_str );
}

void guild_editor_more_toggle_deco()
{
	if ( guild_editor_more.deco_activated )
		guild_editor_more.deco_activated = 0;
	else
		guild_editor_more.deco_activated = 1;

	guild_editor_draw_deco_onoff();

	guild_editor_more_draw_save_changes();

	sdl_flip_mutex();
}

void guild_editor_draw_deco_onoff()
{
	if ( guild_editor_more.deco_activated )
		SDL_BlitSurface ( guild_editor_more.on[1], NULL, screen, &guild_editor_more.button[4] );
	else
		SDL_BlitSurface ( guild_editor_more.on[0], NULL, screen, &guild_editor_more.button[4] );
}

void guild_editor_more_draw_deco ( int deco_num )
{
	//check
	if ( deco_num < 0 )
		deco_num = 0;
	if ( deco_num >= MAX_DECO )
		deco_num = MAX_DECO - 1;

	//set the num
	guild_editor_more.deco_choosen = deco_num;

	//set the texts and such
	guild_editor_more.deco_activated = game.guild.deco_activated[deco_num];
	set_text_box_text ( screen, &guild_editor_more.text_box[3], game.guild.deco_name[deco_num] );


	//draw buttons
	if ( deco_num )
		SDL_BlitSurface ( guild_editor_more.sel_left, NULL, screen, &guild_editor_more.button[2] );
	else
		SDL_FillRect ( screen, &guild_editor_more.button[2], SDL_MapRGB ( screen->format, 0, 0, 0 ) );
	if ( deco_num<MAX_DECO - 1 )
		SDL_BlitSurface ( guild_editor_more.sel_right, NULL, screen, &guild_editor_more.button[3] );
	else
		SDL_FillRect ( screen, &guild_editor_more.button[3], SDL_MapRGB ( screen->format, 0, 0, 0 ) );

	//load deco
	if ( load_deco ( deco_num ) )
	{
		SDL_Rect destination;

		destination.x = 244;
		destination.y = 290;

		//draw deco
		SDL_BlitSurface ( game.game_image.deco_img[deco_num], NULL, screen, &destination );
	}

	guild_editor_draw_deco_onoff();

	guild_editor_more_draw_save_changes();
}

void guild_editor_more_reset_text_boxes()
{
	int i;
	const int text_box_max = 4;


	set_text_box_text ( NULL, &guild_editor_more.text_box[0], game.guild.enemy[2] );
	set_text_box_text ( NULL, &guild_editor_more.text_box[1], game.guild.enemy[1] );
	set_text_box_text ( NULL, &guild_editor_more.text_box[2], game.guild.enemy[0] );

	guild_editor_more.text_box[0].selected = 1;

	select_text_box ( screen, &guild_editor_more.text_box[0] );
	for ( i=1;i<text_box_max;i++ )
		unselect_text_box ( screen, &guild_editor_more.text_box[i] );
}
