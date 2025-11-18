#include "main.h"
#include <sstream>
//Memory
struct login login;
struct create_char create_char;
struct leave_game leave_game;
struct select_server server_select;
struct planet planet;
struct gen_home gen_home;
struct velic_home velic_home;
struct hanger hanger;
struct shop shop;
struct bar bar;
struct repair repair;
struct launching launching;
struct landing landing;
struct space space;
struct map map;
struct death death;
struct trade trade;
struct guild_halls guild_halls;
struct guild_editor guild_editor;
struct guild_editor_more guild_editor_more;
struct guild_editor_more2 guild_editor_more2;
struct guild_listing guild_listing;
struct guild_bank guild_bank;
struct guild_register guild_register;
struct splash_screen splash_screen;
struct stat_viewer stat_viewer;
struct cb_info cb_info;
struct bounty bounty;
struct planet_sat planet_sat;
struct sat_editor sat_editor;
struct planet_editor planet_editor;
struct planet_guild planet_guild;
struct switch_server switch_server;
struct purchase_plans purchase_plans;
struct trade_items trade_items;

void set_forms_invisible()
{
	login.visible 		= 0;
	create_char.visible 	= 0;
	leave_game.visible 	= 0;
	server_select.visible	= 0;
	planet.visible 		= 0;
	gen_home.visible 	= 0;
	velic_home.visible 	= 0;
	hanger.visible 		= 0;
	shop.visible		= 0;
	bar.visible		= 0;
	repair.visible		= 0;
	launching.visible	= 0;
	landing.visible		= 0;
	space.visible		= 0;
	map.visible		= 0;
	death.visible		= 0;
	trade.visible		= 0;
	guild_halls.visible	= 0;
	guild_editor.visible	= 0;
	guild_editor_more.visible = 0;
	guild_editor_more2.visible = 0;
	guild_listing.visible	= 0;
	guild_bank.visible	= 0;
	guild_register.visible	= 0;
	splash_screen.visible	= 0;
	stat_viewer.visible	= 0;
	cb_info.visible		= 0;
	bounty.visible		= 0;
	planet_sat.visible  	= 0;
	sat_editor.visible 	= 0;
	planet_editor.visible 	= 0;
	planet_guild.visible 	= 0;
	switch_server.visible 	= 0;
	purchase_plans.visible	= 0;
	trade_items.visible = 0;
}

void load_purchase_plans()
{
	SDL_Rect destination;


	if ( !purchase_plans.backround )
		purchase_plans.backround = IMG_Load ( "graphics/purchase_plans.jpg" );

	destination.x = 400 - ( 480 / 2 );
	destination.y = 300 - ( 360 / 2 );

	set_forms_invisible();
	purchase_plans.visible = 1;
	SDL_BlitSurface ( purchase_plans.backround, NULL, screen, &destination );

	//screen only stuff
	draw_purchase_plans();

	//flip
	sdl_flip_mutex();
}

void button_purchase_plans ( int x, int y )
{
	int i;
	const int button_max = 2;

	for ( i=0;i<button_max;i++ )
		if ( x >= purchase_plans.button[i].x && x <= purchase_plans.button[i].x + purchase_plans.button[i].w && y >= purchase_plans.button[i].y && y <= purchase_plans.button[i].y + purchase_plans.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0: //exit
			load_planet ( planet.last_planet );
			break;
		case 1: //buy
			do_purchase_plan();
			break;
		default:
			break;
	}
}


void load_planet_guild()
{
	SDL_Rect destination;
	char temp_str[50];

	if ( !planet_guild.backround )
		planet_guild.backround = IMG_Load ( "graphics/planet_guild.jpg" );

	destination.x = 400 - 150;
	destination.y = 300 - ( 225 / 2 );

	set_forms_invisible();
	planet_guild.visible = 1;
	SDL_BlitSurface ( planet_guild.backround, NULL, screen, &destination );

	//screen only stuff

	//draw guild name
	draw_right_label ( screen, server[game.server_id].planet[planet.last_planet].guild, &planet_guild.guild_name_label, 107, 216, 210 );

	//draw guild cost
	sprintf ( temp_str,"Free" );

	draw_right_label ( screen, temp_str, &planet_guild.entry_cost_label, 107, 216, 210 );

	//draw user money
	sprintf ( temp_str,"%d", game.money );
	draw_right_label ( screen, temp_str, &planet_guild.money_label, 107, 216, 210 );

	//draw guild name
	draw_right_label ( screen, game.guild.name, &planet_guild.your_guild_name_label, 107, 216, 210 );

	sdl_flip_mutex();
}

void button_planet_guild ( int x, int y )
{
	int i;
	const int button_max = 2;

	for ( i=0;i<button_max;i++ )
		if ( x >= planet_guild.button[i].x && x <= planet_guild.button[i].x + planet_guild.button[i].w && y >= planet_guild.button[i].y && y <= planet_guild.button[i].y + planet_guild.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0://exit
			load_planet ( planet.last_planet );
			break;
		case 1:// enter guild
			send_hub_enter_planet_guild();
			break;
	}
}

