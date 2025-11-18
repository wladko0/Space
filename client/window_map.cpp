#include "main.h"

void init_form_map()
{
	int i, j, k;

	map.backround = NULL;
	map.visible = 0;
	for ( i=0;i<5;i++ )
	{
		map.button[i].w = 20;
		map.button[i].h = 20;
	}
	//jumpback back button
	map.button[B_MAP_CANCEL].x = 690;
	map.button[B_MAP_CANCEL].y = 567;
	map.button[B_MAP_CANCEL].w = 105;
	map.button[B_MAP_CANCEL].h = 33;

	//zoom plus button
	map.button[B_MAP_ZOOM_PLUS].x = 773;
	map.button[B_MAP_ZOOM_PLUS].y = 3;
	map.button[B_MAP_ZOOM_PLUS].w = 20;
	map.button[B_MAP_ZOOM_PLUS].h = 20;

	//zoom minus button
	map.button[B_MAP_ZOOM_MINUS].x = 676;
	map.button[B_MAP_ZOOM_MINUS].y = 3;
	map.button[B_MAP_ZOOM_MINUS].w = 20;
	map.button[B_MAP_ZOOM_MINUS].h = 20;

	for ( i=B_MAP_SHIELD0;i<=B_MAP_SHIELD4;i++ )
	{
		map.button[i].x = 6 + ((i-B_MAP_SHIELD0) * 19);
		map.button[i].y = 584;
		map.button[i].w = 14;
		map.button[i].h = 14;
	}

	//found marked in red label
	map.scan_label.location.x = 3;
	map.scan_label.location.y = 37;
	map.scan_label.location.w = 307;
	map.scan_label.location.h = 17;
	map.scan_label.message[0] = '\0';

	map.players_online_label = map.scan_label;
	map.players_online_label.location.y = 492;
	map.players_in_zone_label = map.players_online_label;
	map.players_launched_in_zone_label = map.players_online_label;
	map.players_in_zone_label.location.y += 14;
	map.players_launched_in_zone_label.location.y += 14 * 2;

	//online, launched, etc label
	map.player_counts_label.location.x = 87;
	map.player_counts_label.location.y = 584;
	map.player_counts_label.location.w = 321 - 52;
	map.player_counts_label.location.h = 17;
	map.player_counts_label.message[0] = '\0';

	map.under_attack_label.location.x = 2;
	map.under_attack_label.location.y = 540;
	map.under_attack_label.location.w = 99 - 2;
	map.under_attack_label.location.h = 17;
	map.under_attack_label.message[0] = '\0';

	map.text_box.location.x = 150;
	map.text_box.location.y = 7;
	map.text_box.location.w = 154;
	map.text_box.location.h = 10;
	clear_text_box ( NULL, &map.text_box );
	setup_text_box ( &map.text_box );
	map.text_box.selected = 1;
	map.text_box.max_char = 20;
	map.text_box.pass_char = '\0';
	map.scan_last = SDL_CreateRGBSurface ( SDL_HWSURFACE, 38, 38, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );

}

void load_map()
{
	int i, k;
	int range_max;
	char temp_filename[200], temp_str[21];
	double offset_x, offset_y, hypo, temp_dbl;
	SDL_Rect destination;

	if ( !map.backround )
	{
		map.backround 			= IMG_Load ( "graphics/jumpback.jpg" );
		map.backround_cutout 		= IMG_Load ( "graphics/jumpback_cut.png" );
		map.center_button			= IMG_Load ( "graphics/r1.png" );
		map.scan_large			= IMG_Load ( "graphics/scan_large.png" );
		map.scan_small			= IMG_Load ( "graphics/scan_small.png" );
		map.scan_tiny			= IMG_Load ( "graphics/scan_tiny.png" );
		map.scan_up				= IMG_Load ( "graphics/scan_up.png" );
		map.scan_down			= IMG_Load ( "graphics/scan_down.png" );
		map.scan_left			= IMG_Load ( "graphics/scan_left.png" );
		map.scan_right			= IMG_Load ( "graphics/scan_right.png" );
		map.scan_up_left			= IMG_Load ( "graphics/scan_up_left.png" );
		map.scan_up_right			= IMG_Load ( "graphics/scan_up_right.png" );
		map.scan_down_left		= IMG_Load ( "graphics/scan_down_left.png" );
		map.scan_down_right		= IMG_Load ( "graphics/scan_down_right.png" );
		map.sun_img				= IMG_Load ( "graphics/sun_hyper.gif" );
		map.nebula_img			= IMG_Load ( "graphics/nebula_hyper.gif" );
		map.e_mark				= IMG_Load ( "graphics/exclamation_mark.png" );
		map.g_shield			= IMG_Load ( "graphics/gshield.png" );
		map.shield_off[0] = IMG_Load ( "graphics/map_sh1off.png" );
		map.shield_off[1] = IMG_Load ( "graphics/map_sh2off.png" );
		map.shield_off[2] = IMG_Load ( "graphics/map_sh3off.png" );
		map.shield_off[3] = IMG_Load ( "graphics/map_sh4off.png" );
		map.shield_off[4] = IMG_Load ( "graphics/map_sh5off.png" );
		map.shield_on[0] = IMG_Load ( "graphics/map_sh1on.png" );
		map.shield_on[1] = IMG_Load ( "graphics/map_sh2on.png" );
		map.shield_on[2] = IMG_Load ( "graphics/map_sh3on.png" );
		map.shield_on[3] = IMG_Load ( "graphics/map_sh4on.png" );
		map.shield_on[4] = IMG_Load ( "graphics/map_sh5on.png" );
		game.game_image.hyper_s_grey	= IMG_Load ( "graphics/gray_sector.png" );

		SDL_SetAlpha ( map.nebula_img, SDL_SRCALPHA | SDL_RLEACCEL, 170 );
		//SDL_SetColorKey ( map.backround_cutout, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB ( map.backround_cutout->format, 255,255,255 ) );
	}

	//make sure sector icons are loaded
	if ( !server[game.server_id].zone[game.zone].hyper_sel )
	{
		sprintf ( temp_filename, "server/%s/buttons/hyper/sel_%d.png", server[game.server_id].servername, game.zone );
		server[game.server_id].zone[game.zone].hyper_sel = IMG_Load ( temp_filename );

		if ( !server[game.server_id].zone[game.zone].hyper_sel )
			server[game.server_id].zone[game.zone].hyper_sel = IMG_Load ( "graphics/nif/nif_hyper_sel.gif" );
	}

	if ( !server[game.server_id].zone[game.zone].hyper_sec )
	{
		sprintf ( temp_filename, "server/%s/buttons/hyper/sec_%d.png", server[game.server_id].servername, game.zone );
		server[game.server_id].zone[game.zone].hyper_sec = IMG_Load ( temp_filename );

		if ( !server[game.server_id].zone[game.zone].hyper_sec )
			server[game.server_id].zone[game.zone].hyper_sec = IMG_Load ( "graphics/nif/nif_hyper_sec.gif" );
	}

	if ( !server[game.server_id].zone[game.zone].hyper_safe )
	{
		sprintf ( temp_filename, "server/%s/buttons/hyper/safe_%d.png", server[game.server_id].servername, game.zone );
		server[game.server_id].zone[game.zone].hyper_safe = IMG_Load ( temp_filename );

		if ( !server[game.server_id].zone[game.zone].hyper_safe )
			server[game.server_id].zone[game.zone].hyper_safe = IMG_Load ( "graphics/nif/nif_hyper_safe.gif" );
	}

	map.mouse_over_sector = -1;

	//temporarily stop the space thread
	//SDL_LockMutex ( space_mutex );

	set_forms_invisible();
	map.visible = 1;

	//allow it to go again
	//SDL_UnlockMutex ( space_mutex );

	//now do screen only stuff
	map_redraw();

	sdl_flip_mutex();
}

