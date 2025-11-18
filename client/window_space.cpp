#include "main.h"


void load_space()
{
	int i;
	char temp_str[50], temp_filename[100];
	SDL_Rect destination, hull_fill;

	//ehh sound
	if ( launching.visible )
		play_sound_repeat ( sound_engine );

	if ( !space.backround )
	{
		space.backround = IMG_Load ( "graphics/mainback.jpg" );
		space.viewing_ship = IMG_Load ( "graphics/view_ship.jpg" );
		space.viewing_sector = IMG_Load ( "graphics/view_sec.jpg" );
		space.viewing_guns = IMG_Load ( "graphics/view_guns.jpg" );
		space.viewing_missiles = IMG_Load ( "graphics/view_missiles.jpg" );
		space.jump_img = IMG_Load ( "graphics/jump.jpg" );
		space.shield_off[0] = IMG_Load ( "graphics/sh1off.jpg" );
		space.shield_off[1] = IMG_Load ( "graphics/sh2off.jpg" );
		space.shield_off[2] = IMG_Load ( "graphics/sh3off.jpg" );
		space.shield_off[3] = IMG_Load ( "graphics/sh4off.jpg" );
		space.shield_off[4] = IMG_Load ( "graphics/sh5off.jpg" );
		space.shield_on[0] = IMG_Load ( "graphics/sh1on.jpg" );
		space.shield_on[1] = IMG_Load ( "graphics/sh2on.jpg" );
		space.shield_on[2] = IMG_Load ( "graphics/sh3on.jpg" );
		space.shield_on[3] = IMG_Load ( "graphics/sh4on.jpg" );
		space.shield_on[4] = IMG_Load ( "graphics/sh5on.jpg" );
		space.trade_goods_img = IMG_Load ( "graphics/tradegoods.jpg" );
		space.contraband_img = IMG_Load ( "graphics/contraband.jpg" );
		space.trade_goods_grey_img = IMG_Load ( "graphics/tradegoods_grey.jpg" );
		space.contraband_grey_img = IMG_Load ( "graphics/contraband_grey.jpg" );
		space.trade_img = IMG_Load ( "graphics/trade.jpg" );
		space.cancel_img = IMG_Load ( "graphics/cancel.jpg" );
		space.engage_img = IMG_Load ( "graphics/engage.jpg" );
		space.disengage_img = IMG_Load ( "graphics/disengage.jpg" );
		space.chat_img = IMG_Load ( "graphics/chat.jpg" );
		space.viewing_goods_space = IMG_Load ( "graphics/view_good_sector.jpg" );
		space.viewing_goods_ship = IMG_Load ( "graphics/view_good_ship.jpg" );
		space.viewing_contras_space = IMG_Load ( "graphics/view_contra_sector.jpg" );
		space.viewing_contras_ship = IMG_Load ( "graphics/view_contra_ship.jpg" );
        space.shine_img = IMG_Load ( "graphics/shield_shine.png" );
        space.hull_shine_img = IMG_Load ( "graphics/hull_shine.png" ); // image path
		space.loc_sun = IMG_Load ( "graphics/loc_sun.gif" );
		space.enemy_shield = IMG_Load ( "graphics/shield.png" );
		space.enemy_shield_low = IMG_Load ( "graphics/shield_low.png" );
		space.enemy_shield_mid = IMG_Load ( "graphics/shield_mid.png" );
		//SDL_SetAlpha(space.loc_sun, SDL_SRCALPHA | SDL_RLEACCEL, 170);

		for ( i=0;i<50;i++ )
		{
			sprintf ( temp_filename,"graphics/explosion/%d.PNG",i+1 );
			space.destroy_img[i] = IMG_Load ( temp_filename );
		}

		//draw shield off images onto backround
		for ( i=0;i<5;i++ )
			SDL_BlitSurface ( space.shield_off[i], NULL, space.backround, &space.button[40 + i] );
	}


	if ( space.redraw_loc )
		redraw_space_loc();

	//clear last motion user displayed
	space.motion_sel = -1;

	destination.x = 97;
	destination.y = 65;

	SDL_BlitSurface ( space.temp_loc, NULL, space.backround, &destination );

	set_forms_invisible();
	space.visible = 1;
	SDL_BlitSurface ( space.backround, NULL, screen, NULL );

	//now begin writing screen only stuff like text/display boxes
	for ( i=0;i<2;i++ )
	{
		if ( space.text_box[i].selected )
			select_text_box ( screen, &space.text_box[i] );
		else
			unselect_text_box ( screen, &space.text_box[i] );

		draw_display_box ( screen,&space.display_box[i] );
	}

	//good buttons
	draw_space_good_buttons();

	//draw text boxes
	draw_display_box ( screen,&space.display_box[0] );
	draw_display_box ( screen,&space.display_box[1] );

	//redraw nesscary hud images
	if ( space.view_sector_goods )
		SDL_BlitSurface ( space.viewing_sector, NULL, screen, &space.button[48] );
	else
		SDL_BlitSurface ( space.viewing_ship, NULL, screen, &space.button[48] );



	//shield
	SDL_BlitSurface ( space.shield_on[space.shield_level], NULL, screen, &space.button[40 + space.shield_level] );
	sprintf ( temp_str,"%d", game.ship[game.ship_sel].shield * ( space.shield_level / 4 ) );
	draw_center_label ( screen, temp_str, &space.shield_label, 0, 240, 240 );

	//hull
	sprintf ( temp_str,"%d", game.ship[game.ship_sel].hull );
	draw_center_label ( screen, temp_str, &space.hull_label, 240, 240, 0 );
	hull_fill.x = 139;
	hull_fill.w = 24;
	hull_fill.h = ( short unsigned int ) ( 60 * ( 1.0 * game.ship[game.ship_sel].hull / game.ship[game.ship_sel].hull_max ) );
	hull_fill.y = 376 - hull_fill.h;
	SDL_FillRect ( screen, &hull_fill, SDL_MapRGB ( screen->format, 185, 185, 13 ) );

	//name and ship
	if ( space.show_ship )
		space_do_show_ship();

	//as it says
	space_draw_good_box_if_suposed_to();

	if ( space.jump_ok ) //draw jump button //*jumpok
	{
		SDL_Rect jump_fill;

		jump_fill.x = 97;
		jump_fill.w = 24;
		jump_fill.h = 60;
		jump_fill.y = 316;
		SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 190, 26, 7 ) );
		SDL_BlitSurface ( space.jump_img, NULL, screen, &space.button[51] );
	}

    destination.x = 175;
    destination.y = 315;
    SDL_BlitSurface ( space.shine_img, NULL, screen, &destination);

    //displaying the image
    destination.x = 139;
    destination.y = 316;
    SDL_BlitSurface ( space.hull_shine_img, NULL, screen, &destination);

    //jump shine
    destination.x = 97;
    destination.y = 316;
    SDL_BlitSurface ( space.hull_shine_img, NULL, screen, &destination);


	//reselect selected if necessary
	if ( space.user_sel > 0 )
	{
		//this is done because the function is not
		//designed for reselecting an already selected user
		i = space.user_sel;
		space.user_sel = -1;
		space_select_user ( i );
	}

	//show guns if attacking
	if ( space.engaging > -1 )
		space_draw_weapons();

	//good time to set that it loaded
	space.form_load_time = current_time();

	sdl_flip_mutex();

	//start thread if already isn't
