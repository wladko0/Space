#include "main.h"

void init_form_bar()
{
	int i, j, k;

	bar.backround = NULL;
	bar.visible = 0;
	for ( i=0;i<12;i++ )
	{
		bar.player_label[i].location.x = 90;
		bar.player_label[i].location.y = 70 + 17 * i;
		bar.player_label[i].location.w = 135;
		bar.player_label[i].location.h = 17;
		bar.player_label[i].message[0] = '\0';
		bar.player_label[i+12].location.x = 225;
		bar.player_label[i+12].location.y = 70 + 17 * i;
		bar.player_label[i+12].location.w = 135;
		bar.player_label[i+12].location.h = 17;
		bar.player_label[i+12].message[0] = '\0';
		bar.button[4 + i] = bar.player_label[i].location;
		bar.button[4 + i + 12] = bar.player_label[i + 12].location;
		bar.playername[i][0] = '\0';
		bar.playername[i+12][0] = '\0';
		bar.playerguild[i][0] = '\0';
		bar.playerguild[i+12][0] = '\0';
	}
	bar.button[0].x = 389;
	bar.button[0].y = 81;
	bar.button[0].w = 106;
	bar.button[0].h = 16;
	bar.button[1].x = 513;
	bar.button[1].y = 81;
	bar.button[1].w = 84;
	bar.button[1].h = 16;
	bar.button[2].x = 614;
	bar.button[2].y = 81;
	bar.button[2].w = 84;
	bar.button[2].h = 16;
	bar.button[3].x = 595;
	bar.button[3].y = 494;
	bar.button[3].w = 690 - bar.button[3].x;
	bar.button[3].h = 28;
	bar.label.location.x = 387;
	bar.label.location.y = 61;
	bar.label.location.w = 717 - bar.label.location.x;
	bar.label.location.h = 20;
	bar.text_box[0].location.x = 464;
	bar.text_box[0].location.y = 282;
	bar.text_box[0].location.w = 230;
	bar.text_box[0].location.h = 14;
	bar.text_box[1].location.x = 464;
	bar.text_box[1].location.y = 117;
	bar.text_box[1].location.w = 230;
	bar.text_box[1].location.h = 14;
	bar.text_box[2].location = bar.button[1];
	bar.text_box[2].location.x += 3;
	bar.text_box[2].location.y -= -1;
	bar.text_box[2].location.w -= 3;
	for ( i=0;i<3;i++ )
	{
		clear_text_box ( NULL, &bar.text_box[i] );
		setup_text_box ( &bar.text_box[i] );
	}
	set_text_box_displaybox ( &bar.text_box[0],&bar.display_box[0] );
	set_text_box_displaybox ( &bar.text_box[1],&bar.display_box[1] );
	bar.text_box[0].selected = 1;
	bar.text_box[0].max_char = 200;
	bar.text_box[1].max_char = 200;
	bar.text_box[2].max_char = 20;
	bar.text_box[0].pass_char = '\0';
	bar.text_box[1].pass_char = '\0';
	bar.text_box[2].pass_char = '\0';
	bar.display_box[0].x = 400;
	bar.display_box[0].y = 305;
	bar.display_box[0].w = 315;
	bar.display_box[1].x = 400;
	bar.display_box[1].y = 140;
	bar.display_box[1].w = 315;
	bar.display_box[0].lines = 10;
	bar.display_box[1].lines = 9;
	setup_display_box ( &bar.display_box[0] );
	setup_display_box ( &bar.display_box[1] );
	bar.last_planet = -1;
}


