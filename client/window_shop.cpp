#include "main.h"

void init_form_shop()
{
	int i, j, k;

	shop.backround = NULL;
	shop.no_missile = NULL;
	shop.no_gun = NULL;
	shop.no_misc = NULL;
	for ( i=0;i<8;i++ )
		shop.no_ship[i] = NULL;
	shop.temp_backround = SDL_CreateRGBSurface ( SDL_HWSURFACE, 800, 600, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
	shop.visible = 0;
	for ( i=0;i<B_SHOP_MAX_BUTTONS;i++ )
	{
		shop.button[i].x = 0;
		shop.button[i].y = 0;
		shop.button[i].w = 0;
		shop.button[i].h = 0;
	}
	shop.button[B_SHOP_EXIT].x = 456;
	shop.button[B_SHOP_EXIT].y = 62;
	shop.button[B_SHOP_EXIT].w = 45;
	shop.button[B_SHOP_EXIT].h = 14;

	shop.button[B_SHOP_BUY].x = 91;
	shop.button[B_SHOP_BUY].y = 93;
	shop.button[B_SHOP_BUY].w = 34;
	shop.button[B_SHOP_BUY].h = 15;

	shop.button[B_SHOP_SELL].x = 673;
	shop.button[B_SHOP_SELL].y = 92;
	shop.button[B_SHOP_SELL].w = 41;
	shop.button[B_SHOP_SELL].h = 14;

	shop.button[B_SHOP_BUY_1_LEFT].x = 85;
	shop.button[B_SHOP_BUY_1_LEFT].y = 127;
	shop.button[B_SHOP_BUY_1_LEFT].w = 20;
	shop.button[B_SHOP_BUY_1_LEFT].h = 20;

	shop.button[B_SHOP_BUY_1_RIGHT].x = 247;
	shop.button[B_SHOP_BUY_1_RIGHT].y = 127;
	shop.button[B_SHOP_BUY_1_RIGHT].w = 20;
	shop.button[B_SHOP_BUY_1_RIGHT].h = 20;

	shop.button[B_SHOP_BUY_2_LEFT].x = 85;
	shop.button[B_SHOP_BUY_2_LEFT].y = 150;
	shop.button[B_SHOP_BUY_2_LEFT].w = 20;
	shop.button[B_SHOP_BUY_2_LEFT].h = 20;

	shop.button[B_SHOP_BUY_2_RIGHT].x = 247;
	shop.button[B_SHOP_BUY_2_RIGHT].y = 150;
	shop.button[B_SHOP_BUY_2_RIGHT].w = 20;
	shop.button[B_SHOP_BUY_2_RIGHT].h = 20;

	shop.button[B_SHOP_CHASSIS].x = 295;
	shop.button[B_SHOP_CHASSIS].y = 305;
	shop.button[B_SHOP_CHASSIS].w = 45;
	shop.button[B_SHOP_CHASSIS].h = 14;

	shop.button[B_SHOP_GUN].x = 345;
	shop.button[B_SHOP_GUN].y = 305;
	shop.button[B_SHOP_GUN].w = 53;
	shop.button[B_SHOP_GUN].h = 14;

	shop.button[B_SHOP_MISSILE].x = 403;
	shop.button[B_SHOP_MISSILE].y = 305;
	shop.button[B_SHOP_MISSILE].w = 51;
	shop.button[B_SHOP_MISSILE].h = 14;

	shop.button[B_SHOP_MISC].x = 460;
	shop.button[B_SHOP_MISC].y = 305;
	shop.button[B_SHOP_MISC].w = 45;
	shop.button[B_SHOP_MISC].h = 14;

	shop.button[B_SHOP_HANGER_LEFT].x = 668;
	shop.button[B_SHOP_HANGER_LEFT].y = 435;
	shop.button[B_SHOP_HANGER_LEFT].w = 20;
	shop.button[B_SHOP_HANGER_LEFT].h = 20;

	shop.button[B_SHOP_HANGER_RIGHT].x = 693;
	shop.button[B_SHOP_HANGER_RIGHT].y = 435;
	shop.button[B_SHOP_HANGER_RIGHT].w = 20;
	shop.button[B_SHOP_HANGER_RIGHT].h = 20;

	shop.button[B_SHOP_HANGER_STORE_EQUIP].x = 536;
	shop.button[B_SHOP_HANGER_STORE_EQUIP].y = 438;
	shop.button[B_SHOP_HANGER_STORE_EQUIP].w = 657 - 536;
	shop.button[B_SHOP_HANGER_STORE_EQUIP].h = 17;
	for ( i=B_SHOP_MAX_BUTTONS, k=0;k<8;i++,k++ ) //first row of pods
	{
		shop.button[i].x = 429 + ( 36 * k );
		shop.button[i].y = 360;
		shop.button[i].w = 30;
		shop.button[i].h = 20;
	}
	for ( k=0;k<8;i++,k++ ) //second row of pods
	{
		shop.button[i].x = 429 + ( 36 * k );
		shop.button[i].y = 390;
		shop.button[i].w = 30;
		shop.button[i].h = 20;
	}
	for ( k=0;k<8;i++,k++ ) //first row of hanger pods
	{
		shop.button[i].x = 429 + ( 36 * k );
		shop.button[i].y = 460;
		shop.button[i].w = 30;
		shop.button[i].h = 20;
	}
	for ( k=0;k<8;i++,k++ ) //first row of hanger pods
	{
		shop.button[i].x = 429 + ( 36 * k );
		shop.button[i].y = 490;
		shop.button[i].w = 30;
		shop.button[i].h = 20;
	}
	shop.user_money_label.location.x = 352;
	shop.user_money_label.location.y = 63;
	shop.user_money_label.location.w = 98;
	shop.user_money_label.location.h = 11;

	shop.buy_money_label.location.x = 136;
	shop.buy_money_label.location.y = 91;
	shop.buy_money_label.location.w = 80;
	shop.buy_money_label.location.h = 20;

	shop.sell_money_label.location.x = 584;
	shop.sell_money_label.location.y = 91;
	shop.sell_money_label.location.w = 80;
	shop.sell_money_label.location.h = 20;

	shop.sel_left_label[0].location.x = 105;
	shop.sel_left_label[0].location.y = 127;
	shop.sel_left_label[0].location.w = 142;
	shop.sel_left_label[0].location.h = 20;
	shop.sel_left_label[1].location.x = 105;
	shop.sel_left_label[1].location.y = 150;
	shop.sel_left_label[1].location.w = 142;
	shop.sel_left_label[1].location.h = 20;
	shop.sel_right_label[0].location.x = 550;
	shop.sel_right_label[0].location.y = 127;
	shop.sel_right_label[0].location.w = 142;
	shop.sel_right_label[0].location.h = 20;
	shop.sel_right_label[1].location.x = 550;
	shop.sel_right_label[1].location.y = 150;
	shop.sel_right_label[1].location.w = 142;
	shop.sel_right_label[1].location.h = 20;
	shop.user_money_label.message[0] 	= '\0';
	shop.buy_money_label.message[0] 	= '\0';
	shop.sell_money_label.message[0] 	= '\0';
	shop.sel_left_label[0].message[0]	= '\0';
	shop.sel_left_label[1].message[0]	= '\0';
	for ( i=0;i<10;i++ )
	{
		shop.info_left_label[i].location.x = 85;
		shop.info_left_label[i].location.y = 177 + i * 17;
		shop.info_left_label[i].location.w = 110;
		shop.info_left_label[i].location.h = 17;
		shop.stat_left_label[i].location.x = 195;
		shop.stat_left_label[i].location.y = 177 + i * 17;
		shop.stat_left_label[i].location.w = 72;
		shop.stat_left_label[i].location.h = 17;
		shop.info_right_label[i].location.x = 530;
		shop.info_right_label[i].location.y = 177 + i * 17;
		shop.info_right_label[i].location.w = 110;
		shop.info_right_label[i].location.h = 17;
		shop.stat_right_label[i].location.x = 640;
		shop.stat_right_label[i].location.y = 177 + i * 17;
		shop.stat_right_label[i].location.w = 72;
		shop.stat_right_label[i].location.h = 17;
		shop.stat_left_label[i].message[0] = '\0';
		shop.stat_right_label[i].message[0] = '\0';
	}
	shop.info_left_label[0].location.y = 170;
	shop.stat_left_label[0].location.y = 170;
	shop.info_right_label[0].location.y = 170;
	shop.stat_right_label[0].location.y = 170;
	for ( i=0;i<2;i++ )
	{
		shop.sel_left_label[i].message[0] = '\0';
		shop.sel_right_label[i].message[0] = '\0';
	}
	shop.hanger_label.location.x = 430;
	shop.hanger_label.location.y = 438;
	shop.hanger_label.location.w = 534 - 430;
	shop.hanger_label.location.h = 17;
	shop.hanger_label.message[0] = '\0';
	shop.store_equip_label.location.x = 536;
	shop.store_equip_label.location.y = shop.hanger_label.location.y;
	shop.store_equip_label.location.w = 657 - 536;
	shop.store_equip_label.location.h = 17;
	shop.store_equip_label.message[0] = '\0';
	shop.left_display_box.lines = 3;
	shop.right_display_box.lines = 3;
	shop.left_display_box.x = shop.info_left_label[7].location.x;
	shop.left_display_box.y = shop.info_left_label[7].location.y;
	shop.left_display_box.w = 267 - shop.left_display_box.x;
	shop.right_display_box.x = shop.info_right_label[7].location.x;
	shop.right_display_box.y = shop.info_right_label[7].location.y;
	shop.right_display_box.w = shop.left_display_box.w;
	setup_display_box ( & ( shop.left_display_box ) );
	setup_display_box ( & ( shop.right_display_box ) );
	shop.last_planet 	= -1;
	shop.ship_kind_sel 	= -1;
	shop.ship_type_sel 	= -1;
	shop.gun_sel 		= -1;
	shop.missile_sel 	= -1;
	shop.misc_sel 		= -1;
	shop.gun_pod_sel 	= 0;
	shop.missile_pod_sel 	= 0;
	shop.misc_pod_sel	= 0;
	shop.gun_hanger_sel = 0;
	shop.missile_hanger_sel = 0;
	shop.gun_hanger_depth = 0;
	shop.missile_hanger_depth = 0;
	shop.hanger_pod_selected = 0;
}


void load_shop()
{
	char temp_str[32];
	int i, j, k;
	SDL_Rect destination;
	void *nothing = NULL;

	if ( !shop.backround )
	{
		shop.backround = IMG_Load ( "graphics/shopback.jpg" );
		shop.buy_img = IMG_Load ( "graphics/buy.png" );
		shop.sell_img = IMG_Load ( "graphics/sell.png" );
		shop.empty_pod = IMG_Load ( "graphics/empty_pod.jpg" );
		shop.sel_right = IMG_Load ( "graphics/selup.jpg" );
		shop.sel_left = IMG_Load ( "graphics/seldown.jpg" );
		shop.no_misc_pod = IMG_Load ( "graphics/nif/nif_miscpod_pod.jpg" );
		shop.misc_pod[0] = IMG_Load ( "graphics/shop/equipment/icons/Hull Booster.jpg" ); //0-Hull,1-Shield,2-Cargo,3-Jump
		shop.misc_pod[1] = IMG_Load ( "graphics/shop/equipment/icons/Shielding.jpg" );
		shop.misc_pod[2] = IMG_Load ( "graphics/shop/equipment/icons/Cargo Pod.jpg" );
		shop.misc_pod[3] = IMG_Load ( "graphics/shop/equipment/icons/Jump Drive.jpg" );
		shop.sel_blank = SDL_CreateRGBSurface ( SDL_HWSURFACE, 20, 20, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
		shop.ship_blank = SDL_CreateRGBSurface ( SDL_HWSURFACE, 280, 190, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
		shop.buy_blank = SDL_CreateRGBSurface ( SDL_HWSURFACE, 34, 15, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
		shop.sell_blank = SDL_CreateRGBSurface ( SDL_HWSURFACE, 41, 14, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
		shop.blank_pod = SDL_CreateRGBSurface ( SDL_HWSURFACE, 30, 20, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
		SDL_FillRect ( shop.sel_blank, NULL, SDL_MapRGB ( shop.sel_blank->format, 0, 0, 0 ) );
		SDL_FillRect ( shop.ship_blank, NULL, SDL_MapRGB ( shop.ship_blank->format, 0, 0, 0 ) );
		SDL_FillRect ( shop.buy_blank, NULL, SDL_MapRGB ( shop.buy_blank->format, 0, 0, 0 ) );
		SDL_FillRect ( shop.sell_blank, NULL, SDL_MapRGB ( shop.sell_blank->format, 0, 0, 0 ) );
		SDL_FillRect ( shop.blank_pod, NULL, SDL_MapRGB ( shop.blank_pod->format, 0, 0, 0 ) );

	}

	if ( shop.last_planet != planet.last_planet )
	{
		SDL_Surface *shop_img;
		char temp_str[200];

		SDL_BlitSurface ( shop.backround, NULL, shop.temp_backround, NULL );

		sprintf ( temp_str, "server/%s/backs/shop/shop%d.jpg", server[game.server_id].servername, planet.last_planet );
		shop_img = IMG_Load ( temp_str );
		destination.x = 307;
		destination.y = 109;

		if ( !shop_img )
		{
			if ( !game.nif_image.no_shop_img )
				game.nif_image.no_shop_img = IMG_Load ( "graphics/nif/nif_shop.jpg" );

			shop_img = game.nif_image.no_shop_img;
		}

		SDL_BlitSurface ( shop_img, NULL, shop.temp_backround, &destination );

		if ( shop_img != game.nif_image.no_shop_img )
			SDL_FreeSurface ( shop_img );

		shop_set_initial_selections();

		shop.shop_sel 		= -1;
	}

	//set all sell labels to nothing if we dont have a ship...
	if ( game.ship[game.ship_sel].server_id < 0 || game.ship[game.ship_sel].type < 0 || game.ship[game.ship_sel].kind < 0 )
	{
		for ( i=0;i<10;i++ )
		{
			draw_label ( shop.temp_backround,"", &shop.info_right_label[i], 255, 255, 255 );
			draw_right_label ( shop.temp_backround,"", &shop.stat_right_label[i], 255, 255, 255 );
		}
		draw_right_label ( shop.temp_backround,"", &shop.sell_money_label, 255, 255, 255 ); //clear sell ammount
		draw_center_label ( shop.temp_backround,"", &shop.sel_right_label[0], 255, 255, 255 ); //Set Selection Names
		draw_center_label ( shop.temp_backround,"", &shop.sel_right_label[1], 255, 255, 255 );
		SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] ); //clear sell button

		for ( i=0;i<16;i++ ) //clean up the damn mess...
			SDL_BlitSurface ( shop.blank_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

		//handle special case...
		if ( shop.shop_sel == 0 && game.money >= server[game.server_id].ship[shop.ship_type_sel].cost[shop.ship_kind_sel] )
			SDL_BlitSurface ( shop.buy_img, NULL, shop.temp_backround, &shop.button[1] );
		else
			SDL_BlitSurface ( shop.buy_blank, NULL, shop.temp_backround, &shop.button[1] );
	}

	set_forms_invisible();
	shop.visible = 1;
	shop.last_planet = planet.last_planet;
	sprintf ( temp_str,"%d", game.money );
	draw_right_label ( shop.temp_backround, temp_str, &shop.user_money_label, 255, 255, 255 );

	//shop.shop_sel = -1;
	shop_draw_select_pod_box(0);
	change_shop ( 0 );
	if ( !shop.thread )
		shop.thread = SDL_CreateThread ( rotate_shop_buy_pic, nothing );
}

void button_shop ( int x, int y )
{
	const int max_buttons = B_SHOP_MAX_BUTTONS+32;
	int i;

	for ( i=0;i<max_buttons;i++ )
		if ( x >= shop.button[i].x && x <= shop.button[i].x + shop.button[i].w && y >= shop.button[i].y && y <= shop.button[i].y + shop.button[i].h )
			break;

	if ( i == max_buttons ) return;

	switch ( i )
	{
		case B_SHOP_EXIT: //exit
			shop.visible = 0;

			//dont do a thing if the repair screen is still f'ing around
			while ( shop.thread )
			{
#ifdef WIN32
				Sleep ( 1 );
#else
				usleep ( 1000 );
#endif
			}

			load_hanger();

			break;
		case B_SHOP_BUY: //buy
			switch ( shop.shop_sel )
			{
				case 0: //chassis
					if ( game.money >= server[game.server_id].ship[shop.ship_type_sel].cost[shop.ship_kind_sel] )
						purchase_ship ( shop.ship_type_sel, shop.ship_kind_sel );
					break;
				case 1: //gun
					if ( game.money >= server[game.server_id].gun[shop.gun_sel].cost ) //will need to check for if you have a ship selected too...
						purchase_ship_mod ( 1, shop.gun_sel );
					break;
				case 2: //missile
					if ( game.money >= server[game.server_id].missile[shop.missile_sel].cost )
						purchase_ship_mod ( 2, shop.missile_sel );
					break;
				case 3: //misc
					if ( game.money >= misc_pod_cost ( shop.misc_sel ) )
						purchase_ship_mod ( 3, shop.misc_sel );
					break;
			}
			break;
		case B_SHOP_SELL: //sell
			switch ( shop.shop_sel )
			{
				case 0: //chassis
					sell_ship ( game.ship_sel );
					break;
				case 1: //gun
					if(shop.hanger_pod_selected)
						sell_hanger_weapon(0, shop.gun_hanger_sel + (shop.gun_hanger_depth * 16));
					else
						sell_ship_mod ( shop.shop_sel, shop.gun_pod_sel );
					break;
				case 2: //missile
					if(shop.hanger_pod_selected)
						sell_hanger_weapon(1, shop.missile_hanger_sel + (shop.missile_hanger_depth * 16));
					else
						sell_ship_mod ( shop.shop_sel, shop.missile_pod_sel );

					break;
				case 3: //misc
					sell_ship_mod ( shop.shop_sel, shop.misc_pod_sel );
					break;
			}
			break;
		case B_SHOP_BUY_1_LEFT: //left_top
			set_shop_type_down();
			break;
		case B_SHOP_BUY_1_RIGHT: //right_top
			set_shop_type_up();
			break;
		case B_SHOP_BUY_2_LEFT: //left_bottom
			set_shop_kind_down();
			break;
		case B_SHOP_BUY_2_RIGHT: //right_bottom
			set_shop_kind_up();
			break;
		case B_SHOP_CHASSIS: //chassis shop
			change_shop ( 0 );
			break;
		case B_SHOP_GUN: //guns shop
			change_shop ( 1 );
			break;
		case B_SHOP_MISSILE: //missiles shop
			change_shop ( 2 );
			break;
		case B_SHOP_MISC: //misc shop
			change_shop ( 3 );
			break;
		case B_SHOP_HANGER_LEFT:
			shop_hanger_left_button();
			break;
		case B_SHOP_HANGER_RIGHT:
			shop_hanger_right_button();
			break;
		case B_SHOP_HANGER_STORE_EQUIP:
			shop_hanger_store_equip_button();
			break;
		default: //all remaining cases are pod selects, so...
			if(i<B_SHOP_HANGER_WEAPON_POD)
				select_shop_sell_pod ( i - B_SHOP_WEAPON_POD );
			else
				select_shop_hanger_pod ( i - B_SHOP_HANGER_WEAPON_POD );
			break;
	}
}

void shop_hanger_left_button()
{
	int *current_depth = NULL;

	if(shop.shop_sel == 1) current_depth = &shop.gun_hanger_depth;
	if(shop.shop_sel == 2) current_depth = &shop.missile_hanger_depth;

	if(!current_depth) return;
	if(*current_depth <= 0) return;

	*current_depth -= 1;

	if(*current_depth < 0) *current_depth = 0;

	shop_display_hanger_weapons();

	if(shop.hanger_pod_selected) shop_display_sell_item();

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void shop_hanger_right_button()
{
	int *current_depth = NULL;

	if(shop.shop_sel == 1) current_depth = &shop.gun_hanger_depth;
	if(shop.shop_sel == 2) current_depth = &shop.missile_hanger_depth;

	if(!current_depth) return;
	if(*current_depth > 2) return;

	*current_depth += 1;

	if(*current_depth > 2) *current_depth = 2;

	shop_display_hanger_weapons();

	if(shop.hanger_pod_selected) shop_display_sell_item();

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void shop_hanger_store_equip_button()
{
	char send_str[200];

	switch(shop.shop_sel)
	{
	default: return;
	case 1:
		if(shop.hanger_pod_selected)
			sprintf(send_str, "65,0,%d", shop.gun_hanger_sel + (shop.gun_hanger_depth * 16));
		else
			sprintf(send_str, "64,0,%d", shop.gun_pod_sel);
		break;
	case 2:
		if(shop.hanger_pod_selected)
			sprintf(send_str, "65,1,%d", shop.missile_hanger_sel + (shop.missile_hanger_depth * 16));
		else
			sprintf(send_str, "64,1,%d", shop.missile_pod_sel);
		break;
	}

	send_con_hub(send_str);
}

void change_shop ( int new_shop )
{
	char temp_str[32];
	int i, show_buy_img = 1;
	int previous_shop;

	//special case inwhich we may have bought plans at the homeplanet
	if(shop.shop_sel == new_shop && !new_shop && at_home_planet())
	{
		shop_show_type_left_right();
		shop_show_kind_left_right();
	}

	if ( shop.shop_sel != new_shop )
	{
		shop_blank_current_item_sell();

		previous_shop = shop.shop_sel;
		shop.shop_sel = new_shop;
		if(shop_can_be_set_to(new_shop))
		switch ( new_shop )
		{
			case 0: //chassis
				shop_show_type_left_right();
				shop_show_kind_left_right();

				shop_display_buy_ship_stat_names();

				shop_display_buy_ship_stats();

				shop.attempt_load_buy = 0;
				shop.rotate = 0; //reset index to start

				shop_display_hanger_weapons();

				shop_show_buy_button();

				break;
			case 1: //guns
				shop_show_kind_left_right();

				if ( previous_shop == 0 ) //if the last shop was the chassis one, black out these unneeded buttons and label
				{
					SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[3] );
					SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[4] );
					draw_center_label ( shop.temp_backround,"", &shop.sel_left_label[0], 255, 255, 255 );
				}

				shop_display_buy_gun_stat_names();

				shop_display_buy_gun_stats();

				shop.attempt_load_buy = 0;
				shop.rotate = 0; //reset index to start

				shop_display_hanger_weapons();

				shop_show_buy_button();

				//shop.shop_sel = 1;
				break;
			case 2: //missiles
				shop_show_kind_left_right();

				if ( previous_shop == 0 ) //if the last shop was the chassis one, black out these unneeded buttons and label
				{
					SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[3] );
					SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[4] );
					draw_center_label ( shop.temp_backround,"", &shop.sel_left_label[0], 255, 255, 255 );
				}

				shop_display_buy_missile_stat_names();

				shop_display_buy_missile_stats();

				shop.attempt_load_buy = 0;
				shop.rotate = 0; //reset index to start

				shop_display_hanger_weapons();

				shop_show_buy_button();

				break;
			case 3: //misc
				shop_show_kind_left_right();

				if ( previous_shop == 0 ) //if the last shop was the chassis one, black out these unneeded buttons and label
				{
					SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[3] );
					SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[4] );
					draw_center_label ( shop.temp_backround,"", &shop.sel_left_label[0], 255, 255, 255 );
				}

				shop_display_buy_misc_stat_names();

				shop_display_buy_misc();

				shop.attempt_load_buy = 0;
				shop.rotate = 0; //reset index to start

				shop_display_hanger_weapons();

				shop_show_buy_button();

				break;
		}

	}

	if ( game.ship[game.ship_sel].server_id > -1 && game.ship[game.ship_sel].type > -1 && game.ship[game.ship_sel].kind > -1 )
		view_sell_shop();
	else
		SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] );

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();

}

