#include "main.h"

void init_form_bounty()
{
	int i,j,k;

	bounty.backround = NULL;
	bounty.visible = 0;
	bounty.button[0].x = 666;
	bounty.button[0].y = 500;
	bounty.button[0].w = 50;
	bounty.button[0].h = 20;
	bounty.button[1].x = 299;
	bounty.button[1].y = 500;
	bounty.button[1].w = 50;
	bounty.button[1].h = 20;
	for ( i=0;i<38;i++ )
	{
		const int left_x = 85, right_x = 418, interval_x1 = 180 - left_x, interval_x2 = 277 - left_x;
		const int start_y = 90, interval_y = 20;

		clear_text_box ( NULL, &bounty.text_box[i] );
		setup_text_box ( &bounty.text_box[i] );
		bounty.text_box[i].max_char = 21;
		bounty.text_box[i].pass_char = '\0';

		bounty.name_list_label[i].message[0] = 0;
		bounty.price_list_label[i].message[0] = 0;

		if ( i<19 )
		{
			bounty.name_list_label[i].location.x = left_x + 5;
			bounty.name_list_label[i].location.y = start_y + ( i * interval_y ) + 3;
			bounty.name_list_label[i].location.w = interval_x1;
			bounty.name_list_label[i].location.h = interval_y;

			bounty.price_list_label[i].location.x = left_x + interval_x1;
			bounty.price_list_label[i].location.y = start_y + ( i * interval_y ) + 3;
			bounty.price_list_label[i].location.w = interval_x1 - 6;
			bounty.price_list_label[i].location.h = interval_y;

			bounty.text_box[i].location.x = left_x + interval_x2 + 5;
			bounty.text_box[i].location.y = start_y + ( i * interval_y ) + 2;
			bounty.text_box[i].location.w = interval_x1 - 2;
			bounty.text_box[i].location.h = interval_y - 10;
		}
		else
		{
			bounty.name_list_label[i].location.x = right_x + 5;
			bounty.name_list_label[i].location.y = start_y + ( ( i-19 ) * interval_y ) + 3;
			bounty.name_list_label[i].location.w = interval_x1;
			bounty.name_list_label[i].location.h = interval_y;

			bounty.price_list_label[i].location.x = right_x + interval_x1;
			bounty.price_list_label[i].location.y = start_y + ( ( i-19 ) * interval_y ) + 3;
			bounty.price_list_label[i].location.w = interval_x1 - 6;
			bounty.price_list_label[i].location.h = interval_y;

			bounty.text_box[i].location.x = right_x + interval_x2 + 5;
			bounty.text_box[i].location.y = start_y + ( ( i-19 ) * interval_y ) + 2;
			bounty.text_box[i].location.w = interval_x1 - 2;
			bounty.text_box[i].location.h = interval_y - 10;
		}

	}
	for ( ;i<40;i++ )
	{
		clear_text_box ( NULL, &bounty.text_box[i] );
		setup_text_box ( &bounty.text_box[i] );
		bounty.text_box[i].location.x = 122;
		bounty.text_box[i].location.w = 155;
		bounty.text_box[i].location.h = 10;
		bounty.text_box[i].max_char = 21;
		bounty.text_box[i].pass_char = '\0';
	}
	//NAME
	bounty.text_box[38].selected = 1;
	bounty.text_box[38].location.y = 496;
	bounty.text_box[38].location.x = 134;
	bounty.text_box[38].location.h = 10;
	bounty.text_box[38].location.w = 135;
	//PRICE
	bounty.text_box[39].location.y = 527;
	bounty.text_box[39].location.x = 134;
	bounty.text_box[39].location.h = 10;
	bounty.text_box[39].location.w = 135;
	//CURRENT MONEY
	bounty.money_label.location.x = 566;
	bounty.money_label.location.y = 497;
	bounty.money_label.location.w = 78;
	bounty.money_label.location.h = 20;
	bounty.money_label.message[0] = '\0';
	//BOUNTY STATUS
	bounty.status_label.location.x = 375;
	bounty.status_label.location.y = 497;
	bounty.status_label.location.w = 107;
	bounty.status_label.location.h = 20;
	bounty.status_label.message[0] = '\0';
	bounty.list_max = 0;
}