void button_wheel_map ( int is_up )
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

void button_up_map ( int x, int y )
{
	map_set_shift ( x,y,0 );
}

void button_map ( int x, int y )
{
	int i;
	char rtn_str[10];
	const int button_max = B_MAP_MAX_BUTTONS;


	for ( i=0;i<button_max;i++ )
		if ( x >= map.button[i].x && x <= map.button[i].x + map.button[i].w && y >= map.button[i].y && y <= map.button[i].y + map.button[i].h )
			break;


	if ( i == button_max )
    { //*NEW mouse over sector get node ID, etc .. Warp with node click for admins
        int new_mouse_over_sector = -1;
        int s_id = game.server_id, z = game.zone;

        for (int sec=0;sec<SECTOR_MAX;sec++ )
            if ( server[s_id].zone[z].sector[sec].x ) //if sector is there
            {
                SDL_Rect location;
                int p;

                location.x = 400 + ( server[s_id].zone[z].sector[sec].x - map.sector_x );
                location.y = 300 + ( server[s_id].zone[z].sector[sec].y - map.sector_y );
                location.x += map.shift_x;
                location.y += map.shift_y;
                location.x -= 5;
                location.y -= 5;

                if(x < location.x) continue;
                if(y < location.y) continue;
                if(x > location.x + 10) continue;
                if(y > location.y + 10) continue;

                new_mouse_over_sector = sec;
            }

        const char *admin_names[] = {"Admin", "Administrator"}; // checkk admin names v2.0 (client -> con -> send_server_packet)
        bool name_found = false; // default admin check = no admin

        for(int i=0;i<sizeof(admin_names)/sizeof(char*);++i) // need to get character size
            {
                if (strcmp(game.username, admin_names[i]) == 0) name_found = true; // check character size, output value (either true or false)
            }

        if (name_found) // if username matches admin_names, name_found = true .. proceed
            {
            if(new_mouse_over_sector != -1) // get sector
                {
                    char warp_str[50]; // fake string
                    sprintf ( warp_str, "4,@warp,%d,%d", game.zone, new_mouse_over_sector ); // the magic happens
                    send_con_server ( warp_str ); // tell the server
                }
            }

        map_set_shift ( x,y,1 );
        return;
    }

	switch ( i )
	{
	case B_MAP_JUMP0:
	case B_MAP_JUMP1:
	case B_MAP_JUMP2:
	case B_MAP_JUMP3:
	case B_MAP_JUMP4:
		if ( map.sector_link[i]<0 ) break; //dont send if it isn't valid
		sprintf ( rtn_str, "8,%d", map.sector_link[i] );
		send_con_server ( rtn_str );
		break;
	case B_MAP_CANCEL:
		load_space();
		break;
	case B_MAP_ZOOM_PLUS:
		map_zoom_in();
		break;
	case B_MAP_ZOOM_MINUS:
		map_zoom_out();
		break;
	case B_MAP_SHIELD0:
	case B_MAP_SHIELD1:
	case B_MAP_SHIELD2:
	case B_MAP_SHIELD3:
	case B_MAP_SHIELD4:
		set_shield(i-B_MAP_SHIELD0);
		break;
	}
}