void load_bar()
{
	SDL_Rect destination;
	char rtn_str[3] = "2";
	int i;

	if ( !bar.backround )
	{
		bar.backround = IMG_Load ( "graphics/barback.jpg" );
		bar.nif_bar = IMG_Load ( "graphics/nif/nif_bar.jpg" );
		bar.but1_clear = IMG_Load ( "graphics/bar_but1.jpg" );
		bar.but1_transfer = IMG_Load ( "graphics/bar_but1_transfer.jpg" );
		bar.but1_enlist = IMG_Load ( "graphics/bar_but1_enlist.jpg" );
		bar.but1_promote = IMG_Load ( "graphics/bar_but1_promote.jpg" );
		bar.but1_trade = IMG_Load ( "graphics/bar_but1_trade.jpg" );
		bar.but2_clear = IMG_Load ( "graphics/bar_but2.jpg" );
		bar.but2_remove = IMG_Load ( "graphics/bar_but2_remove.jpg" );
		bar.but2_demote = IMG_Load ( "graphics/bar_but2_demote.jpg" );
		bar.but2_guild = IMG_Load ( "graphics/bar_but2_guild.jpg" );
		bar.but2_chat = IMG_Load ( "graphics/bar_but2_chat.jpg" );
		bar.but3_clear = IMG_Load ( "graphics/bar_but3.jpg" );
		bar.but3_cancel = IMG_Load ( "graphics/bar_but3_cancel.jpg" );
		bar.but3_other = IMG_Load ( "graphics/bar_but3_other.jpg" );
	}

	if ( bar.last_planet != planet.last_planet )
	{
		SDL_Surface *bar_img;
		char temp_str[200];

		sprintf ( temp_str, "server/%s/backs/bar/bar%d.jpg", server[game.server_id].servername, planet.last_planet );
		bar_img = IMG_Load ( temp_str );
		destination.x = 94;
		destination.y = 310;

		if ( bar_img )
			SDL_BlitSurface ( bar_img, NULL, bar.backround, &destination );
		else
			SDL_BlitSurface ( bar.nif_bar, NULL, bar.backround, &destination );
	}

	set_forms_invisible();
	bar.visible = 1;
	bar.last_planet = planet.last_planet;
	SDL_BlitSurface ( bar.backround, NULL, screen, NULL );

	//make "no selection"
	bar.selected_i = -1;

	//now begin writing screen only stuff like text/display boxes
	for ( i=0;i<2;i++ )
	{
		if ( bar.text_box[i].selected )
			select_text_box ( screen, &bar.text_box[i] );
		else
			unselect_text_box ( screen, &bar.text_box[i] );
	}

	//clear and setup begining message for displaybox0
	clear_display_box ( NULL,&bar.display_box[0] );

	draw_display_box ( screen,&bar.display_box[0] );
	draw_display_box ( screen,&bar.display_box[1] );

	sdl_flip_mutex();

	send_con_server ( rtn_str ); //ask for bar info
}

void button_bar ( int x, int y )
{
	int i, success = 0, button;
	char rtn_str[3] = "3";
	const int button_max = 4 + MAX_BAR_ENTRY, text_box_max = 3;

	for ( i=0;i<button_max;i++ )
		if ( x >= bar.button[i].x && x <= bar.button[i].x + bar.button[i].w && y >= bar.button[i].y && y <= bar.button[i].y + bar.button[i].h )
			{success = 1; button = 1; break;}

	if ( !success ) for ( i=0;i<text_box_max;i++ )
			if ( x >= bar.text_box[i].location.x && x <= bar.text_box[i].location.x + bar.text_box[i].location.w && y >= bar.text_box[i].location.y && y <= bar.text_box[i].location.y + bar.text_box[i].location.h )
				{success = 1; button = 0; break;}

	if ( !success ) return;

	if ( button )
	{
		switch ( i )
		{
			case 0: //
			case 1: //
			case 2: //
				bar_button_choice ( i );
				break;
			case 3: //exit
				load_planet ( planet.last_planet );
				send_con_server ( rtn_str ); //notify the server you left the bar
				send_cancel_trade_items();
				break;
			default: //player select
				bar_select_player ( i - 4 );
				break;
		}
	}
	else
	{
		int k;

		//already selected ?
		if ( bar.text_box[i].selected ) return;

		//transfer box?
		if ( i==2 && !bar_transfer_box_visible() ) return;

		//unselect those who are
		for ( k=0;k<2;k++ )
			if ( bar.text_box[k].selected )
				unselect_text_box ( screen, &bar.text_box[k] );

		//special
		if ( bar_transfer_box_visible() && bar.text_box[2].selected )
			unselect_text_box ( screen, &bar.text_box[2] );

		//select the lover
		select_text_box ( screen, &bar.text_box[i] );

		//flip the mother
		sdl_flip_mutex();
	}
}