// 	if ( !space.thread )
// 		space.thread = SDL_CreateThread ( space_thread, NULL );

}

void button_wheel_space ( int is_up )
{
	int new_level;

	//set_shield ( i - 40 );
	if(is_up)
	{
		new_level = space.shield_level + 1;
		if(new_level >= 5) new_level = 4;

		set_shield(new_level);
	}
	else
	{
		new_level = space.shield_level - 1;
		if(new_level < 0) new_level = 0;

		set_shield(new_level);
	}
}

//*NEW main double click in space handler
void dblclick_left_space( int x, int y )
{
    	int i, k, button;

	for ( i=0;i<79;i++ )
		if ( x >= space.button[i].x && x <= space.button[i].x + space.button[i].w && y >= space.button[i].y && y <= space.button[i].y + space.button[i].h )
		{
			if ( space.viewing_cargo && i >= 53 && i <= 68 ) continue;
			if ( space.engaging == -1 && i == 52 ) continue;

			break;
		}

    switch ( i )
	{
		case 0: //planet
		case 1: //1-39, the launched users
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
            space_select_user_to_scan ( i );
            break;
	}
}
void button_right_space ( int x, int y )
{
	int i, k, button;

	for ( i=0;i<79;i++ )
		if ( x >= space.button[i].x && x <= space.button[i].x + space.button[i].w && y >= space.button[i].y && y <= space.button[i].y + space.button[i].h )
		{
			if ( space.viewing_cargo && i >= 53 && i <= 68 ) continue;
			if ( space.engaging == -1 && i == 52 ) continue;

			break;
		}

	switch ( i )
	{
		case 0: //planet
		case 1: //1-39, the launched users
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        // right click engage - disengage
        space_select_user(i);
        space_select_user_to_engage(i);
			break;
		case 40://shield change
		case 41:
		case 42:
		case 43:
		case 44:
			break;
		case 45: //engage / transfer
		case 46: //chat
			break;
		case 47: //trade
			break;
		case 48: //ship/sector
			break;
		case 49: //trade goods
			break;
		case 50: //contraband
			break;
		case 51: //jump
			break;
		case 52: //change weapons viewied
			break;
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
			break;
		case 69:
		case 70:
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
		case 76:
		case 77:
		case 78:
			space_select_good ( i - 69 );
			space_auto_do_good ( i - 69 );
			break;
	}
}

void button_space ( int x, int y )
{
	int i, k, success = 0, button;
	char land_msg[4] = "7,";

	for ( i=0;i<79;i++ )
		if ( x >= space.button[i].x && x <= space.button[i].x + space.button[i].w && y >= space.button[i].y && y <= space.button[i].y + space.button[i].h )
		{
			if ( space.viewing_cargo && i >= 53 && i <= 68 ) continue;
			if ( space.engaging == -1 && i == 52 ) continue;

			success = 1; button = 1; break;
		}

	if ( !success ) for ( i=0;i<4;i++ )
			if ( x >= space.text_box[i].location.x && x <= space.text_box[i].location.x + space.text_box[i].location.w && y >= space.text_box[i].location.y && y <= space.text_box[i].location.y + space.text_box[i].location.h )
			{


				success = 1; button = 0; break;
			}

	if ( !success ) return;

	if ( button )
	{
		switch ( i )
		{
			case 0: //posible land
				if ( space.at_planet )
				{
					load_landing();
					send_con_server ( land_msg );
				}
				else
				{
					space_select_user ( 0 );
				}
				break;
			default: //1-39, the launched users
				space_select_user ( i );
				break;
			case 40://shield change
			case 41:
			case 42:
			case 43:
			case 44:
				set_shield ( i - 40 );
				break;
			case 45: //engage / transfer
				if ( space.user_sel != -1 ) //if someone selected (and your not transfering)
					if ( !space.transferring ) //engage
						space_engage_user();
					else
						transfer_money_to ( space.user[space.user_sel].username,0 );
				break;
			case 46: //chat
				space_chat_button();
				break;
			case 47: //trade
				break;
			case 48: //ship/sector
				space_toggle_ship_sector();
				break;
			case 49: //trade goods
				if ( space.engaging != -1 ) break;

				space_draw_good_box ( 1,space.view_cargo_sector );
				break;
			case 50: //contraband
				if ( space.engaging != -1 ) break;

				space_draw_good_box ( 0,space.view_cargo_sector );
				break;
			case 51: //jump
				//if ( !space.jump_ok ) break; //*jumpok
				load_map();
				break;
			case 52: //change weapons viewied


				if ( space.weapon_viewing )
					space.weapon_viewing = 0;
				else
					space.weapon_viewing = 1;

				space_draw_weapons();
				sdl_flip_mutex();
				break;
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
			case 58:
			case 59:
			case 60:
			case 61:
			case 62:
			case 63:
			case 64:
			case 65:
			case 66:
			case 67:
			case 68:
				if ( space.weapon_viewing == 1 ) //missiles
					space_fire_missile ( i - 53 );
				break;
			case 69:
			case 70:
			case 71:
			case 72:
			case 73:
			case 74:
			case 75:
			case 76:
			case 77:
			case 78:
				space_select_good ( i - 69 );
				break;
		}
	}
	else
	{

		//checks....
		if ( i==2 )
			if ( !space.viewing_cargo || space.engaging != -1 )
				return;
		if ( i==3 )
			return;


		//do the stuff...
		for ( k=0;k<4;k++ )
		{
			if ( k==2 )
				if ( !space.viewing_cargo || space.engaging != -1 )
					continue;
			if ( k==3 )
				continue;

			space.text_box[k].selected = 0;

			if ( k != i )
				unselect_text_box ( screen, &space.text_box[k] );
			else
				select_text_box ( screen, &space.text_box[k] );
		}

		sdl_flip_mutex();
	}
}