void motion_map ( int x, int y )
{
	int i;
	int new_mouse_over_sector = -1;
	int s_id, z;

	s_id = game.server_id;
	z = game.zone;

	for ( i=0;i<SECTOR_MAX;i++ )
		if ( server[s_id].zone[z].sector[i].x ) //if sector is there
		{
			SDL_Rect location;
			int p;

			if(!server[s_id].zone[z].sector[i].has_guild_member) continue;

			location.x = 400 + ( server[s_id].zone[z].sector[i].x - map.sector_x );
			location.y = 300 + ( server[s_id].zone[z].sector[i].y - map.sector_y );
			location.x += map.shift_x;
			location.y += map.shift_y;
			location.x -= 5;
			location.y -= 5;

			if(x < location.x) continue;
			if(y < location.y) continue;
			if(x > location.x + 10) continue;
			if(y > location.y + 10) continue;

			new_mouse_over_sector = i;
		}

	if(map.mouse_over_sector != new_mouse_over_sector)
	{
		printf("new mouse_over_sector:%d\n", new_mouse_over_sector);
		map.mouse_over_sector = new_mouse_over_sector;
		map_redraw();
		sdl_flip_mutex();
	}
}

void key_map ( int c )
{
	int i, len;
	char rtn_str[500];

    //char to int ?? blahhhhhhh
    len = strlen ( map.text_box.message );

	if ( c == 13 )
	{
        if (len==0 || len<3) return; //check emptyness xx..
		sprintf ( rtn_str, "13,%s", map.text_box.message );
		add_text_box_entry ( &map.text_box, map.text_box.message );
		send_con_server ( rtn_str );
	}
	else
	{
		add_text_box ( screen, &map.text_box, c );
		sdl_flip_mutex();
	}
}



int map_check_sector_on_map ( int x, int y )
{
	if ( x < 10 || y < 10 || x > 790 || y > 590 ) return 0; //set sector bounderies
	if ( x > 790 && y > 590 ) return 0; //to work around the cancel button 694 566

	return 1;
}

void map_draw_planet_names()
{
	int i;
    std::string ggt = "Gen Gate Top";
    std::string ggl = "Gen Gate Left";
    std::string ggr = "Gen Gate Right";
    std::string vgl = "Velic Gate Left";
    std::string vgm = "Velic Gate Mid";
    std::string vgr = "Velic Gate Right";
    std::string fg = "Forbidden Gate";

	for ( i=0;i<SECTOR_MAX;i++ )
		if ( server[game.server_id].zone[game.zone].sector[i].x ) //if sector is there
			if ( server[game.server_id].zone[game.zone].sector[i].planet > -1 )
			{
				SDL_Rect location;
				int p;

				p = server[game.server_id].zone[game.zone].sector[i].planet;

				location.x = 400 + ( server[game.server_id].zone[game.zone].sector[i].x - map.sector_x );
				location.y = 300 + ( server[game.server_id].zone[game.zone].sector[i].y - map.sector_y );
				location.x += map.shift_x;
				location.y += map.shift_y;
				if ( game.sector == i )
					location.y += 15;
				else
                location.y += 10;
				location.w = 0;
				location.h = 0;
				if (game.zone == 0 && server[game.server_id].planet[p].name == ggt )
                {
				draw_raw_center_label ( screen, "Universal Gate Top", location, 240, 240, 240 );
				}
				else if (game.zone == 0 && server[game.server_id].planet[p].name == ggl )
                {
                draw_raw_center_label ( screen, "Universal Gate Bot", location, 240, 240, 240 );
                }
                else if (game.zone == 0 && server[game.server_id].planet[p].name == ggr )
                {
                draw_raw_center_label ( screen, "Universal Gate Mid", location, 240, 240, 240 );
                }
                else if (game.zone == 1 && server[game.server_id].planet[p].name == vgl )
                {
                draw_raw_center_label ( screen, "Universal Gate Top", location, 240, 240, 240 );
                }
                else if (game.zone == 1 && server[game.server_id].planet[p].name == vgm )
                {
                draw_raw_center_label ( screen, "Universal Gate Mid", location, 240, 240, 240 );
                }
                else if (game.zone == 1 && server[game.server_id].planet[p].name == vgr )
                {
                draw_raw_center_label ( screen, "Universal Gate Bot", location, 240, 240, 240 );
                }
                else if (game.zone == 3 && server[game.server_id].planet[p].name == fg )
                {
                draw_raw_center_label ( screen, "Universal Gate", location, 240, 240, 240 );
                }
                else
                {
				draw_raw_center_label ( screen, server[game.server_id].planet[p].name, location, 240, 240, 240 );
				}
			}
}