void clear_sell_shop()
{
	int i, show_buy_img = 1;

	for ( i=0;i<10;i++ )
	{
		draw_label ( shop.temp_backround,"", &shop.info_right_label[i], 255, 255, 255 );
		draw_right_label ( shop.temp_backround,"", &shop.stat_right_label[i], 255, 255, 255 );
	}

	draw_right_label ( shop.temp_backround,"", &shop.sell_money_label, 255, 255, 255 );

	draw_center_label ( shop.temp_backround,"", &shop.sel_right_label[0], 255, 255, 255 ); //Set Selection Names
	draw_center_label ( shop.temp_backround,"", &shop.sel_right_label[1], 255, 255, 255 );

	SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] ); //remove sell button

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			shop_show_buy_button();
			break;
		case 1: //gun
			shop_show_buy_button();
			break;
		case 2: //missile
			shop_show_buy_button();
			break;
		case 3: //misc
			shop_show_buy_button();
			break;
	}
}

void view_sell_shop()
{
	char temp_str[32], temp_filename[200];
	int i, temp_misc;

	switch ( shop.shop_sel )
	{
		case 0://chassis

			shop_display_sell_ship_stat_names();

			shop_display_sell_ship();

			shop.attempt_load_sell = 0;
			shop.rotate_sell = 0; //reset index to start

			for ( i=0;i<16;i++ ) //clean up the damn mess...
				SDL_BlitSurface ( shop.blank_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

			SDL_BlitSurface ( shop.buy_blank, NULL, shop.temp_backround, &shop.button[1] ); //remove buy button
			SDL_BlitSurface ( shop.sell_img, NULL, shop.temp_backround, &shop.button[2] ); //add sell button
			break;
		case 1://gun

			shop_display_sell_gun_stat_names();

			shop_display_sell_item();

			shop_display_sell_guns();

			break;
		case 2://missile

			shop_display_sell_missile_stat_names();

			shop_display_sell_item();

			for ( i=0;i<game.ship[game.ship_sel].missile_ammount;i++ ) //show those missile pods
				if ( game.ship[game.ship_sel].missile[i] > -1 && game.ship[game.ship_sel].missile[i] < MISSILE_MAX && game.ship[game.ship_sel].missile_id[i] > -1 && game.ship[game.ship_sel].missile_id[i] < MAX_SERVER )
				{
					if ( !load_missile_pod_img ( i ) ) //still not loaded... wah
						SDL_BlitSurface ( game.nif_image.no_missile_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
					else //or is it?
						SDL_BlitSurface ( server[game.ship[game.ship_sel].missile_id[i]].missile[game.ship[game.ship_sel].missile[i]].missile_pod_img, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

				}
				else
				{
					SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
				}

			for ( ;i<16;i++ ) //blank out remaining spots
				SDL_BlitSurface ( shop.blank_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

			break;
		case 3://misc

			shop_display_sell_misc_stat_names();

			shop_display_sell_item();

			for ( i=0;i<game.ship[game.ship_sel].misc_ammount;i++ ) //show those misc pods
				if ( game.ship[game.ship_sel].misc[i] > -1 )
				{
					temp_misc = game.ship[game.ship_sel].misc[i];

					switch(temp_misc)
					{ //*newa
					case MK2_HULL:
					case MK3_HULL:
						temp_misc = MK1_HULL;
						break;
					case MK2_SHIELD:
					case MK3_SHIELD:
						temp_misc = MK1_SHIELD;
						break;
					case MK2_CARGO:
					case MK3_CARGO:
						temp_misc = MK1_CARGO;
						break;
					case MK2_JUMP:
					case MK3_JUMP:
						temp_misc = MK1_JUMP;
						break;
					}

					if ( !shop.misc_pod[temp_misc] ) //odd, its not loaded...
						SDL_BlitSurface ( shop.no_misc_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
					else //or is it?
						SDL_BlitSurface ( shop.misc_pod[temp_misc], NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

				}
				else
				{
					SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
				}

			for ( ;i<16;i++ ) //blank out remaining spots
				SDL_BlitSurface ( shop.blank_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

			break;
	}
}

int shop_hanger_weapon_is_selected( int ht, int hk )
{
	if(!shop.hanger_pod_selected) return 0;

	switch(ht)
	{
	case 0:
		if(shop.shop_sel != 1) return 0;
		return hk == shop.gun_hanger_sel + (shop.gun_hanger_depth * 16);
		break;
	case 1:
		if(shop.shop_sel != 2) return 0;
		return hk == shop.missile_hanger_sel + (shop.missile_hanger_depth * 16);
		break;
	}

	return 0;
}

void shop_update_weapon_hanger( int ht, int hk )
{
	//spare me brother
	if ( !shop.visible ) return;

	switch(ht)
	{
	default: return;
	case 0: if ( shop.shop_sel != 1 ) return; break;
	case 1: if ( shop.shop_sel != 2 ) return; break;
	}

	shop_display_hanger_weapon_pod(hk % 16);

	if(shop_hanger_weapon_is_selected(ht, hk)) shop_display_sell_item();

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void update_shop_sell ( int mod_type, int slot_number )
{
	char temp_str[32], temp_filename[200];
	int i, temp_misc;

	if ( !shop.visible ) return; //ya uh spare us if were not there...

	switch ( mod_type )
	{
		case 0://gun
			if ( shop.shop_sel != 1 ) break; //don't bother if we aren't even viewing this shop...

			if ( game.ship[game.ship_sel].gun[slot_number] > -1 && game.ship[game.ship_sel].gun[slot_number] < GUN_MAX && game.ship[game.ship_sel].gun_id[slot_number] > -1 && game.ship[game.ship_sel].gun_id[slot_number] < MAX_SERVER ) //if this selection isn't empty
			{
				shop_display_sell_item();

				//if ( slot_number == shop.gun_pod_sel ) //only dick around with stuff if we are editing the selected item
				//{
				//	shop_display_sell_gun();

				//	SDL_BlitSurface ( shop.sell_img, NULL, shop.temp_backround, &shop.button[2] );
				//}

				//load the image if needed
				if ( load_gun_pod_img ( slot_number ) )
					SDL_BlitSurface ( server[game.ship[game.ship_sel].gun_id[slot_number]].gun[game.ship[game.ship_sel].gun[slot_number]].gun_pod_img, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
				else
					SDL_BlitSurface ( game.nif_image.no_gun_pod, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
			}
			else
			{
				if ( slot_number == shop.gun_pod_sel ) //only dick around with stuff if we are editing the selected item
				{
					shop_select_next_sell_item();

					shop_display_sell_item();
				}

				SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
			}

			//check if we used up all the slots and the buy img should not be removed
			for ( i=0;i<server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].gun_ammount[game.ship[game.ship_sel].kind];i++ )
				if ( game.ship[game.ship_sel].gun[i] < 0 || game.ship[game.ship_sel].gun_id[i] < 0 ) //check for emptyness
					break;

			if ( i == server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].gun_ammount[game.ship[game.ship_sel].kind] )
				SDL_BlitSurface ( shop.buy_blank, NULL, shop.temp_backround, &shop.button[1] );
			else
				SDL_BlitSurface ( shop.buy_img, NULL, shop.temp_backround, &shop.button[1] );

			SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
			break;
		case 1://missile
			if ( shop.shop_sel != 2 ) break;

			if ( game.ship[game.ship_sel].missile[slot_number] > -1 && game.ship[game.ship_sel].missile[slot_number] < MISSILE_MAX && game.ship[game.ship_sel].missile_id[slot_number] > -1 && game.ship[game.ship_sel].missile_id[slot_number] < MAX_SERVER )
			{
				if ( slot_number == shop.missile_pod_sel ) //only dick around with stuff if we are editing the selected item
				{
					shop_display_sell_item();

					//shop_display_sell_missile();

					//SDL_BlitSurface ( shop.sell_img, NULL, shop.temp_backround, &shop.button[2] );
				}

				if ( load_missile_pod_img ( slot_number ) )
					SDL_BlitSurface ( server[game.ship[game.ship_sel].missile_id[slot_number]].missile[game.ship[game.ship_sel].missile[slot_number]].missile_pod_img, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
				else
					SDL_BlitSurface ( game.nif_image.no_missile_pod, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
			}
			else
			{
				if ( slot_number == shop.missile_pod_sel ) //only dick around with stuff if we are editing the selected item
				{
					shop_select_next_sell_item();

					shop_display_sell_item();
				}

				SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
			}

			//check if we used up all the slots and the buy img should not be removed
			for ( i=0;i<server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].missile_ammount[game.ship[game.ship_sel].kind];i++ )
				if ( game.ship[game.ship_sel].missile[i] < 0 || game.ship[game.ship_sel].missile_id[i] < 0 ) //check for emptyness
					break;

			if ( i == server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].missile_ammount[game.ship[game.ship_sel].kind] )
				SDL_BlitSurface ( shop.buy_blank, NULL, shop.temp_backround, &shop.button[1] );
			else
				SDL_BlitSurface ( shop.buy_img, NULL, shop.temp_backround, &shop.button[1] );

			SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
			break;
		case 2://misc
			if ( shop.shop_sel != 3 ) break;

			if ( game.ship[game.ship_sel].misc[slot_number] > -1 )
			{
				if ( shop.misc_pod_sel == slot_number )
				{
					shop_display_sell_item();

					//shop_display_sell_misc();

					//SDL_BlitSurface ( shop.sell_img, NULL, shop.temp_backround, &shop.button[2] );
				}

				temp_misc = game.ship[game.ship_sel].misc[slot_number];

				switch(temp_misc)
					{
					case MK2_HULL:
					case MK3_HULL:
						temp_misc = MK1_HULL;
						break;
					case MK2_SHIELD:
					case MK3_SHIELD:
						temp_misc = MK1_SHIELD;
						break;
					case MK2_CARGO:
					case MK3_CARGO:
						temp_misc = MK1_CARGO;
						break;
					case MK2_JUMP:
					case MK3_JUMP:
						temp_misc = MK1_JUMP;
						break;
					}

				if ( !shop.misc_pod[temp_misc] ) //odd, its not loaded...
					SDL_BlitSurface ( shop.no_misc_pod, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
				else //or is it?
					SDL_BlitSurface ( shop.misc_pod[temp_misc], NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
			}
			else
			{
				if ( shop.misc_pod_sel == slot_number )
				{
					shop_select_next_sell_item();

					shop_display_sell_item();
				}

				SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, &shop.button[slot_number + B_SHOP_MAX_BUTTONS] );
			}

			//check if we used up all the slots and the buy img should not be removed
			for ( i=0;i<server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].misc_ammount[game.ship[game.ship_sel].kind];i++ )
				if ( game.ship[game.ship_sel].misc[i] < 0 ) //check for emptyness
					break;

			if ( i == server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].misc_ammount[game.ship[game.ship_sel].kind] )
				SDL_BlitSurface ( shop.buy_blank, NULL, shop.temp_backround, &shop.button[1] );
			else
				SDL_BlitSurface ( shop.buy_img, NULL, shop.temp_backround, &shop.button[1] );

			SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
			break;
	}
}

void select_shop_hanger_pod( int p )
{
	int *cur_sel = NULL;

	if(shop.shop_sel == 1) cur_sel = &shop.gun_hanger_sel;
	if(shop.shop_sel == 2) cur_sel = &shop.missile_hanger_sel;

	if(!cur_sel) return;

	//unselect
	shop_draw_select_pod_box(0);

	//set new
	*cur_sel = p;
	shop.hanger_pod_selected = 1;

	//display
	shop_display_sell_item();

	//draw
	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();

	printf("select_shop_hanger_pod:%d\n", p);
}

void select_shop_sell_pod ( int pod_number )
{
	char temp_str[32];
	int i;
	int *cur_sel = NULL;
	int max_available = 0;
	int sh;

	sh = game.ship_sel;

	//have to have a ship obviously
	if(game.ship[sh].server_id < 0) return;
	if(game.ship[sh].type < 0) return;
	if(game.ship[sh].kind < 0) return;

	//collect particulars
	switch ( shop.shop_sel )
	{
	default: return;
	case 0: return;
	case 1:
		max_available = game.ship[sh].gun_ammount;
		cur_sel = &shop.gun_pod_sel;
		break;
	case 2:
		max_available = game.ship[sh].missile_ammount;
		cur_sel = &shop.missile_pod_sel;
		break;
	case 3:
		max_available = game.ship[sh].misc_ammount;
		cur_sel = &shop.misc_pod_sel;
		break;
	}

	if(pod_number >= max_available) return;

	//unselect
	shop_draw_select_pod_box(0);

	//set
	shop.hanger_pod_selected = 0;
	*cur_sel = pod_number;

	//render
	shop_display_sell_item();
	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
}

int rotate_shop_buy_pic ( void *nothing )
{
	int temp_misc;
	SDL_Rect buy_pic_location, sell_pic_location;
	char temp_filename[200], temp_str[21];
	int attempt_load_buy_safety, attempt_load_sell_safety;
	int show_ship_buy, show_gun_buy, show_missile_buy;

	show_ship_buy = shop_can_be_set_to(0);
	show_gun_buy = shop_can_be_set_to(0);
	show_missile_buy = shop_can_be_set_to(0);

	buy_pic_location.x = 100;
	buy_pic_location.y = 345;
	sell_pic_location.x = 420;
	sell_pic_location.y = 345;

	while ( shop.visible )
	{
		if ( shop.rotate == 16 ) shop.rotate = 0; //loop back to start..
		if ( shop.rotate_sell == 16 ) shop.rotate_sell = 0;

		switch ( shop.shop_sel )
		{
			case 0: //chassis
				//Begin sell ship rotate code...

				if ( game.ship[game.ship_sel].server_id > -1 && game.ship[game.ship_sel].type > -1 && game.ship[game.ship_sel].kind > -1 ) //if we got a ship...
				{
					if ( shop.attempt_load_sell > -1 ) //load img if requested
					{
						shop.rotate_sell = attempt_load_sell_safety = shop.attempt_load_sell;//make sure they are insync, and set safety

						if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][shop.attempt_load_sell] )
						{
							sprintf ( temp_filename, "server/%s/shop/ships/%s/%s%d.JPG", server[game.ship[game.ship_sel].server_id].servername, ship_name ( game.ship[game.ship_sel].kind, temp_str ), server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].name, attempt_load_sell_safety + 1 );
							server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][attempt_load_sell_safety] = IMG_Load ( temp_filename );
						}

						if ( shop.attempt_load_sell == 15 || !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][attempt_load_sell_safety] )
							shop.attempt_load_sell = -2;

						if ( attempt_load_sell_safety == shop.attempt_load_sell )
							shop.attempt_load_sell++;
					}

					if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][0] ) //if no starting index then display the "no ship" img
					{
						if ( !shop.no_ship[game.ship[game.ship_sel].kind] ) //load the image if not already.
						{
							sprintf ( temp_filename, "graphics/nif/nif_%s.jpg", ship_name ( game.ship[game.ship_sel].kind, temp_str ) );
							shop.no_ship[game.ship[game.ship_sel].kind] = IMG_Load ( temp_filename );
						}
						SDL_BlitSurface ( shop.no_ship[game.ship[game.ship_sel].kind], NULL, screen, &sell_pic_location );
					}
					else
					{
						if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][shop.rotate_sell] )
							shop.rotate_sell = 0; //Set back if you hit a premature end

						SDL_BlitSurface ( server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][shop.rotate_sell], NULL, screen, &sell_pic_location );
					}

				}

				//Begin buy ship rotate code...
				if(!show_ship_buy) break;

				if ( shop.attempt_load_buy > -1 ) //load img if requested
				{
					shop.rotate = attempt_load_buy_safety = shop.attempt_load_buy;//make sure they are insync, and set safety

					if ( !server[game.server_id].ship[shop.ship_type_sel].ship_img[shop.ship_kind_sel][shop.attempt_load_buy] )
					{
						sprintf ( temp_filename, "server/%s/shop/ships/%s/%s%d.JPG", server[game.server_id].servername, ship_name ( shop.ship_kind_sel, temp_str ), server[game.server_id].ship[shop.ship_type_sel].name, attempt_load_buy_safety + 1 );
						server[game.server_id].ship[shop.ship_type_sel].ship_img[shop.ship_kind_sel][attempt_load_buy_safety] = IMG_Load ( temp_filename );
					}

					if ( shop.attempt_load_buy == 15 || !server[game.server_id].ship[shop.ship_type_sel].ship_img[shop.ship_kind_sel][attempt_load_buy_safety] )
						shop.attempt_load_buy = -2;

					if ( attempt_load_buy_safety == shop.attempt_load_buy )
						shop.attempt_load_buy++;
				}

				if ( !server[game.server_id].ship[shop.ship_type_sel].ship_img[shop.ship_kind_sel][0] ) //if no starting index then display the "no ship" img
				{
					if ( !shop.no_ship[shop.ship_kind_sel] ) //load the image if not already.
					{
						sprintf ( temp_filename, "graphics/nif/nif_%s.jpg", ship_name ( shop.ship_kind_sel, temp_str ) );
						shop.no_ship[shop.ship_kind_sel] = IMG_Load ( temp_filename );
					}
					SDL_BlitSurface ( shop.no_ship[shop.ship_kind_sel], NULL, screen, &buy_pic_location );
					sdl_flip_mutex();
					break;
				}

				if ( !server[game.server_id].ship[shop.ship_type_sel].ship_img[shop.ship_kind_sel][shop.rotate] )
					shop.rotate = 0; //Set back if you hit a premature end

				SDL_BlitSurface ( server[game.server_id].ship[shop.ship_type_sel].ship_img[shop.ship_kind_sel][shop.rotate], NULL, screen, &buy_pic_location );
				sdl_flip_mutex();
				break;
			case 1: //guns
				if(!show_gun_buy) break;

				if ( shop.attempt_load_buy > -1 ) //load img if requested
				{
					shop.rotate = attempt_load_buy_safety = shop.attempt_load_buy;//make sure they are insync, and set safety

					if ( !server[game.server_id].gun[shop.gun_sel].gun_img[shop.attempt_load_buy] )
					{
						sprintf ( temp_filename, "server/%s/shop/guns/pics/%s%d.jpg", server[game.server_id].servername, server[game.server_id].gun[shop.gun_sel].name, attempt_load_buy_safety + 1 );
						server[game.server_id].gun[shop.gun_sel].gun_img[attempt_load_buy_safety] = IMG_Load ( temp_filename );
					}

					if ( shop.attempt_load_buy == 15 || !server[game.server_id].gun[shop.gun_sel].gun_img[attempt_load_buy_safety] )
						shop.attempt_load_buy = -2;

					if ( attempt_load_buy_safety == shop.attempt_load_buy )
						shop.attempt_load_buy++;
				}

				if ( !server[game.server_id].gun[shop.gun_sel].gun_img[0] ) //if no starting index then display the "no ship" img
				{
					if ( !shop.no_gun ) //load the image if not already.
					{
						strcpy ( temp_filename, "graphics/nif/nif_Gun.jpg" );
						shop.no_gun = IMG_Load ( temp_filename );
					}
					SDL_BlitSurface ( shop.no_gun, NULL, screen, &buy_pic_location );
					sdl_flip_mutex();
					break;
				}

				if ( !server[game.server_id].gun[shop.gun_sel].gun_img[shop.rotate] )
					shop.rotate = 0; //Set back if you hit a premature end

				SDL_BlitSurface ( server[game.server_id].gun[shop.gun_sel].gun_img[shop.rotate], NULL, screen, &buy_pic_location );
				sdl_flip_mutex();
				break;
			case 2: //missiles
				if(!show_missile_buy) break;

				if ( shop.attempt_load_buy > -1 ) //load img if requested
				{
					shop.rotate = attempt_load_buy_safety = shop.attempt_load_buy;//make sure they are insync, and set safety

					if ( !server[game.server_id].missile[shop.missile_sel].missile_img[shop.attempt_load_buy] )
					{
						sprintf ( temp_filename, "server/%s/shop/missiles/pics/%s%d.jpg", server[game.server_id].servername, server[game.server_id].missile[shop.missile_sel].name, attempt_load_buy_safety + 1 );
						server[game.server_id].missile[shop.missile_sel].missile_img[attempt_load_buy_safety] = IMG_Load ( temp_filename );
					}

					if ( shop.attempt_load_buy == 15 || !server[game.server_id].missile[shop.missile_sel].missile_img[attempt_load_buy_safety] )
						shop.attempt_load_buy = -2;

					if ( attempt_load_buy_safety == shop.attempt_load_buy )
						shop.attempt_load_buy++;
				}

				if ( !server[game.server_id].missile[shop.missile_sel].missile_img[0] ) //if no starting index then display the "no ship" img
				{
					if ( !shop.no_missile ) //load the image if not already.
					{
						strcpy ( temp_filename, "graphics/nif/nif_Missile.jpg" );
						shop.no_missile = IMG_Load ( temp_filename );
					}
					SDL_BlitSurface ( shop.no_missile, NULL, screen, &buy_pic_location );
					sdl_flip_mutex();
					break;
				}

				if ( !server[game.server_id].missile[shop.missile_sel].missile_img[shop.rotate] )
					shop.rotate = 0; //Set back if you hit a premature end

				SDL_BlitSurface ( server[game.server_id].missile[shop.missile_sel].missile_img[shop.rotate], NULL, screen, &buy_pic_location );
				sdl_flip_mutex();
				break;
			case 3: //misc
				temp_misc = shop.misc_sel;

				while ( temp_misc>3 ) //reduce shop.misc_sel to 0-3 for use
					temp_misc -= 4;

				if ( shop.attempt_load_buy > -1 ) //load img if requested
				{
					shop.rotate = attempt_load_buy_safety = shop.attempt_load_buy;//make sure they are insync, and set safety

					if ( !shop.misc_img[temp_misc][shop.attempt_load_buy] )
					{
						switch ( temp_misc )
						{
							case 0:
								sprintf ( temp_filename, "graphics/shop/equipment/pics/Hull Booster%d.JPG", attempt_load_buy_safety + 1 );
								break;
							case 1:
								sprintf ( temp_filename, "graphics/shop/equipment/pics/Shielding%d.JPG", attempt_load_buy_safety + 1 );
								break;
							case 2:
								sprintf ( temp_filename, "graphics/shop/equipment/pics/Cargo Pod%d.JPG", attempt_load_buy_safety + 1 );
								break;
							case 3:
								sprintf ( temp_filename, "graphics/shop/equipment/pics/Jump Drive%d.JPG", attempt_load_buy_safety + 1 );
								break;
						}
						shop.misc_img[temp_misc][attempt_load_buy_safety] = IMG_Load ( temp_filename );
					}

					if ( shop.attempt_load_buy == 15 || !shop.misc_img[temp_misc][attempt_load_buy_safety] )
						shop.attempt_load_buy = -2;

					if ( attempt_load_buy_safety == shop.attempt_load_buy )
						shop.attempt_load_buy++;
				}

				if ( !shop.misc_img[temp_misc][0] ) //if no starting index then display the "no ship" img
				{
					if ( !shop.no_misc ) //load the image if not already.
					{
						strcpy ( temp_filename, "graphics/nif/nif_Miscpod.jpg" );
						shop.no_misc = IMG_Load ( temp_filename );
					}
					SDL_BlitSurface ( shop.no_misc, NULL, screen, &buy_pic_location );
					sdl_flip_mutex();
					break;
				}

				if ( !shop.misc_img[temp_misc][shop.rotate] )
					shop.rotate = 0; //Set back if you hit a premature end

				SDL_BlitSurface ( shop.misc_img[temp_misc][shop.rotate], NULL, screen, &buy_pic_location );
				sdl_flip_mutex();
				break;
		}