void motion_space ( int x, int y )
{
	int i;
	char hover_str[500], temp_str[21];
    std::string asteroid = "Asteroid";
    std::string mbox = "Mystery";
    std::string coll = "Iron";
 //   std::string smugg = "Smuggler";
	for ( i=0;i<40;i++ )
		if ( x >= space.button[i].x && x <= space.button[i].x + space.button[i].w && y >= space.button[i].y && y <= space.button[i].y + space.button[i].h )
			break;

	if ( i == 40 ) return;

	//check if anyone is there
	if ( space.user[i].ship_id != -1 )
	{
		if ( space.info_label_mode == 0 && space.motion_sel == i ) return;
		if ( space.info_label_mode == 1 && space.motion_sel == space.user_sel ) return;
		if ( space.info_label_mode == -1 && space.user_sel == i ) return;

		space.motion_sel = i;
		space.info_label_mode = 0;
		if ( space.user[i].ship_name == asteroid)
        sprintf ( hover_str, "%s : Space Rock :: %s", space.user[i].username, space.user[i].guild );
        else if ( space.user[i].ship_name == mbox)
        sprintf ( hover_str, "%s : Dark Cube :: %s", space.user[i].username, space.user[i].guild );
        else if ( space.user[i].ship_name == coll)
        sprintf ( hover_str, "%s : Collector :: %s", space.user[i].username, space.user[i].guild );
//        else if ( space.user[i].ship_name == smugg)
//        sprintf ( hover_str, "%s : White Hat Smuggler :: %s", space.user[i].username, space.user[i].guild );
        else
		sprintf ( hover_str, "%s : %s %s :: %s", space.user[i].username, space.user[i].ship_name, ship_name ( space.user[i].ship_kind, temp_str ), space.user[i].guild );
		draw_label ( screen, hover_str, &space.info_label, 0, 230, 0 );
		sdl_flip_mutex();
		//printf("sss: %s\n", space.user[i].ship_name);
	}

	else if ( space.user[i].ship_id == -1 && space.user[i].ship_kind > -1 && space.user[i].ship_kind < SPECIAL_FSHIP_MAX )
	{
		//sat
		if ( space.info_label_mode == 0 && space.motion_sel == i ) return;
		if ( space.info_label_mode == 1 && space.motion_sel == space.user_sel ) return;
		if ( space.info_label_mode == -1 && space.user_sel == i ) return;

		space.motion_sel = i;
		space.info_label_mode = 0;
		sprintf ( hover_str, "%s : Defense System :: %s", space.user[i].username, space.user[i].guild );
		draw_label ( screen, hover_str, &space.info_label, 0, 230, 0 );
		sdl_flip_mutex();

	}
	else if ( space.user_sel != -1 ) //over a userless sector
	{
		if ( space.info_label_mode != 0 ) return; //leave if not coming from motion

		//check what we should be drawing
		space.motion_sel = -1;
		space.info_label_mode = 1;
		if ( space.user[space.user_sel].ship_id == -1 && space.user[space.user_sel].ship_kind > -1 && space.user[space.user_sel].ship_kind < 2 )
			sprintf ( hover_str, "%s : Defense System :: %s", space.user[space.user_sel].username, space.user[space.user_sel].guild );
		else if ( space.user[space.user_sel].ship_type == 40 )
			sprintf ( hover_str, "%s : Space Rock :: %s", space.user[space.user_sel].username, space.user[space.user_sel].guild );
        else if ( space.user[space.user_sel].ship_type == 14 )
			sprintf ( hover_str, "%s : Dark Cube :: %s", space.user[space.user_sel].username, space.user[space.user_sel].guild );
        else if ( space.user[space.user_sel].ship_type == 18 )
			sprintf ( hover_str, "%s : Collector :: %s", space.user[space.user_sel].username, space.user[space.user_sel].guild );
//        else if ( space.user[space.user_sel].ship_type == 12 )
//			sprintf ( hover_str, "%s : White Hat Smuggler :: %s", space.user[space.user_sel].username, space.user[space.user_sel].guild );
		else
			sprintf ( hover_str, "%s : %s %s :: %s", space.user[space.user_sel].username, space.user[space.user_sel].ship_name, ship_name ( space.user[space.user_sel].ship_kind, temp_str ), space.user[space.user_sel].guild );
		draw_label ( screen, hover_str, &space.info_label, 0, 230, 0 );
		sdl_flip_mutex();
	}
	else //over a userless sector when no one is selected
	{
		if ( space.info_label_mode == -1 ) return;

		space.motion_sel = -1;
		space.info_label_mode = -1;
		draw_label ( screen,"", &space.info_label, 0, 230, 0 );
		sdl_flip_mutex();
	}
}