void map_draw_sector_images()
{
	double offset_x, offset_y, hypo, temp_dbl, sun_offset_x, sun_offset_y;
	SDL_Rect destination;
	int i, k;
	int s_id, z;
	int range_max;

	s_id = game.server_id;
	z = game.zone;
	range_max = game.ship[game.ship_sel].range;

	if ( !game.activated && range_max > DEACTIVATED_RANGE_LIMIT )
		range_max = DEACTIVATED_RANGE_LIMIT;

	//draw all sectors
	offset_x = server[s_id].zone[z].hyper_sec->w / 2;
	offset_y = server[s_id].zone[z].hyper_sec->h / 2;
	sun_offset_x = map.sun_img->w / 2;
	sun_offset_y = map.sun_img->h / 2;
	for ( i=0;i<SECTOR_MAX;i++ )
		if ( server[s_id].zone[z].sector[i].x ) //if sector is there
		{
			int x, y;

			x = 400 + ( server[s_id].zone[z].sector[i].x - map.sector_x );
			y = 300 + ( server[s_id].zone[z].sector[i].y - map.sector_y );
			x += map.shift_x;
			y += map.shift_y;

			//check if within boundaries
			if ( !map_check_sector_on_map ( x, y ) ) continue;

			if ( !server[s_id].zone[z].sector[i].is_sun && server[s_id].zone[z].sector[i].planet < 0 )
			{
				destination.x = ( short int ) ( x - offset_x );
				destination.y = ( short int ) ( y - offset_y );

				//check if in jump range
				if ( server[s_id].zone[z].sector[i].range > range_max )
					SDL_BlitSurface ( game.game_image.hyper_s_grey, NULL, screen, &destination );
				else
					SDL_BlitSurface ( server[s_id].zone[z].hyper_sec, NULL, screen, &destination );
			}
			else if ( server[s_id].zone[z].sector[i].planet >= 0 && i!=game.sector ) //has planet
			{
				if ( load_map_planet ( s_id, server[s_id].zone[z].sector[i].planet ) )
				{
					destination.x = x - ( server[s_id].planet[server[s_id].zone[z].sector[i].planet].hyper_img->w / 2 );
					destination.y = y - ( server[s_id].planet[server[s_id].zone[z].sector[i].planet].hyper_img->h / 2 );
					SDL_BlitSurface ( server[s_id].planet[server[s_id].zone[z].sector[i].planet].hyper_img, NULL, screen, &destination );
				}
				else
				{
					//use nif image
					if ( !game.nif_image.no_hyper_p_img )
						game.nif_image.no_hyper_p_img = IMG_Load ( "graphics/nif/nif_hyper_p.gif" );

					if ( game.nif_image.no_hyper_p_img )
					{
						destination.x = x - ( game.nif_image.no_hyper_p_img->w / 2 );
						destination.y = y - ( game.nif_image.no_hyper_p_img->h / 2 );
						SDL_BlitSurface ( game.nif_image.no_hyper_p_img, NULL, screen, &destination );
					}
				}
			}
			else
			{
				if ( i!=game.sector )
				{
					destination.x = ( short int ) ( x - sun_offset_x );
					destination.y = ( short int ) ( y - sun_offset_y );
					SDL_BlitSurface ( map.sun_img, NULL, screen, &destination );
				}
			}

			//either way, is there an enemy there?
			if ( server[s_id].zone[z].sector[i].has_player && (server[s_id].zone[z].free_scan || server[s_id].zone[z].sector[i].free_scan) && i!=game.sector )
			{
				destination.x = ( short int ) ( x - 15 );
				destination.y = ( short int ) ( y );
				SDL_BlitSurface ( map.e_mark, NULL, screen, &destination );
			}

			if(server[s_id].zone[z].sector[i].has_guild_member && i!=game.sector)
			{
				destination.x = ( short int ) ( x + 10 );
				destination.y = ( short int ) ( y - 2 );
				SDL_BlitSurface ( map.g_shield, NULL, screen, &destination );
			}
		}
}