void key_bar ( int c )
{
	int i;
	const int text_box_max = 3;

	//find the selected one
	for ( i=0;i<text_box_max;i++ )
		if ( bar.text_box[i].selected ) break;

	if ( c == 9 ) //tab
	{
		//unselect it
		if ( i<text_box_max )
		{
			if ( i==2 )
			{
				if ( bar_transfer_box_visible() )
					unselect_text_box ( screen, &bar.text_box[i] );
			}
			else
			{
				unselect_text_box ( screen, &bar.text_box[i] );
			}
		}

		//do the addition
		i++;

		//this mother visible?
		if ( i==2 && !bar_transfer_box_visible() ) i++;

		//over the monkey?
		if ( i >= text_box_max ) i = 0;

		//select the shitter
		select_text_box ( screen, &bar.text_box[i] );

		//flip the shitter
		sdl_flip_mutex();
	}
	else if ( c == 13 )
	{
		//f?
		if ( i>=text_box_max ) return;

		switch ( i )
		{
			case 0: // reg chat
				send_public_chat ( bar.text_box[0].message );
				add_text_box_entry ( &bar.text_box[0], bar.text_box[0].message );
				clear_text_box ( screen, &bar.text_box[0] );
				sdl_flip_mutex();
				break;
			case 1: //private chat
				private_chat_send ( bar.text_box[1].message );
				add_text_box_entry ( &bar.text_box[1], bar.text_box[1].message );
				clear_text_box ( screen, &bar.text_box[1] );
				sdl_flip_mutex();
				break;
			case 2: //transfer
				if ( !bar_transfer_box_visible() ) return;

				i = bar.selected_i;

				if ( i==-1 ) return;

				transfer_money_to ( bar.playername[i],atoi ( bar.text_box[2].message ) );

				break;
		}
	}
	else if ( c == 280 || c == 281 )
	{
		if ( i>1 ) return; //not for the higher folk

		if ( c == 280 )
			scroll_up_display_box ( screen, bar.text_box[i].display_box_link );

		if ( c == 281 )
			scroll_down_display_box ( screen, bar.text_box[i].display_box_link );

		sdl_flip_mutex();
	}
	else
	{
		//f?
		if ( i>=text_box_max ) return;

		//bastard?
		if ( i==2 && !bar_transfer_box_visible() ) return;
		if ( i==2 && ( ! ( c >= '0' && c <= '9' ) && ! ( c == 8 || c == 127 || c == 273 || c == 274 || c == 275 || c == 276 ) ) ) return;

		add_text_box ( screen, &bar.text_box[i], c );
		sdl_flip_mutex();
	}
}

void read_bar_info ( char *bar_info )
{
	int i, point = 0, temp_len;
	char temp_str[1025];

	temp_len = strlen ( bar_info ); //gotta know this

	for ( i=0;i<24;i++ ) //clear all
	{
		bar.playername[i][0] = '\0';
		bar.playerguild[i][0] = '\0';
		bar.playerguild_rank[i][0] = '\0';
		bar.playerguild_rank_id[i] = 0;
	}

	for ( i=0;i<24 && point < temp_len; i++ ) //read in info
	{
		split ( temp_str,bar_info,',',&point ); //read in name
		temp_str[20] = '\0'; //cap for security
		strcpy ( bar.playername[i],temp_str ); //move to right location

		split ( temp_str,bar_info,',',&point ); //same for guild
		temp_str[20] = '\0';
		strcpy ( bar.playerguild[i],temp_str );

		split ( temp_str,bar_info,',',&point ); //same for guild_rank
		temp_str[20] = '\0';
		strcpy ( bar.playerguild_rank[i],temp_str );

		split ( temp_str,bar_info,',',&point ); //same for guild_rank_id
		bar.playerguild_rank_id[i] = atoi ( temp_str );
	}



	if ( bar.visible )
	{
		bar_redraw_listing();
	}
}

void bar_redraw_listing()
{
	int i;

	for ( i=0;i<24;i++ )
		draw_label ( screen, bar.playername[i], &bar.player_label[i], 255, 255, 255 );
	sdl_flip_mutex();
}

void add_bar_entry ( char *username, char *userguild, char *user_guild_rank, int user_guild_rank_id )
{
	int i;

	for ( i=0;i<24;i++ ) //look for copy
		if ( str_match ( bar.playername[i], username ) )
		{
			userguild[20] = '\0'; //safety
			user_guild_rank[20] = 0;
			strcpy ( bar.playerguild[i], userguild );
			strcpy ( bar.playerguild_rank[i], user_guild_rank );
			bar.playerguild_rank_id[i] = user_guild_rank_id;

			//now make changes to title if this player is selected.
			if ( bar.selected_i == i )
			{
				bar_draw_name_tag();
				if ( bar.selection_enlist || bar.selection_demote || bar.selection_remove ) //make sure we have the right guild type thing selected
				{
					bar_clear_selection_type();
					bar_correct_guild_select();
					bar_draw_buttons();
				}


				if ( bar.visible ) sdl_flip_mutex();
			}

			return;
		}

	for ( i=0;i<24;i++ ) //no copy found so look for empty slot
		if ( !bar.playername[i][0] )
		{
			userguild[20] = '\0'; //safety
			username[20] = '\0'; //safety
			user_guild_rank[20] = 0;
			strcpy ( bar.playername[i], username );
			strcpy ( bar.playerguild[i], userguild );
			strcpy ( bar.playerguild_rank[i], user_guild_rank );
			bar.playerguild_rank_id[i] = user_guild_rank_id;

			//add player to list
			if ( bar.visible )
			{
				draw_label ( screen, bar.playername[i], &bar.player_label[i], 255, 255, 255 );
				sdl_flip_mutex();
			}
			return;
		}
}