void key_space ( int c )
{
	int i, sel;
	const int text_max = 4;

	for ( i=0;i<text_max;i++ )
		if ( space.text_box[i].selected )
			break;

	//wtf?
	if ( i==text_max ) i=0;
	//if ( i==0 ) return;

	sel = i;

	if ( c == 9 ) //tab
	{
		sel++;

		if ( sel==text_max ) sel = 0;

		//okay now for the pisser tests
		if ( sel==2 )
			if ( !space.viewing_cargo || space.engaging != -1 )
			{
				sel++;
				if ( sel==text_max ) sel = 0;

			}
		if ( sel==3 ) //just completely skip this one for now
		{
			sel++;
			if ( sel==text_max ) sel = 0;
		}

		//do the stuff...
		for ( i=0;i<text_max;i++ )
		{
			//checks....
			if ( i==2 )
				if ( !space.viewing_cargo || space.engaging != -1 )
				{
					space.text_box[i].selected = 0;
					continue;
				}
			if ( i==3 )
			{
				space.text_box[i].selected = 0;
				continue;
			}

			if ( i != sel )
				unselect_text_box ( screen, &space.text_box[i] );
			else
				select_text_box ( screen, &space.text_box[i] );
		}

		sdl_flip_mutex();
	}
	else if ( c == 13 ) //enter
	{
		switch ( sel )
		{
			case 0: //public chat
				send_public_chat ( space.text_box[0].message );
				add_text_box_entry ( &space.text_box[0], space.text_box[0].message );
				clear_text_box ( screen, &space.text_box[0] );
				sdl_flip_mutex();
				break;
			case 1: //private chat
				private_chat_send ( space.text_box[1].message );
				add_text_box_entry ( &space.text_box[1], space.text_box[1].message );
				clear_text_box ( screen, &space.text_box[1] );
				sdl_flip_mutex();
				break;
			case 2: //good drop/pickup
				space_do_drop_good ( atoi ( space.text_box[2].message ) );
				break;
			case 3: //transfer money
				break;
		}
	}
	else if ( c == 280 || c == 281 )
	{
		if ( i>1 ) return; //not for the higher folk

		if ( c == 280 )
			scroll_up_display_box ( screen, space.text_box[i].display_box_link );

		if ( c == 281 )
			scroll_down_display_box ( screen, space.text_box[i].display_box_link );

		sdl_flip_mutex();
	}
	else
	{
		//now for special cases
		if ( sel >= 2 && ( ! ( c >= '0' && c <= '9' ) && ! ( c == 8 || c == 127 || c == 275 || c == 276 ) ) ) return;

		add_text_box ( screen, &space.text_box[sel], c );
		sdl_flip_mutex();
	}
}