void map_draw_local_sectors()
{
	double offset_x, offset_y, hypo, temp_dbl, sun_offset_x, sun_offset_y;
	SDL_Rect destination;
	int i, k;
	int s_id, z;
	int range_max;
	char temp_filename[200], temp_str[21];

	s_id = game.server_id;
	z = game.zone;

	range_max = game.ship[game.ship_sel].range;

	//draw all sectors
	offset_x = server[s_id].zone[z].hyper_sec->w / 2;
	offset_y = server[s_id].zone[z].hyper_sec->h / 2;
	sun_offset_x = map.sun_img->w / 2;
	sun_offset_y = map.sun_img->h / 2;

	for ( i=0;i<5;i++ )
	{
		int s;

		s = server[s_id].zone[z].sector[game.sector].sector[i];
		//check if in jump range
		if ( server[s_id].zone[z].sector[s].range > range_max ) continue;


		if ( map.sector_link[i] >= 0 )
		{
			//draw lines
			offset_x = 400 - map.sector_link_x[i];
			offset_y = 300 - map.sector_link_y[i];
			hypo = pow ( pow ( offset_x,2 ) + pow ( offset_y,2 ), 0.5 );

			if ( offset_y && offset_x )
			{
				temp_dbl = -0.9 * offset_x / hypo;
				offset_x = 0.9 * offset_y / hypo;
				offset_y = temp_dbl;
			}
			else if ( fabs ( offset_x ) < 0.0001 )
			{
				offset_x = 1;
				offset_y = 0;
			}
			else if ( fabs ( offset_y ) < 0.0001 )
			{
				offset_x = 0;
				offset_y = 1;
			}

			for ( k=3;k>0;k-- )
			{
				short int x1, y1, x2, y2;

				x1 = ( short int ) ( ( 400 + ( offset_x ) ) + map.shift_x );
				y1 = ( short int ) ( ( 300 + ( offset_y ) ) + map.shift_y );
				x2 = ( short int ) ( ( map.sector_link_x[i] + ( k * offset_x ) ) + map.shift_x );
				y2 = ( short int ) ( ( map.sector_link_y[i] + ( k * offset_y ) ) + map.shift_y );

				aalineRGBA ( screen, x1, y1, x2, y2, 255, 255, 255, 255 );

				x1 = ( short int ) ( ( 400 - ( offset_x ) ) + map.shift_x );
				y1 = ( short int ) ( ( 300 - ( offset_y ) ) + map.shift_y );
				x2 = ( short int ) ( ( map.sector_link_x[i] - ( k * offset_x ) ) + map.shift_x );
				y2 = ( short int ) ( ( map.sector_link_y[i] - ( k * offset_y ) ) + map.shift_y );

				aalineRGBA ( screen, x1, y1, x2, y2, 255, 255, 255, 255 );
			}
			aalineRGBA ( screen, 400 + map.shift_x, 300 + map.shift_y, map.sector_link_x[i] + map.shift_x, map.sector_link_y[i] + map.shift_y, 255, 255, 255, 255 );

			//draw little icon
			if ( server[s_id].zone[z].sector[map.sector_link[i]].planet >= 0 ) //has planet
			{
				if ( load_map_planet ( s_id, server[s_id].zone[z].sector[map.sector_link[i]].planet ) )
				{
					destination.x = map.sector_link_x[i] - ( server[s_id].planet[server[s_id].zone[z].sector[map.sector_link[i]].planet].hyper_img->w / 2 );
					destination.y = map.sector_link_y[i] - ( server[s_id].planet[server[s_id].zone[z].sector[map.sector_link[i]].planet].hyper_img->h / 2 );
					destination.x += map.shift_x;
					destination.y += map.shift_y;
					SDL_BlitSurface ( server[s_id].planet[server[s_id].zone[z].sector[map.sector_link[i]].planet].hyper_img, NULL, screen, &destination );
				}
				else
				{
					//use nif image
					if ( !game.nif_image.no_hyper_p_img )
						game.nif_image.no_hyper_p_img = IMG_Load ( "graphics/nif/nif_hyper_p.gif" );

					if ( game.nif_image.no_hyper_p_img )
					{
						destination.x = map.sector_link_x[i] - ( game.nif_image.no_hyper_p_img->w / 2 );
						destination.y = map.sector_link_y[i] - ( game.nif_image.no_hyper_p_img->h / 2 );
						destination.x += map.shift_x;
						destination.y += map.shift_y;
						SDL_BlitSurface ( game.nif_image.no_hyper_p_img, NULL, screen, &destination );
					}
				}
			}
			else //normal sector
			{
				if ( server[s_id].zone[z].sector[map.sector_link[i]].is_sun )
				{
					destination.x = ( short int ) ( map.sector_link_x[i] - sun_offset_x );
					destination.y = ( short int ) ( map.sector_link_y[i] - sun_offset_y );
					destination.x += map.shift_x;
					destination.y += map.shift_y;
					SDL_BlitSurface ( map.sun_img, NULL, screen, &destination );
				}
				else if ( server[s_id].zone[z].sector[map.sector_link[i]].shield )
				{
					destination.x = map.sector_link_x[i] - ( server[s_id].zone[z].hyper_safe->w / 2 );
					destination.y = map.sector_link_y[i] - ( server[s_id].zone[z].hyper_safe->h / 2 );
					destination.x += map.shift_x;
					destination.y += map.shift_y;
					SDL_BlitSurface ( server[s_id].zone[z].hyper_safe, NULL, screen, &destination );
				}
				else
				{
					destination.x = map.sector_link_x[i] - ( server[s_id].zone[z].hyper_sel->w / 2 );
					destination.y = map.sector_link_y[i] - ( server[s_id].zone[z].hyper_sel->h / 2 );
					destination.x += map.shift_x;
					destination.y += map.shift_y;
					SDL_BlitSurface ( server[s_id].zone[z].hyper_sel, NULL, screen, &destination );
				}
			}

			//either way, is there an enemy there?
			if( server[s_id].zone[z].sector[s].has_player && (server[s_id].zone[z].free_scan || server[s_id].zone[z].sector[s].free_scan) )
			{
				destination.x = ( short int ) ( map.sector_link_x[i] - 15 );
				destination.y = ( short int ) ( map.sector_link_y[i] );
				destination.x += map.shift_x;
				destination.y += map.shift_y;
				SDL_BlitSurface ( map.e_mark, NULL, screen, &destination );
			}

			if(server[s_id].zone[z].sector[s].has_guild_member)
			{
				destination.x = ( short int ) ( map.sector_link_x[i] + 10 );
				destination.y = ( short int ) ( map.sector_link_y[i] - 2);
				destination.x += map.shift_x;
				destination.y += map.shift_y;
				SDL_BlitSurface ( map.g_shield, NULL, screen, &destination );
			}
		}

	}

	//draw center image
	destination.x = 385;
	destination.y = 285;
	destination.x += map.shift_x;
	destination.y += map.shift_y;
	SDL_BlitSurface ( map.center_button, NULL, screen, &destination );

	//draw our little ship image
	if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].rad_img[game.ship[game.ship_sel].kind] )
	{
		sprintf ( temp_filename, "server/%s/radships/%s/%s.jpg", server[game.ship[game.ship_sel].server_id].servername, ship_name ( game.ship[game.ship_sel].kind, temp_str ), server[game.server_id].ship[game.ship[game.ship_sel].type].name );
		server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].rad_img[game.ship[game.ship_sel].kind] = IMG_Load ( temp_filename );
	}
	if ( server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].rad_img[game.ship[game.ship_sel].kind] )
	{
		destination.x = 400 - ( server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].rad_img[game.ship[game.ship_sel].kind]->w / 2 );
		destination.y = 300 - ( server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].rad_img[game.ship[game.ship_sel].kind]->h / 2 );
		destination.x += map.shift_x;
		destination.y += map.shift_y;
		SDL_BlitSurface ( server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].rad_img[game.ship[game.ship_sel].kind], NULL, screen, &destination );
	}
	else
	{
		;//nif image
	}
}

void map_redraw_side_hud()
{
	SDL_Rect destination;

	destination.x = 0;
	destination.y = 0;

	SDL_BlitSurface ( map.backround_cutout, NULL, screen, &destination );
}