void load_cb_info()
{
	if ( !cb_info.backround )
		cb_info.backround = IMG_Load ( "graphics/cbback.jpg" );

	set_forms_invisible();
	cb_info.visible = 1;
	SDL_BlitSurface ( cb_info.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_cb_info ( int x, int y )
{
	int i;
	const int button_max = 3;
	char rtn_str[10];

	for ( i=0;i<button_max;i++ )
		if ( x >= cb_info.button[i].x && x <= cb_info.button[i].x + cb_info.button[i].w && y >= cb_info.button[i].y && y <= cb_info.button[i].y + cb_info.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0: //leave
			load_planet ( planet.last_planet );
			break;
		case 1: //stat viewer
			load_stat_viewer();
			break;
		case 2: //bounty
			load_bounty();
			break;
	}
}

void load_stat_viewer()
{
	if ( !stat_viewer.backround )
	{
		stat_viewer.backround = IMG_Load ( "graphics/statback.jpg" );
		stat_viewer.class_img[0] = IMG_Load ( "graphics/velic_stat.jpg" );
		stat_viewer.class_img[1] = IMG_Load ( "graphics/gen_stat.jpg" );
		stat_viewer.pointer_img = IMG_Load ( "graphics/pointer.gif" );
		stat_viewer.sel_left = IMG_Load ( "graphics/seldown.jpg" );
		stat_viewer.sel_right = IMG_Load ( "graphics/selup.jpg" );
	}

	set_forms_invisible();
	stat_viewer.visible = 1;
	SDL_BlitSurface ( stat_viewer.backround, NULL, screen, NULL );

	//screen stuff only

	//draw textbox
	select_text_box ( screen, &stat_viewer.text_box );

	//draw stats
	stat_viewer_display_list();

	sdl_flip_mutex();

	//start rotation thread
	if ( !stat_viewer.thread )
		stat_viewer.thread = SDL_CreateThread ( stat_viewer_thread, NULL );
}

int stat_viewer_thread ( void *nothing )
{
	SDL_Rect destination;
	char temp_str[21], temp_filename[512];
	int i = 0;
	int s_id = -1, s_type = -1, s_kind = -1;

	destination.x = 85;
	destination.y = 335;

	while ( stat_viewer.visible )
	{
		//we loading shit?
		if ( stat_viewer.load_ship )
		{
			s_id = stat_viewer.s_id;
			s_type = stat_viewer.s_type;
			s_kind = stat_viewer.s_kind;
			stat_viewer.load_ship = 0;

			//set some stuff...
			stat_viewer_clear_ship_area();
			i=0;
		}

		//pissing on my face?
		if ( s_id < 0 ) continue;
		if ( s_type < 0 ) continue;
		if ( s_kind < 0 ) continue;

		//check if we need to load
		if ( !server[s_id].ship[s_type].ship_img[s_kind][i] )
		{
			sprintf ( temp_filename, "server/%s/shop/ships/%s/%s%d.JPG", server[s_id].servername, ship_name ( s_kind, temp_str ), server[s_id].ship[s_type].name, i + 1 );
			server[s_id].ship[s_type].ship_img[s_kind][i] = IMG_Load ( temp_filename );
		}

		//if no starting index then display the "no ship" img
		if ( !server[s_id].ship[s_type].ship_img[s_kind][0] )
		{
			if ( !shop.no_ship[s_kind] ) //load the image if not already.
			{
				sprintf ( temp_filename, "graphics/nif/nif_%s.jpg", ship_name ( s_kind, temp_str ) );
				shop.no_ship[s_kind] = IMG_Load ( temp_filename );
			}
			SDL_BlitSurface ( shop.no_ship[s_kind], NULL, screen, &destination );
		}
		else //image found so show it
		{
			if ( !server[s_id].ship[s_type].ship_img[s_kind][i] )
				shop.rotate_sell = 0; //Set back if you hit a premature end

			SDL_BlitSurface ( server[s_id].ship[s_type].ship_img[s_kind][i], NULL, screen, &destination );
		}

		i++;

		if ( i==16 )
			i=0;

#ifdef _M_IX86 //if linux or windows
		Sleep ( 75 );
#else
		usleep ( 50000 );
#endif

		sdl_flip_mutex();
	}


	stat_viewer.thread = NULL; //let everyone know it has exited
	return 0;
}

void button_stat_viewer ( int x, int y )
{
	int i;
	const int button_max = 16;
	char rtn_str[500];

	for ( i=0;i<button_max;i++ )
		if ( x >= stat_viewer.button[i].x && x <= stat_viewer.button[i].x + stat_viewer.button[i].w && y >= stat_viewer.button[i].y && y <= stat_viewer.button[i].y + stat_viewer.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0: //leave
			stat_viewer.visible = 0;

			//dont do a thing if the repair screen is still f'ing around
			while ( stat_viewer.thread )
				SDL_Delay ( 40 );

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
		case 1:
		case 2:
		case 3:
			//request list info
			sprintf ( rtn_str,"25,%d",i );
			send_con_hub ( rtn_str );
			break;
		default:
			//list selects
			sprintf ( rtn_str, "24,%s", stat_viewer.list_name_label[i-4].message );
			send_con_hub ( rtn_str );
			break;
		case 14: //left deco
			stat_viewer_left_deco();
			break;
		case 15: //right deco
			stat_viewer_right_deco();
			break;
	}
}

void key_stat_viewer ( int c )
{
	int i;
	char rtn_str[500];

	if ( c == 13 )
	{
		sprintf ( rtn_str, "24,%s", stat_viewer.text_box.message );
		send_con_hub ( rtn_str );
	}
	else
	{
		add_text_box ( screen, &stat_viewer.text_box, c );
		sdl_flip_mutex();
	}
}

void load_splash_screen()
{
	int i;
	SDL_Surface *blackout;
	SDL_Rect clear_space;
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	clear_space.x = 0;
	clear_space.y = 0;
	clear_space.h = 600;
	clear_space.w = 800;

	blackout = SDL_CreateRGBSurface ( SDL_HWSURFACE, 800, 600, 32, rmask, gmask, bmask, amask );
	SDL_FillRect ( blackout,&clear_space,SDL_MapRGBA ( blackout->format,0,0,0,10 ) );


	if ( !splash_screen.backround )
	{
		splash_screen.backround = IMG_Load ( "graphics/splashback.jpg" );
	}


	set_forms_invisible();
	splash_screen.visible = 1;
	SDL_BlitSurface ( splash_screen.backround, NULL, screen, NULL );
	sdl_flip_mutex();

	SDL_Delay ( 1000 );

	load_sounds();

	for ( i=0;i + 10<=150;i+=3 )
	{
		SDL_SetAlpha ( blackout, SDL_RLEACCEL | SDL_SRCALPHA, 10 + i );
		SDL_BlitSurface ( blackout, NULL, screen, NULL );
		sdl_flip_mutex();
		SDL_Delay ( 5 );
	}

}

void load_login()
{
	SDL_Surface *create_button;
	SDL_Surface *exit_button;
	SDL_Rect destination;
	int i;

	if ( !login.backround )
	{
		login.backround = IMG_Load ( "graphics/logback.jpg" );
		create_button = IMG_Load ( "graphics/newchar.png" );
		exit_button = IMG_Load ( "graphics/leave.png" );

		destination.x = 660;
		destination.y = 520;
		SDL_BlitSurface ( create_button, NULL, login.backround, &login.button[0] );
		SDL_BlitSurface ( exit_button, NULL, login.backround, &destination );
	}

	set_forms_invisible();
	login.visible = 1;
	SDL_BlitSurface ( login.backround, NULL, screen, NULL );

	for ( i=0;i<2;i++ )
		if ( login.text_box[i].selected )
			select_text_box ( screen, &login.text_box[i] );
		else
			unselect_text_box ( screen, &login.text_box[i] );

	draw_raw_label ( screen, login.label.message, login.label.location, 255, 255, 255 );

	sdl_flip_mutex();
}

void button_login ( int x, int y )
{
	int i, success = 0, button;

	for ( i=0;i<3;i++ )
		if ( x >= login.button[i].x && x <= login.button[i].x + login.button[i].w && y >= login.button[i].y && y <= login.button[i].y + login.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<2;i++ )
			if ( x >= login.text_box[i].location.x && x <= login.text_box[i].location.x + login.text_box[i].location.w && y >= login.text_box[i].location.y && y <= login.text_box[i].location.y + login.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
		switch ( i )
		{
			case 0: //create char
				load_create_char();
				break;
			case 1: //exit game
				load_leave_game();
				break;
		  //case 2:
				//load_switch_server();
				//break;
		}
	else
		switch ( i )
		{
			case 0: //top text_box
				if ( login.text_box[i].selected ) return;
				select_text_box ( screen, &login.text_box[i] );
				unselect_text_box ( screen, &login.text_box[1] );
				sdl_flip_mutex();
				break;
			case 1: //2nd text..
				if ( login.text_box[i].selected ) return;
				select_text_box ( screen, &login.text_box[i] );
				unselect_text_box ( screen, &login.text_box[0] );
				sdl_flip_mutex();
				break;
		}
}


void key_login ( int c )
{
	int i;
	char rtn_str[50] = "3,";

	if ( c == 9 ) //tab
	{
		if ( login.text_box[0].selected )
		{
			unselect_text_box ( screen, &login.text_box[0] );
			select_text_box ( screen, &login.text_box[1] );
			sdl_flip_mutex();
		}
		else
		{
			unselect_text_box ( screen, &login.text_box[1] );
			select_text_box ( screen, &login.text_box[0] );
			sdl_flip_mutex();
		}
	}
	else if ( c == 13 ) //enter
	{
		strcat ( rtn_str,login.text_box[0].message );
		strcat ( rtn_str,"," );
		strcat ( rtn_str,login.text_box[1].message );
		strcpy ( game.password,login.text_box[1].message );
		draw_label ( screen,"Processing, please wait ...", &login.label, 255, 255, 255 );
		send_con_hub ( rtn_str );
	}
	else
	{
		for ( i=0;i<2;i++ )
			if ( login.text_box[i].selected )
			{
				add_text_box ( screen, &login.text_box[i], c );
				sdl_flip_mutex();
			}
	}

}

void load_create_char()
{
	SDL_Surface *submit_button;
	int i;


	if ( !create_char.backround )
	{
		create_char.backround = IMG_Load ( "graphics/newback.jpg" );
		submit_button = IMG_Load ( "graphics/tBtn.png" );

		SDL_BlitSurface ( submit_button, NULL, create_char.backround, &create_char.button[0] );
	}

	set_forms_invisible();
	create_char.visible = 1;
	SDL_BlitSurface ( create_char.backround, NULL, screen, NULL );

	for ( i=0;i<6;i++ )
		if ( create_char.text_box[i].selected )
			select_text_box ( screen, &create_char.text_box[i] );
		else
			unselect_text_box ( screen, &create_char.text_box[i] );

	if ( create_char.label.message[0] != '\0' ) draw_raw_label ( screen, create_char.label.message, create_char.label.location, 240, 240, 0 ); //maybe

	sdl_flip_mutex();
}

void button_create_char ( int x, int y )
{
	int i, k, success = 0, button;

	for ( i=0;i<2;i++ )
		if ( x >= create_char.button[i].x && x <= create_char.button[i].x + create_char.button[i].w && y >= create_char.button[i].y && y <= create_char.button[i].y + create_char.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<6;i++ )
			if ( x >= create_char.text_box[i].location.x && x <= create_char.text_box[i].location.x + create_char.text_box[i].location.w && y >= create_char.text_box[i].location.y && y <= create_char.text_box[i].location.y + create_char.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
		switch ( i )
		{
			case 0: //submit creation
				send_create_char();
				break;
			case 1: //cancel
				load_login();
				break;
		}
	else
	{
		if ( create_char.text_box[i].selected ) return;
		select_text_box ( screen, &create_char.text_box[i] );
		for ( k=0;k<6;k++ )
			if ( k != i ) unselect_text_box ( screen, &create_char.text_box[k] );
		sdl_flip_mutex();
	}
}

void key_create_char ( int c )
{
	int i;

	if ( c == 9 ) //tab
	{
		for ( i=0;i<6;i++ )
			if ( create_char.text_box[i].selected ) break;

		unselect_text_box ( screen, &create_char.text_box[i] );

		if ( i==5 )
			{i=0;}
		else
			{i++;}

		select_text_box ( screen, &create_char.text_box[i] );
		sdl_flip_mutex();
	}
	else if ( c == 13 )
	{
		send_create_char();
	}
	else
	{
		for ( i=0;i<6;i++ )
			if ( create_char.text_box[i].selected )
			{
				add_text_box ( screen, &create_char.text_box[i], c );
				sdl_flip_mutex();
			}
	}

}

void load_leave_game()
{
	if ( !leave_game.backround )
		leave_game.backround = IMG_Load ( "graphics/exitback.jpg" );

	set_forms_invisible();
	leave_game.visible = 1;
	SDL_BlitSurface ( leave_game.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_leave_game ( int x, int y )
{
	exit ( 1 );
}

void load_server_select()
{
	int i;
	SDL_Rect destination;

	if ( !server_select.backround )
	{
		server_select.backround = IMG_Load ( "graphics/tBtn.png" );
		server_select.circle = IMG_Load ( "graphics/tBtn.png" );
		server_select.planetbut = IMG_Load ( "graphics/tBtn.png" );
	}

set_forms_invisible();
server_select.visible = 0;
game.server_id = server_select.server_id[i];
strcpy(game.server_address, server_select.server_ip[i]);
sdl_flip_mutex();
}

void button_server_select ( int x, int y )
{
	int i, success = 0, button;
	char temp_message[80];

	if ( x >= server_select.button.x && x <= server_select.button.x + server_select.button.w && y >= server_select.button.y && y <= server_select.button.y + server_select.button.h )
		{success = 1; button = 1;}

	if ( !success ) for ( i=0;i<15 && server_select.server_x[i] > 0 && server_select.server_y[i] > 0;i++ )
			if ( ( x >= server_select.server_x[i] && x <= server_select.server_x[i] + 20 && y >= server_select.server_y[i] && y <= server_select.server_y[i] + 20 ) || ( x >= server_select.server_x[i] + 20 && x <= server_select.server_x[i] + 160 && y >= server_select.server_y[i] + 20 && y <= server_select.server_y[i] + 40 ) )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
	{
		if ( planet.last_planet == -1 || !server_select.connected )
			load_leave_game();
		else
			load_planet ( planet.last_planet );
		return;
	}
	else
	{
		if ( server_select.connecting ) return;
		server_select.connecting = 1;
		game.server_id = server_select.server_id[i];

		strcpy(game.server_address, server_select.server_ip[i]);

		sprintf ( temp_message,"Warping to %s...", server_select.servername[i] );
		draw_label ( screen, temp_message, &server_select.label, 255, 255, 255 );
		sdl_flip_mutex();
	}
}

void load_planet_sat()
{
	SDL_Rect destination;
	char temp_str[200];

	if ( !planet_sat.backround )
	{
		planet_sat.backround = IMG_Load ( "graphics/satback.jpg" );
		planet_sat.planetbut = planet.planetbut;
	}

	set_forms_invisible();
	planet_sat.visible = 1;
	SDL_BlitSurface ( planet_sat.backround, NULL, screen, NULL );

	//screen only fool

	//label
	destination.x = 88;
	destination.y = 60;
	if ( !planet_sat.sat.guild_name[0] )
		sprintf ( temp_str, "This planet is currently unowned" );
	else
		sprintf ( temp_str, "This planet is currently under the control of the %s guild", planet_sat.sat.guild_name );
	draw_raw_label ( screen, temp_str, destination, 255, 255, 0 );

	//buttons
	//we own this sat? or under no control?
	if ( !planet_sat.sat.guild_name[0] )
	{
		SDL_BlitSurface ( planet_sat.planetbut, NULL, screen, &planet_sat.button[1] );
		draw_raw_center_label ( screen,"Satellite Maintenance", planet_sat.button[1], 255, 255, 255 );

		planet_sat.show_sat_editor = 1;
		planet_sat.show_planet_editor = 0;
	}
	else if ( str_match ( game.guild.name, planet_sat.sat.guild_name ) )
	{
		SDL_BlitSurface ( planet_sat.planetbut, NULL, screen, &planet_sat.button[1] );
		draw_raw_center_label ( screen,"Satellite Maintenance", planet_sat.button[1], 255, 255, 255 );

		SDL_BlitSurface ( planet_sat.planetbut, NULL, screen, &planet_sat.button[2] );
		draw_raw_center_label ( screen,"Planet Maintenance", planet_sat.button[2], 255, 255, 255 );

		planet_sat.show_sat_editor = 1;
		planet_sat.show_planet_editor = 1;
	}
	else
	{
		planet_sat.show_sat_editor = 0;
		planet_sat.show_planet_editor = 0;
	}


	sdl_flip_mutex();
}

void load_planet ( int planet_number )
{
	if ( !planet.backround )
	{
		planet.planetbut = IMG_Load ( "graphics/planetbut.jpg" );
		planet.exit = IMG_Load ( "graphics/exit.png" );
	}

	if ( planet_number != planet.last_planet )
	{
		int i, k, z;
		char temp_str[200];
		SDL_Rect destination;

		sprintf ( temp_str, "server/%s/backs/planet/planet%d.jpg", server[game.server_id].servername, planet_number );

		//spare us the memory leak
		if ( planet.backround && game.nif_image.no_planet_img != planet.backround )
			SDL_FreeSurface ( planet.backround );

		planet.backround = IMG_Load ( temp_str );

		if ( !planet.backround )
		{
			//load nif
			if ( !game.nif_image.no_planet_img )
				game.nif_image.no_planet_img = IMG_Load ( "graphics/nif/nif_planet.jpg" );

			planet.backround = IMG_Load ( "graphics/nif/nif_planet.jpg" );
		}

		destination.x = 88;
		destination.y = 60;
		sprintf ( temp_str, "Welcome to %s", server[game.server_id].planet[planet_number].name );
		draw_raw_label ( planet.backround, temp_str, destination, 255, 255, 0 );

		//clear the button stuff
		for ( i=0;i<PLANET_MAX_BUTTON;i++ )
		{
			planet.button_type[i] = -1;
			planet.button_zone[i] = -1;
		}

		for ( i=0;i<4;i++ ) //only 4 buttons are guarenteed to be written
			SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[i] );

		if ( planet_number == game.home_planet && game.home_id == game.server_id )
		{
			sprintf ( temp_str, "%s's Home", game.username );
			draw_raw_center_label ( planet.backround, temp_str, planet.button[0], 255, 255, 255 );
		}
		else
		{
			draw_raw_center_label ( planet.backround,"CB Information Banks", planet.button[0], 255, 255, 255 );
		}

		draw_raw_center_label ( planet.backround, server[game.server_id].planet[planet_number].bar_name, planet.button[1], 255, 255, 255 );
		if ( server[game.server_id].planet[planet_number].is_gate ) {
		draw_raw_center_label ( planet.backround,"Can't repair on gates", planet.button[2], 255, 0, 0 );
		} else {
        draw_raw_center_label ( planet.backround,"Repair", planet.button[2], 255, 255, 255 );
		}
		if ( server[game.server_id].planet[planet_number].is_gate ) //if is a normal gate
		{
			//no trade, sat or guild
			z = 0;
			if ( server[game.server_id].planet[planet_number].is_server_gate )
			{
				draw_raw_center_label ( planet.backround,"Warp to Server", planet.button[3+z], 255, 255, 255 );
				planet.button_type[3+z] = 5;
				planet.button_zone[3+z] = -2;
				z++;
			}

			for ( i=0;i<ZONE_MAX;i++ )
				if ( server[game.server_id].zone[i].name[0] != '\0' )
					for ( k=0;k<SECTOR_MAX;k++ )
						if ( server[game.server_id].zone[i].sector[k].planet == planet_number )
						{
							sprintf ( temp_str, "Warp to %s Zone", server[game.server_id].zone[i].name );
							if ( z > 0 ) SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[3 + z] ); //write new button if needed
							draw_raw_center_label ( planet.backround, temp_str, planet.button[3 + z], 255, 255, 255 );
							planet.button_type[3+z] = 4;
							planet.button_zone[3+z] = i;
							z++;
						}

		}
		else //normal planet
		{
			z = 0;
			draw_raw_center_label ( planet.backround,"Trade Center", planet.button[3], 255, 255, 255 );
			planet.button_type[3] = 0;

			if ( server[game.server_id].planet[planet_number].has_guild_halls )
			{
				SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[4 + z] );
				draw_raw_center_label ( planet.backround,"Guild Halls", planet.button[4 + z], 255, 255, 255 );
				planet.button_type[4 + z] = 1;
				z++;
			}

			if ( server[game.server_id].planet[planet_number].guild[0] != '\0' )
			{
				SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[4 + z] );
				sprintf ( temp_str, "%s Guild", server[game.server_id].planet[planet_number].guild );
				draw_raw_center_label ( planet.backround, temp_str, planet.button[4 + z], 255, 255, 255 );
				planet.button_type[4 + z] = 2;
				z++;
			}

			printf("server[game.server_id].planet[planet_number].ship_plan:%d\n", server[game.server_id].planet[planet_number].ship_plan);
			if ( server[game.server_id].planet[planet_number].ship_plan)
			{
				int the_plan;

				the_plan = server[game.server_id].planet[planet_number].ship_plan;

				if(the_plan > -1 && the_plan < SHIP_MAX)
				{
					SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[4 + z] );
					sprintf ( temp_str, "%s Plans", server[game.server_id].ship[the_plan].name);
					draw_raw_center_label ( planet.backround, temp_str, planet.button[4 + z], 255, 255, 255 );
					planet.button_type[4 + z] = 7;
					z++;
				}
			}

			//sat monkies
			SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[4 + z] );
			draw_raw_center_label ( planet.backround,"Satellite", planet.button[4 + z], 255, 255, 255 );
			planet.button_type[4 + z] = 3;
			z++;

			if ( server[game.server_id].planet[planet_number].is_server_gate )
			{
				SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[4 + z] );
				draw_raw_center_label ( planet.backround,"Warp to Server", planet.button[4+z], 255, 255, 255 );
				planet.button_type[4+z] = 5;
				planet.button_zone[4+z] = -2;
				z++;
			}

			SDL_BlitSurface ( planet.planetbut, NULL, planet.backround, &planet.button[4 + z] );
			draw_raw_center_label ( planet.backround,"Launch", planet.button[4 + z], 255, 255, 255 );
			planet.button_type[4 + z] = 4;
			planet.button_zone[4 + z] = -1;
		}

		SDL_BlitSurface ( planet.exit, NULL, planet.backround, &planet.button[PLANET_MAX_BUTTON] );

		planet.last_planet = planet_number;
	}

	//special little bit for the ship lost screen
	if ( !death.visible )
	{
		set_forms_invisible();
		planet.visible = 1;
		SDL_BlitSurface ( planet.backround, NULL, screen, NULL );
		sdl_flip_mutex();
	}
	else
	{
		death.okay = 1;
	}

	//good time to reset this
	space.show_ship = 1;
}