#ifdef _M_IX86 //if linux or windows
		Sleep ( 75 );
#else
		usleep ( 50000 );
#endif

		shop.rotate++;
		shop.rotate_sell++;
	}

	shop.thread = NULL;
	return 0; //if not in the shop, then scado
}


void shop_blank_current_item_sell()
{
	shop_draw_select_pod_box(0);
}

void shop_select_next_sell_item()
{
	int w;
	int max_w;
	int s_sel, s_id, s_t, s_k;

	s_sel = game.ship_sel;
	s_id = game.ship[s_sel].server_id;
	s_t = game.ship[s_sel].type;
	s_k = game.ship[s_sel].kind;

	switch ( shop.shop_sel )
	{
		case 1: // gun
			max_w = game.ship[s_sel].gun_ammount;

			for ( w=max_w-1;w>=0;w-- )
			{
				//checks
				if ( game.ship[s_sel].gun[w] < 0 ) continue;
				if ( game.ship[s_sel].gun_id[w] < 0 ) continue;
				if ( game.ship[s_sel].gun[w] >= GUN_MAX ) continue;
				if ( game.ship[s_sel].gun_id[w] >= MAX_SERVER ) continue;

				//guess we found one

				//unselect the old one
				shop_draw_select_pod_box(0);
				//shop_draw_sell_item_unselected ( shop.gun_pod_sel );

				//set the new one
				shop.gun_pod_sel = w;

				break;
			}

			break;
		case 2: // missile
			max_w = game.ship[s_sel].missile_ammount;

			for ( w=max_w-1;w>=0;w-- )
			{
				//checks
				if ( game.ship[s_sel].missile[w] < 0 ) continue;
				if ( game.ship[s_sel].missile_id[w] < 0 ) continue;
				if ( game.ship[s_sel].missile[w] >= MISSILE_MAX ) continue;
				if ( game.ship[s_sel].missile_id[w] >= MAX_SERVER ) continue;

				//guess we found one

				//unselect the old one
				shop_draw_select_pod_box(0);
				//shop_draw_sell_item_unselected ( shop.missile_pod_sel );

				//set the new one
				shop.missile_pod_sel = w;

				break;
			}

			break;
		case 3: // misc
			max_w = game.ship[s_sel].misc_ammount;

			for ( w=max_w-1;w>=0;w-- )
			{
				//checks
				if ( game.ship[s_sel].misc[w] < 0 ) continue;

				//guess we found one

				//unselect the old one
				shop_draw_select_pod_box(0);
				//shop_draw_sell_item_unselected ( shop.misc_pod_sel );

				//set the new one
				shop.misc_pod_sel = w;

				break;
			}

			break;
	}
}