void map_draw_nebula_and_sun()
{
	int i, k;
	int glow_radius, glow_int;
	int range_max;
	range_max = game.ship[game.ship_sel].range;

	if ( !map.zoom_level )
	{
		glow_radius = SUN_RADIUS;
		glow_int = 4;
	}
	else if ( map.zoom_level > 0 )
	{
		glow_radius = ( int ) ( SUN_RADIUS * pow ( ZOOM_IN_AMT, map.zoom_level ) );
		glow_int = ( int ) ( 4 * pow ( ZOOM_IN_AMT, map.zoom_level ) );
	}
	else if ( map.zoom_level < 0 )
	{
		glow_radius = ( int ) ( SUN_RADIUS * pow ( ZOOM_OUT_AMT, -map.zoom_level ) );
		glow_int = ( int ) ( 4 * pow ( ZOOM_OUT_AMT, -map.zoom_level ) );
	}

	for ( i=0;i<SECTOR_MAX;i++ )
		if ( server[game.server_id].zone[game.zone].sector[i].x ) //if sector is there
		{
			if ( server[game.server_id].zone[game.zone].sector[i].is_sun )
			{
				int x, y;

				x = 400 + ( server[game.server_id].zone[game.zone].sector[i].x - map.sector_x );
				y = 300 + ( server[game.server_id].zone[game.zone].sector[i].y - map.sector_y );
				x += map.shift_x;
				y += map.shift_y;

				for ( k=15;k<glow_radius;k+=glow_int )
					filledCircleRGBA ( screen, x, y, k, 255, 200, 0, 10 );
			}
		}

	for ( i=0;i<SECTOR_MAX;i++ )
		if ( server[game.server_id].zone[game.zone].sector[i].x ) //if sector is there
		{
			if ( server[game.server_id].zone[game.zone].sector[i].range > range_max ) continue;

			if ( server[game.server_id].zone[game.zone].sector[i].is_nebula )
			{
				SDL_Rect destination;

				destination.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[i].x - map.sector_x ) ) - ( map.nebula_img->w / 2 );
				destination.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[i].y - map.sector_y ) ) - ( map.nebula_img->h / 2 );
				destination.x += map.shift_x;
				destination.y += map.shift_y;

				SDL_BlitSurface ( map.nebula_img, NULL, screen, &destination );
			}
		}
}


void map_zoom_in()
{
	int s, z, i;

	//check
	if ( map.zoom_level >= ZOOM_MAX ) return;

	//set
	map.zoom_level++;
	z = game.zone;
	s = game.server_id;

	//spank all sectors
	for ( z=0;z<ZONE_MAX;z++ )
		if ( server[s].zone[z].name[0] )
			for ( i=0;i<SECTOR_MAX;i++ )
				if ( server[s].zone[z].sector[i].x )
				{
					server[s].zone[z].sector[i].x = ( int ) ( server[s].zone[z].sector[i].x * ZOOM_IN_AMT );
					server[s].zone[z].sector[i].y = ( int ) ( server[s].zone[z].sector[i].y * ZOOM_IN_AMT );
				}

	//forget no one
	map.shift_x = ( int ) ( map.shift_x * ZOOM_IN_AMT );
	map.shift_y = ( int ) ( map.shift_y * ZOOM_IN_AMT );

	map_set_local_sector_info();

	//now redraw
	map_redraw();

	sdl_flip_mutex();
}

void map_zoom_out()
{
	int s, z, i;

	//check
	if ( map.zoom_level <= -ZOOM_MAX ) return;

	//set
	map.zoom_level--;
	z = game.zone;
	s = game.server_id;

	//spank all sectors
	for ( z=0;z<ZONE_MAX;z++ )
		if ( server[s].zone[z].name[0] )
			for ( i=0;i<SECTOR_MAX;i++ )
				if ( server[s].zone[z].sector[i].x )
				{
					server[s].zone[z].sector[i].x = ( int ) ( server[s].zone[z].sector[i].x * ZOOM_OUT_AMT );
					server[s].zone[z].sector[i].y = ( int ) ( server[s].zone[z].sector[i].y * ZOOM_OUT_AMT );
				}

	//forget no one
	map.shift_x = ( int ) ( map.shift_x * ZOOM_OUT_AMT );
	map.shift_y = ( int ) ( map.shift_y * ZOOM_OUT_AMT );

	map_set_local_sector_info();

	//now redraw
	map_redraw();

	sdl_flip_mutex();
}

void map_redraw()
{
	SDL_BlitSurface ( map.backround, NULL, screen, NULL );

	//hell ya
	map_draw_nebula_and_sun();

	//draw sectors ----------
	map_draw_sector_images();

	//draw connecting sector images
	map_draw_local_sectors();

	//draw scan stuff
	if ( map.scan_sector >= 0 )
		map_draw_scan();

	map_draw_planet_names();

	//sector userlist
	map_draw_hover_sector_userlist();

	//think so
	map_redraw_side_hud();

	//player count text
	map_draw_hud_stuff();

	//draw textbox
	select_text_box ( screen, &map.text_box );
}

void map_set_local_sector_info()
{
	int z, s, i;

	z = game.zone;
	s = game.sector;

	map.sector_x = server[game.server_id].zone[z].sector[s].x;
	map.sector_y = server[game.server_id].zone[z].sector[s].y;
	for ( i=0;i<5;i++ )
	{
		map.sector_link[i] = server[game.server_id].zone[z].sector[s].sector[i];

		if ( map.sector_link[i] >= 0 )
		{
			map.sector_link_x[i] = 400 + ( server[game.server_id].zone[z].sector[map.sector_link[i]].x - map.sector_x );
			map.sector_link_y[i] = 300 + ( server[game.server_id].zone[z].sector[map.sector_link[i]].y - map.sector_y );
			map.button[i].x = map.sector_link_x[i] - 10;
			map.button[i].y = map.sector_link_y[i] - 10;
			map.button[i].x += map.shift_x;
			map.button[i].y += map.shift_y;
		}
		else
		{
			map.button[i].x = 0;
			map.button[i].y = 0;
		}
	}
}

//*NEW lock map from moving, haha
void map_set_shift ( int x, int y, int button_down )
{
//	static int x_save, y_save;
//
//	if ( button_down )
//	{
//		if ( map_check_sector_on_map ( x,y ) )
//		{
//			x_save = x;
//			y_save = y;
//			map.do_shift = 1;
//		}
//	}
//	else if ( map.do_shift )
//	{
//		map.shift_x += x - x_save;
//		map.shift_y += y - y_save;
//
//		map.do_shift = 0;
//
//		map_set_local_sector_info();
//
//		//now redraw
//		map_redraw();
//
//		sdl_flip_mutex();
//	}
}