int space_thread ( void *nothing )
{
	int jump_set = 0, redraw, reset_backround = 0, gun_x, gun_y, i, k;
	int hit_on, hit_x[16], hit_y[16];
	double the_time, interval_time, gun_time = 0, temp_time, temp_ratio, hit_time;
	SDL_Rect jump_fill, user_spot, destination, odamage_box, idamage_box;
	const double hit_time_max = 0.5;

	destination.x = 97;
	destination.y = 65;

	jump_fill.x = 97;
	jump_fill.w = 24;

	odamage_box.w = 60;
	odamage_box.h = 5;

	idamage_box.h = 3;

	the_time = current_time();

	for ( ; space.visible || map.visible;redraw = 0 )
	{
		//sync with server requests
		//SDL_LockMutex ( space_mutex );
		//SDL_UnlockMutex(space_mutex);

		//save old time
		interval_time = current_time() - the_time;
		//setup "time"
		the_time = current_time();

		//reset backround if requested
		if ( reset_backround )
		{
			if ( space.visible )
				SDL_BlitSurface ( space.temp_loc, NULL, screen, &destination );
			reset_backround = 0;
			redraw = 1;
		}

		//jump
		if ( the_time - space.jump_time_start < space.jump_time )
		{
			//how about now? eh? EH
			if ( space.clear_jump_bar )
			{
				jump_fill.h = 60;
				jump_fill.y = 316;
				if ( space.visible )
					SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 0, 0, 0 ) );

				space.clear_jump_bar = 0;
			}
			space.jump_time_start += interval_time * 0.25 * space.shield_level;
			jump_fill.h = ( short unsigned int ) ( 60 * ( ( the_time - space.jump_time_start ) / space.jump_time ) );
			jump_fill.y = 376 - jump_fill.h;
			if ( space.visible )
            SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 190, 26, 7 ) );

			redraw = 1;
		}
		else if ( space.jump_ok ) //draw jump button //*jumpok
		{
			space.jump_ok = 1;
			jump_fill.h = 60;
			jump_fill.y = 316;
			if ( space.visible )
			{
				SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 190, 26, 7 ) );
				SDL_BlitSurface ( space.jump_img, NULL, screen, &space.button[51] );
			}
			redraw = 1;
		}

		//selection box
		if ( space.user_sel != -1 )
		{
			//increment
			space.selection_box_i++;
			if ( space.selection_box_i > 4 )
				space.selection_box_i = 0;

			//clear this area
			user_spot = space.button[space.user_sel];
			user_spot.x -= 97;
			user_spot.y -= 65;
			user_spot.w = 60;
			user_spot.h = 50;
			if ( space.visible )
				SDL_BlitSurface ( space.temp_loc, &user_spot, screen, &space.button[space.user_sel] );

			//draw the box
			if ( space.visible )
				rectangleRGBA ( screen, space.button[space.user_sel].x + space.selection_box_i, space.button[space.user_sel].y + space.selection_box_i, ( space.button[space.user_sel].x + 59 ) - ( space.selection_box_i * 2 ), ( space.button[space.user_sel].y + 49 ) - ( space.selection_box_i * 2 ), 255, 255, 255, 255 );

			redraw = 1;
		}

		//damage box
		if ( space.engaging > -1 )
		{
			odamage_box.x = space.button[space.engaging].x;
			odamage_box.y = space.button[space.engaging].y;
			idamage_box.x = odamage_box.x + 1;
			idamage_box.y = odamage_box.y + 1;
			idamage_box.w = ( short unsigned int ) ( 58 * space.user[space.engaging].hull_percent * 0.01 );

			//draw outter
			if ( space.visible )
				SDL_FillRect ( screen, &odamage_box, SDL_MapRGB ( screen->format, 0, 73, 70 ) );

			//draw inner
			if ( space.user[space.engaging].hull_percent > 50 )
			{
				if ( space.visible )
					SDL_FillRect ( screen, &idamage_box, SDL_MapRGB ( screen->format, ( unsigned char ) ( 510 * ( 1 - space.user[space.engaging].hull_percent * 0.01 ) ), 0,255 ) );
			}
			else
			{
				if ( space.visible )
					SDL_FillRect ( screen, &idamage_box, SDL_MapRGB ( screen->format, 255, 0, ( unsigned char ) ( 510 * space.user[space.engaging].hull_percent * 0.01 ) ) );
			}

			//now for shields
			space_draw_enemy_shield();

			//now for jump status
			space_draw_enemy_jump_status();

			//now for ref ratio
			space_draw_enemy_ref_ratio();

			redraw = 1;
		}

		//starting circle stuff
		if ( space.engaging > -1 && space.hit_enemy )
		{
			hit_on = space.hit_max;

			//set time
			hit_time = the_time;

			//set locs
			for ( i=0;i<space.hit_actual_max;i++ )
			{
				//set centers
				hit_x[i] = space.button[space.engaging].x + 30;
				hit_y[i] = space.button[space.engaging].y + 25;

				//set offsets
				hit_x[i] += ( rand() % 20 ) - 10;
				hit_y[i] += ( rand() % 24 ) - 12;
			}

			space.hit_enemy = 0;

			//force fire
			gun_time = 0;
		}
		//drawing circle stuff
		if ( the_time - hit_time < hit_time_max && space.visible )
		{
			double percent_done;

			percent_done = ( the_time - hit_time ) / hit_time_max;

			//draw
			for ( i=0;i<space.hit_actual_max;i++ )
				if ( i<hit_on )
				{
					for ( k= ( int ) ( ( 5 * percent_done ) + 1 );k<6;k++ )
						circleRGBA ( screen,hit_x[i],hit_y[i],k,255 - ( k* 20 ),0,0,150 );
				}
				else
				{
					for ( k= ( int ) ( ( 5 * percent_done ) + 1 );k<6;k++ )
						circleRGBA ( screen,hit_x[i],hit_y[i],k,0,255 - ( k* 20 ),0,150 );
				}

			reset_backround = 1;
			redraw = 1;
		}

		//destroy user
		for ( i=0;i<40;i++ )
			if ( space.user[i].destroy )
			{
				//clear that bit
				user_spot = space.button[i];
				user_spot.x -= 97;
				user_spot.y -= 65;
				if ( space.visible )
					SDL_BlitSurface ( space.loc, &user_spot, screen,  &space.button[i] );

				k = ( int ) ( 51.0 * ( ( the_time - space.user[i].destroy_time ) / 4.0 ) );

				if ( k<52 ) //display
				{
					if ( space.visible )
						SDL_BlitSurface ( space.destroy_img[k], NULL, screen, &space.button[i] );
				}
				else
				{
					//stuff stolen from remove_from_sector()
					space.user[i].ship_id 		= -1;
					space.user[i].ship_kind 	= -1;
					space.user[i].ship_type 	= -1;
					space.user[i].ship_name[0] 	= '\0';
					space.user[i].username[0] 	= '\0';
					space.user[i].guild[0] 		= '\0';
					space.user[i].destroy 		= 0;
					space.user[i].destroy_time	= 0;

					//stuff stolen from remove_from_sector()
					SDL_BlitSurface ( space.loc, &user_spot, space.temp_loc, &user_spot );
				}

				redraw = 1;
			}

		//enemy guns
		for ( i=0;i<40;i++ )
			if ( space.user[i].attacking > -1 )
			{
				int &v_u = space.user[i].attacking;

				//attacking monkey space?
				if ( !space.user[v_u].username[0] )
				{
					space.user[i].attacking = 0;
					for ( k=0;k<16;k++ )
						space.user[i].missile_firing[k] = 0;
					continue;
				}

				//do missiles
				for ( k=0;k<16;k++ )
					if ( space.user[i].missile_firing[k] )
					{
						//should it be?
						temp_ratio = ( the_time - space.user[i].missile_time[k] ) / space.user[i].missile_speed[k];

						if ( temp_ratio >= 1 )
						{
							space.user[i].missile_firing[k] = 0;
							continue;
						}

						if ( space.visible )
							space_draw_enemy_missile ( i, k, temp_ratio );

						reset_backround = 1;
						redraw = 1;
					}

				//do guns
				temp_time = the_time - space.user[i].attack_time;
				if ( temp_time < 3 ) continue;

				if ( !space.user[i].attack_x )
				{
					space.user[i].attack_x = space.button[v_u].x + 15 + ( rand() % 30 );
					space.user[i].attack_y = space.button[v_u].y + 12 + ( rand() % 25 );

					play_sound ( sound_enemy_gun[rand() % 2] );
				}

				if ( space.visible )
					space_draw_line_to_user ( i );

				if ( temp_time > 3.5 )
				{
					space.user[i].attack_time = the_time;

					space.user[i].attack_x = 0;
					space.user[i].attack_y = 0;
				}

				reset_backround = 1;
				redraw = 1;
			}
			else if ( space.user[i].attacking == -2 ) //attacking you
			{
				//do missiles
				for ( k=0;k<16;k++ )
					if ( space.user[i].missile_firing[k] )
					{
						//should it be?
						temp_ratio = ( the_time - space.user[i].missile_time[k] ) / space.user[i].missile_speed[k];

						if ( temp_ratio >= 1 )
						{
							space.user[i].missile_firing[k] = 0;
							continue;
						}

						if ( space.visible )
							space_draw_enemy_missile ( i, k, temp_ratio );

						reset_backround = 1;
						redraw = 1;
					}

				//do guns
				temp_time = the_time - space.user[i].attack_time;
				if ( temp_time < 3 ) continue;


				if ( !space.user[i].attack_position )
				{
					space.user[i].attack_side = ( rand() % 4 );
					if ( space.user[i].attack_side == 0 || space.user[i].attack_side == 1 )
						space.user[i].attack_position = ( rand() % 190 ) + 5;
					else
						space.user[i].attack_position = ( rand() % 590 ) + 5;

					play_sound ( sound_enemy_gun[rand() % 2] );
				}

				if ( space.visible )
					space_draw_line ( space.user[i].attack_position, space.user[i].attack_side, space.button[i].x + 30, space.button[i].y + 25 );

				if ( temp_time > 3.5 )
				{
					space.user[i].attack_time = the_time;

					space.user[i].attack_position = 0;
				}

				reset_backround = 1;
				redraw = 1;
			}


		//engage guns
		if ( space.engaging > -1 )
		{
			gun_time -= interval_time;

			if ( gun_time <= 0 )
			{
				gun_x = 3 + ( rand() % 30 );
				gun_y = 8 + ( rand() % 25 );
				gun_time = game.ship[game.ship_sel].gun_speed + 1; //set new interval

				play_sound ( sound_gun );
			}

			if ( game.ship[game.ship_sel].gun_speed - gun_time < -0.75 )
				if ( space.visible )
				{
					space_draw_gun_lines ( gun_x, gun_y ); //draw all lines
					reset_backround = 1;
				}

			if ( game.ship[game.ship_sel].gun_speed - gun_time >= -0.75 && ( game.ship[game.ship_sel].gun_speed - gun_time ) - interval_time < -0.75 )
			{
				if ( space.visible )
					space_draw_gun_lines ( gun_x, gun_y ); //draw all lines
				reset_backround = 1;
				redraw = 1;
			}

		}

		//engage missiles
		if ( space.engaging > -1 )
			for ( i=0;i<16;i++ )
				if ( space.missile_firing[i] )
				{
					temp_ratio = ( the_time - space.missile_time[i] ) / space.missile_speed[i];

					if ( temp_ratio >= 1 )
					{
						space.missile_firing[i] = 0;
						continue;
					}

					if ( space.visible )
						space_draw_missile ( i, temp_ratio );
					reset_backround = 1;
					redraw = 1;
				}


		//good selection the life made easy way
		if ( space_good_select_animate() )
			redraw = 1;

		//redraw screen if required
		if ( redraw && space.visible )
			sdl_flip_mutex();

		//SDL_UnlockMutex ( space_mutex );