int shop_can_be_set_to(int shop_type)
{
	int i;
	int &s = game.server_id;
	int &p = planet.last_planet;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			//it got any ships?
			if(at_home_planet())
			{
				for(i=0;i<SHIP_MAX;i++)
					if(server[s].planet[p].ship[i].have || game.has_plan[s][i])
						return 1;
			}
			else
			{
				for(i=0;i<SHIP_MAX;i++)
					if(server[s].planet[p].ship[i].have)
						return 1;
			}

			return 0;
			break;
		case 1: //guns
			//got any guns?
			for(i=0;i<GUN_MAX;i++)
				if(server[s].planet[p].gun[i])
					return 1;

			return 0;
			break;
		case 2: //missiles
			//got any missiles?
			for(i=0;i<MISSILE_MAX;i++)
				if(server[s].planet[p].missile[i])
					return 1;

			return 0;
			break;
		case 3: //misc
			return 1;
			break;
	}
}

void set_shop_type_down()
{
	int previous_kind_max;
	int temp_type;
	char temp_str[21];

	//if this isnt chassis then exit (only chassis uses upmost buttons)
	if ( shop.shop_sel ) return;

	//find the next type;
	temp_type = next_shop_type_down();
	if(temp_type != shop.ship_type_sel)
		shop.ship_type_sel = temp_type;
	else
		return;

	shop_show_type_left_right();

	shop_choose_available_ship_kind();
	draw_center_label ( shop.temp_backround, ship_name ( shop.ship_kind_sel, temp_str ), &shop.sel_left_label[1], 255, 255, 255 );

	shop_show_kind_left_right();

	shop_display_buy_ship_stats();

	shop.attempt_load_buy = 0;
	shop.rotate = 0; //reset index to start

	shop_show_buy_button();

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void set_shop_type_up()
{
	int previous_kind_max;
	char temp_str[21];
	int temp_type;

	if ( shop.shop_sel ) return; //if this isnt chassis then exit (only chassis uses upmost buttons)

	temp_type = next_shop_type_up();
	if(temp_type != shop.ship_type_sel)
		shop.ship_type_sel = temp_type;
	else
		return;

	shop_show_type_left_right();

	shop_choose_available_ship_kind();
	draw_center_label ( shop.temp_backround, ship_name ( shop.ship_kind_sel, temp_str ), &shop.sel_left_label[1], 255, 255, 255 );

	shop_show_kind_left_right();

	shop_display_buy_ship_stats();

	shop.attempt_load_buy = 0;
	shop.rotate = 0; //reset index to start

	shop_show_buy_button();

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void set_shop_kind_down()
{
	char temp_str[21];
	int i, show_buy_img;
	int temp_kind;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			temp_kind = next_shop_kind_down();
			if(temp_kind == shop.ship_kind_sel) return;
			shop.ship_kind_sel = temp_kind;

			shop_show_kind_left_right();

			//yayayaya
			shop_display_buy_ship_stats();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
		case 1: //guns
			temp_kind = next_shop_kind_down();
			if(temp_kind == shop.gun_sel) return;
			shop.gun_sel = temp_kind;

			shop_show_kind_left_right();

			//heyheyhey
			shop_display_buy_gun_stats();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
		case 2: //missiles
			temp_kind = next_shop_kind_down();
			if(temp_kind == shop.missile_sel) return;
			shop.missile_sel = temp_kind;

			shop_show_kind_left_right();

			//waaaahhh
			shop_display_buy_missile_stats();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
		case 3: //misc
			temp_kind = next_shop_kind_down();
			if(temp_kind == shop.misc_sel) return;
			shop.misc_sel = temp_kind;

			shop_show_kind_left_right();

			//ya
			shop_display_buy_misc();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
	}


	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void set_shop_kind_up()
{
	char temp_str[21];
	int i, show_buy_img;
	int temp_kind;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			temp_kind = next_shop_kind_up();
			if(temp_kind == shop.ship_kind_sel) return;
			shop.ship_kind_sel = temp_kind;

			shop_show_kind_left_right();

			//as it states
			shop_display_buy_ship_stats();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
		case 1: //guns
			temp_kind = next_shop_kind_up();
			if(temp_kind == shop.gun_sel) return;
			shop.gun_sel = temp_kind;

			shop_show_kind_left_right();

			//as it states
			shop_display_buy_gun_stats();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
		case 2: //missiles
			temp_kind = next_shop_kind_up();
			if(temp_kind == shop.missile_sel) return;
			shop.missile_sel = temp_kind;

			shop_show_kind_left_right();

			//as it states
			shop_display_buy_missile_stats();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
		case 3: //misc
			temp_kind = next_shop_kind_up();
			if(temp_kind == shop.misc_sel) return;
			shop.misc_sel = temp_kind;

			shop_show_kind_left_right();

			shop_display_buy_misc();

			shop.attempt_load_buy = 0;
			shop.rotate = 0; //reset index to start

			shop_show_buy_button();

			break;
	}

	SDL_BlitSurface ( shop.temp_backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void shop_display_buy_ship_stats()
{
	char temp_str[200];

	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].cost[shop.ship_kind_sel] ); //Set Purchase Ship info
	draw_right_label ( shop.temp_backround, temp_str, &shop.buy_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].exp[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].hull[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[1], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].shield[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[2], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].range[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[3], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].speed[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[4], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].evasion[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[5], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].cargo[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[6], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].gun_ammount[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[7], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].missile_ammount[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[8], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[game.server_id].ship[shop.ship_type_sel].misc_ammount[shop.ship_kind_sel] );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[9], 255, 255, 255 );

	draw_center_label ( shop.temp_backround, server[game.server_id].ship[shop.ship_type_sel].name, &shop.sel_left_label[0], 255, 255, 255 ); //Set Selection Names
	draw_center_label ( shop.temp_backround, ship_name ( shop.ship_kind_sel, temp_str ), &shop.sel_left_label[1], 255, 255, 255 );
}