void button_sat_editor ( int x, int y )
{
	const int button_max = 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 7, text_box_max = 1;
	int i, success = 0, button;

	for ( i=0;i<button_max;i++ )
		if ( x >= sat_editor.button[i].x && x <= sat_editor.button[i].x + sat_editor.button[i].w && y >= sat_editor.button[i].y && y <= sat_editor.button[i].y + sat_editor.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<text_box_max;i++ )
			if ( x >= sat_editor.text_box[i].location.x && x <= sat_editor.text_box[i].location.x + sat_editor.text_box[i].location.w && y >= sat_editor.text_box[i].location.y && y <= sat_editor.text_box[i].location.y + sat_editor.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
		switch ( i )
		{
			case 0://exit
				load_planet_sat();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 0://upgrade/purchase
				sat_send_upgrade_purchase();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 1://viewing wep but
				sat_toggle_weapons_viewing();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 2://left
				sat_choose_left();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 3://right
				sat_choose_right();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 4://buy/sell
				sat_send_buy_sell();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 5://reload/repair
				sat_send_reload_repair();
				break;
			case 1 + ( SAT_LEVEL_MAX * SAT_GUN_INC ) + 6://reload/repair
				sat_send_bug_sat();
				break;
			default:
				sat_make_weapon_select ( i-1 );
				break;
		}
	else
	{
		;
	}
}

void button_planet_editor ( int x, int y )
{
	int i;
	const int button_max = 1;

	for ( i=0;i<button_max;i++ )
		if ( x >= planet_editor.button[i].x && x <= planet_editor.button[i].x + planet_editor.button[i].w && y >= planet_editor.button[i].y && y <= planet_editor.button[i].y + planet_editor.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0://exit
			load_planet_sat();
			break;
	}
}

void button_planet_sat ( int x, int y )
{
	int i;
	const int button_max = 3;

	for ( i=0;i<button_max;i++ )
		if ( x >= planet_sat.button[i].x && x <= planet_sat.button[i].x + planet_sat.button[i].w && y >= planet_sat.button[i].y && y <= planet_sat.button[i].y + planet_sat.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0://exit
			load_planet ( planet.last_planet );
			break;
		case 1:// sat editor
			if ( !planet_sat.show_sat_editor ) break;
			load_sat_editor();
			break;
		case 2:// planet editor
			if ( !planet_sat.show_planet_editor ) break;
			load_planet_editor();
			break;
	}
}

void button_planet ( int x, int y )
{
	int i;
	char launch_msg[8];
	const int button_max = 1+PLANET_MAX_BUTTON;

	for ( i=0;i<button_max;i++ )
		if ( x >= planet.button[i].x && x <= planet.button[i].x + planet.button[i].w && y >= planet.button[i].y && y <= planet.button[i].y + planet.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0: //but1 CB or home
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
			else
			{
				load_cb_info();//load CB form
			}
			break;
		case 1: //bar
			load_bar();
			break;
		case 2: //repair
			load_repair();
			break;
		case PLANET_MAX_BUTTON: //exit
			load_leave_game();
			break;
		default:
			switch ( planet.button_type[i] )
			{
				case 0: //Trade
					load_trade();
					break;
				case 1: //Guild Halls
					load_guild_halls();
					break;
				case 2: //Guild Join
					load_planet_guild();
					break;
				case 3: //Sat
					load_planet_sat();
					break;
				case 4: //Launch
					if ( game.ship[game.ship_sel].server_id == -1 ) break;
					load_launching();
					sprintf ( launch_msg, "6,%d", planet.button_zone[i] );
					send_con_server ( launch_msg );
					break;
				case 5: //Server Select
					load_server_select();
					break;
				case 6: //hanger
					load_hanger();
					break;
				case 7: //ship plans
					load_purchase_plans();
					break;
			}
			break;
	}
}

void load_gen_home()
{
	if ( !gen_home.backround )
		gen_home.backround = IMG_Load ( "graphics/genback.jpg" );

	set_forms_invisible();
	gen_home.visible = 1;
	SDL_BlitSurface ( gen_home.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_gen_home ( int x, int y )
{
	int i;

	for ( i=0;i<6;i++ )
		if ( x >= gen_home.button[i].x && x <= gen_home.button[i].x + gen_home.button[i].w && y >= gen_home.button[i].y && y <= gen_home.button[i].y + gen_home.button[i].h )
			break;

	if ( i == 6 ) return;

	switch ( i )
	{
		case 0: //hanger
			load_hanger();
			break;
		case 1: //new pass
			break;
		case 2: //message
			break;
		case 3: //stats
			load_stat_viewer();
			break;
		case 4: //bounty
			load_bounty();
			break;
		case 5: //leave
			load_planet ( planet.last_planet );
			break;
	}
}

void load_velic_home()
{
	if ( !velic_home.backround )
		velic_home.backround = IMG_Load ( "graphics/velicback.jpg" );

	set_forms_invisible();
	velic_home.visible = 1;
	SDL_BlitSurface ( velic_home.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_velic_home ( int x, int y )
{
	int i;

	for ( i=0;i<6;i++ )
		if ( x >= velic_home.button[i].x && x <= velic_home.button[i].x + velic_home.button[i].w && y >= velic_home.button[i].y && y <= velic_home.button[i].y + velic_home.button[i].h )
			break;

	if ( i == 6 ) return;

	switch ( i )
	{
		case 0: //hanger
			load_hanger();
			break;
		case 1: //new pass
			break;
		case 2: //message
			break;
		case 3: //stats
			load_stat_viewer();
			break;
		case 4: //bounty
			load_bounty();
			break;
		case 5: //leave
			load_planet ( planet.last_planet );
			break;
	}
}

void load_trade()
{
	SDL_Rect destination;
	int i;
	char temp_str[32];

	if ( !trade.backround )
	{
		trade.backround = IMG_Load ( "graphics/tradeback.jpg" );
		trade.nif_trade = IMG_Load ( "graphics/nif/nif_trade.jpg" );
		trade.large_good[0] = IMG_Load ( "graphics/gpic1.jpg" );
		trade.large_good[1] = IMG_Load ( "graphics/gpic2.jpg" );
		trade.large_good[2] = IMG_Load ( "graphics/gpic3.jpg" );
		trade.large_good[3] = IMG_Load ( "graphics/gpic4.jpg" );
		trade.large_good[4] = IMG_Load ( "graphics/gpic5.jpg" );
		trade.large_good[5] = IMG_Load ( "graphics/gpic6.jpg" );
		trade.large_good[6] = IMG_Load ( "graphics/gpic7.jpg" );
		trade.large_good[7] = IMG_Load ( "graphics/gpic8.jpg" );
		trade.large_good[8] = IMG_Load ( "graphics/gpic9.jpg" );
		trade.large_good[9] = IMG_Load ( "graphics/gpic10.jpg" );
		trade.goto_trade_but = IMG_Load ( "graphics/exit_trade_news_but.jpg" );
		trade.goto_news_but = IMG_Load ( "graphics/goto_trade_news_but.jpg" );
		trade.sell_all_but = IMG_Load ( "graphics/trade_sell_all_but.jpg" );

		load_good_images();
	}

	if ( trade.last_planet != planet.last_planet )
	{
		SDL_Surface *trade_img;
		char temp_str[200];

		sprintf ( temp_str, "server/%s/backs/trade/bar%d.jpg", server[game.server_id].servername, planet.last_planet );
		trade_img = IMG_Load ( temp_str );
		destination.x = 115;
		destination.y = 148;

		if ( trade_img )
			SDL_BlitSurface ( trade_img, NULL, trade.backround, &destination );
		else
			SDL_BlitSurface ( trade.nif_trade, NULL, trade.backround, &destination );
	}

	set_forms_invisible();
	trade.visible = 1;
	trade.last_planet = planet.last_planet;
	SDL_BlitSurface ( trade.backround, NULL, screen, NULL );

	//Just alittle curious
	sprintf ( temp_str,"%d", game.money );
	draw_right_label ( screen, temp_str, &trade.money_label, 107, 216, 210 );

	sprintf ( temp_str,"%d", game.ship[game.ship_sel].cargo - ship_total_good_ammount ( game.ship_sel ) );
	draw_right_label ( screen, temp_str, &trade.cargo_label, 107, 216, 210 );

	//draw in the shop..
	trade_draw_news_or_shop();

	sdl_flip_mutex();
}

void button_trade ( int x, int y )
{
	int i, success = 0, button;

	for ( i=0;i<13;i++ )
		if ( x >= trade.button[i].x && x <= trade.button[i].x + trade.button[i].w && y >= trade.button[i].y && y <= trade.button[i].y + trade.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<2;i++ )
			if ( x >= trade.text_box[i].location.x && x <= trade.text_box[i].location.x + trade.text_box[i].location.w && y >= trade.text_box[i].location.y && y <= trade.text_box[i].location.y + trade.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
	{
		switch ( i )
		{
			default:
				if ( trade.viewing_news ) break;
				trade_draw_selection ( i );
				sdl_flip_mutex();
				break;
			case 10: //exit
				load_planet ( planet.last_planet );
				break;
			case 11: //news/trade
				trade_toggle_news_and_shop();
				break;
			case 12: //sell all
				if ( !trade.viewing_news )
					trade_sell_all_goods();
				break;
		}
	}
	else
	{
		switch ( i )
		{
			case 0: //top text_box
				if ( trade.text_box[0].selected ) return;
				select_text_box ( screen, &trade.text_box[0] );
				unselect_text_box ( screen, &trade.text_box[1] );
				sdl_flip_mutex();
				break;
			case 1: //2nd text..
				if ( trade.text_box[1].selected ) return;
				select_text_box ( screen, &trade.text_box[1] );
				unselect_text_box ( screen, &trade.text_box[0] );
				sdl_flip_mutex();
				break;
		}
	}
}

void key_trade ( int c )
{
	int i;
	char rtn_str[32];

	if ( c == 9 ) //tab
	{
		if ( trade.text_box[0].selected )
		{
			unselect_text_box ( screen, &trade.text_box[0] );
			select_text_box ( screen, &trade.text_box[1] );
			sdl_flip_mutex();
		}
		else
		{
			unselect_text_box ( screen, &trade.text_box[1] );
			select_text_box ( screen, &trade.text_box[0] );
			sdl_flip_mutex();
		}
	}
	else if ( c == 13 )
	{
		if ( trade.text_box[0].selected )
		{
			sprintf ( rtn_str,"17,%d,%d", trade.good_selected, atoi ( trade.text_box[0].message ) );
			send_con_hub ( rtn_str );
			clear_text_box ( screen, &trade.text_box[0] );
			sdl_flip_mutex();
		}
		else
		{
			sprintf ( rtn_str,"18,%d,%d", trade.good_selected, atoi ( trade.text_box[1].message ) );
			send_con_hub ( rtn_str );
			clear_text_box ( screen, &trade.text_box[1] );
			sdl_flip_mutex();
		}
	}
	else if ( ( c >= '0' && c <= '9' ) || c == 8 || c == 127 || c == 275 || c == 276 )
	{
		for ( i=0;i<2;i++ )
			if ( trade.text_box[i].selected )
			{
				add_text_box ( screen, &trade.text_box[i], c );
				sdl_flip_mutex();
			}
	}
}

void load_repair()
{
	SDL_Rect destination, ohull_box, ihull_box;
	int i;
	char temp_str[30];
	if ( !repair.backround )
	{
		repair.backround = IMG_Load ( "graphics/repairback.jpg" );
		repair.reload_wep_img = IMG_Load ( "graphics/reload_wep.jpg" );
		repair.repair_wep_img = IMG_Load ( "graphics/repair_wep.jpg" );
		repair.repair_ship_img = IMG_Load ( "graphics/repair_ship.jpg" );
	}

	if ( repair.last_planet != planet.last_planet )
	{
		SDL_Surface *repair_img;
		char temp_str[200];

		sprintf ( temp_str, "server/%s/backs/repair/rep%d.jpg", server[game.server_id].servername, planet.last_planet );
		repair_img = IMG_Load ( temp_str );
		destination.x = 91;
		destination.y = 124;

		if ( !repair_img )
		{
			if ( !game.nif_image.no_repair_img )
				game.nif_image.no_repair_img = IMG_Load ( "graphics/nif/nif_repair.jpg" );

			repair_img = game.nif_image.no_repair_img;
		}

		SDL_BlitSurface ( repair_img, NULL, repair.backround, &destination );

		if ( repair_img != game.nif_image.no_repair_img )
			SDL_FreeSurface ( repair_img );
	}

	//draw weapons if requested.
	if ( repair.redraw_weapons )
    repair_draw_weapons();

	set_forms_invisible();
	repair.visible = 1;
	repair.last_planet = planet.last_planet;
	SDL_BlitSurface ( repair.backround, NULL, screen, NULL );
	//----------------------------------------------------
	//screen only stuff

	//show money
	sprintf ( temp_str,"%d", game.money );
	draw_right_label ( screen, temp_str, &repair.money_label, 82, 177, 188 );

	//draw hull box
	ohull_box.x = 470;
	ohull_box.y = 82;
	ohull_box.w = 180;
	ohull_box.h = 16;
	ihull_box.x = 472;
	ihull_box.y = 84;
	ihull_box.w = ( int ) ( 176.0 * game.ship[game.ship_sel].hull / game.ship[game.ship_sel].hull_max );
	ihull_box.h = 12;
	SDL_FillRect ( screen, &ohull_box, SDL_MapRGB ( screen->format, 167, 169, 23 ) );
	if ( game.ship[game.ship_sel].server_id > -1 )
		SDL_FillRect ( screen, &ihull_box, SDL_MapRGB ( screen->format, 246, 246, 62 ) );

	if ( game.ship[game.ship_sel].server_id > -1 && game.ship[game.ship_sel].type > -1 && game.ship[game.ship_sel].kind > -1 )
	{
		//draw repair button if needed
		if ( game.ship[game.ship_sel].hull_max - game.ship[game.ship_sel].hull > 0 )
			SDL_BlitSurface ( repair.repair_ship_img, NULL, screen, &repair.button[1] );

		//draw damage cost
		sprintf ( temp_str,"%d", ( game.ship[game.ship_sel].hull_max - game.ship[game.ship_sel].hull ) * 10 );
		draw_right_label ( screen, temp_str, &repair.cost_label, 82, 177, 188 );
	}

	//draw all gun/missile rep buttons
	if ( game.ship[game.ship_sel].server_id >= 0 && game.ship[game.ship_sel].type >= 0 && game.ship[game.ship_sel].kind >= 0 )
	{
		for ( i=0;i<game.ship[game.ship_sel].gun_ammount;i++ )
			if ( game.ship[game.ship_sel].gun_destroyed[i] && game.ship[game.ship_sel].gun[i] > -1 )
				SDL_BlitSurface ( repair.repair_wep_img, NULL, screen, &repair.button[2 + i] );

		for ( i=0;i<game.ship[game.ship_sel].missile_ammount;i++ )
			if ( game.ship[game.ship_sel].missile_left[i] < 4 && game.ship[game.ship_sel].missile[i] > -1 )
				SDL_BlitSurface ( repair.reload_wep_img, NULL, screen, &repair.button[18 + i] );
	}

	sdl_flip_mutex();

	//start rotation thread
	if ( !repair.thread )
		repair.thread = SDL_CreateThread ( repair_thread, NULL );
}

int repair_thread ( void *nothing )
{
	SDL_Rect destination;
	char temp_str[21], temp_filename[512];
	int i = 0;

	//make sure it is set first
	while ( !repair.thread ) SDL_Delay ( 40 );

	if ( game.ship[game.ship_sel].server_id < 0 ) 	{repair.thread = NULL; return 0;}
	if ( game.ship[game.ship_sel].type < 0 ) 		{repair.thread = NULL; return 0;}
	if ( game.ship[game.ship_sel].kind < 0 ) 		{repair.thread = NULL; return 0;}

	destination.x = 85;
	destination.y = 335;

	while ( repair.visible )
	{
		//check if we need to load
		if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][i] )
		{
			sprintf ( temp_filename, "server/%s/shop/ships/%s/%s%d.JPG", server[game.ship[game.ship_sel].server_id].servername, ship_name ( game.ship[game.ship_sel].kind, temp_str ), server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].name, i + 1 );
			server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][i] = IMG_Load ( temp_filename );
		}

		//if no starting index then display the "no ship" img
		if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][0] )
		{
			if ( !shop.no_ship[game.ship[game.ship_sel].kind] ) //load the image if not already.
			{
				sprintf ( temp_filename, "graphics/nif/nif_%s.jpg", ship_name ( game.ship[game.ship_sel].kind, temp_str ) );
				shop.no_ship[game.ship[game.ship_sel].kind] = IMG_Load ( temp_filename );
			}
			SDL_BlitSurface ( shop.no_ship[game.ship[game.ship_sel].kind], NULL, screen, &destination );

			sdl_flip_mutex();//if the purchase half wont flip the screen then do it here..

			//and exit this thread, its job here is done.
			repair.thread = NULL;
			return 0;
		}
		else //image found so show it
		{
			if ( !server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][i] )
				shop.rotate_sell = 0; //Set back if you hit a premature end

			SDL_BlitSurface ( server[game.ship[game.ship_sel].server_id].ship[game.ship[game.ship_sel].type].ship_img[game.ship[game.ship_sel].kind][i], NULL, screen, &destination );
		}

		i++;

		if ( i==16 ) i=0;

#ifdef _WIN32 //if linux or windows
		Sleep ( 75 );
#else
		usleep ( 50000 );
#endif

		sdl_flip_mutex();
	}


	repair.thread = NULL; //let everyone know it has exited
	return 0;
}