#ifdef _WIN32 //if linux or windows
		Sleep ( 100 );
#else
		usleep ( 100000 );
#endif
	}

	space.thread = NULL; //let everyone know it has exited
	return 0;
}

void space_threadless()
{
	static int jump_set = 0, redraw, gun_x, gun_y, i, k;
	static int hit_on, hit_x[16], hit_y[16];
	static double interval_time, gun_time = 0, temp_time, temp_ratio, hit_time;
	static SDL_Rect jump_fill, user_spot, destination, odamage_box, idamage_box;

	const double hit_time_max = 0.5;
	static double the_time = 0;
	static int reset_backround = 0;

	if(!space.visible && !map.visible)
	{
		the_time = 0;
		return;
	}

	destination.x = 97;
	destination.y = 65;

	jump_fill.x = 97;
	jump_fill.w = 24;

	odamage_box.w = 60;
	odamage_box.h = 5;

	idamage_box.h = 3;

	if(the_time > -0.00001 && the_time < 0.00001)
		the_time = current_time();

	//save old time
	interval_time = current_time() - the_time;

	//sync up with the old thread version
	if(interval_time < 0.1) return;

	//setup "time"
	the_time = current_time();

	//reset backround if requested
	if ( reset_backround )
	{
		if ( space.visible )
			SDL_BlitSurface ( space.temp_loc, NULL, screen, &destination );
		reset_backround = 0;
		redraw = 1;
	}

	//jump
	if ( the_time - space.jump_time_start < space.jump_time )
	{
		//how about now? eh? EH
		if ( space.clear_jump_bar )
		{
			jump_fill.h = 60;
			jump_fill.y = 316;
			if ( space.visible )
				SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 0, 0, 0 ) );

			space.clear_jump_bar = 0;
		}
		space.jump_time_start += interval_time * 0.25 * space.shield_level;
		jump_fill.h = ( short unsigned int ) ( 60 * ( ( the_time - space.jump_time_start ) / space.jump_time ) );
		jump_fill.y = 376 - jump_fill.h;
		if ( space.visible )
        SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 190, 26, 7 ) );

        SDL_Rect jump_shine_fill;
        jump_shine_fill.x = 0;
        jump_shine_fill.w = 24;
        jump_shine_fill.h = ( short unsigned int ) ( 60 * ( ( the_time - space.jump_time_start ) / space.jump_time ) );
        jump_shine_fill.y = 60-jump_shine_fill.h;
        //jump shine
        destination.x = 97;//97;
        destination.y = 316+59-jump_shine_fill.h+1;//315;
        //SDL_SetAlpha(space.hull_shine_img, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
        if ( !map.visible ) {
        SDL_BlitSurface ( space.hull_shine_img, &jump_shine_fill, screen, &destination);
        }
		redraw = 1;
	}
	else if ( !space.jump_ok ) //draw jump button
	{
		space.jump_ok = 1;
		jump_fill.h = 60;
		jump_fill.y = 316;
		if ( space.visible )
		{
			SDL_FillRect ( screen, &jump_fill, SDL_MapRGB ( screen->format, 190, 26, 7 ) );
			SDL_BlitSurface ( space.jump_img, NULL, screen, &space.button[51] );

        SDL_Rect jump_shine_fill;
        jump_shine_fill.x = 0;
        jump_shine_fill.w = 24;
        jump_shine_fill.h = ( short unsigned int ) ( 60 * ( ( the_time - space.jump_time_start ) / space.jump_time ) );
        jump_shine_fill.y = 60-jump_shine_fill.h;
        //jump shine
        destination.x = 97;//97;
        destination.y = 316+59-jump_shine_fill.h+1;//315;
        //SDL_SetAlpha(space.hull_shine_img, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
        SDL_BlitSurface ( space.hull_shine_img, &jump_shine_fill, screen, &destination);

		}

		redraw = 1;
	}

	//selection box
	if ( space.user_sel != -1 )
	{
		//increment
		space.selection_box_i++;
		if ( space.selection_box_i > 4 )
			space.selection_box_i = 0;

		//clear this area
		user_spot = space.button[space.user_sel];
		user_spot.x -= 97;
		user_spot.y -= 65;
		user_spot.w = 60;
		user_spot.h = 50;
		if ( space.visible )
			SDL_BlitSurface ( space.temp_loc, &user_spot, screen, &space.button[space.user_sel] );

		//draw the box
		if ( space.visible )
			rectangleRGBA ( screen, space.button[space.user_sel].x + space.selection_box_i, space.button[space.user_sel].y + space.selection_box_i, ( space.button[space.user_sel].x + 59 ) - ( space.selection_box_i * 2 ), ( space.button[space.user_sel].y + 49 ) - ( space.selection_box_i * 2 ), 255, 255, 255, 255 );

		redraw = 1;
	}

	//damage box
	if ( space.engaging > -1 )
	{
		odamage_box.x = space.button[space.engaging].x;
		odamage_box.y = space.button[space.engaging].y;
		idamage_box.x = odamage_box.x + 1;
		idamage_box.y = odamage_box.y + 1;
		idamage_box.w = ( short unsigned int ) ( 58 * space.user[space.engaging].hull_percent * 0.01 );

		//draw outter
		if ( space.visible )
			SDL_FillRect ( screen, &odamage_box, SDL_MapRGB ( screen->format, 0, 73, 70 ) );

		//draw inner
		if ( space.user[space.engaging].hull_percent > 60 )
		{
			if ( space.visible )
				SDL_FillRect ( screen, &idamage_box, SDL_MapRGB ( screen->format, 0, 255, 0 ) );
		}
		else
		{
			if ( space.visible )
				SDL_FillRect ( screen, &idamage_box, SDL_MapRGB ( screen->format, 255, 255, 0 ) );
		}

		//now for shields
		space_draw_enemy_shield();

		//now for jump status
		space_draw_enemy_jump_status();

		//now for ref ratio
		space_draw_enemy_ref_ratio();

		redraw = 1;
	}

	//starting circle stuff
	if ( space.engaging > -1 && space.hit_enemy )
	{
		hit_on = space.hit_max;

		//set time
		hit_time = the_time;

		//set locs
		for ( i=0;i<space.hit_actual_max;i++ )
		{
			//set centers
			hit_x[i] = space.button[space.engaging].x + 30;
			hit_y[i] = space.button[space.engaging].y + 25;

			//set offsets
			hit_x[i] += ( rand() % 20 ) - 10;
			hit_y[i] += ( rand() % 24 ) - 12;
		}

		space.hit_enemy = 0;

		//force fire
		gun_time = 0;
	}
	//drawing circle stuff
	if ( the_time - hit_time < hit_time_max && space.visible )
	{
		double percent_done;

		percent_done = ( the_time - hit_time ) / hit_time_max;

		//draw
		for ( i=0;i<space.hit_actual_max;i++ )
			if ( i<hit_on )
		{
			for ( k= ( int ) ( ( 5 * percent_done ) + 1 );k<6;k++ )
                //*new draw hit color based on shield level
                if (space.user[space.engaging].shield_level > 0 && space.user[space.engaging].shield_level <= 2)
                circleRGBA ( screen,hit_x[i],hit_y[i],k,0,200,255 - ( k* 20 ),150 );
                else if (space.user[space.engaging].shield_level > 2)
                circleRGBA ( screen,hit_x[i],hit_y[i],k,0,100,255 - ( k* 20 ),150 );
                else
				circleRGBA ( screen,hit_x[i],hit_y[i],k,255 - ( k* 20 ),0,0,150 );
		}
		else
		{
			for ( k= ( int ) ( ( 5 * percent_done ) + 1 );k<6;k++ )
                //*new draw hit color based on shield level
                if (space.user[space.engaging].shield_level > 0 && space.user[space.engaging].shield_level <= 2)
                circleRGBA ( screen,hit_x[i],hit_y[i],k,0,200,255 - ( k* 20 ),150 );
                else if (space.user[space.engaging].shield_level > 2)
                circleRGBA ( screen,hit_x[i],hit_y[i],k,0,100,255 - ( k* 20 ),150 );
                else
				circleRGBA ( screen,hit_x[i],hit_y[i],k,0,255 - ( k* 20 ),0,150 );
		}

		reset_backround = 1;
		redraw = 1;
	}

	//destroy user
	for ( i=0;i<40;i++ )
		if ( space.user[i].destroy )
	{
			//clear that bit
		user_spot = space.button[i];
		user_spot.x -= 97;
		user_spot.y -= 65;
		if ( space.visible )
			SDL_BlitSurface ( space.loc, &user_spot, screen,  &space.button[i] );

		k = ( int ) ( 51.0 * ( ( the_time - space.user[i].destroy_time ) / 4.0 ) );

		if ( k<52 ) //display
		{
			if ( space.visible )
				SDL_BlitSurface ( space.destroy_img[k], NULL, screen, &space.button[i] );
		}
		else
		{
				//stuff stolen from remove_from_sector()
			space.user[i].ship_id 		= -1;
			space.user[i].ship_kind 	= -1;
			space.user[i].ship_type 	= -1;
			space.user[i].ship_name[0] 	= '\0';
			space.user[i].username[0] 	= '\0';
			space.user[i].guild[0] 		= '\0';
			space.user[i].destroy 		= 0;
			space.user[i].destroy_time	= 0;

				//stuff stolen from remove_from_sector()
			SDL_BlitSurface ( space.loc, &user_spot, space.temp_loc, &user_spot );
		}

		redraw = 1;
	}

	//enemy guns
	for ( i=0;i<40;i++ )
		if ( space.user[i].attacking > -1 )
	{
		int &v_u = space.user[i].attacking;

			//attacking monkey space?
		if ( !space.user[v_u].username[0] )
		{
			space.user[i].attacking = 0;
			for ( k=0;k<16;k++ )
				space.user[i].missile_firing[k] = 0;
			continue;
		}

			//do missiles
		for ( k=0;k<16;k++ )
			if ( space.user[i].missile_firing[k] )
		{
					//should it be?
			temp_ratio = ( the_time - space.user[i].missile_time[k] ) / space.user[i].missile_speed[k];

			if ( temp_ratio >= 1 )
			{
				space.user[i].missile_firing[k] = 0;
				continue;
			}

			if ( space.visible )
				space_draw_enemy_missile ( i, k, temp_ratio );

			reset_backround = 1;
			redraw = 1;
		}

			//do guns
		temp_time = the_time - space.user[i].attack_time;
		if ( temp_time < 3 ) continue;

		if ( !space.user[i].attack_x )
		{
			space.user[i].attack_x = space.button[v_u].x + 15 + ( rand() % 30 );
			space.user[i].attack_y = space.button[v_u].y + 12 + ( rand() % 25 );

			play_sound ( sound_enemy_gun[rand() % 2] );
		}

		if ( space.visible )
			space_draw_line_to_user ( i );

		if ( temp_time > 3.5 )
		{
			space.user[i].attack_time = the_time;

			space.user[i].attack_x = 0;
			space.user[i].attack_y = 0;
		}

		reset_backround = 1;
		redraw = 1;
	}
	else if ( space.user[i].attacking == -2 ) //attacking you
	{
			//do missiles
		for ( k=0;k<16;k++ )
			if ( space.user[i].missile_firing[k] )
		{
					//should it be?
			temp_ratio = ( the_time - space.user[i].missile_time[k] ) / space.user[i].missile_speed[k];

			if ( temp_ratio >= 1 )
			{
				space.user[i].missile_firing[k] = 0;
				continue;
			}

			if ( space.visible )
				space_draw_enemy_missile ( i, k, temp_ratio );

			reset_backround = 1;
			redraw = 1;
		}

			//do guns
		temp_time = the_time - space.user[i].attack_time + 2;
		if ( temp_time < 3 ) continue;


		if ( !space.user[i].attack_position )
		{
			space.user[i].attack_side = ( rand() % 4 );
			if ( space.user[i].attack_side == 0 || space.user[i].attack_side == 1 )
				space.user[i].attack_position = ( rand() % 190 ) + 5;
			else
				space.user[i].attack_position = ( rand() % 590 ) + 5;

			play_sound ( sound_enemy_gun[rand() % 2] );
		}

		if ( space.visible )
			space_draw_line ( space.user[i].attack_position, space.user[i].attack_side, space.button[i].x + 30, space.button[i].y + 25 );

		if ( temp_time > 3.5 )
		{
			space.user[i].attack_time = the_time;

			space.user[i].attack_position = 0;
		}

		reset_backround = 1;
		redraw = 1;
	}


	//engage guns
	if ( space.engaging > -1 )
	{
		gun_time -= interval_time;

		if ( gun_time <= 1 )
		{
			gun_x = 3 + ( rand() % 30 );
			gun_y = 8 + ( rand() % 25 );
			gun_time = game.ship[game.ship_sel].gun_speed + 1; //set new interval

			play_sound ( sound_gun );
		}

		if ( game.ship[game.ship_sel].gun_speed - gun_time < -0.75 )
			if ( space.visible )
		{
			space_draw_gun_lines ( gun_x, gun_y ); //draw all lines
			reset_backround = 1;
		}

		if ( game.ship[game.ship_sel].gun_speed - gun_time >= -0.75 && ( game.ship[game.ship_sel].gun_speed - gun_time ) - interval_time < -0.75 )
		{
			if ( space.visible )
				space_draw_gun_lines ( gun_x, gun_y ); //draw all lines
			reset_backround = 1;
			redraw = 1;
		}

	}

	//engage missiles
	if ( space.engaging > -1 )
		for ( i=0;i<16;i++ )
			if ( space.missile_firing[i] )
	{
		temp_ratio = ( the_time - space.missile_time[i] ) / space.missile_speed[i];

		if ( temp_ratio >= 1 )
		{
			space.missile_firing[i] = 0;
			continue;
		}

		if ( space.visible )
			space_draw_missile ( i, temp_ratio );
		reset_backround = 1;
		redraw = 1;
	}


	//good selection the life made easy way
	if ( space_good_select_animate() )
		redraw = 1;

	//redraw screen if required
	if ( redraw && space.visible )
		sdl_flip_mutex();

}