void map_draw_player_counts()
{
	char message[500];

	if(game.zone > -1 && game.zone < ZONE_MAX)
		sprintf(message, "Online :: %d | Zone :: %d | Launched :: %d", game.server_online_player_count, game.server_zone_player_count[game.zone], game.server_zone_launched_player_count[game.zone]);
	else
		sprintf(message, "Online :: %d", game.server_online_player_count);
	draw_center_label ( screen, message, &map.player_counts_label, 240, 240, 0 );
}

void map_draw_hud_stuff()
{
	char message[500];
	int i;
	//online users
	{
		if(game.zone > -1 && game.zone < ZONE_MAX)
			sprintf(message, "Online :: %d | Zone :: %d | Launched :: %d", game.server_online_player_count, game.server_zone_player_count[game.zone], game.server_zone_launched_player_count[game.zone]);
		else
			sprintf(message, "Online :: %d", game.server_online_player_count);

		draw_center_label ( screen, message, &map.player_counts_label, 240, 240, 0 );
	}


	//hull
	{
		SDL_Rect destination, ohull_box, ihull_box;

		ohull_box.x = 6;
		ohull_box.y = 564;
		ohull_box.w = 90;
		ohull_box.h = 16;
		ihull_box.x = 8;
		ihull_box.y = 566;
		ihull_box.w = ( int ) ( (ohull_box.w - 4.0) * game.ship[game.ship_sel].hull / game.ship[game.ship_sel].hull_max );
		ihull_box.h = 12;
		SDL_FillRect ( screen, &ohull_box, SDL_MapRGB ( screen->format, 167, 169, 23 ) );
		if ( game.ship[game.ship_sel].server_id > -1 )
			SDL_FillRect ( screen, &ihull_box, SDL_MapRGB ( screen->format, 246, 246, 62 ) );
	}

	//shield
	{
		//SDL_Rect dest;

		//dest.x = 86 + (space.shield_level * 19);
		//dest.y = 521;
		//dest.w = 14;
		//dest.h = 14;
		SDL_BlitSurface ( map.shield_on[space.shield_level], NULL, screen, &map.button[space.shield_level + B_MAP_SHIELD0] );
	}

	//being attacked
	{
		int being_attacked = 0;

		for ( i=0;i<40;i++ )
			if ( space.user[i].attacking == -2 )
			{
				being_attacked = 1;
				break;
			}

		if(being_attacked) draw_center_label ( screen,"Under Attack", &map.under_attack_label, 255, 0, 0 ); //kkkkkkkkkkkkkkkkkkkk
	}
}

void map_draw_scan()
{
	int i;

	//draw text
	draw_label ( screen, map.scan_label.message, &map.scan_label, 255, 255, 255 );

	//draw new area
	//check which selection box to draw
	if ( map.scan_sector == game.sector )
	{
		map.scan_location.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[map.scan_sector].x - map.sector_x ) ) - 19;
		map.scan_location.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[map.scan_sector].y - map.sector_y ) ) - 19;
		map.scan_location.w = 38;
		map.scan_location.h = 38;

		map.scan_location.x += map.shift_x;
		map.scan_location.y += map.shift_y;

		SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
		SDL_BlitSurface ( map.scan_large, NULL, screen, &map.scan_location );
	}
	else
	{
		for ( i=0;i<5;i++ )
			if ( map.sector_link[i] == map.scan_sector )
				break;

		if ( i==5 ) //its a tiny selection
		{
			map.scan_location.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[map.scan_sector].x - map.sector_x ) ) - 9;
			map.scan_location.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[map.scan_sector].y - map.sector_y ) ) - 9;
			map.scan_location.w = 18;
			map.scan_location.h = 18;

			map.scan_location.x += map.shift_x;
			map.scan_location.y += map.shift_y;

			if ( map.scan_location.x < 301 && map.scan_location.y < 28 ) //up left search field
			{
				map.scan_location.x = 308;
				map.scan_location.y = 30;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_up_left, NULL, screen, &map.scan_location );

				return;
			}
			if ( map.scan_location.x > 799 && map.scan_location.y < 1 ) //up right
			{
				map.scan_location.x = 800;
				map.scan_location.y = 3;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_up_right, NULL, screen, &map.scan_location );

				return;
			}
			if ( map.scan_location.x < 340 && map.scan_location.y > 558 ) //down left hull,shield,zone online,etc
			{
				map.scan_location.x = 344;
				map.scan_location.y = 534;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_down_left, NULL, screen, &map.scan_location );

				return;
			}
			if ( ( map.scan_location.x > 690 && map.scan_location.y > 560 ) || ( map.scan_location.x > 715 && map.scan_location.y > 565 ) ) // down right back button
			{
				map.scan_location.x = 697;
				map.scan_location.y = 569;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_down_right, NULL, screen, &map.scan_location );

				return;
			}
			//check for left/right/up/down
			if ( map.scan_location.y < 5 ) //up
			{
				map.scan_location.y = 10;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_up, NULL, screen, &map.scan_location );

				return;
			}
			if ( map.scan_location.y > 595 && map.scan_location.x >= 795 ) //down low
			{
				map.scan_location.y = 593;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_down, NULL, screen, &map.scan_location );

				return;
			}
			if ( map.scan_location.y > 595 && map.scan_location.x < 795 ) //down high
			{
				map.scan_location.y = 593;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_down, NULL, screen, &map.scan_location );

				return;
			}
			if ( map.scan_location.x >= 795 ) //right
			{
				map.scan_location.x = 793;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_right, NULL, screen, &map.scan_location );

				return;
			}
			if ( map.scan_location.x < 2 ) //left
			{
				map.scan_location.x = 4;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_left, NULL, screen, &map.scan_location );

				return;
			}

			SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
			SDL_BlitSurface ( map.scan_tiny, NULL, screen, &map.scan_location );
		}
		else //its a "small" neighbooring selection
		{
			map.scan_location.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[map.scan_sector].x - map.sector_x ) ) - 14;
			map.scan_location.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[map.scan_sector].y - map.sector_y ) ) - 14;
			map.scan_location.w = 28;
			map.scan_location.h = 28;

			map.scan_location.x += map.shift_x;
			map.scan_location.y += map.shift_y;

			SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
			SDL_BlitSurface ( map.scan_small, NULL, screen, &map.scan_location );
		}
	}
}