void shop_display_buy_gun_stats()
{
	char temp_str[200];
	int i;
	int s, w, sh_exp;

	clear_display_box ( shop.temp_backround, & ( shop.left_display_box ) );

	s = game.server_id;
	w = shop.gun_sel;
	sh_exp = game.ship[game.ship_sel].exp;

	sprintf ( temp_str,"%d",server[s].gun[w].cost ); //Set Purchase Gun info and clear others
	draw_right_label ( shop.temp_backround, temp_str, &shop.buy_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d", gun_exp_requirement ( server[s].gun, w, sh_exp ) );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].accuracy );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[1], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].speed );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[2], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].damage );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[3], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].tech_level );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[4], 255, 255, 255 );
	draw_right_label ( shop.temp_backround, gun_type_name ( temp_str, server[s].gun[w].type ), &shop.stat_left_label[5], 255, 255, 255 );
	for ( i=6;i<10;i++ ) //clear the rest
		draw_right_label ( shop.temp_backround,"", &shop.stat_left_label[i], 255, 255, 255 );

	draw_center_label ( shop.temp_backround,"", &shop.sel_left_label[0], 255, 255, 255 );
	draw_center_label ( shop.temp_backround, server[s].gun[w].name, &shop.sel_left_label[1], 255, 255, 255 );

	add_display_box ( shop.temp_backround, & ( shop.left_display_box ), 0, gun_type_description ( temp_str, server[s].gun[w].type ) );
}

void shop_display_buy_missile_stats()
{
	char temp_str[200];
	int i;
	int s, w, sh_exp;

	clear_display_box ( shop.temp_backround, & ( shop.left_display_box ) );

	s = game.server_id;
	w = shop.missile_sel;
	sh_exp = game.ship[game.ship_sel].exp;

	sprintf ( temp_str,"%d",server[s].missile[w].cost ); //Set Purchase Gun info and clear others
	draw_right_label ( shop.temp_backround, temp_str, &shop.buy_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d", missile_exp_requirement ( server[s].missile, w, sh_exp ) );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].accuracy );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[1], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].speed );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[2], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].damage );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[3], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].tech_level );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[4], 255, 255, 255 );
	draw_right_label ( shop.temp_backround, missile_type_name ( temp_str, server[s].missile[w].type ), &shop.stat_left_label[5], 255, 255, 255 );
	for ( i=6;i<10;i++ ) //clear the rest
		draw_right_label ( shop.temp_backround,"", &shop.stat_left_label[i], 255, 255, 255 );

	draw_center_label ( shop.temp_backround,"", &shop.sel_left_label[0], 255, 255, 255 );
	draw_center_label ( shop.temp_backround, server[s].missile[w].name, &shop.sel_left_label[1], 255, 255, 255 );

	add_display_box ( shop.temp_backround, & ( shop.left_display_box ), 0, missile_type_description ( temp_str, server[s].missile[w].type ) );
}

void shop_display_buy_misc()
{
	char temp_str[200];
	int i;

	clear_display_box ( shop.temp_backround, & ( shop.left_display_box ) );

	switch ( shop.misc_sel )
	{
		case 0:
		case 4:
			draw_label ( shop.temp_backround,"Hull Increase ::", &shop.info_left_label[1], 255, 255, 255 );
			break;
		case 1:
		case 5:
			draw_label ( shop.temp_backround,"Shield Increase ::", &shop.info_left_label[1], 255, 255, 255 );
			break;
		case 2:
		case 6:
			draw_label ( shop.temp_backround,"Cargo Increase ::", &shop.info_left_label[1], 255, 255, 255 );
			break;
		case 3:
		case 7:
			draw_label ( shop.temp_backround,"Speed Increase ::", &shop.info_left_label[1], 255, 255, 255 );
			break;
	}

	sprintf ( temp_str,"%d",misc_pod_cost ( shop.misc_sel ) ); //Set Purchase Gun info and clear others
	draw_right_label ( shop.temp_backround, temp_str, &shop.buy_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d",misc_pod_exp ( shop.misc_sel ) + game.ship[game.ship_sel].exp );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",misc_pod_value ( shop.misc_sel ) );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_left_label[1], 255, 255, 255 );
	for ( i=2;i<10;i++ ) //clear the rest
		draw_right_label ( shop.temp_backround,"", &shop.stat_left_label[i], 255, 255, 255 );

	draw_center_label ( shop.temp_backround, misc_pod_name ( shop.misc_sel, temp_str ), &shop.sel_left_label[1], 255, 255, 255 );
}

void shop_display_sell_ship()
{
	char temp_str[200];

	sprintf ( temp_str,"%.0lf", ( game.ship[game.ship_sel].cost * 0.75 ) + ship_equipment_worth ( game.ship_sel ) ); //Set Purchase Ship info
	draw_right_label ( shop.temp_backround, temp_str, &shop.sell_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].exp );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].hull );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[1], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].shield );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[2], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].range );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[3], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].speed );
    //*NEW evasion labels (only visual)
    //zep seeker, ara fighter, nis fighter, tal fighter, ner fighter, endy seeker
    if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 0 ||
        game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 1 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 1 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 1 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 1 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 0 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"45" ); //fake amount
    }
    //zep fighter, ara carr, nis carr, tal carr, ner carr, ner hunter, endy fighter, helios seeker (is 40 eva anyways...)
    else if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 1 ||
        game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 1 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"40" ); //fake amount
    }
    //ara seeker, nis seeker, tal seeker, ner seeker
    else if ( game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 0 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 0 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 0 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 0 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"50" ); //fake amount
    }
    //zep carr, ara hunter, nis hunter, tal hunter, endy carr(is 35eva anyways), helios fighter, ery seeker
    else if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 1 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 0 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"35" ); //fake amount
    }
    //zep hunter, ner att, endy hunter, helios hunter, ery fighter
    else if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 1 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"30" ); //fake amount
    }
    //ara fr8, nis fr8, tal fr8, ner fr8, endy fr8, hel carr, hel att, ery hunter, and seeker, and fighter
    else if ( game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 0 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 1 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"25" ); //fake amount
    }
    //zep fr8, ata att, nis att, tal att, ner dess, endy att, ery carr, ery fr8
    else if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 4 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"20" ); //fake amount
    }
    //ara dess, nis dess, tal dess, ner behe, endy dess, hel fr8, hel dessy, ery att, and carr, and hunter, and att
    else if ( game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 4 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 4 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 2 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 3 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 5 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"15" ); //fake amount
    }
    //zep dessy, ara behe, nis behe, tal behe, endy behe, hel behe, ery dess, ery behe, and dess (10 eva anyways), and behe
    else if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 1 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 2 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 3 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 5 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 6 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 6 ||
        game.ship[game.ship_sel].type == 7 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 7 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"10" ); //fake amount
    }
    //zep att, zep behe, and fr8
    else if ( game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 5 ||
        game.ship[game.ship_sel].type == 0 && game.ship[game.ship_sel].kind == 7 ||
        game.ship[game.ship_sel].type == 8 && game.ship[game.ship_sel].kind == 4 )
    {
    draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"5" ); //fake amount
    }
    else
    { //*NEW end evasion (visual only)
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].evasion ); //real amount
    }
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[5], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].cargo );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[6], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].gun_ammount );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[7], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].missile_ammount );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[8], 255, 255, 255 );
	sprintf ( temp_str,"%d",game.ship[game.ship_sel].misc_ammount );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[9], 255, 255, 255 );

	draw_center_label ( shop.temp_backround, server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].name, &shop.sel_right_label[0], 255, 255, 255 ); //Set Selection Names
	draw_center_label ( shop.temp_backround, ship_name ( game.ship[game.ship_sel].kind, temp_str ), &shop.sel_right_label[1], 255, 255, 255 );
}