void redraw_space_loc()
{
	int i;
	char temp_filename[200], temp_str[21];
	SDL_Rect img_location;

	//reset temp loc
	SDL_BlitSurface ( space.loc, NULL, space.temp_loc, NULL );

	//add players to loc
	for ( i=0;i<40;i++ )
		draw_space_user_ship ( i );

	space.redraw_loc = 0;
}

void space_draw_enemy_ref_ratio()
{
	SDL_Rect obox, ibox;
	int i;
	int u;

	if ( !space.visible ) return;

	u = space.engaging;

	obox.w = 8;
	obox.h = 4;

	ibox.w = 6;
	ibox.h = 2;

	obox.x = space.button[u].x;
	obox.y = space.button[u].y + 6;

	ibox.x = obox.x + 1;
	ibox.y = obox.y + 1;

	//outer
	SDL_FillRect ( screen, &obox, SDL_MapRGB ( screen->format, 255, 255, 0 ) );

	if(space.user[u].ref_ratio > 0) SDL_FillRect ( screen, &ibox, SDL_MapRGB ( screen->format, 0, 250 * 100 / space.user[u].ref_ratio, 0 ) );
	if(space.user[u].ref_ratio < 0) SDL_FillRect ( screen, &ibox, SDL_MapRGB ( screen->format, 250 * -100 / space.user[u].ref_ratio, 0, 0 ) );

	//printf("ref ratio: %d\n", space.user[u].ref_ratio);
}