void load_launching()
{
	set_forms_invisible();
	launching.visible = 1;
	SDL_BlitSurface ( launching.backround, NULL, screen, NULL );
	sdl_flip_mutex();

	//may need removal, can't decide right now
	check_to_load_server_sun_damages();
}

void load_landing()
{

	stop_sound_repeat ( sound_engine );
	set_forms_invisible();
	landing.visible = 1;
	SDL_BlitSurface ( landing.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_repair ( int x, int y )
{
	int i;
	char rtn_str[20];

	for ( i=0;i<34;i++ )
		if ( x >= repair.button[i].x && x <= repair.button[i].x + repair.button[i].w && y >= repair.button[i].y && y <= repair.button[i].y + repair.button[i].h )
			break;

	if ( i == 34 ) return;

	switch ( i )
	{
		case 0: //exit
			repair.visible = 0;

			//dont do a thing if the repair screen is still f'ing around
			while ( repair.thread )
				SDL_Delay ( 40 );

			load_planet ( planet.last_planet );
			break;
		case 1: //repair ship
			if ( game.ship[game.ship_sel].hull_max - game.ship[game.ship_sel].hull < 0 ) break;

			strcpy ( rtn_str,"13," );
			send_con_hub ( rtn_str );
			break;
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
		case 17: //gun repair
			if ( !game.ship[game.ship_sel].gun_destroyed[i-2] ) break;
			sprintf ( rtn_str,"15,%d", i-2 );
			send_con_hub ( rtn_str );
			break;
		default: //missile restock
			if ( game.ship[game.ship_sel].missile_left[i-18] >= 4 ) break;
			sprintf ( rtn_str,"16,%d", i-18 );
			send_con_hub ( rtn_str );
			break;
	}
}

void load_death()
{
	//sound...
	stop_sound_repeat ( sound_engine );

	if ( !death.backround )
		death.backround = IMG_Load ( "graphics/shiplost.png" );

	set_forms_invisible();
	death.visible = 1;
	SDL_BlitSurface ( death.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_death ( int x, int y )
{
	if ( death.okay )
	{
		//crude planet screen loader
		death.okay = 0;

		set_forms_invisible();
		planet.visible = 1;
		SDL_BlitSurface ( planet.backround, NULL, screen, NULL );
		sdl_flip_mutex();
	}
}

void load_guild_halls()
{
	if ( !guild_halls.backround )
	{
		guild_halls.backround = IMG_Load ( "graphics/guildhalls.jpg" );
		game.game_image.guild_toggle_off = IMG_Load ( "graphics/guild_off.jpg" );
		game.game_image.guild_toggle_on = IMG_Load ( "graphics/guild_on.jpg" );
	}

	set_forms_invisible();
	guild_halls.visible = 1;
	SDL_BlitSurface ( guild_halls.backround, NULL, screen, NULL );
	sdl_flip_mutex();
}

void button_guild_halls ( int x, int y )
{
	int i;
	char rtn_str[20];

	for ( i=0;i<5;i++ )
		if ( x >= guild_halls.button[i].x && x <= guild_halls.button[i].x + guild_halls.button[i].w && y >= guild_halls.button[i].y && y <= guild_halls.button[i].y + guild_halls.button[i].h )
			break;

	if ( i == 5 ) return;

	switch ( i )
	{
		case 0: //exit
			load_planet ( planet.last_planet );
			break;
		case 1: //bank
			load_guild_bank();
			break;
		case 2: //listings
			load_guild_listing();
			break;
		case 3: //registry
			load_guild_register();
			break;
		case 4: //editor
			load_guild_editor();
			break;
	}
}

void load_sat_editor()
{
	SDL_Rect destination;

	if ( !sat_editor.backround )
	{
		sat_editor.backround = IMG_Load ( "graphics/sateditor.jpg" );
		sat_editor.empty_pod = IMG_Load ( "graphics/empty_pod.jpg" );
		sat_editor.sat_upgrade_but = IMG_Load ( "graphics/sat_upgrade_but.jpg" );
		sat_editor.sat_bug_but = IMG_Load ( "graphics/sat_bug_but.jpg" );
		sat_editor.sat_purchase_but = IMG_Load ( "graphics/sat_purchase_but.jpg" );
		sat_editor.wep_left_but = IMG_Load ( "graphics/seldown.jpg" );
		sat_editor.wep_right_but = IMG_Load ( "graphics/selup.jpg" );
		sat_editor.wep_buy_but = IMG_Load ( "graphics/sat_wep_buy_but.jpg" );
		sat_editor.wep_sell_but = IMG_Load ( "graphics/sat_wep_sell_but.jpg" );
		sat_editor.wep_repair_but = IMG_Load ( "graphics/sat_wep_repair_but.jpg" );
		sat_editor.wep_reload_but = IMG_Load ( "graphics/sat_wep_reload_but.jpg" );
		sat_editor.viewing_guns_img = IMG_Load ( "graphics/view_guns.jpg" );
		sat_editor.viewing_missiles_img = IMG_Load ( "graphics/view_missiles.jpg" );
	}

	destination.x = 400 - ( 480 / 2 );
	destination.y = 300 - ( 360 / 2 );

	set_forms_invisible();
	sat_editor.visible = 1;
	SDL_BlitSurface ( sat_editor.backround, NULL, screen, &destination );

	//screen only shit
	sat_editor_redraw_entire_screen();

	sdl_flip_mutex();
}

void load_planet_editor()
{
	SDL_Rect destination;

	if ( !planet_editor.backround )
	{
		planet_editor.backround = IMG_Load ( "graphics/planeteditor.jpg" );
	}

	destination.x = 400 - ( 480 / 2 );
	destination.y = 300 - ( 360 / 2 );

	set_forms_invisible();
	planet_editor.visible = 1;
	SDL_BlitSurface ( planet_editor.backround, NULL, screen, &destination );

	//screen only stuff
	//guild_editor_reset_variables();
	//guild_editor_reset_text_boxes();
	//guild_editor_reset_toggles();

	sdl_flip_mutex();
}

void load_guild_listing()
{
	if ( !guild_listing.backround )
	{
		guild_listing.backround = IMG_Load ( "graphics/guildlisting.jpg" );
		guild_listing.next_on = IMG_Load ( "graphics/guild_listing_next.jpg" );
		guild_listing.next_off = IMG_Load ( "graphics/guild_listing_next_grey.jpg" );
		guild_listing.prev_on = IMG_Load ( "graphics/guild_listing_previous.jpg" );
		guild_listing.prev_off = IMG_Load ( "graphics/guild_listing_previous_grey.jpg" );

		if ( !game.game_image.guild_toggle_off ) game.game_image.guild_toggle_off = IMG_Load ( "graphics/guild_off.jpg" );
		if ( !game.game_image.guild_toggle_on ) game.game_image.guild_toggle_on = IMG_Load ( "graphics/guild_on.jpg" );
	}

	set_forms_invisible();
	guild_listing.visible = 1;
	SDL_BlitSurface ( guild_listing.backround, NULL, screen, NULL );

	//screen only

	//clear some stuff
	guild_listing_reset_variables();

	//textbox
	select_text_box ( screen, &guild_listing.text_box );

	sdl_flip_mutex();

	//ask for the list
	guild_listing_request_list();
}

void load_guild_bank()
{
	SDL_Rect destination;
	char money_str[50];

	if ( !guild_bank.backround )
		guild_bank.backround = IMG_Load ( "graphics/guildbank.jpg" );

	destination.x = 400 - 150;
	destination.y = 300 - ( 225 / 2 );

	set_forms_invisible();
	guild_bank.visible = 1;
	SDL_BlitSurface ( guild_bank.backround, NULL, screen, &destination );

	select_text_box ( screen, &guild_bank.text_box );
	guild_bank.money_label.message[0] = '\0';
	guild_bank.balance_label.message[0] = '\0';
	sprintf ( money_str,"%d",game.money );
	draw_label ( screen, money_str, &guild_bank.money_label, 0, 240, 240 );
	sprintf ( money_str,"%d",game.guild_balance );
	draw_label ( screen, money_str, &guild_bank.balance_label, 0, 240, 240 );

	sdl_flip_mutex();
}

void load_guild_register()
{
	SDL_Rect destination;

	if ( !guild_register.backround )
		guild_register.backround = IMG_Load ( "graphics/guildregister.jpg" );

	destination.x = 400 - 150;
	destination.y = 300 - ( 225 / 2 );

	set_forms_invisible();
	guild_register.visible = 1;
	SDL_BlitSurface ( guild_register.backround, NULL, screen, &destination );

	select_text_box ( screen, &guild_register.text_box );
	guild_register.info_label.message[0] = '\0';
	draw_center_label ( screen,"Enter new guild and hit enter.", &guild_register.info_label, 0, 240, 240 );


	sdl_flip_mutex();
}

void key_sat_editor ( int c )
{
	int i;
	const int text_box_max = 1;

	if ( c==13 )
	{
		sat_send_deposit ( atoi ( sat_editor.text_box[0].message ) );//send

		//clear
		clear_text_box ( screen, &sat_editor.text_box[0] );
		sdl_flip_mutex();
	}
	else
	{
		if ( ! ( c >= '0' && c <= '9' ) && ! ( c == 8 || c == 127 || c == 275 || c == 276 ) ) return;

		add_text_box ( screen, &sat_editor.text_box[0], c );
		sdl_flip_mutex();
	}

}

void button_guild_listing ( int x, int y )
{
	int i;
	const int button_max = 6 + MAX_GUILD_LISTING;

	for ( i=0;i<button_max;i++ )
		if ( x >= guild_listing.button[i].x && x <= guild_listing.button[i].x + guild_listing.button[i].w && y >= guild_listing.button[i].y && y <= guild_listing.button[i].y + guild_listing.button[i].h )
			break;

	if ( i == button_max ) return;

	switch ( i )
	{
		case 0: //exit
			load_guild_halls();
			break;
		case 1: //sort name
			guild_listing_sort_name();
			break;
		case 2: //sort worth
			guild_listing_sort_worth();
			break;
		case 3: //sort players
			guild_listing_sort_players();
			break;
		case 4: //previous
			guild_listing_previous();
			break;
		case 5: //next
			guild_listing_next();
			break;
		default:
			guild_listing_select_guild ( i-6 );
			break;
	}
}

void button_guild_bank ( int x, int y )
{
	int i;
	char rtn_str[500];

	for ( i=0;i<3;i++ )
		if ( x >= guild_bank.button[i].x && x <= guild_bank.button[i].x + guild_bank.button[i].w && y >= guild_bank.button[i].y && y <= guild_bank.button[i].y + guild_bank.button[i].h )
			break;

	if ( i == 3 ) return;

	switch ( i )
	{
		case 0: //exit
			load_guild_halls();
			break;
		case 1: //withdraw
			sprintf ( rtn_str,"22,%s",guild_bank.text_box.message );
			send_con_hub ( rtn_str );
			break;
		case 2: //deposit
			sprintf ( rtn_str,"23,%s",guild_bank.text_box.message );
			send_con_hub ( rtn_str );
			break;
	}
}

void button_guild_register ( int x, int y )
{
	int i;

	for ( i=0;i<1;i++ )
		if ( x >= guild_register.button[i].x && x <= guild_register.button[i].x + guild_register.button[i].w && y >= guild_register.button[i].y && y <= guild_register.button[i].y + guild_register.button[i].h )
			break;

	if ( i == 1 ) return;

	switch ( i )
	{
		case 0: //exit
			load_guild_halls();
			break;
	}
}

void key_guild_register ( int c )
{
	int i;
	char rtn_str[500];

	if ( c == 13 )
	{
		sprintf ( rtn_str, "19,%s", guild_register.text_box.message );
		send_con_hub ( rtn_str );
	}
	else
	{
		add_text_box ( screen, &guild_register.text_box, c );
		sdl_flip_mutex();
	}
}

void key_guild_listing ( int c )
{
	int i;
	char rtn_str[500];

	if ( c == 13 )
	{
		sprintf ( rtn_str, "28,%s", guild_listing.text_box.message );
		send_con_hub ( rtn_str );
	}
	else
	{
		add_text_box ( screen, &guild_listing.text_box, c );
		sdl_flip_mutex();
	}
}

void key_guild_bank ( int c )
{
	int i;

	if ( ( c >= '0' && c <= '9' ) || c == 8 || c == 127 || c == 275 || c == 276 )
	{
		add_text_box ( screen, &guild_bank.text_box, c );
		sdl_flip_mutex();
	}
}

void handle_button_wheel ( int is_up )
{
	if ( map.visible ) {button_wheel_map ( is_up ); return;}
	if ( space.visible ) {button_wheel_space ( is_up ); return;}
}

void handle_button_right ( int x, int y )
{
	if ( space.visible ) 		{button_right_space ( x,y ); return;}
}

void handle_button_up ( int x, int y )
{
	if ( map.visible ) 		{button_up_map ( x,y ); return;}
}

void handle_button ( int x, int y )
{
	if ( login.visible ) 		{button_login ( x,y ); return;}
	if ( create_char.visible ) 	{button_create_char ( x,y ); return;}
	if ( leave_game.visible ) 	{button_leave_game ( x,y ); return;}
	if ( server_select.visible ) 	{button_server_select ( x,y ); return;}
	if ( planet.visible ) 		{button_planet ( x,y ); return;}
	if ( planet_sat.visible ) 	{button_planet_sat ( x,y ); return;}
	if ( gen_home.visible ) 		{button_gen_home ( x,y ); return;}
	if ( velic_home.visible ) 	{button_velic_home ( x,y ); return;}
	if ( hanger.visible ) 		{button_hanger ( x,y ); return;}
	if ( shop.visible ) 		{button_shop ( x,y ); return;}
	if ( bar.visible ) 		{button_bar ( x,y ); return;}
	if ( repair.visible ) 		{button_repair ( x,y ); return;}
	if ( space.visible ) 		{button_space ( x,y ); return;}
	if ( map.visible ) 		{button_map ( x,y ); return;}
	if ( death.visible ) 		{button_death ( x,y ); return;}
	if ( trade.visible ) 		{button_trade ( x,y ); return;}
	if ( guild_halls.visible ) 	{button_guild_halls ( x,y ); return;}
	if ( guild_editor.visible ) 	{button_guild_editor ( x,y ); return;}
	if ( guild_editor_more.visible ) 	{button_guild_editor_more ( x,y ); return;}
	if ( guild_editor_more2.visible ) 	{button_guild_editor_more2 ( x,y ); return;}
	if ( guild_listing.visible ) 	{button_guild_listing ( x,y ); return;}
	if ( guild_bank.visible ) 	{button_guild_bank ( x,y ); return;}
	if ( guild_register.visible ) 	{button_guild_register ( x,y ); return;}
	if ( stat_viewer.visible ) 	{button_stat_viewer ( x,y ); return;}
	if ( cb_info.visible ) 		{button_cb_info ( x,y ); return;}
	if ( bounty.visible ) 		{button_bounty ( x,y ); return;}
	if ( sat_editor.visible ) 		{button_sat_editor ( x,y ); return;}
	if ( planet_editor.visible ) 		{button_planet_editor ( x,y ); return;}
	if ( planet_guild.visible ) 		{button_planet_guild ( x,y ); return;}
	//if ( switch_server.visible ) 	{button_switch_server ( x,y ); return;}
	if ( purchase_plans.visible ) 	{button_purchase_plans ( x,y ); return;}
	if ( trade_items.visible ) 	{button_trade_items ( x,y ); return;}
}

//*NEW double click handler
void handle_dblclick_left(int x, int y)
{
    if ( space.visible ) 		{dblclick_left_space ( x,y ); return;}
}

void handle_motion ( int x, int y )
{
	if ( space.visible ) 	{motion_space ( x,y ); return;}
	if ( map.visible ) 		{motion_map ( x,y ); return;}
	if ( trade_items.visible ) 		{motion_trade_items ( x,y ); return;}
}

void handle_key ( int c )
{
	if ( login.visible ) 		{key_login ( c ); return;}
	if ( create_char.visible ) 	{key_create_char ( c ); return;}
	if ( bar.visible ) 		{key_bar ( c ); return;}
	if ( space.visible ) 		{key_space ( c ); return;}
	if ( map.visible ) 		{key_map ( c ); return;}
	if ( trade.visible ) 		{key_trade ( c ); return;}
	if ( guild_register.visible ) 	{key_guild_register ( c ); return;}
	if ( guild_bank.visible ) 	{key_guild_bank ( c ); return;}
	if ( stat_viewer.visible ) 	{key_stat_viewer ( c ); return;}
	if ( bounty.visible ) 		{key_bounty ( c ); return;}
	if ( guild_editor.visible ) 		{key_guild_editor ( c ); return;}
	if ( guild_editor_more.visible ) 		{key_guild_editor_more ( c ); return;}
	if ( guild_listing.visible ) 		{key_guild_listing ( c ); return;}
	if ( sat_editor.visible ) 		{key_sat_editor ( c ); return;}
	if ( trade_items.visible ) 		{key_trade_items ( c ); return;}
}

void handle_ctrl_key ( int c )
{
	switch ( c )
	{
		case 108:
			ctrl_l();
			break;
		case 103:
			ctrl_g();
			break;
		case 99:
			ctrl_c();
			break;
		case 'v':
			ctrl_v();
            break;
	}
}

void redraw_visible()
{
	if ( login.visible )
	{
		SDL_BlitSurface ( login.backround, NULL, screen, NULL );
		sdl_flip_mutex(); return;
	}
	if ( create_char.visible )
	{
		SDL_BlitSurface ( create_char.backround, NULL, screen, NULL );
		sdl_flip_mutex(); return;
	}
	if ( leave_game.visible )
	{
		SDL_BlitSurface ( leave_game.backround, NULL, screen, NULL );
		sdl_flip_mutex(); return;
	}
}

void check_draw_login()
{
	if ( login.visible )
	{
		SDL_BlitSurface ( login.backround, NULL, screen, NULL );
		sdl_flip_mutex();
	}
}

void init_form_memory()
{
	int i, j, k;

	login.backround = NULL;
	login.visible = 0;

	//NEW CHARACTER
	login.button[0].x = 90;
	login.button[0].y = 145;
	login.button[0].w = 244;
	login.button[0].h = 32;

	//LEAVE
	login.button[1].x = 655;
	login.button[1].y = 513;
	login.button[1].w = 61;
	login.button[1].h = 25;

	//SWITCH SERVER
	login.button[2].x = 90;
	login.button[2].y = 206;
	login.button[2].w = 175;
	login.button[2].h = 30;

    //Welcome + Users Online Lavel
	login.label.location.x = 352;
	login.label.location.y = 79;
	login.label.location.w = 242;
	login.label.location.h = 22;
	login.label.message[0] = '\0';

	//CLEAR
	clear_text_box ( NULL, &login.text_box[0] );
	clear_text_box ( NULL, &login.text_box[1] );

	//MAKE
	setup_text_box ( &login.text_box[0] );
	setup_text_box ( &login.text_box[1] );

	//LOGIN LIMITATION, NO CHARMARK
	login.text_box[0].max_char = 20;
	login.text_box[0].pass_char = '\0';

	//PASS LIMITATION, CHARMARK = *
	login.text_box[1].max_char = 20;
	login.text_box[1].pass_char = '*';

	//LOGIN
	login.text_box[0].location.x = 203;
	login.text_box[0].location.y = 76;
	login.text_box[0].location.w = 130;
	login.text_box[0].location.h = 10;

	//PASS
	login.text_box[1].location.x = 203;
	login.text_box[1].location.y = 102;
	login.text_box[1].location.w = 130;
	login.text_box[1].location.h = 10;

	//LOGIN SELECTED BY DEFALUT
	login.text_box[0].selected = 1;

	create_char.backround = NULL;
	create_char.visible = 0;
	create_char.button[0].x = 270;
	create_char.button[0].y = 257;
	create_char.button[0].w = 50;
	create_char.button[0].h = 10;
	create_char.button[1].x = 615;
	create_char.button[1].y = 500;
	create_char.button[1].w = 100;
	create_char.button[1].h = 30;
	create_char.label.location.x = 91;
	create_char.label.location.y = 62;
	create_char.label.location.w = 329;
	create_char.label.location.h = 17;
	create_char.label.message[0] = '\0';
	for ( i=0;i<6;i++ )
	{
		clear_text_box ( NULL, &create_char.text_box[i] );
		setup_text_box ( &create_char.text_box[i] );
		create_char.text_box[i].location.x = 196;
		create_char.text_box[i].location.w = 123;
		create_char.text_box[i].location.h = 17;
		create_char.text_box[i].max_char = 20;
		create_char.text_box[i].pass_char = '\0';
	}
	//login,pass,charname,realname,email,age
	create_char.text_box[0].location.y = 105;
	create_char.text_box[1].location.y = 131;
	create_char.text_box[2].location.y = 157;
	create_char.text_box[3].location.y = 183;
	create_char.text_box[4].location.y = 209;
	create_char.text_box[5].location.y = 235;

	//set their heights
	create_char.text_box[0].location.h = 10;
	create_char.text_box[1].location.h = 10;
	create_char.text_box[2].location.h = 10;
	create_char.text_box[3].location.h = 10;
	create_char.text_box[4].location.h = 10;
	create_char.text_box[5].location.h = 10;
	create_char.text_box[0].selected = 1;
	create_char.text_box[1].pass_char = '*';
	create_char.text_box[4].max_char = 50;

	leave_game.backround = NULL;
	leave_game.visible = 0;

	server_select.backround = NULL;
	server_select.visible = 0;
	server_select.label.location.x = 86;
	server_select.label.location.y = 61;
	server_select.label.location.w = 329;
	server_select.label.location.h = 17;
	server_select.button.x = 613;
	server_select.button.y = 502;
	server_select.button.w = 102;
	server_select.button.h = 28;
	server_select.label.message[0] = '\0';
	server_select.connecting = 0;
	server_select.connected = 0;
	server_select.newlist = 0;

	planet.backround = NULL;
	planet.planetbut = NULL;
	planet.last_planet = -1;
	planet.visible = 0;
	for ( i=0;i<PLANET_MAX_BUTTON;i++ )
	{
		planet.button[i].x = 576;
		planet.button[i].y = 99 + i * 20;
		planet.button[i].w = 140;
		planet.button[i].h = 20;
	}
	planet.button[PLANET_MAX_BUTTON].x = 658;
	planet.button[PLANET_MAX_BUTTON].y = 504;
	planet.button[PLANET_MAX_BUTTON].w = 57;
	planet.button[PLANET_MAX_BUTTON].h = 24;

	gen_home.backround = NULL;
	gen_home.visible = 0;
	gen_home.button[0].x = 301;
	gen_home.button[0].y = 152;
	gen_home.button[0].w = 172;
	gen_home.button[0].h = 111;
	gen_home.button[1].x = 149;
	gen_home.button[1].y = 226;
	gen_home.button[1].w = 117;
	gen_home.button[1].h = 105;
	gen_home.button[2].x = 391;
	gen_home.button[2].y = 272;
	gen_home.button[2].w = 80;
	gen_home.button[2].h = 51;
	gen_home.button[3].x = 481;
	gen_home.button[3].y = 268;
	gen_home.button[3].w = 80;
	gen_home.button[3].h = 57;
	gen_home.button[4].x = 572;
	gen_home.button[4].y = 276;
	gen_home.button[4].w = 93;
	gen_home.button[4].h = 75;
	gen_home.button[5].x = 655;
	gen_home.button[5].y = 515;
	gen_home.button[5].w = 60;
	gen_home.button[5].h = 25;

	velic_home.backround = NULL;
	velic_home.visible = 0;
	velic_home.button[0].x = 260;
	velic_home.button[0].y = 128;
	velic_home.button[0].w = 250;
	velic_home.button[0].h = 136;
	velic_home.button[1].x = 530;
	velic_home.button[1].y = 210;
	velic_home.button[1].w = 110;
	velic_home.button[1].h = 140;
	velic_home.button[2].x = 260;
	velic_home.button[2].y = 280;
	velic_home.button[2].w = 90;
	velic_home.button[2].h = 55;
	velic_home.button[3].x = 380;
	velic_home.button[3].y = 275;
	velic_home.button[3].w = 80;
	velic_home.button[3].h = 55;
	velic_home.button[4].x = 160;
	velic_home.button[4].y = 310;
	velic_home.button[4].w = 90;
	velic_home.button[4].h = 60;
	velic_home.button[5].x = 655;
	velic_home.button[5].y = 515;
	velic_home.button[5].w = 60;
	velic_home.button[5].h = 25;

	init_form_hanger();

	init_form_shop();

	init_form_bar();

	repair.backround = NULL;
	repair.visible = 0;
	repair.money_label.location.x = 147;
	repair.money_label.location.y = 105;
	repair.money_label.location.w = 151;
	repair.money_label.location.h = 15;
	repair.money_label.message[0] = '\0';
	repair.cost_label.location.x = 623;
	repair.cost_label.location.y = 65;
	repair.cost_label.location.w = 88;
	repair.cost_label.location.h = 15;
	repair.cost_label.message[0] = '\0';
	for ( i=0;i<16;i++ )
	{
		repair.button[i+2].x = 450 + ( 120 * ( i>7 ) );
		repair.button[i+2].y = ( 132 + ( i * 22 ) ) - ( 176 * ( i>7 ) );
		repair.button[i+2].w = 55;
		repair.button[i+2].h = 16;
		repair.button[i+18].x = repair.button[i+2].x;
		repair.button[i+18].y = repair.button[i+2].y + 211;
		repair.button[i+18].w = 65;
		repair.button[i+18].h = 16;
	}
	repair.button[0].x = 322;
	repair.button[0].y = 101;
	repair.button[0].w = 151;
	repair.button[0].h = 16;
	repair.button[1].x = 655;
	repair.button[1].y = 82;
	repair.button[1].w = 55;
	repair.button[1].h = 16;
	repair.thread = NULL;
	repair.redraw_weapons = 1;
	repair.last_planet = -1;

	launching.backround = NULL;
	launching.visible = 0;

	landing.backround = NULL;
	landing.visible = 0;

	space.backround = NULL;
	space.loc = SDL_CreateRGBSurface ( SDL_HWSURFACE, 600, 200, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
	space.temp_loc = SDL_DisplayFormat ( space.loc );
	space.last_loc_number = -1;
	space.last_loc_planet = -1;
	space.last_loc_safe = -1;
	space.last_loc_zone = -1;
	for ( i=0;i<10;i++ )
	{
		space.button[i].x = 97 + ( 60 * i );
		space.button[i + 10].x = 97 + ( 60 * i );
		space.button[i + 20].x = 97 + ( 60 * i );
		space.button[i + 30].x = 97 + ( 60 * i );
		space.button[i].y = 65;
		space.button[i + 10].y = 115;
		space.button[i + 20].y = 165;
		space.button[i + 30].y = 215;
		space.button[i].w = 60;
		space.button[i + 10].w = 60;
		space.button[i + 20].w = 60;
		space.button[i + 30].w = 60;
		space.button[i].h = 50;
		space.button[i + 10].h = 50;
		space.button[i + 20].h = 50;
		space.button[i + 30].h = 50;
	}
	for ( i=40;i<45;i++ )
	{
		space.button[i].x = 176;
		space.button[i].y = 365 - ( 12 * ( i - 40 ) );
		space.button[i].w = 33;
		space.button[i].h = 10;
	}
	for ( i=53;i<69;i++ )
	{

		space.button[i].x = 218 + ( ( ( i-53 ) / 4 ) * 34 );
		space.button[i].y = 288 + ( ( ( i-53 ) % 4 ) * 24 );
		space.button[i].w = 34;
		space.button[i].h = 24;
	}
	//top row buttons
	space.button[45].x = 422;
	space.button[45].y = 293;
	space.button[45].w = 84;
	space.button[45].h = 15;
	space.button[46].x = 519;
	space.button[46].y = 293;
	space.button[46].w = 84;
	space.button[46].h = 15;
	space.button[47].x = 614;
	space.button[47].y = 293;
	space.button[47].w = 84;
	space.button[47].h = 15;
	//bottom row buttons
	space.button[48].x = 422;
	space.button[48].y = 316;
	space.button[48].w = 84;
	space.button[48].h = 15;
	space.button[49].x = 519;
	space.button[49].y = 316;
	space.button[49].w = 84;
	space.button[49].h = 15;
	space.button[50].x = 614;
	space.button[50].y = 316;
	space.button[50].w = 84;
	space.button[50].h = 15;
	space.button[51].x = 91;
	space.button[51].y = 278;
	space.button[51].w = 33;
	space.button[51].h = 33;
	space.button[52].x = 215;
	space.button[52].y = 277;
	space.button[52].w = 165;
	space.button[52].h = 10;
	space.text_box[0].location.x = 458;
	space.text_box[0].location.y = 339;
	space.text_box[0].location.w = 242;
	space.text_box[0].location.h = 16;

	space.text_box[1].location.x = 150;
	space.text_box[1].location.y = 391;
	space.text_box[1].location.w = 222;
	space.text_box[1].location.h = 16;

	space.text_box[2].location.x = 330;
	space.text_box[2].location.y = 281;
	space.text_box[2].location.w = 42;
	space.text_box[2].location.h = 10;

	space.text_box[3].location.x = 615;
	space.text_box[3].location.y = 292;
	space.text_box[3].location.w = 85;
	space.text_box[3].location.h = 16;
	for ( i=0;i<4;i++ )
	{
		clear_text_box ( NULL, &space.text_box[i] );
		setup_text_box ( &space.text_box[i] );
	}
	set_text_box_displaybox ( &space.text_box[0],&space.display_box[0] );
	set_text_box_displaybox ( &space.text_box[1],&space.display_box[1] );
	space.text_box[0].selected = 1;
	space.text_box[1].selected = 0;
	space.text_box[2].selected = 0;
	space.text_box[3].selected = 0;
	space.text_box[0].max_char = 200;
	space.text_box[1].max_char = 200;
	space.text_box[2].max_char = 10;
	space.text_box[3].max_char = 10;
	space.text_box[0].pass_char = '\0';
	space.text_box[1].pass_char = '\0';
	space.text_box[2].pass_char = '\0';
	space.text_box[3].pass_char = '\0';
	space.display_box[0].x = 393;
	space.display_box[0].y = 361;
	space.display_box[0].w = 305;

	space.display_box[1].x = 88;
	space.display_box[1].y = 417;
	space.display_box[1].w = 285;

	space.display_box[0].lines = 12;
	space.display_box[1].lines = 8;
	setup_display_box ( &space.display_box[0] );
	setup_display_box ( &space.display_box[1] );

	// USER :: GUILD
	space.user_label.location.x = 219;
	space.user_label.location.y = 366;
	space.user_label.location.w = 159;
	space.user_label.location.h = 15;
	space.user_label.message[0] = '\0';
	//space.guild_label.location.x = 218;
	//space.guild_label.location.y = 368;
	//space.guild_label.location.w = 159;
	//space.guild_label.location.h = 15;
	//space.guild_label.message[0] = '\0';

	// HULL LABEL
	space.hull_label.location.x = 134;
	space.hull_label.location.y = 288;
	space.hull_label.location.w = 35;
	space.hull_label.location.h = 15;
	space.hull_label.message[0] = '\0';

	// SHIELD LABEL
	space.shield_label.location.x = 176;
	space.shield_label.location.y = 288;
	space.shield_label.location.w = 35;
	space.shield_label.location.h = 15;
	space.shield_label.message[0] = '\0';

	// SELECTED USER LABEL
	space.info_label.location.x = 425;
	space.info_label.location.y = 276;
	space.info_label.location.w = 275;
	space.info_label.location.h = 13;
	space.info_label.message[0] = '\0';
	space.info_label_mode = -1; //0-motion,1-user,2-transfer
	for ( i=0;i<5;i++ )
	{
		//destination.x = 216;
		//destination.y = 279;
		//left row
		space.good_label[i].location.x = 240;
		space.good_label[i].location.y = 296 + ( i * 18 );
		space.good_label[i].location.w = 55;
		space.good_label[i].location.h = 13;
		space.good_label[i].message[0] = '\0';

		//right row
		space.good_label[i+5].location.x = 320;
		space.good_label[i+5].location.y = 296 + ( i * 18 );
		space.good_label[i+5].location.w = 55;
		space.good_label[i+5].location.h = 13;
		space.good_label[i+5].message[0] = '\0';

		//now for those buttons
		space.button[i+69].x = 218;
		space.button[i+69].y = 292 + ( i * 18 );
		space.button[i+69].w = 20;
		space.button[i+69].h = 17;

		space.button[i+74].x = 300;
		space.button[i+74].y = 292 + ( i * 18 );
		space.button[i+74].w = 20;
		space.button[i+74].h = 17;
	}
	space.user_sel = -1;
	space.motion_sel = -1;
	space.view_cargo_goods = 1;
	space.view_cargo_sector = 0;
	space.viewing_cargo = 0;
	space.good_viewing = 0;
	space.show_ship = 1;
	space.jump_ok = 0; //*jumpok
	space.shield_level = 0;
	space.transferring = 0;
	space.engaging = -1;
	space.hit_enemy = 0;
	space.weapon_viewing = 0;
	space.was_sun = 0;
	space.thread = NULL;
	space.shield_disable_time = current_time() - SHIELD_DISABLE_TIME;
	space.visible = 0;
	setup_private_comms ( & ( space.display_box[1] ) ); //setup initial displaybox

	init_form_map();

	death.backround = NULL;
	death.visible = 0;
	death.okay = 0;

	trade.backround = NULL;
	trade.visible = 0;
	trade.last_planet = -1;
	for ( i=0;i<10;i++ )
	{
		trade.button[i].x = 367 + i * 35;
		trade.button[i].y = 100;
		trade.button[i].w = 20;
		trade.button[i].h = 20;
	}
	trade.button[10].x = 83;
	trade.button[10].y = 105;
	trade.button[10].w = 50;
	trade.button[10].h = 13;
	trade.button[11].x = 162;
	trade.button[11].y = 104;
	trade.button[11].w = 128;
	trade.button[11].h = 14;
	trade.button[12].x = 655;
	trade.button[12].y = 516;
	trade.button[12].w = 55;
	trade.button[12].h = 16;
	for ( i=0;i<3;i++ )
	{
		trade.trade_label[i].message[0] = '\0';
		trade.trade_display[i].x = 363;
		trade.trade_display[i].w = 308;
	}
	trade.trade_label[0].location.x = 439;
	trade.trade_label[0].location.y = 162;
	trade.trade_label[0].location.w = 100;
	trade.trade_label[0].location.h = 20;

	trade.trade_label[1].location.x = 425;
	trade.trade_label[1].location.y = 300;
	trade.trade_label[1].location.w = 100;
	trade.trade_label[1].location.h = 20;

	trade.trade_label[2].location.x = 425;
	trade.trade_label[2].location.y = 415;
	trade.trade_label[2].location.w = 100;
	trade.trade_label[2].location.h = 20;

	trade.money_label.location.x = 168;
	trade.money_label.location.y = 396;
	trade.money_label.location.w = 149;
	trade.money_label.location.h = 20;

	trade.cargo_label.location.x = 226;
	trade.cargo_label.location.y = 430;
	trade.cargo_label.location.w = 91;
	trade.cargo_label.location.h = 20;

	trade.money_label.message[0] = '\0';
	trade.cargo_label.message[0] = '\0';

	trade.text_box[0].location.x = 438;
	trade.text_box[0].location.y = 380;
	trade.text_box[0].location.w = 92;
	trade.text_box[0].location.h = 10;

	trade.text_box[1].location.x = 438;
	trade.text_box[1].location.y = 497;
	trade.text_box[1].location.w = 92;
	trade.text_box[1].location.h = 10;

	trade.text_box[0].max_char = 10;
	trade.text_box[0].pass_char = '\0';
	trade.text_box[1].max_char = 10;
	trade.text_box[1].pass_char = '\0';
	for ( i=0;i<2;i++ )
	{
		clear_text_box ( NULL, &trade.text_box[i] );
		setup_text_box ( &trade.text_box[i] );
	}
	trade.text_box[0].selected = 1;
	trade.trade_display[0].y = 205;
	trade.trade_display[1].y = 335;
	trade.trade_display[2].y = 455;
	trade.trade_display[0].lines = 6;
	trade.trade_display[1].lines = 3;
	trade.trade_display[2].lines = 3;
	setup_display_box ( &trade.trade_display[0] );
	setup_display_box ( &trade.trade_display[1] );
	setup_display_box ( &trade.trade_display[2] );
	trade.news_disaster_display.lines = 17;
	trade.news_disaster_display.x = 363;
	trade.news_disaster_display.y = 90;
	trade.news_disaster_display.w = 330;
	setup_display_box ( &trade.news_disaster_display );
	struct label best_trade_planet_name_label[PLANET_TRADE_MAX];
	struct label best_trade_good_difference_label[PLANET_TRADE_MAX * 10];
	struct label best_trade_suggested_label[PLANET_TRADE_MAX];
	for ( i=0;i<PLANET_TRADE_MAX;i++ )
	{
		trade.best_trade_planet_name_label[i].location.x = 363;
		trade.best_trade_planet_name_label[i].location.y = 350 + ( i * 34 );
		trade.best_trade_planet_name_label[i].location.w = 330;
		trade.best_trade_planet_name_label[i].location.h = 15;

		trade.best_trade_suggested_label[i].location.x = 363;
		trade.best_trade_suggested_label[i].location.y = 365 + ( i * 34 );
		trade.best_trade_suggested_label[i].location.w = 330;
		trade.best_trade_suggested_label[i].location.h = 15;
	}
	trade.viewing_news = 1;

	guild_halls.backround = NULL;
	guild_halls.visible = 0;
	for ( i=1;i<5;i++ )
	{
		guild_halls.button[i].y = 344;
		guild_halls.button[i].h = 66;
	}
	guild_halls.button[0].x = 655;
	guild_halls.button[0].y = 515;
	guild_halls.button[0].w = 60;
	guild_halls.button[0].h = 25;
	guild_halls.button[1].x = 118;
	guild_halls.button[1].w = 56;
	guild_halls.button[2].x = 188;
	guild_halls.button[2].w = 100;
	guild_halls.button[3].x = 295;
	guild_halls.button[3].w = 100;
	guild_halls.button[4].x = 396;
	guild_halls.button[4].w = 72;

	init_form_guild_editor();

	init_form_guild_editor_more();

	init_form_guild_editor_more2();

	guild_bank.backround = NULL;
	guild_bank.visible = 0;
	guild_bank.button[0].x = 450;
	guild_bank.button[0].y = 367;
	guild_bank.button[0].w = 63;
	guild_bank.button[0].h = 20;
	guild_bank.button[1].x = 287;
	guild_bank.button[1].y = 367;
	guild_bank.button[1].w = 78;
	guild_bank.button[1].h = 20;
	guild_bank.button[2].x = 365;
	guild_bank.button[2].y = 367;
	guild_bank.button[2].w = 78;
	guild_bank.button[2].h = 20;

	guild_bank.money_label.location.x = 373;
	guild_bank.money_label.location.y = 295;
	guild_bank.money_label.location.w = 122;
	guild_bank.money_label.location.h = 20;
	guild_bank.money_label.message[0] = '\0';

	guild_bank.balance_label.location.x = 373;
	guild_bank.balance_label.location.y = 324;
	guild_bank.balance_label.location.w = 139;
	guild_bank.balance_label.location.h = 20;
	guild_bank.balance_label.message[0] = '\0';
	guild_bank.text_box.location.x = 373;
	guild_bank.text_box.location.y = 342;
	guild_bank.text_box.location.w = 139;
	guild_bank.text_box.location.h = 20;
	guild_bank.text_box.max_char = 20;
	guild_bank.text_box.pass_char = '\0';
	guild_bank.text_box.selected = 1;
	clear_text_box ( NULL, &guild_bank.text_box );
	setup_text_box ( &guild_bank.text_box );

	guild_register.backround = NULL;
	guild_register.visible = 0;
	guild_register.button[0].x = 450;
	guild_register.button[0].y = 367;
	guild_register.button[0].w = 63;
	guild_register.button[0].h = 20;

	guild_register.info_label.location.x = 288;
	guild_register.info_label.location.y = 345;
	guild_register.info_label.location.w = 226;
	guild_register.info_label.location.h = 10;
	guild_register.info_label.message[0] = '\0';

	guild_register.text_box.location.x = 296;
	guild_register.text_box.location.y = 369;
	guild_register.text_box.location.w = 156;
	guild_register.text_box.location.h = 20;
	guild_register.text_box.max_char = 20;
	guild_register.text_box.pass_char = '\0';
	guild_register.text_box.selected = 1;
	clear_text_box ( NULL, &guild_register.text_box );
	setup_text_box ( &guild_register.text_box );

	guild_listing.backround = NULL;
	guild_listing.visible = 0;
	guild_listing.button[0].x = 593;
	guild_listing.button[0].y = 494;
	guild_listing.button[0].w = 99;
	guild_listing.button[0].h = 28;
	guild_listing.button[1].x = 193;
	guild_listing.button[1].y = 446;
	guild_listing.button[1].w = 236 - 193;
	guild_listing.button[1].h = 462 - 446;
	guild_listing.button[2].x = 237;
	guild_listing.button[2].y = 446;
	guild_listing.button[2].w = 310 - 237;
	guild_listing.button[2].h = 462 - 446;
	guild_listing.button[3].x = 310;
	guild_listing.button[3].y = 446;
	guild_listing.button[3].w = 363 - 310;
	guild_listing.button[3].h = 462 - 446;
	guild_listing.button[4].x = 360;
	guild_listing.button[4].y = 64;
	guild_listing.button[4].w = 16;
	guild_listing.button[4].h = 125;
	guild_listing.button[5].x = 360;
	guild_listing.button[5].y = 64 + 125;
	guild_listing.button[5].w = 16;
	guild_listing.button[5].h = 79;

	guild_listing.guild_name_label.location.x = 550;
	guild_listing.guild_name_label.location.y = 121;
	guild_listing.guild_name_label.location.w = 717 - 550;
	guild_listing.guild_name_label.location.h = 20;

	guild_listing.guild_owner_label.location.x = 550;
	guild_listing.guild_owner_label.location.y = 138;
	guild_listing.guild_owner_label.location.w = 717 - 550;
	guild_listing.guild_owner_label.location.h = 20;

	guild_listing.guild_website_label.location.x = 550;
	guild_listing.guild_website_label.location.y = 156;
	guild_listing.guild_website_label.location.w = 717 - 550;
	guild_listing.guild_website_label.location.h = 20;

	guild_listing.guild_money_label.location.x = 550;
	guild_listing.guild_money_label.location.y = 174;
	guild_listing.guild_money_label.location.w = 717 - 550;
	guild_listing.guild_money_label.location.h = 20;

	guild_listing.guild_lend_label.location.x = 550;
	guild_listing.guild_lend_label.location.y = 192;
	guild_listing.guild_lend_label.location.w = 717 - 550;
	guild_listing.guild_lend_label.location.h = 20;

	guild_listing.guild_players_label.location.x = 550;
	guild_listing.guild_players_label.location.y = 210;
	guild_listing.guild_players_label.location.w = 717 - 550;
	guild_listing.guild_players_label.location.h = 20;

	guild_listing.guild_enemy_label[2].location.x = 550;
	guild_listing.guild_enemy_label[2].location.y = 230;
	guild_listing.guild_enemy_label[2].location.w = 717 - 550;
	guild_listing.guild_enemy_label[2].location.h = 20;

	guild_listing.guild_enemy_label[1].location.x = 550;
	guild_listing.guild_enemy_label[1].location.y = 248;
	guild_listing.guild_enemy_label[1].location.w = 717 - 550;
	guild_listing.guild_enemy_label[1].location.h = 20;

	guild_listing.guild_enemy_label[0].location.x = 550;
	guild_listing.guild_enemy_label[0].location.y = 267;
	guild_listing.guild_enemy_label[0].location.w = 717 - 550;
	guild_listing.guild_enemy_label[0].location.h = 20;

	guild_listing.guild_rank_label[0].location.x = 405;
	guild_listing.guild_rank_label[0].location.y = 319 + ( 23 * 5 );
	guild_listing.guild_rank_label[0].location.w = 480 - 405;
	guild_listing.guild_rank_label[0].location.h = 20;

	guild_listing.guild_rank_label[1].location.x = 405;
	guild_listing.guild_rank_label[1].location.y = 319 + ( 23 * 4 );
	guild_listing.guild_rank_label[1].location.w = 480 - 405;
	guild_listing.guild_rank_label[1].location.h = 20;

	guild_listing.guild_rank_label[2].location.x = 405;
	guild_listing.guild_rank_label[2].location.y = 319 + ( 23 * 3 );
	guild_listing.guild_rank_label[2].location.w = 480 - 405;
	guild_listing.guild_rank_label[2].location.h = 20;

	guild_listing.guild_rank_label[3].location.x = 405;
	guild_listing.guild_rank_label[3].location.y = 319 + ( 23 * 2 );
	guild_listing.guild_rank_label[3].location.w = 480 - 405;
	guild_listing.guild_rank_label[3].location.h = 20;

	guild_listing.guild_rank_label[4].location.x = 405;
	guild_listing.guild_rank_label[4].location.y = 319 + ( 23 * 1 );
	guild_listing.guild_rank_label[4].location.w = 480 - 405;
	guild_listing.guild_rank_label[4].location.h = 20;

	guild_listing.guild_rank_label[5].location.x = 405;
	guild_listing.guild_rank_label[5].location.y = 319 + ( 23 * 0 );
	guild_listing.guild_rank_label[5].location.w = 480 - 405;
	guild_listing.guild_rank_label[5].location.h = 20;

	guild_listing.text_box.location.x = 81;
	guild_listing.text_box.location.y = 481;
	guild_listing.text_box.location.w = 360 - 80;
	guild_listing.text_box.location.h = 10;
	guild_listing.text_box.max_char = 20;
	guild_listing.text_box.pass_char = '\0';
	guild_listing.text_box.selected = 1;
	clear_text_box ( NULL, &guild_listing.text_box );
	setup_text_box ( &guild_listing.text_box );
	guild_listing.max_entry = 0;
	for ( i=0;i<MAX_GUILD_LISTING;i++ )
	{
		const int y_int = 16;

		if ( i<HALF_MAX_GUILD_LISTING )
		{
			guild_listing.guild_listing_label[i].location.x = 95;
			guild_listing.guild_listing_label[i].location.y = 75 + ( y_int * i );
			guild_listing.guild_listing_label[i].location.w = ( 360 - 95 ) / 2;
			guild_listing.guild_listing_label[i].location.h = 15;
		}
		else
		{
			guild_listing.guild_listing_label[i].location.x = 95 + ( ( 360 - 95 ) / 2 );
			guild_listing.guild_listing_label[i].location.y = guild_listing.guild_listing_label[i-HALF_MAX_GUILD_LISTING].location.y;
			guild_listing.guild_listing_label[i].location.w = ( 360 - 95 ) / 2;
			guild_listing.guild_listing_label[i].location.h = 15;
		}

		//now for corresponding buttons
		guild_listing.button[6 + i] = guild_listing.guild_listing_label[i].location;
	}

	sat_editor.backround = NULL;
	sat_editor.visible = 0;
	sat_editor.button[0].x = 530;
	sat_editor.button[0].y = 415;
	sat_editor.button[0].w = 63;
	sat_editor.button[0].h = 20;
	for ( i=1;i<1 + ( SAT_LEVEL_MAX * SAT_GUN_INC );i++ )
	{
		sat_editor.button[i].x = 398 + ( ( ( i-1 ) %6 ) * 31 );
		sat_editor.button[i].y = 281 + ( ( ( i-1 ) /6 ) * 21 );
		sat_editor.button[i].w = 30;
		sat_editor.button[i].h = 20;
	}
	sat_editor.button[i+0].x = 301; //upgrade/purchase
	sat_editor.button[i+0].y = 269;
	sat_editor.button[i+0].w = 55;
	sat_editor.button[i+0].h = 16;
	sat_editor.button[i+1].x = 408; //view gun/missile but
	sat_editor.button[i+1].y = 268;
	sat_editor.button[i+1].w = 165;
	sat_editor.button[i+1].h = 9;
	sat_editor.button[i+2].x = 220;//left
	sat_editor.button[i+2].y = 294;
	sat_editor.button[i+2].w = 20;
	sat_editor.button[i+2].h = 20;
	sat_editor.button[i+3].x = 371;//right
	sat_editor.button[i+3].y = 294;
	sat_editor.button[i+3].w = 20;
	sat_editor.button[i+3].h = 20;
	sat_editor.button[i+4].x = 210;//buy/sell
	sat_editor.button[i+4].y = 378;
	sat_editor.button[i+4].w = 55;
	sat_editor.button[i+4].h = 16;
	sat_editor.button[i+5].x = 272;//repair/reload
	sat_editor.button[i+5].y = 378;
	sat_editor.button[i+5].w = 55;
	sat_editor.button[i+5].h = 16;
	sat_editor.button[i+6].x = 300; //bug
	sat_editor.button[i+6].y = 288;
	sat_editor.button[i+6].w = 55;
	sat_editor.button[i+6].h = 16;


	sat_editor.money_label.location.x = 400;
	sat_editor.money_label.location.y = 241;
	sat_editor.money_label.location.w = 460 - sat_editor.money_label.location.x;
	sat_editor.money_label.location.h = 20;

	sat_editor.current_level_label.location.x = 340;
	sat_editor.current_level_label.location.y = 396;
	sat_editor.current_level_label.location.w = 393 - sat_editor.current_level_label.location.x;
	sat_editor.current_level_label.location.h = 20;

	sat_editor.wep_name_label.location.x = 240;
	sat_editor.wep_name_label.location.y = 296;
	sat_editor.wep_name_label.location.w = 368 - sat_editor.wep_name_label.location.x;
	sat_editor.wep_name_label.location.h = 20;

	sat_editor.wep_accuracy_label.location.x = 292;
	sat_editor.wep_accuracy_label.location.y = 316;
	sat_editor.wep_accuracy_label.location.w = 393 - sat_editor.wep_accuracy_label.location.x;
	sat_editor.wep_accuracy_label.location.h = 20;

	sat_editor.wep_speed_label.location = sat_editor.wep_accuracy_label.location;
	sat_editor.wep_damage_label.location = sat_editor.wep_accuracy_label.location;
	sat_editor.wep_speed_label.location.y += 14;
	sat_editor.wep_damage_label.location.y += 28;
	sat_editor.annual_tax_label.location = sat_editor.current_level_label.location;
	sat_editor.taxes_collected_label.location = sat_editor.current_level_label.location;
	sat_editor.annual_tax_label.location.y += 14;
	sat_editor.taxes_collected_label.location.y += 28;

	sat_editor.text_box[0].location.x = 530;
	sat_editor.text_box[0].location.y = sat_editor.money_label.location.y + 1;
	sat_editor.text_box[0].location.w = 581 - sat_editor.text_box[0].location.x;
	sat_editor.text_box[0].location.h = 10;
	clear_text_box ( NULL, &sat_editor.text_box[0] );
	setup_text_box ( &sat_editor.text_box[0] );
	sat_editor.text_box[0].max_char = 21;
	sat_editor.text_box[0].pass_char = '\0';

	planet_editor.backround = NULL;
	planet_editor.visible = 0;
	planet_editor.button[0].x = 530;
	planet_editor.button[0].y = 415;
	planet_editor.button[0].w = 63;
	planet_editor.button[0].h = 20;

	splash_screen.backround = NULL;
	splash_screen.visible = 0;

	cb_info.backround = NULL;
	cb_info.visible = 0;
	cb_info.button[0].x = 655;
	cb_info.button[0].y = 515;
	cb_info.button[0].w = 60;
	cb_info.button[0].h = 25;
	cb_info.button[1].x = 400;
	cb_info.button[1].y = 280;
	cb_info.button[1].w = 75;
	cb_info.button[1].h = 70;
	cb_info.button[2].x = 482;
	cb_info.button[2].y = 270;
	cb_info.button[2].w = 70;
	cb_info.button[2].h = 70;

	//GENERAL
	stat_viewer.backround = NULL;
	stat_viewer.visible = 0;
	stat_viewer.button[0].x = 322;
	stat_viewer.button[0].y = 101;
	stat_viewer.button[0].w = 151;
	stat_viewer.button[0].h = 16;

	//MONEY | EXPERIENCE | KILLS
	stat_viewer.button[1].x = 84;
	stat_viewer.button[1].y = 144;
	stat_viewer.button[1].w = 80;
	stat_viewer.button[1].h = 13;

	stat_viewer.button[2].x = 171;
	stat_viewer.button[2].y = 144;
	stat_viewer.button[2].w = 135;
	stat_viewer.button[2].h = 13;

	stat_viewer.button[3].x = 312;
	stat_viewer.button[3].y = 144;
	stat_viewer.button[3].w = 66;
	stat_viewer.button[3].h = 13;

	//TINY BUTTONS
	stat_viewer.button[14].x = 405;
	stat_viewer.button[14].y = 420;
	stat_viewer.button[14].w = 20;
	stat_viewer.button[14].h = 20;

	stat_viewer.button[15].x = 540;
	stat_viewer.button[15].y = 420;
	stat_viewer.button[15].w = 20;
	stat_viewer.button[15].h = 20;

	//NAME TO SCAN TEXTBOX
	stat_viewer.text_box.location.x = 163;
	stat_viewer.text_box.location.y = 103;
	stat_viewer.text_box.location.w = 115;
	stat_viewer.text_box.location.h = 10;
	stat_viewer.text_box.max_char = 20;
	stat_viewer.text_box.pass_char = '\0';
	stat_viewer.text_box.selected = 1;
	for ( i=0;i<10;i++ )
	{
	    //TOP STATS - NAMES
		stat_viewer.list_name_label[i].location.x = 105;
		stat_viewer.list_name_label[i].location.y = 164 + ( i * 15 );
		stat_viewer.list_name_label[i].location.w = 100;
		stat_viewer.list_name_label[i].location.h = 20;
		stat_viewer.list_name_label[i].message[0] = '\0';

		//TOP STATS - SCORES
		stat_viewer.list_attr_label[i].location.x = 250;
		stat_viewer.list_attr_label[i].location.y = stat_viewer.list_name_label[i].location.y;
		stat_viewer.list_attr_label[i].location.w = 100;
		stat_viewer.list_attr_label[i].location.h = 20;
		stat_viewer.list_attr_label[i].message[0] = '\0';

		stat_viewer.list_class[i] = -1;

		//BUTTONS
		stat_viewer.button[i+4].x = 90;
		stat_viewer.button[i+4].y = stat_viewer.list_name_label[i].location.y;
		stat_viewer.button[i+4].w = 377 - 90;
		stat_viewer.button[i+4].h = 15;
	}
	//PLAYER NAME
	stat_viewer.player_name_label.location.x = 570;
	stat_viewer.player_name_label.location.y = 169;
	stat_viewer.player_name_label.location.w = 90;
	stat_viewer.player_name_label.location.h = 20;
	stat_viewer.player_name_label.message[0] = '\0';

	//PLAYER GUILD
	stat_viewer.guild_name_label.location.x = 570;
	stat_viewer.guild_name_label.location.y = 184;
	stat_viewer.guild_name_label.location.w = 90;
	stat_viewer.guild_name_label.location.h = 20;
	stat_viewer.guild_name_label.message[0] = '\0';

	//GUILD RANK
	stat_viewer.guild_rank_label.location.x = 570;
	stat_viewer.guild_rank_label.location.y = 199;
	stat_viewer.guild_rank_label.location.w = 90;
	stat_viewer.guild_rank_label.location.h = 20;
	stat_viewer.guild_rank_label.message[0] = '\0';

	//PLAYER MONEY
	stat_viewer.player_worth_label.location.x = 570;
	stat_viewer.player_worth_label.location.y = 229;
	stat_viewer.player_worth_label.location.w = 90;
	stat_viewer.player_worth_label.location.h = 20;
	stat_viewer.player_worth_label.message[0] = '\0';

	//PLAYER EXP
	stat_viewer.player_exp_label.location.x = 570;
	stat_viewer.player_exp_label.location.y = 244;
	stat_viewer.player_exp_label.location.w = 90;
	stat_viewer.player_exp_label.location.h = 20;
	stat_viewer.player_exp_label.message[0] = '\0';

	//PLAYER KILLS
	stat_viewer.player_kills_label.location.x = 570;
	stat_viewer.player_kills_label.location.y = 259;
	stat_viewer.player_kills_label.location.w = 90;
	stat_viewer.player_kills_label.location.h = 20;
	stat_viewer.player_kills_label.message[0] = '\0';

	//HOME PLANET
	stat_viewer.player_home_planet_label.location.x = 570;
	stat_viewer.player_home_planet_label.location.y = 289;
	stat_viewer.player_home_planet_label.location.w = 90;
	stat_viewer.player_home_planet_label.location.h = 20;
	stat_viewer.player_home_planet_label.message[0] = '\0';

	//don't know how to remove them, so just get'em outta this screen
	stat_viewer.player_home_server_label.location.x = 1000;
	stat_viewer.player_home_server_label.location.y = 1000;
	stat_viewer.player_home_server_label.location.w = 90;
	stat_viewer.player_home_server_label.location.h = 20;
	stat_viewer.player_home_server_label.message[0] = '\0';

	//don't know how to remove them, so just get'em outta this screen
	stat_viewer.player_last_server_label.location.x = 1000;
	stat_viewer.player_last_server_label.location.y = 1000;
	stat_viewer.player_last_server_label.location.w = 90;
	stat_viewer.player_last_server_label.location.h = 20;
	stat_viewer.player_last_server_label.message[0] = '\0';

	//ONLINE STATUS
	stat_viewer.player_online_label.location.x = 570;
	stat_viewer.player_online_label.location.y = 304;
	stat_viewer.player_online_label.location.w = 90;
	stat_viewer.player_online_label.location.h = 20;
	stat_viewer.player_online_label.message[0] = '\0';

	//don't know how to remove them, so just get'em outta this screen
	stat_viewer.player_actvated_label.location.x = 1000;
	stat_viewer.player_actvated_label.location.y = 1000;
	stat_viewer.player_actvated_label.location.w = 90;
	stat_viewer.player_actvated_label.location.h = 20;
	stat_viewer.player_actvated_label.message[0] = '\0';

	//DECORATIONS
	stat_viewer.deco_label.location.x = 570;
	stat_viewer.deco_label.location.y = 319;
	stat_viewer.deco_label.location.w = 710 - stat_viewer.deco_label.location.x;
	stat_viewer.deco_label.location.h = 20;
	stat_viewer.deco_label.message[0] = '\0';

	//CHECKS ..?!
	clear_text_box ( NULL, &stat_viewer.text_box );
	setup_text_box ( &stat_viewer.text_box );
	stat_viewer.thread = NULL;
	stat_viewer.s_id = -1;
	stat_viewer.s_type = -1;
	stat_viewer.s_kind = -1;
	stat_viewer.load_ship = 0;
	stat_viewer.player_class_points = 0;

	init_form_bounty();

	planet_sat.backround = NULL;
	planet_sat.planetbut = NULL;
	planet_sat.visible = 0;
	planet_sat.button[0].x = 612;
	planet_sat.button[0].y = 498;
	planet_sat.button[0].w = 130;
	planet_sat.button[0].h = 30;
	for ( i=1;i<3;i++ )
	{
		planet_sat.button[i].x = 576;
		planet_sat.button[i].y = 99 + ( i-1 ) * 20;
		planet_sat.button[i].w = 140;
		planet_sat.button[i].h = 20;
	}

	planet_guild.backround = NULL;
	planet_guild.visible = 0;
	planet_guild.button[0].x = 450;
	planet_guild.button[0].y = 367;
	planet_guild.button[0].w = 63;
	planet_guild.button[0].h = 20;
	planet_guild.button[1].x = 290;
	planet_guild.button[1].y = 368;
	planet_guild.button[1].w = 386 - 290;
	planet_guild.button[1].h = 383 - 368;
	planet_guild.guild_name_label.location.x = 400;
	planet_guild.guild_name_label.location.y = 258;
	planet_guild.guild_name_label.location.w = 511 - planet_guild.guild_name_label.location.x;
	planet_guild.guild_name_label.location.h = 20;
	planet_guild.entry_cost_label.location = planet_guild.guild_name_label.location;
	planet_guild.money_label.location = planet_guild.guild_name_label.location;
	planet_guild.your_guild_name_label.location = planet_guild.guild_name_label.location;
	planet_guild.entry_cost_label.location.y += 17;
	planet_guild.money_label.location.y += 34;
	planet_guild.your_guild_name_label.location.y += 51;

	switch_server.backround = NULL;
	switch_server.visible = 0;
	switch_server.button[0].x = 530; //exit
	switch_server.button[0].y = 415;
	switch_server.button[0].w = 63;
	switch_server.button[0].h = 20;
	switch_server.button[1].x = 428; //left
	switch_server.button[1].y = 419;
	switch_server.button[1].w = 20;
	switch_server.button[1].h = 20;
	switch_server.button[2].x = 493; //right
	switch_server.button[2].y = 419;
	switch_server.button[2].w = 20;
	switch_server.button[2].h = 20;
	switch_server.info_label.location.x = 220;
	switch_server.info_label.location.y = 215;
	switch_server.info_label.location.w = 580 - switch_server.info_label.location.x;
	switch_server.info_label.location.h = 20;
	switch_server.server_max = 0;
	for ( i=0;i<SWITCH_SERVER_PAGE_DISPLAY;i++ )
	{
		switch_server.server_name_label[i].location.x = 220;
		switch_server.server_name_label[i].location.y = 270 + ( i*20 );
		switch_server.server_name_label[i].location.w = 340 - switch_server.server_name_label[i].location.x;
		switch_server.server_name_label[i].location.h = 20;

		switch_server.server_ip_label[i].location.x = 345;
		switch_server.server_ip_label[i].location.y = 270 + ( i*20 );
		switch_server.server_ip_label[i].location.w = 465 - switch_server.server_ip_label[i].location.x;
		switch_server.server_ip_label[i].location.h = 20;

		switch_server.server_players_label[i].location.x = 470;
		switch_server.server_players_label[i].location.y = 270 + ( i*20 );
		switch_server.server_players_label[i].location.w = 545 - switch_server.server_players_label[i].location.x;
		switch_server.server_players_label[i].location.h = 20;

		switch_server.server_ping_label[i].location.x = 540;
		switch_server.server_ping_label[i].location.y = 270 + ( i*20 );
		switch_server.server_ping_label[i].location.w = 580 - switch_server.server_ping_label[i].location.x;
		switch_server.server_ping_label[i].location.h = 20;

		switch_server.button[3 + i].x = 220; //right
		switch_server.button[3 + i].y = 270 + ( i*20 );
		switch_server.button[3 + i].w = 580 - switch_server.button[3 + i].x;
		switch_server.button[3 + i].h = 20;
	}

	purchase_plans.backround = NULL;
	purchase_plans.visible = 0;
	purchase_plans.button[0].x = 530; //exit
	purchase_plans.button[0].y = 415;
	purchase_plans.button[0].w = 63;
	purchase_plans.button[0].h = 20;
	purchase_plans.button[1].x = 219; //buy
	purchase_plans.button[1].y = 292;
	purchase_plans.button[1].w = 45;
	purchase_plans.button[1].h = 20;
	purchase_plans.cost_label.location.x = 293;
	purchase_plans.cost_label.location.y = 237;
	purchase_plans.cost_label.location.w = 373 - 293;
	purchase_plans.cost_label.location.h = 20;
	purchase_plans.exp_label.location = purchase_plans.cost_label.location;
	purchase_plans.kills_label.location = purchase_plans.cost_label.location;
	purchase_plans.exp_label.location.y += 17;
	purchase_plans.kills_label.location.y += 17 * 2;

	init_form_trade_items();
}