void shop_display_sell_item()
{
	char temp_str[10][200];
	char cost_str[200];
	char name_str[200];
	char disp_str[500];
	int sh, sh_exp;
	int sh_w = 0;
	int damage_boost, speed_boost, accuracy_boost;
	int i;
	int s = -1, w = -1;

	if(shop.shop_sel == 0) return;

	//clear out
	for(i=0;i<10;i++) temp_str[i][0] = 0;
	cost_str[0] = 0;
	name_str[0] = 0;
	disp_str[0] = 0;
	sh = game.ship_sel;
	sh_exp = game.ship[sh].exp;

	//draw the red
	shop_draw_select_pod_box(1);

	if(shop.hanger_pod_selected)
	{
		switch(shop.shop_sel)
		{
		case 1:
			sh_w = shop.gun_hanger_sel + (shop.gun_hanger_depth * 16);
			s = game.hanger_gun[sh_w].w_id;
			w = game.hanger_gun[sh_w].w;
			damage_boost = game.hanger_gun[sh_w].damage_boost;
			speed_boost = game.hanger_gun[sh_w].speed_boost;
			accuracy_boost = game.hanger_gun[sh_w].accuracy_boost;
			break;
		case 2:
			sh_w = shop.missile_hanger_sel + (shop.missile_hanger_depth * 16);
			s = game.hanger_missile[sh_w].w_id;
			w = game.hanger_missile[sh_w].w;
			damage_boost = game.hanger_missile[sh_w].damage_boost;
			speed_boost = game.hanger_missile[sh_w].speed_boost;
			accuracy_boost = game.hanger_missile[sh_w].accuracy_boost;
			break;
		case 3:
			sh_w = shop.misc_pod_sel;
			w = game.ship[sh].misc[sh_w];
			break;
		}
	}
	else
	{
		switch(shop.shop_sel)
		{
		case 1:
			sh_w = shop.gun_pod_sel;
			s = game.ship[sh].gun_id[sh_w];
			w = game.ship[sh].gun[sh_w];
			damage_boost = game.ship[sh].gun_damage_boost[sh_w];
			speed_boost = game.ship[sh].gun_speed_boost[sh_w];
			accuracy_boost = game.ship[sh].gun_accuracy_boost[sh_w];
			break;
		case 2:
			sh_w = shop.missile_pod_sel;
			s = game.ship[sh].missile_id[sh_w];
			w = game.ship[sh].missile[sh_w];
			damage_boost = game.ship[sh].missile_damage_boost[sh_w];
			speed_boost = game.ship[sh].missile_speed_boost[sh_w];
			accuracy_boost = game.ship[sh].missile_accuracy_boost[sh_w];
			break;
		case 3:
			sh_w = shop.misc_pod_sel;
			w = game.ship[sh].misc[sh_w];
			break;
		}
	}

	//clear out
	{
		draw_right_label ( shop.temp_backround,"", &shop.sell_money_label, 255, 255, 255 );
		SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] );

		draw_center_label ( shop.temp_backround,"", &shop.sel_right_label[0], 255, 255, 255 );
		draw_center_label ( shop.temp_backround,"", &shop.sel_right_label[1], 255, 255, 255 );
		for ( i=0;i<10;i++ ) draw_right_label ( shop.temp_backround,"", &shop.stat_right_label[i], 255, 255, 255 );

		clear_display_box ( shop.temp_backround, & ( shop.right_display_box ) );

		if(shop.shop_sel == 3) draw_label ( shop.temp_backround,"Attribute Increase ::", &shop.info_right_label[1], 255, 255, 255 );
	}

	//no good?
	if(w < 0) return;

	switch(shop.shop_sel)
	{
	case 0:
		break;
	case 1:
		strcpy(name_str, server[s].gun[w].name);
		gun_type_description ( disp_str, server[s].gun[w].type );
		sprintf ( cost_str,"%.0lf",server[s].gun[w].cost * .75 ); //Set Purchase Gun info and clear others
		sprintf ( temp_str[0],"%d", gun_exp_requirement ( server[s].gun, w, sh_exp ) );
		sprintf ( temp_str[1],"%d",server[s].gun[w].accuracy + accuracy_boost );
		sprintf ( temp_str[2],"%d",server[s].gun[w].speed + speed_boost );
		sprintf ( temp_str[3],"%d",server[s].gun[w].damage + damage_boost );
		sprintf ( temp_str[4],"%d",server[s].gun[w].tech_level );
		gun_type_name ( temp_str[5], server[s].gun[w].type );
		break;
	case 2:
		strcpy(name_str, server[s].missile[w].name);
		gun_type_description ( disp_str, server[s].missile[w].type );
		sprintf ( cost_str,"%.0lf",server[s].missile[w].cost * .75 ); //Set Purchase Gun info and clear others
		sprintf ( temp_str[0],"%d", missile_exp_requirement ( server[s].missile, w, sh_exp ) );
		sprintf ( temp_str[1],"%d",server[s].missile[w].accuracy + accuracy_boost );
		sprintf ( temp_str[2],"%d",server[s].missile[w].speed + speed_boost );
		sprintf ( temp_str[3],"%d",server[s].missile[w].damage + damage_boost );
		sprintf ( temp_str[4],"%d",server[s].missile[w].tech_level );
		missile_type_name ( temp_str[5], server[s].missile[w].type );
		break;
	case 3:
		switch(w)
		{
		case MK1_HULL:
		case MK2_HULL:
		case MK3_HULL:
			draw_label ( shop.temp_backround,"Hull Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		case MK1_SHIELD:
		case MK2_SHIELD:
		case MK3_SHIELD:
			draw_label ( shop.temp_backround,"Shield Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		case MK1_CARGO:
		case MK2_CARGO:
		case MK3_CARGO:
			draw_label ( shop.temp_backround,"Cargo Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		case MK1_JUMP:
		case MK2_JUMP:
		case MK3_JUMP:
			draw_label ( shop.temp_backround,"Speed Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		}

		misc_pod_name ( w, name_str );
		sprintf ( cost_str,"%.0lf",misc_pod_cost ( w ) * .75 );
		sprintf ( temp_str[0],"%d",misc_pod_exp ( w ) + sh_exp );
		sprintf ( temp_str[1],"%d",misc_pod_value ( w ) );
		break;
	}

	//draw out
	draw_center_label ( shop.temp_backround, name_str, &shop.sel_right_label[1], 255, 255, 255 );
	for(i=0;i<10;i++) draw_right_label ( shop.temp_backround, temp_str[i], &shop.stat_right_label[i], 255, 255, 255 );
	add_display_box ( shop.temp_backround, & ( shop.right_display_box ), 0, disp_str );

	//sell cost / button
	draw_right_label ( shop.temp_backround, cost_str, &shop.sell_money_label, 255, 255, 255 );
	SDL_BlitSurface ( shop.sell_img, NULL, shop.temp_backround, &shop.button[2] );
}

/*
void shop_display_sell_gun()
{
	char temp_str[200];
	int i;
	int s, w, sh_exp;
	int sh, sh_w;
	int damage_boost, speed_boost, accuracy_boost;

	sh = game.ship_sel;
	sh_w = shop.gun_pod_sel;

	//draw the red
	shop_draw_select_pod_box(1);
	//shop_draw_sell_item_selected ( sh_w );

	clear_display_box ( shop.temp_backround, & ( shop.right_display_box ) );

	s = game.ship[sh].gun_id[sh_w];
	w = game.ship[sh].gun[sh_w];
	damage_boost = game.ship[sh].gun_damage_boost[sh_w];
	speed_boost = game.ship[sh].gun_speed_boost[sh_w];
	accuracy_boost = game.ship[sh].gun_accuracy_boost[sh_w];
	sh_exp = game.ship[sh].exp;

	if ( s<0 || w<0 ) //clear out?
	{
		draw_right_label ( shop.temp_backround, "", &shop.sell_money_label, 255, 255, 255 );
		SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] );
		for ( i=0;i<10;i++ )
			draw_right_label ( shop.temp_backround, "", &shop.stat_right_label[i], 255, 255, 255 );
		draw_center_label ( shop.temp_backround, "", &shop.sel_right_label[1], 255, 255, 255 );
		return;
	}

	sprintf ( temp_str,"%.0lf",server[s].gun[w].cost * .75 ); //Set Purchase Gun info and clear others
	draw_right_label ( shop.temp_backround, temp_str, &shop.sell_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d", gun_exp_requirement ( server[s].gun, w, sh_exp ) );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].accuracy + accuracy_boost );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[1], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].speed + speed_boost );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[2], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].damage + damage_boost );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[3], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].gun[w].tech_level );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	draw_right_label ( shop.temp_backround, gun_type_name ( temp_str, server[s].gun[w].type ), &shop.stat_right_label[5], 255, 255, 255 );
	for ( i=6;i<10;i++ ) //clear the rest
		draw_right_label ( shop.temp_backround, "", &shop.stat_right_label[i], 255, 255, 255 );

	draw_center_label ( shop.temp_backround, "", &shop.sel_right_label[0], 255, 255, 255 );
	draw_center_label ( shop.temp_backround, server[s].gun[w].name, &shop.sel_right_label[1], 255, 255, 255 );

	add_display_box ( shop.temp_backround, & ( shop.right_display_box ), 0, gun_type_description ( temp_str, server[s].gun[w].type ) );
}

void shop_display_sell_missile()
{
	char temp_str[200];
	int i;
	int s, w, sh_exp;
	int sh, sh_w;
	int damage_boost, speed_boost, accuracy_boost;

	sh = game.ship_sel;
	sh_w = shop.missile_pod_sel;

	//draw the red
	shop_draw_select_pod_box(1);
	//shop_draw_sell_item_selected ( sh_w );

	clear_display_box ( shop.temp_backround, & ( shop.right_display_box ) );

	s = game.ship[sh].missile_id[sh_w];
	w = game.ship[sh].missile[sh_w];
	damage_boost = game.ship[sh].missile_damage_boost[sh_w];
	speed_boost = game.ship[sh].missile_speed_boost[sh_w];
	accuracy_boost = game.ship[sh].missile_accuracy_boost[sh_w];
	sh_exp = game.ship[sh].exp;

	if ( s<0 || w<0 ) //clear out?
	{
		draw_right_label ( shop.temp_backround, "", &shop.sell_money_label, 255, 255, 255 );
		SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] );
		for ( i=0;i<10;i++ )
			draw_right_label ( shop.temp_backround, "", &shop.stat_right_label[i], 255, 255, 255 );
		draw_center_label ( shop.temp_backround, "", &shop.sel_right_label[1], 255, 255, 255 );
		return;
	}

	sprintf ( temp_str,"%.0lf",server[s].missile[w].cost * .75 ); //Set Purchase Gun info and clear others
	draw_right_label ( shop.temp_backround, temp_str, &shop.sell_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d", missile_exp_requirement ( server[s].missile, w, sh_exp ) );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].accuracy + accuracy_boost );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[1], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].speed + speed_boost );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[2], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].damage + damage_boost );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[3], 255, 255, 255 );
	sprintf ( temp_str,"%d",server[s].missile[w].tech_level );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[4], 255, 255, 255 );
	draw_right_label ( shop.temp_backround, missile_type_name ( temp_str, server[s].missile[w].type ), &shop.stat_right_label[5], 255, 255, 255 );
	for ( i=6;i<10;i++ ) //clear the rest
		draw_right_label ( shop.temp_backround, "", &shop.stat_right_label[i], 255, 255, 255 );

	draw_center_label ( shop.temp_backround, "", &shop.sel_right_label[0], 255, 255, 255 );
	draw_center_label ( shop.temp_backround, server[s].missile[w].name, &shop.sel_right_label[1], 255, 255, 255 );

	add_display_box ( shop.temp_backround, & ( shop.right_display_box ), 0, missile_type_description ( temp_str, server[s].missile[w].type ) );
}

void shop_display_sell_misc()
{
	char temp_str[200];
	int i;
	int w;

	//draw the red
	shop_draw_select_pod_box(1);
	//shop_draw_sell_item_selected ( shop.misc_pod_sel );

	w = game.ship[game.ship_sel].misc[shop.misc_pod_sel];

	clear_display_box ( shop.temp_backround, & ( shop.right_display_box ) );

	if ( w<0 ) //clear out?
	{
		draw_right_label ( shop.temp_backround, "", &shop.sell_money_label, 255, 255, 255 );
		SDL_BlitSurface ( shop.sell_blank, NULL, shop.temp_backround, &shop.button[2] );
		for ( i=0;i<10;i++ )
			draw_right_label ( shop.temp_backround, "", &shop.stat_right_label[i], 255, 255, 255 );
		draw_center_label ( shop.temp_backround, "", &shop.sel_right_label[1], 255, 255, 255 );
		return;
	}

	switch ( w )
	{
		case 0:
		case 4:
			draw_label ( shop.temp_backround, "Hull Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		case 1:
		case 5:
			draw_label ( shop.temp_backround, "Shield Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		case 2:
		case 6:
			draw_label ( shop.temp_backround, "Cargo Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
		case 3:
		case 7:
			draw_label ( shop.temp_backround, "Speed Increase ::", &shop.info_right_label[1], 255, 255, 255 );
			break;
	}

	sprintf ( temp_str,"%.0lf",misc_pod_cost ( game.ship[game.ship_sel].misc[shop.misc_pod_sel] ) * .75 ); //Set Purchase Gun info and clear others
	draw_right_label ( shop.temp_backround, temp_str, &shop.sell_money_label, 255, 255, 255 );
	sprintf ( temp_str,"%d",misc_pod_exp ( game.ship[game.ship_sel].misc[shop.misc_pod_sel] ) + game.ship[game.ship_sel].exp );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[0], 255, 255, 255 );
	sprintf ( temp_str,"%d",misc_pod_value ( game.ship[game.ship_sel].misc[shop.misc_pod_sel] ) );
	draw_right_label ( shop.temp_backround, temp_str, &shop.stat_right_label[1], 255, 255, 255 );
	for ( i=2;i<10;i++ ) //clear the rest
		draw_right_label ( shop.temp_backround, "", &shop.stat_right_label[i], 255, 255, 255 );

	draw_center_label ( shop.temp_backround, "", &shop.sel_right_label[0], 255, 255, 255 );
	draw_center_label ( shop.temp_backround, misc_pod_name ( game.ship[game.ship_sel].misc[shop.misc_pod_sel], temp_str ), &shop.sel_right_label[1], 255, 255, 255 );
}
*/

void shop_display_sell_ship_stat_names()
{
	clear_display_box ( shop.temp_backround, & ( shop.right_display_box ) );

	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_right_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"Hull ::", &shop.info_right_label[1], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Shields ::", &shop.info_right_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Jump Range ::", &shop.info_right_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Speed ::", &shop.info_right_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Evasion ::", &shop.info_right_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Cargo ::", &shop.info_right_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Max Guns ::", &shop.info_right_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Max Missles ::", &shop.info_right_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Max Misc Pods ::", &shop.info_right_label[9], 255, 255, 255 );
}

void shop_display_sell_gun_stat_names()
{
	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_right_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"Accuracy ::", &shop.info_right_label[1], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Speed ::", &shop.info_right_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Damage ::", &shop.info_right_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Tech Level ::", &shop.info_right_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Weapon Type ::", &shop.info_right_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Description ::", &shop.info_right_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[9], 255, 255, 255 );
}

void shop_display_sell_missile_stat_names()
{
	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_right_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"Accuracy ::", &shop.info_right_label[1], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Speed ::", &shop.info_right_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Damage ::", &shop.info_right_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Tech Level ::", &shop.info_right_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Weapon Type ::", &shop.info_right_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Description ::", &shop.info_right_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[9], 255, 255, 255 );
}

void shop_display_sell_misc_stat_names()
{
	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_right_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"", &shop.info_right_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_right_label[9], 255, 255, 255 );
}

void shop_display_buy_ship_stat_names()
{
	clear_display_box ( shop.temp_backround, & ( shop.left_display_box ) );

	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_left_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"Hull ::", &shop.info_left_label[1], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Shields ::", &shop.info_left_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Jump Range ::", &shop.info_left_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Speed ::", &shop.info_left_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Evasion ::", &shop.info_left_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Cargo ::", &shop.info_left_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Max Guns ::", &shop.info_left_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Max Missles ::", &shop.info_left_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Max Misc Pods ::", &shop.info_left_label[9], 255, 255, 255 );
}

void shop_display_buy_gun_stat_names()
{
	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_left_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"Accuracy ::", &shop.info_left_label[1], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Speed ::", &shop.info_left_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Damage ::", &shop.info_left_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Tech Level ::", &shop.info_left_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Weapon Type ::", &shop.info_left_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Description ::", &shop.info_left_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[9], 255, 255, 255 );
}

void shop_display_buy_missile_stat_names()
{
	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_left_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"Accuracy ::", &shop.info_left_label[1], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Speed ::", &shop.info_left_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Damage ::", &shop.info_left_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Tech Level ::", &shop.info_left_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Weapon Type ::", &shop.info_left_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"Description ::", &shop.info_left_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[9], 255, 255, 255 );
}