void map_set_scan ( int new_sector, char *message )
{
	int i;
	SDL_Rect temp_location;

	if ( map.visible )
	{
		//clear old scan
		if ( new_sector == -1 )
		{
			map.scan_sector = -1;
			map_redraw();
		}

		//draw text
		draw_label ( screen, message, &map.scan_label, 255, 255, 255 );

		//hub got fucked up
		if ( new_sector < 0 || new_sector >= SECTOR_MAX ) {sdl_flip_mutex(); return;}
		//nothing needs changed if...
		if ( map.scan_sector == new_sector ) {sdl_flip_mutex(); return;}

		//"redraw" old area
		if ( map.scan_sector >= 0 )
		{
			temp_location = map.scan_location;
			temp_location.x = 0;
			temp_location.y = 0;
			SDL_BlitSurface ( map.scan_last, &temp_location, screen, &map.scan_location );
		}



		//draw new area
		//check which selection box to draw
		if ( new_sector == game.sector )
		{
			map.scan_location.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[new_sector].x - map.sector_x ) ) - 19;
			map.scan_location.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[new_sector].y - map.sector_y ) ) - 19;
			map.scan_location.w = 38;
			map.scan_location.h = 38;
			map.scan_location.x += map.shift_x;
			map.scan_location.y += map.shift_y;

			SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
			SDL_BlitSurface ( map.scan_large, NULL, screen, &map.scan_location );

		}
		else
		{
			for ( i=0;i<5;i++ )
				if ( map.sector_link[i] == new_sector )
					break;

			if ( i==5 ) //its a tiny selection
			{
				map.scan_location.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[new_sector].x - map.sector_x ) ) - 9;
				map.scan_location.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[new_sector].y - map.sector_y ) ) - 9;
				map.scan_location.w = 18;
				map.scan_location.h = 18;
				map.scan_location.x += map.shift_x;
				map.scan_location.y += map.shift_y;

				if ( map.scan_location.x < 301 && map.scan_location.y < 28 ) //up left
				{
					map.scan_location.x = 308;
					map.scan_location.y = 30;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_up_left, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( map.scan_location.x > 799 && map.scan_location.y < 1 ) //up right
				{
					map.scan_location.x = 800;
					map.scan_location.y = 3;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_up_right, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( map.scan_location.x < 340 && map.scan_location.y > 558 ) //down left
				{
					map.scan_location.x = 344;
					map.scan_location.y = 534;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_down_left, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( ( map.scan_location.x > 690 && map.scan_location.y > 560 ) || ( map.scan_location.x > 715 && map.scan_location.y > 565 ) ) // down right
				{
					map.scan_location.x = 697;
					map.scan_location.y = 569;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_down_right, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				//check for left/right/up/down
				if ( map.scan_location.y < 5 ) //up
				{
					map.scan_location.y = 10;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_up, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( map.scan_location.y > 595 && map.scan_location.x >= 795 ) //down low
				{
					map.scan_location.y = 593;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_down, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( map.scan_location.y > 595 && map.scan_location.x < 795 ) //down high
				{
					map.scan_location.y = 593;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_down, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( map.scan_location.x >= 795 ) //right
				{
					map.scan_location.x = 793;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_right, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}
				if ( map.scan_location.x <= 2 ) //left
				{
					map.scan_location.x = 4;

					SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
					SDL_BlitSurface ( map.scan_left, NULL, screen, &map.scan_location );

					map.scan_sector = new_sector;
					return;
				}

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_tiny, NULL, screen, &map.scan_location );
			}
			else //its a "small" neighbooring selection
			{
				map.scan_location.x = ( 400 + ( server[game.server_id].zone[game.zone].sector[new_sector].x - map.sector_x ) ) - 14;
				map.scan_location.y = ( 300 + ( server[game.server_id].zone[game.zone].sector[new_sector].y - map.sector_y ) ) - 14;
				map.scan_location.w = 28;
				map.scan_location.h = 28;
				map.scan_location.x += map.shift_x;
				map.scan_location.y += map.shift_y;

				SDL_BlitSurface ( screen, &map.scan_location, map.scan_last, NULL );
				SDL_BlitSurface ( map.scan_small, NULL, screen, &map.scan_location );
			}
		}

		//set stuff
		map.scan_sector = new_sector;
	}
	else //map not visible
	{
		//set for when map is loaded
		strcpy ( map.scan_label.message, message );
		map.scan_sector = new_sector;
	}

}

void map_draw_hover_sector_userlist()
{
	SDL_Rect location;

	if(map.mouse_over_sector == -1) return;
	if(!game.sector_userlist[game.zone][map.mouse_over_sector].size()) return;

	location.x = 400 + ( server[game.server_id].zone[game.zone].sector[map.mouse_over_sector].x - map.sector_x );
	location.y = 300 + ( server[game.server_id].zone[game.zone].sector[map.mouse_over_sector].y - map.sector_y );
	location.x += map.shift_x;
	location.y += map.shift_y;

	location.x += 15;
	location.y += 15;

	for(vector<map_sector_user>::iterator u=game.sector_userlist[game.zone][map.mouse_over_sector].begin(); u!=game.sector_userlist[game.zone][map.mouse_over_sector].end(); u++)
	{
		string message;

		message = u->guild + " :: " + u->username;

		draw_raw_label ( screen, (char *)message.c_str(), location, 0, 240, 0 );

		location.y += 14;
	}
}