void space_draw_enemy_jump_status()
{
	SDL_Rect obox, ibox;
	int i;
	int u;

	u = space.engaging;

	obox.w = 8;
	obox.h = 4;

	ibox.w = 6;
	ibox.h = 2;

	obox.x = space.button[u].x + 52;
	obox.y = space.button[u].y + 6;

	ibox.x = obox.x + 1;
	ibox.y = obox.y + 1;

	//draw the outter
	if ( space.visible )
		SDL_FillRect ( screen, &obox, SDL_MapRGB ( screen->format, 0, 40, 230 ) );

	//draw the inners
	if ( space.user[u].jump_status )
		if ( space.visible )
			SDL_FillRect ( screen, &ibox, SDL_MapRGB ( screen->format, 0, 210, 255 ) );

}

void space_draw_enemy_shield()
{
	SDL_Rect destination;
	int i;
	int u;

	u = space.engaging;

	destination.x = space.button[u].x;
	destination.y = space.button[u].y;

	for ( i=0;i<4;i++ )
	{
		//draw the innerss
		if ( i<space.user[u].shield_level )
		{
			if ( space.visible )
                if (i<=1)
                SDL_BlitSurface ( space.enemy_shield_low, NULL, screen, &destination );
                else if (i>1 && i<=3)
                SDL_BlitSurface ( space.enemy_shield_mid, NULL, screen, &destination );
                //low shield
                else
				SDL_BlitSurface ( space.enemy_shield, NULL, screen, &destination );
		}
	}

	space.user[u].refresh_shield = 0;
}