void remove_bar_entry ( char *username )
{
	int i;

	for ( i=0;i<24;i++ ) //look for copy
		if ( str_match ( bar.playername[i], username ) )
		{
			bar.playername[i][0] = 0;
			bar.playerguild[i][0] = 0;
			bar.playerguild_rank[i][0] = 0;
			bar.playerguild_rank_id[i] = 0;

			//now make changes to title if this player is selected.
			if ( bar.visible )
			{
				if ( i==bar.selected_i )
					bar_clear_selection();
				draw_label ( screen,"", &bar.player_label[i], 255, 255, 255 );
				sdl_flip_mutex();
			}

			return;
		}
}

void bar_select_player ( int i )
{
	//have we actaully even selected someone?
	if ( !bar.playername[i][0] ) return;

	//"unselect" selected
	bar_unselect();

	//set the i
	bar.selected_i = i;

	//"select" selected
	bar_select();

	//clear out selection type
	bar_clear_selection_type();

	//set selection type
	bar.selection_fresh = 1;

	//draw according name tag
	bar_draw_name_tag();

	//draw according buttons
	bar_draw_buttons();

	//flip the monkey
	sdl_flip_mutex();
}

void bar_clear_selection_type()
{
	bar.selection_fresh = 0;
	bar.selection_remove = 0;
	bar.selection_demote = 0;
	bar.selection_enlist = 0;
	bar.selection_transfer = 0;
	bar.selection_other = 0;
}

void bar_draw_name_tag()
{
	char selection_name[200];
	int i;

	i = bar.selected_i;

	sprintf ( selection_name,"%s : %s of %s", bar.playername[i], bar.playerguild_rank[i], bar.playerguild[i] );

	//draw the label
	draw_label ( screen, selection_name, &bar.label, 107, 216, 210 );
}

void bar_draw_buttons()
{
	SDL_Surface *but1, *but2, *but3;

	//the clear monkeys
	but1 = bar.but1_clear;
	but2 = bar.but2_clear;
	but3 = bar.but3_clear;

	if ( bar.selection_fresh )
	{
		but1 = bar.but1_transfer;
		but2 = bar.but2_guild;
		but3 = bar.but3_other;
	}

	if ( bar.selection_remove )
	{
		but1 = bar.but1_promote;
		but2 = bar.but2_remove;
		but3 = bar.but3_cancel;
	}

	if ( bar.selection_demote )
	{
		but1 = bar.but1_promote;
		but2 = bar.but2_demote;
		but3 = bar.but3_cancel;
	}

	if ( bar.selection_enlist )
	{
		but1 = bar.but1_enlist;
		but2 = bar.but2_clear;
		but3 = bar.but3_cancel;
	}

	if ( bar.selection_transfer )
	{
		but1 = bar.but1_transfer;
		but2 = bar.but2_clear;
		but3 = bar.but3_cancel;
	}

	if ( bar.selection_other )
	{
		but1 = bar.but1_trade;
		but2 = bar.but2_chat;
		but3 = bar.but3_cancel;
	}

	//now for the etching in the rock face
	SDL_BlitSurface ( but1, NULL, screen, &bar.button[0] );
	SDL_BlitSurface ( but2, NULL, screen, &bar.button[1] );
	SDL_BlitSurface ( but3, NULL, screen, &bar.button[2] );
}

void bar_unselect()
{
	int i;

	i = bar.selected_i;

	//reasons to break
	if ( i == -1 ) return;
	if ( !bar.playername[i][0] ) return;

	draw_label ( screen, bar.playername[i], &bar.player_label[i], 255, 255, 255 );
}

void bar_select()
{
	int i;

	i = bar.selected_i;

	draw_label ( screen, bar.playername[i], &bar.player_label[i], 255, 255, 0 );
}

