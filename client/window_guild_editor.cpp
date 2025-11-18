#include "main.h"

void init_form_guild_editor()
{
	int i, j, k;

	guild_editor.backround = NULL;
	guild_editor.visible = 0;
	guild_editor.button[0].x = 530;
	guild_editor.button[0].y = 415;
	guild_editor.button[0].w = 63;
	guild_editor.button[0].h = 20;
	guild_editor.button[1].x = 217;
	guild_editor.button[1].y = 418;
	guild_editor.button[1].w = 326 - 217;
	guild_editor.button[1].h = 436 - 418;
	guild_editor.button[32].x = ( 400 - ( 480 / 2 ) ) + 180;
	guild_editor.button[32].y = ( 300 - ( 360 / 2 ) ) + 300;
	guild_editor.button[32].w = 285 - 180;
	guild_editor.button[32].h = 315 - 285;
	for ( i=0;i<2+6;i++ )
	{
		clear_text_box ( NULL, &guild_editor.text_box[i] );
		setup_text_box ( &guild_editor.text_box[i] );
		guild_editor.text_box[i].max_char = 21;
		guild_editor.text_box[i].pass_char = '\0';

		guild_editor.text_box[i].location.x = 225;
		guild_editor.text_box[i].location.y = 279 + ( ( i-2 ) * 23 );
		guild_editor.text_box[i].location.w = 318 - 225;
		guild_editor.text_box[i].location.h = 10;
	}
	for ( i=0;i<30;i++ )
	{
		int h, v;

		k = i + 2;

		h = i % 6;
		v = i / 6;

		guild_editor.button[k].x = 340 + ( v * 53 );
		guild_editor.button[k].y = 277 + ( ( 5-h ) * 23 );
		guild_editor.button[k].w = 20;
		guild_editor.button[k].h = 20;
	}
	guild_editor.text_box[0].location.x = 340;
	guild_editor.text_box[0].location.y = 210;
	guild_editor.text_box[0].location.w = 582 - 340;
	guild_editor.text_box[0].location.h = 10;

	guild_editor.text_box[0].max_char = 200;
	guild_editor.text_box[1].location.x = 340;
	guild_editor.text_box[1].location.y = 226;
	guild_editor.text_box[1].location.w = 582 - 340;
	guild_editor.text_box[1].location.h = 10;

	guild_editor.website[0] = 0;
	guild_editor.bank_money = 0;
	guild_editor.bank_lend = 0;
	for ( i=0;i<6;i++ )
	{
		guild_editor.rank_name[i][0] = 0;
		for ( k=0;k<5;k++ )
			guild_editor.rank_allow[i][k] = 0;
	}
}

void load_guild_editor()
{
	SDL_Rect destination;

	if ( !guild_editor.backround )
	{
		guild_editor.backround = IMG_Load ( "graphics/guildeditor.jpg" );

		if ( !game.game_image.guild_toggle_off ) game.game_image.guild_toggle_off = IMG_Load ( "graphics/guild_off.jpg" );
		if ( !game.game_image.guild_toggle_on ) game.game_image.guild_toggle_on = IMG_Load ( "graphics/guild_on.jpg" );
	}

	destination.x = 400 - ( 480 / 2 );
	destination.y = 300 - ( 360 / 2 );

	set_forms_invisible();
	guild_editor.visible = 1;
	SDL_BlitSurface ( guild_editor.backround, NULL, screen, &destination );

	//screen only shit
	guild_editor_reset_variables();
	guild_editor_reset_text_boxes();
	guild_editor_reset_toggles();

	sdl_flip_mutex();
}


void key_guild_editor ( int c )
{
	int i;

	if ( c == 9 ) //tab
	{
		for ( i=0;i<8;i++ )
			if ( guild_editor.text_box[i].selected ) break;

		unselect_text_box ( screen, &guild_editor.text_box[i] );

		if ( i>=7 )
			{i=0;}
		else
			{i++;}


		select_text_box ( screen, &guild_editor.text_box[i] );
		sdl_flip_mutex();
	}
	else
	{
		for ( i=0;i<8;i++ )
			if ( guild_editor.text_box[i].selected )
			{
				add_text_box ( screen, &guild_editor.text_box[i], c );
				sdl_flip_mutex();
			}
	}
}

void button_guild_editor ( int x, int y )
{
	const int button_max = 2 + 30 + 1, text_box_max = 2 + 6;
	int i, success = 0, button;

	for ( i=0;i<button_max;i++ )
		if ( x >= guild_editor.button[i].x && x <= guild_editor.button[i].x + guild_editor.button[i].w && y >= guild_editor.button[i].y && y <= guild_editor.button[i].y + guild_editor.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<text_box_max;i++ )
			if ( x >= guild_editor.text_box[i].location.x && x <= guild_editor.text_box[i].location.x + guild_editor.text_box[i].location.w && y >= guild_editor.text_box[i].location.y && y <= guild_editor.text_box[i].location.y + guild_editor.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
		switch ( i )
		{
			case 0: //exit
				load_guild_halls();
				break;
			case 1: //save
				guild_editor_send_save();
				break;
			case 32: //more options
				load_guild_editor_more();
				break;
			default:
				guild_editor_toggle_button ( i );
				sdl_flip_mutex();
				break;
		}
	else
	{
		int k;

		for ( k=0;k<text_box_max;k++ )
			if ( guild_editor.text_box[k].selected )
				unselect_text_box ( screen, &guild_editor.text_box[k] );

		select_text_box ( screen, &guild_editor.text_box[i] );

		sdl_flip_mutex();
	}
}