void load_bounty()
{
	char temp_str[50];

	if ( !bounty.backround )
	{
		bounty.backround = IMG_Load ( "graphics/bountyback.jpg" );
		bounty.bounty_text_img = IMG_Load ( "graphics/bounty_text.jpg" );
	}

	set_forms_invisible();
	bounty.visible = 1;
	SDL_BlitSurface ( bounty.backround, NULL, screen, NULL );

	//screen only stuff

	//draw money
	sprintf ( temp_str,"%d", game.money );
	draw_right_label ( screen, temp_str, &bounty.money_label, 107, 216, 210 );

	//clear stuff
	bounty_clear_all_text_boxes();

	//draw lists
	bounty_draw_raw_lists();

	//draw status label
	draw_center_label ( screen, bounty.status_label.message, &bounty.status_label, 107, 216, 210 );

	//draw our two text boxes
	if ( bounty.text_box[38].selected )
		select_text_box ( screen, &bounty.text_box[38] );
	else
		unselect_text_box ( screen, &bounty.text_box[38] );

	if ( bounty.text_box[39].selected )
		select_text_box ( screen, &bounty.text_box[39] );
	else
		unselect_text_box ( screen, &bounty.text_box[39] );

	sdl_flip_mutex();

	//now ask for the damn list
	bounty_request();
}

void button_bounty ( int x, int y )
{
	const int button_max = 2, text_box_max = 40;
	char rtn_str[10];
	int i, success = 0, button;

	for ( i=0;i<button_max;i++ )
		if ( x >= bounty.button[i].x && x <= bounty.button[i].x + bounty.button[i].w && y >= bounty.button[i].y && y <= bounty.button[i].y + bounty.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<text_box_max;i++ )
			if ( x >= bounty.text_box[i].location.x && x <= bounty.text_box[i].location.x + bounty.text_box[i].location.w && y >= bounty.text_box[i].location.y && y <= bounty.text_box[i].location.y + bounty.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
	{
		switch ( i )
		{
			case 0: //leave
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
					load_cb_info();
				}
				break;
			case 1: //submit
				bounty_add ( bounty.text_box[38].message,atoi ( bounty.text_box[39].message ) );
				break;
		}
	}
	else
	{
		int k;

		if ( i>=bounty.list_max  && i < text_box_max - 2 ) return;

		for ( k=0;k<text_box_max;k++ )
			if ( bounty.text_box[k].selected )
				unselect_text_box ( screen, &bounty.text_box[k] );

		select_text_box ( screen, &bounty.text_box[i] );

		sdl_flip_mutex();
	}
}

void key_bounty ( int c )
{
	int i;

	if ( c == 9 ) //tab
	{
		for ( i=0;i<40;i++ )
			if ( bounty.text_box[i].selected ) break;

		unselect_text_box ( screen, &bounty.text_box[i] );

		if ( i>=39 )
			{i=0;}
		else
			{i++;}

		if ( i>=bounty.list_max && i<38 ) i = 38;


		select_text_box ( screen, &bounty.text_box[i] );
		sdl_flip_mutex();
	}
	else if ( c == 13 ) //enter
	{
		for ( i=0;i<40;i++ )
			if ( bounty.text_box[i].selected ) break;

		if ( i==40 ) return;

		if ( i==38 || i==39 )
		{
			bounty_add ( bounty.text_box[38].message,atoi ( bounty.text_box[39].message ) );
		}
		else
		{
			bounty_add ( bounty.name_list_label[i].message,atoi ( bounty.text_box[i].message ) );
			clear_text_box ( screen, &bounty.text_box[i] );
		}
	}
	else
	{
		for ( i=0;i<40;i++ )
			if ( bounty.text_box[i].selected )
			{
				//never know
				if ( i>=bounty.list_max && i<38 ) continue;

				if ( i != 38 && ( ! ( c >= '0' && c <= '9' ) && ! ( c == 8 || c == 127 || c == 275 || c == 276 ) ) ) continue;

				add_text_box ( screen, &bounty.text_box[i], c );
				sdl_flip_mutex();
			}
	}

}