void shop_display_buy_misc_stat_names()
{
	draw_label ( shop.temp_backround,"Exp Needed ::", &shop.info_left_label[0], 255, 255, 255 ); //Set obvious texts
	draw_label ( shop.temp_backround,"", &shop.info_left_label[2], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[3], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[4], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[5], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[6], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[7], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[8], 255, 255, 255 );
	draw_label ( shop.temp_backround,"", &shop.info_left_label[9], 255, 255, 255 );
}

void shop_display_hanger_weapons()
{
	int i;

	//show
	if(shop.shop_sel == 1 || shop.shop_sel == 2)
	{
		int current_depth = 0;
		int current_shift;

		if(shop.shop_sel == 1) current_depth = shop.gun_hanger_depth;
		if(shop.shop_sel == 2) current_depth = shop.missile_hanger_depth;
		current_shift = current_depth * 16;

		draw_label ( shop.temp_backround,"Weapon Hanger ::", &shop.hanger_label, 255, 255, 255 );
		draw_label ( shop.temp_backround,"Store / Equip Weapon", &shop.store_equip_label, 255, 0, 0 );

		if(current_depth > 0) SDL_BlitSurface ( shop.sel_left, NULL, shop.temp_backround, &shop.button[B_SHOP_HANGER_LEFT] );
		else SDL_FillRect ( shop.temp_backround, &shop.button[B_SHOP_HANGER_LEFT], SDL_MapRGB ( shop.temp_backround->format, 0, 0, 0 ) );

		if(current_depth < 2) SDL_BlitSurface ( shop.sel_right, NULL, shop.temp_backround, &shop.button[B_SHOP_HANGER_RIGHT] );
		else SDL_FillRect ( shop.temp_backround, &shop.button[B_SHOP_HANGER_RIGHT], SDL_MapRGB ( shop.temp_backround->format, 0, 0, 0 ) );

		for(i=0;i<16;i++) shop_display_hanger_weapon_pod(i);
	}
	else
	{
		//hide
		draw_label ( shop.temp_backround,"", &shop.hanger_label, 255, 255, 255 );
		draw_label ( shop.temp_backround,"", &shop.store_equip_label, 255, 0, 0 );

		SDL_FillRect ( shop.temp_backround, &shop.button[B_SHOP_HANGER_LEFT], SDL_MapRGB ( shop.temp_backround->format, 0, 0, 0 ) );
		SDL_FillRect ( shop.temp_backround, &shop.button[B_SHOP_HANGER_RIGHT], SDL_MapRGB ( shop.temp_backround->format, 0, 0, 0 ) );

		for(i=0;i<16;i++) SDL_FillRect ( shop.temp_backround, &shop.button[i + B_SHOP_HANGER_WEAPON_POD], SDL_MapRGB ( shop.temp_backround->format, 0, 0, 0 ) );
	}
}

void shop_display_hanger_weapon_pod(int i)
{
	SDL_Rect *rend_loc;
	int w, w_id;
	int current_shift;

	if(i<0) return;
	if(i>=16) return;

	rend_loc = &shop.button[i + B_SHOP_HANGER_WEAPON_POD];

	switch(shop.shop_sel)
	{
	default: return;
	case 1:
		current_shift = shop.gun_hanger_depth * 16;
		w = game.hanger_gun[i + current_shift].w;
		w_id = game.hanger_gun[i + current_shift].w_id;

		if(w > -1 && w_id > -1)
		{
			if (load_gun_pod_img_specific ( w_id, w ))
				SDL_BlitSurface ( server[w_id].gun[w].gun_pod_img, NULL, shop.temp_backround, rend_loc );
			else
				SDL_BlitSurface ( game.nif_image.no_gun_pod, NULL, shop.temp_backround, rend_loc );
		}
		else
			SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, rend_loc );
		break;
	case 2:
		current_shift = shop.missile_hanger_depth * 16;
		w = game.hanger_missile[i + current_shift].w;
		w_id = game.hanger_missile[i + current_shift].w_id;

		if(w > -1 && w_id > -1)
		{
			if (load_missile_pod_img_specific ( w_id, w ))
				SDL_BlitSurface ( server[w_id].missile[w].missile_pod_img, NULL, shop.temp_backround, rend_loc );
			else
				SDL_BlitSurface ( game.nif_image.no_missile_pod, NULL, shop.temp_backround, rend_loc );
		}
		else
			SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, rend_loc );
		break;
	}
}