void bar_button_choice ( int b )
{
	int draw_n_flip = 0;

	switch ( b )
	{
		case 0:
			if ( bar.selection_fresh ) //transfer
			{
				bar_clear_selection_type();
				bar.selection_transfer = 1;
				draw_n_flip = 1;

				clear_text_box ( NULL, &bar.text_box[2] );
				break;
			}

			if ( bar.selection_enlist ) //enlist
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				guild_enlist_user ( bar.playername[bar.selected_i] );
				break;
			}

			if ( bar.selection_demote ) //promote
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				guild_promote_user ( bar.playername[i] );
				break;
			}

			if ( bar.selection_remove ) //promote
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				guild_promote_user ( bar.playername[i] );
				break;
			}

			if ( bar.selection_transfer ) //send transfer
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				transfer_money_to ( bar.playername[i],atoi ( bar.text_box[2].message ) );
				break;
			}

			if ( bar.selection_other ) //chat
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				do_trade_button ( bar.playername[i] );

				break;
			}
			break;
		case 1:
			if ( bar.selection_fresh ) //guild
			{
				bar_clear_selection_type();
				//make the proper choice
				bar_correct_guild_select();
				draw_n_flip = 1;
				break;
			}

			if ( bar.selection_enlist ) //nothing.
			{
				break;
			}

			if ( bar.selection_demote ) //demote
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				guild_demote_user ( bar.playername[i] );
				break;
			}

			if ( bar.selection_remove ) //remove
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				guild_remove_user ( bar.playername[i] );
				break;
			}

			if ( bar.selection_transfer ) //select textbox 3
			{
				int k, i;
				const int text_box_max = 3;

				i = 2;

				//already selected ?
				if ( bar.text_box[i].selected ) return;

				//transfer box?
				if ( i==2 && !bar_transfer_box_visible() ) return;

				//unselect those who are
				for ( k=0;k<text_box_max;k++ )
					if ( bar.text_box[k].selected )
						unselect_text_box ( screen, &bar.text_box[k] );

				//select the lover
				select_text_box ( screen, &bar.text_box[i] );

				//flip the mother
				sdl_flip_mutex();
				break;
			}

			if ( bar.selection_other ) //chat
			{
				int i;

				i = bar.selected_i;

				if ( i==-1 ) return;

				do_chat_button ( bar.playername[i] );

				break;
			}
			break;
		case 2:
			if ( bar.selection_fresh ) //chat
			{
				//int i;

				//i = bar.selected_i;

				//if ( i==-1 ) return;

				//do_chat_button ( bar.playername[i] );

				bar_clear_selection_type();
				bar.selection_other = 1;
				draw_n_flip = 1;
				break;
			}

			if ( bar.selection_enlist ) //cancel
			{
				bar_clear_selection_type();
				bar.selection_fresh = 1;
				draw_n_flip = 1;
				break;
			}

			if ( bar.selection_demote ) //cancel
			{
				bar_clear_selection_type();
				bar.selection_fresh = 1;
				draw_n_flip = 1;
				break;
			}

			if ( bar.selection_remove ) //cancel
			{
				bar_clear_selection_type();
				bar.selection_fresh = 1;
				draw_n_flip = 1;
				break;
			}

			if ( bar.selection_transfer ) //cancel
			{
				bar_clear_selection_type();
				bar.selection_fresh = 1;
				draw_n_flip = 1;
				break;
			}

			if ( bar.selection_other ) //cancel
			{
				bar_clear_selection_type();
				bar.selection_fresh = 1;
				draw_n_flip = 1;
				break;
			}
			break;
	}

	if ( draw_n_flip )
	{
		bar_draw_buttons();

		sdl_flip_mutex();
	}
}

void bar_correct_guild_select()
{
	int i, r;

	i = bar.selected_i;
	r = game.guild_rank_id;

	//check?
	if ( i == -1 ) return;

	//first check if in same guild
	if ( !strcmp ( bar.playerguild[i], game.guild.name ) )
	{
		//same guild, so can we demote?
		if ( bar.playerguild_rank_id[i] && game.guild.rank_allow[r][1] ) bar.selection_demote = 1;

		//what about remove?
		//if(bar.playerguild_rank_id[i] == 5 && r == 5 && game.guild.rank_allow[r][2]) bar.selection_remove = 1;
		if ( bar.playerguild_rank_id[i] == 0 && game.guild.rank_allow[r][2] ) bar.selection_remove = 1;
	}
	else
	{
		//not same guild, can we enlist?
		if ( game.guild.rank_allow[r][0] ) bar.selection_enlist = 1;
	}

	//well were we able to make a choice?
	if ( !bar.selection_enlist && !bar.selection_demote && !bar.selection_remove ) bar.selection_fresh = 1;
}

int bar_transfer_box_visible()
{
	if ( bar.selection_transfer ) return 1;

	return 0;
}

void bar_clear_selection()
{
	bar_clear_selection_type();

	bar_draw_buttons();

	draw_label ( screen,"", &bar.label, 255, 255, 0 );
}