void shop_display_sell_guns()
{
	int i;

	for ( i=0;i<game.ship[game.ship_sel].gun_ammount;i++ ) //show those gun pods
		if ( game.ship[game.ship_sel].gun[i] > -1 && game.ship[game.ship_sel].gun[i] < GUN_MAX && game.ship[game.ship_sel].gun_id[i] > -1 && game.ship[game.ship_sel].gun_id[i] < MAX_SERVER )
		{
			if ( !load_gun_pod_img ( i ) ) //still not loaded... wah
				SDL_BlitSurface ( game.nif_image.no_gun_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
			else //or is it?
				SDL_BlitSurface ( server[game.ship[game.ship_sel].gun_id[i]].gun[game.ship[game.ship_sel].gun[i]].gun_pod_img, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );

		}
		else
		{
			SDL_BlitSurface ( shop.empty_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
		}

	for ( ;i<16;i++ ) //blank out remaining spots
		SDL_BlitSurface ( shop.blank_pod, NULL, shop.temp_backround, &shop.button[i + B_SHOP_MAX_BUTTONS] );
}

//void shop_draw_sell_item_selected ( int i )
//{
//	if ( i<0 ) return;
//	if ( i>=16 ) return;
//
//	rectangleRGBA ( shop.temp_backround, shop.button[i + B_SHOP_MAX_BUTTONS].x - 1, shop.button[i + B_SHOP_MAX_BUTTONS].y - 1, shop.button[i + B_SHOP_MAX_BUTTONS].x + shop.button[i + B_SHOP_MAX_BUTTONS].w + 1, shop.button[i + B_SHOP_MAX_BUTTONS].y + shop.button[i + B_SHOP_MAX_BUTTONS].h + 1, 255, 0 , 0, 255 );
//}
//
//void shop_draw_sell_item_unselected ( int i )
//{
//	if ( i<0 ) return;
//	if ( i>=16 ) return;
//
//	rectangleRGBA ( shop.temp_backround, shop.button[i + B_SHOP_MAX_BUTTONS].x - 1, shop.button[i + B_SHOP_MAX_BUTTONS].y - 1, shop.button[i + B_SHOP_MAX_BUTTONS].x + shop.button[i + B_SHOP_MAX_BUTTONS].w + 1, shop.button[i + B_SHOP_MAX_BUTTONS].y + shop.button[i + B_SHOP_MAX_BUTTONS].h + 1, 0, 0 , 0, 255 );
//}

int shop_selected_pod_is_valid()
{
	int cur_sel = 0;
	int max_available = 0;
	int sh;

	if(shop.hanger_pod_selected) return 1;

	sh = game.ship_sel;

	//have to have a ship obviously
	if(game.ship[sh].server_id < 0) return 0;
	if(game.ship[sh].type < 0) return 0;
	if(game.ship[sh].kind < 0) return 0;

	//collect particulars
	switch ( shop.shop_sel )
	{
	default: return 0;
	case 0: return 0;
	case 1:
		max_available = game.ship[sh].gun_ammount;
		cur_sel = shop.gun_pod_sel;
		break;
	case 2:
		max_available = game.ship[sh].missile_ammount;
		cur_sel = shop.missile_pod_sel;
		break;
	case 3:
		max_available = game.ship[sh].misc_ammount;
		cur_sel = shop.misc_pod_sel;
		break;
	}

	return (cur_sel < max_available);
}

void shop_clear_all_pod_box()
{
	int bi;

	for(bi=B_SHOP_WEAPON_POD;bi<32+B_SHOP_WEAPON_POD;bi++)
	{
		int x1, x2;
		int y1, y2;

		x1 = shop.button[bi].x - 1;
		y1 = shop.button[bi].y - 1;
		x2 = shop.button[bi].x + shop.button[bi].w + 1;
		y2 = shop.button[bi].y + shop.button[bi].h + 1;

		rectangleRGBA( shop.temp_backround, x1, y1, x2, y2, 0, 0, 0, 255);
	}
}

void shop_draw_select_pod_box(int show)
{
	int bi = 0;
	int x1, x2;
	int y1, y2;

	if(shop.hanger_pod_selected)
	{
		if(shop.shop_sel == 1) bi = shop.gun_hanger_sel + B_SHOP_HANGER_WEAPON_POD;
		if(shop.shop_sel == 2) bi = shop.missile_hanger_sel + B_SHOP_HANGER_WEAPON_POD;
	}
	else
	{
		if(shop.shop_sel == 1) bi = shop.gun_pod_sel + B_SHOP_WEAPON_POD;
		if(shop.shop_sel == 2) bi = shop.missile_pod_sel + B_SHOP_WEAPON_POD;
	}

	if(shop.shop_sel == 3) bi = shop.misc_pod_sel + B_SHOP_WEAPON_POD;

	x1 = shop.button[bi].x - 1;
	y1 = shop.button[bi].y - 1;
	x2 = shop.button[bi].x + shop.button[bi].w + 1;
	y2 = shop.button[bi].y + shop.button[bi].h + 1;

	if(show && shop_selected_pod_is_valid())
		rectangleRGBA( shop.temp_backround, x1, y1, x2, y2, 255, 0, 0, 255);
	else if(!show)
		rectangleRGBA( shop.temp_backround, x1, y1, x2, y2, 0, 0, 0, 255);
}

int ship_total_good_ammount ( int ship_number )
{
	int i, temp_int = 0;

	for ( i=0;i<10;i++ )
	{
		temp_int += game.ship[ship_number].good_ammount[i];
		temp_int += game.ship[ship_number].contra_ammount[i];
	}

	return temp_int;
}


int next_shop_type_down()
{
	int i;
	int s, p;

	//only for the ship type
	if ( shop.shop_sel ) return shop.ship_type_sel;

	s = game.server_id;
	p = planet.last_planet;

	//begin
	if(at_home_planet())
	{
		for(i = shop.ship_type_sel - 1; i>=0; i--)
			if(server[s].planet[p].ship[i].have || game.has_plan[s][i])
				return i;
	}
	else
	{
		for(i = shop.ship_type_sel - 1; i>=0; i--)
			if(server[s].planet[p].ship[i].have)
				return i;
	}

	//none found
	return shop.ship_type_sel;
}

int next_shop_type_up()
{
	int i;
	int s, p;

	//only for the ship type
	if ( shop.shop_sel ) return shop.ship_type_sel;

	s = game.server_id;
	p = planet.last_planet;

	//begin
	if(at_home_planet())
	{
		for(i = shop.ship_type_sel + 1; i<SHIP_MAX; i++)
			if(server[s].planet[p].ship[i].have || game.has_plan[s][i])
				return i;
	}
	else
	{
		for(i = shop.ship_type_sel + 1; i<SHIP_MAX; i++)
			if(server[s].planet[p].ship[i].have)
				return i;
	}

	//none found
	return shop.ship_type_sel;
}

int next_shop_kind_down()
{
	int i;
	int s, p;

	s = game.server_id;
	p = planet.last_planet;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			for(i=shop.ship_kind_sel-1;i>=0;i--)
				if(shop_ship_available_for_purchase(shop.ship_type_sel, i))
					return i;

			//not found
			return shop.ship_kind_sel;

			break;
		case 1: //guns
			for(i=shop.gun_sel-1;i>=0;i--)
				if(server[s].planet[p].gun[i])
					return i;

			return shop.gun_sel;

			break;
		case 2: //missiles
			for(i=shop.missile_sel-1;i>=0;i--)
				if(server[s].planet[p].missile[i])
					return i;

			return shop.missile_sel;

			break;
		case 3: //misc
			if ( shop.misc_sel <= 0 ) return shop.misc_sel;

			return shop.misc_sel-1;
			break;
	}
}

int next_shop_kind_up()
{
	int i;
	int s, p;

	s = game.server_id;
	p = planet.last_planet;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			for(i=shop.ship_kind_sel+1;i<=7;i++)
				if(shop_ship_available_for_purchase(shop.ship_type_sel, i))
					return i;

			//not found
			return shop.ship_kind_sel;

			break;
		case 1: //guns
			for(i=shop.gun_sel+1;i<GUN_MAX;i++)
				if(server[s].planet[p].gun[i])
					return i;

			return shop.gun_sel;

			break;
		case 2: //missiles
			for(i=shop.missile_sel+1;i<MISSILE_MAX;i++)
				if(server[s].planet[p].missile[i])
					return i;

			return shop.missile_sel;

			break;
		case 3: //misc
			if ( shop.misc_sel >= 7 ) return shop.misc_sel;
			//if ( shop.misc_sel >= MAX_MISC_TYPES ) return shop.misc_sel;

			return shop.misc_sel+1;
			break;
	}
}

void shop_show_buy_button()
{
	int show_it, got_space;
	int i, s;
	int sh, sh_id, sh_t, sh_k, max;

	s = game.server_id;
	sh = game.ship_sel;
	sh_id = game.ship[sh].server_id;
	sh_t = game.ship[sh].type;
	sh_k = game.ship[sh].kind;

	show_it = 0;
	got_space = 0;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			if(game.money < server[s].ship[shop.ship_type_sel].cost[shop.ship_kind_sel]) break;
			if(game.exp < server[s].ship[shop.ship_type_sel].exp[shop.ship_kind_sel]) break;
			if(sh_id > -1) break;

			show_it = 1;

			break;
		case 1: //guns
			if(sh_id > -1 && sh_t > -1 && sh_k > -1)
			{
				max = server[sh_id].ship[sh_t].gun_ammount[sh_k];
				for ( i=0;i<max;i++ )
					if ( game.ship[sh].gun_id[i] < 0 || game.ship[sh].gun[i] < 0 ) //check for emptyness
				{
					got_space = 1;
					break;
				}
			}

			if(!got_space) break;
			if(game.money < server[s].gun[shop.gun_sel].cost) break;
			if(game.exp < gun_exp_requirement(server[s].gun, shop.gun_sel, server[sh_id].ship[sh_t].exp[sh_k])) break;

            //*NEW check required plans to buy guns, hide buy button if doesn't met x))
            if(server[s].gun[shop.gun_sel].cost == 2000 || server[s].gun[shop.gun_sel].cost == 4000 || server[s].gun[shop.gun_sel].cost == 10000) { //check gun
            if(!game.has_plan[s][1]) //check plan
            break; //hide buy button
            }

            if(server[s].gun[shop.gun_sel].cost == 8000) { //check gun
            if(!game.has_plan[s][3]) //check plan
            break; //hide buy button
            }

            if(server[s].gun[shop.gun_sel].cost == 15000) { //check gun
            if(!game.has_plan[s][4]) //check plan
            break; //hide buy button
            }

            if(server[s].gun[shop.gun_sel].cost == 28000) { //check gun
            if(!game.has_plan[s][5]) //check plan
            break; //hide buy button
            }

            if(server[s].gun[shop.gun_sel].cost == 30000) { //check gun
            if(!game.has_plan[s][6]) //check plan
            break; //hide buy button
            }

            if(server[s].gun[shop.gun_sel].cost == 50000) { //check gun
            if(!game.has_plan[s][7]) //check plan
            break; //hide buy button
            }

			show_it = 1;
			break;
		case 2: //missiles
			if(sh_id > -1 && sh_t > -1 && sh_k > -1)
			{
				max = server[sh_id].ship[sh_t].missile_ammount[sh_k];
				for ( i=0;i<max;i++ )
					if ( game.ship[sh].missile_id[i] < 0 || game.ship[sh].missile[i] < 0 ) //check for emptyness
				{
					got_space = 1;
					break;
				}
			}

			if(!got_space) break;
			if(game.money < server[s].missile[shop.missile_sel].cost) break;
			if(game.exp < missile_exp_requirement(server[s].missile, shop.missile_sel, server[sh_id].ship[sh_t].exp[sh_k])) break;

			show_it = 1;
			break;
		case 3: //misc
			if(sh_id > -1 && sh_t > -1 && sh_k > -1)
			{
				max = server[sh_id].ship[sh_t].misc_ammount[sh_k];
				for ( i=0;i<max;i++ )
					if ( game.ship[sh].misc[i] < 0 ) //check for emptyness
				{
					got_space = 1;
					break;
				}
			}

			if(!got_space) break;
			if( game.money < misc_pod_cost ( shop.misc_sel )) break;
			if(game.exp < misc_pod_exp ( shop.misc_sel ) + server[sh_id].ship[sh_t].exp[sh_k]) break;

			show_it = 1;
			break;
	}

	if(show_it)
		SDL_BlitSurface ( shop.buy_img, NULL, shop.temp_backround, &shop.button[1] );
	else
		SDL_BlitSurface ( shop.buy_blank, NULL, shop.temp_backround, &shop.button[1] );
}

void shop_show_type_left_right()
{
	int test_type;

	//only do this for the ship screen
	if(shop.shop_sel) return;

	test_type = shop.ship_type_sel;

	//are we currently at the bottom?
	if ( test_type == next_shop_type_down() )
		SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[3] );
	else
		SDL_BlitSurface ( shop.sel_left, NULL, shop.temp_backround, &shop.button[3] );

	//are we currently at the top?
	if ( test_type == next_shop_type_up() )
		SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[4] );
	else
		SDL_BlitSurface ( shop.sel_right, NULL, shop.temp_backround, &shop.button[4] );

}

void shop_show_kind_left_right()
{
	int test_kind;

	switch ( shop.shop_sel )
	{
		case 0: //chassis
			test_kind = shop.ship_kind_sel;
			break;
		case 1: //guns
			test_kind = shop.gun_sel;
			break;
		case 2: //missiles
			test_kind = shop.missile_sel;
			break;
		case 3: //misc
			test_kind = shop.misc_sel;
			break;
	}

	if ( test_kind == next_shop_kind_down() ) //if sellected first ship then remove left select button
		SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[5] );
	else
		SDL_BlitSurface ( shop.sel_left, NULL, shop.temp_backround, &shop.button[5] );

	if ( test_kind == next_shop_kind_up() )
		SDL_BlitSurface ( shop.sel_blank, NULL, shop.temp_backround, &shop.button[6] );
	else
		SDL_BlitSurface ( shop.sel_right, NULL, shop.temp_backround, &shop.button[6] );
}

int shop_ship_available_for_purchase(int sh_t, int sh_k)
{
	int max;

	int &s = game.server_id;
	int &p = planet.last_planet;

	//we got the plan?
	if(at_home_planet() && game.has_plan[s][sh_t]) return 1;

	if(server[s].planet[p].ship[shop.ship_type_sel].max < 7)
		max = server[s].planet[p].ship[shop.ship_type_sel].max;
	else
		max = 7;

	//it excluded?
	if(server[s].planet[p].ship[sh_t].exclude[sh_k]) return 0;

	//over the max?
	if(sh_k>max) return 0;

	//then ok
	return 1;
}

void shop_choose_available_ship_kind()
{
	int sh_t, sh_k;
	int temp_kind;

	sh_t = shop.ship_type_sel;
	sh_k = shop.ship_kind_sel;

	//should we be even choosing another ship kind?
	if(shop_ship_available_for_purchase(sh_t, sh_k)) return;

	//go left
	temp_kind = next_shop_kind_down();
	if(temp_kind != sh_k)
	{
		shop.ship_kind_sel = temp_kind;
		return;
	}

	temp_kind = next_shop_kind_up();
	if(temp_kind != sh_k)
	{
		shop.ship_kind_sel = temp_kind;
		return;
	}

	//well I guess it didn't find anything good?
}

void shop_set_initial_selections()
{
	int i, j;
	int &s = game.server_id;
	int &p = planet.last_planet;

	//ship
	for(i=0;i<SHIP_MAX;i++)
		if(server[s].planet[p].ship[i].have)
	{
		shop.ship_type_sel = i;

		//consider plans?
		if(at_home_planet())
		{
			for(j=0;j<=server[s].planet[p].ship[i].max;j++)
				if(!server[s].planet[p].ship[i].exclude[j] || game.has_plan[s][i])
			{
				shop.ship_kind_sel = j;
				break;
			}
		}
		else
		{
			for(j=0;j<=server[s].planet[p].ship[i].max;j++)
				if(!server[s].planet[p].ship[i].exclude[j])
			{
				shop.ship_kind_sel = j;
				break;
			}
		}
		break;
	}

	//gun
	for(i=0;i<GUN_MAX;i++)
		if(server[s].planet[p].gun[i])
	{
		shop.gun_sel = i;
		break;
	}

	//missile
	for(i=0;i<MISSILE_MAX;i++)
		if(server[s].planet[p].missile[i])
	{
		shop.missile_sel = i;
		break;
	}

	//misc
	shop.misc_sel =  0;
}
