#include "main.h"

void init_form_trade_items()
{
	int i;
	const int their_shift = 318;

	trade_items.backround = NULL;
	trade_items.visible = 0;
	trade_items.username[0] = 0;
	trade_items.guildname[0] = 0;
	for(i=0;i<B_TRADE_ITEMS_MAX_BUTTONS;i++)
	{
		trade_items.button[i].x = 0;
		trade_items.button[i].y = 0;
		trade_items.button[i].w = 0;
		trade_items.button[i].h = 0;
	}
	for(i=0;i<TB_TRADE_ITEMS_MAX_TEXTBOXES;i++)
	{
		clear_text_box ( NULL, &trade_items.text_box[i] );
		setup_text_box ( &trade_items.text_box[i] );
		trade_items.text_box[i].location.x = 0;
		trade_items.text_box[i].location.y = 0;
		trade_items.text_box[i].location.w = 0;
		trade_items.text_box[i].location.h = 20;
		trade_items.text_box[i].max_char = 30;
		trade_items.text_box[i].pass_char = '\0';
	}
	for(i=0;i<8;i++)
	{
		trade_items.our_gun_button[i].x = 102 + (17 * i);
		trade_items.our_gun_button[i+8].x = trade_items.our_gun_button[i].x;
		trade_items.our_gun_button[i+16].x = trade_items.our_gun_button[i].x;
		trade_items.our_gun_button[i+24].x = trade_items.our_gun_button[i].x;
		trade_items.our_gun_button[i+32].x = trade_items.our_gun_button[i].x;
		trade_items.our_gun_button[i+40].x = trade_items.our_gun_button[i].x;
		trade_items.our_gun_button[i].y = 110;
		trade_items.our_gun_button[i+8].y = 110 + 12;
		trade_items.our_gun_button[i+16].y = 110 + (12 * 2);
		trade_items.our_gun_button[i+24].y = 110 + (12 * 3);
		trade_items.our_gun_button[i+32].y = 110 + (12 * 4);
		trade_items.our_gun_button[i+40].y = 110 + (12 * 5);
	}
	for(i=0;i<MAX_HANGER_WEAPONS;i++)
	{
		trade_items.our_gun_button[i].w = 15;
		trade_items.our_gun_button[i].h = 10;
		trade_items.our_missile_button[i].w = 15;
		trade_items.our_missile_button[i].h = 10;

		trade_items.our_missile_button[i].x = trade_items.our_gun_button[i].x + 140;
		trade_items.our_missile_button[i].y = trade_items.our_gun_button[i].y;

		trade_items.their_gun_button[i] = trade_items.our_gun_button[i];
		trade_items.their_missile_button[i] = trade_items.our_missile_button[i];
		trade_items.their_gun_button[i].x += their_shift;
		trade_items.their_missile_button[i].x += their_shift;
	}
	for(i=0;i<5;i++)
	{
		trade_items.our_ship_button[i].x = 84 + (62 * i);
		trade_items.our_ship_button[i+5].x = trade_items.our_ship_button[i].x;
		trade_items.our_ship_button[i].y = 230;
		trade_items.our_ship_button[i+5].y = 230 + 52;
	}
	for(i=0;i<10;i++)
	{
		trade_items.our_ship_button[i].w = 60;
		trade_items.our_ship_button[i].h = 50;

		trade_items.their_ship_button[i] = trade_items.our_ship_button[i];
		trade_items.their_ship_button[i].x += their_shift;
	}
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected = 1;
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].max_char = 200;
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].location.x = 82;
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].location.y = 497;
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].location.w = 276 - 82;
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].location.h = 10;

	trade_items.text_box[TB_TRADE_ITEMS_MONEY].location.x = 376;
	trade_items.text_box[TB_TRADE_ITEMS_MONEY].location.y = 497;
	trade_items.text_box[TB_TRADE_ITEMS_MONEY].location.w = 482 - 376;
	trade_items.text_box[TB_TRADE_ITEMS_MONEY].location.h = 10;

	trade_items.button[B_TRADE_ITEMS_EXIT].x = 666;
	trade_items.button[B_TRADE_ITEMS_EXIT].y = 500;
	trade_items.button[B_TRADE_ITEMS_EXIT].w = 50;
	trade_items.button[B_TRADE_ITEMS_EXIT].h = 20;

	trade_items.button[B_TRADE_ITEMS_ACCEPT].x = 300;
	trade_items.button[B_TRADE_ITEMS_ACCEPT].y = 500;
	trade_items.button[B_TRADE_ITEMS_ACCEPT].w = 50;
	trade_items.button[B_TRADE_ITEMS_ACCEPT].h = 20;

	trade_items.chat_display_box.x = 85;
	trade_items.chat_display_box.y = 382;
	trade_items.chat_display_box.w = 350 - 83;
	trade_items.chat_display_box.lines = 6;
	setup_display_box ( &trade_items.chat_display_box );
	set_text_box_displaybox ( &trade_items.text_box[TB_TRADE_ITEMS_CHAT], &trade_items.chat_display_box );
	trade_items.money_label.location.x = 565;
	trade_items.money_label.location.y = 497;
	trade_items.money_label.location.w = 78;
	trade_items.money_label.location.h = 20;
	trade_items.money_label.message[0] = '\0';

	trade_items.accept_label.location.x = 303;
	trade_items.accept_label.location.y = 498;
	trade_items.accept_label.location.w = 50;
	trade_items.accept_label.location.h = 20;
	trade_items.accept_label.message[0] = '\0';

	trade_items.our_user_label.location.x = 131;
	trade_items.our_user_label.location.y = 64;
	trade_items.our_user_label.location.w = 324 - 131;
	trade_items.our_user_label.location.h = 20;
	trade_items.our_user_label.message[0] = '\0';

	trade_items.their_user_label.location.x = 469;
	trade_items.their_user_label.location.y = 64;
	trade_items.their_user_label.location.w = 654 - 469;
	trade_items.their_user_label.location.h = 20;
	trade_items.their_user_label.message[0] = '\0';

	trade_items.our_guns_label.location.x = trade_items.our_gun_button[0].x;
	trade_items.our_guns_label.location.y = 90;
	trade_items.our_guns_label.location.w = 136;
	trade_items.our_guns_label.location.h = 20;
	trade_items.our_guns_label.message[0] = '\0';

	trade_items.our_missiles_label.location.x = trade_items.our_missile_button[0].x;
	trade_items.our_missiles_label.location.y = 90;
	trade_items.our_missiles_label.location.w = 136;
	trade_items.our_missiles_label.location.h = 20;
	trade_items.our_missiles_label.message[0] = '\0';

	trade_items.our_ships_label.location.x = 84;
	trade_items.our_ships_label.location.y = 210;
	trade_items.our_ships_label.location.w = 310;
	trade_items.our_ships_label.location.h = 20;
	trade_items.our_ships_label.message[0] = '\0';

	trade_items.our_money_label.location.x = 84;
	trade_items.our_money_label.location.y = 340;
	trade_items.our_money_label.location.w = 310;
	trade_items.our_money_label.location.h = 20;
	trade_items.our_money_label.message[0] = '\0';

	trade_items.their_guns_label = trade_items.our_guns_label;
	trade_items.their_missiles_label = trade_items.our_missiles_label;
	trade_items.their_ships_label = trade_items.our_ships_label;
	trade_items.their_money_label = trade_items.our_money_label;

	trade_items.their_guns_label.location.x += their_shift;
	trade_items.their_missiles_label.location.x += their_shift;
	trade_items.their_ships_label.location.x += their_shift;
	trade_items.their_money_label.location.x += their_shift;

	for(i=0;i<TRADE_ITEMS_INFO_LABELS_MAX;i++)
	{
		trade_items.info_label[i].location.x = 370;
		trade_items.info_label[i].location.y = 365 + (i * 14);
		trade_items.info_label[i].location.w = 344;
		trade_items.info_label[i].location.h = 20;
		trade_items.info_label[i].message[0] = '\0';
	}
}

void attempt_load_trade_items_window(char *username, char *guildname)
{
	int i;

	//only open if bar visible
	if(bar.visible)
	{
		username[20] = 0;
		guildname[20] = 0;
		trade_items.our_money = 0;
		trade_items.their_money = 0;
		trade_items.our_accept = 0;
		trade_items.their_accept = 0;

		for(i=0;i<MAX_HANGER_WEAPONS;i++)
		{
			trade_items.our_gun_traded[i] = 0;
			trade_items.our_missile_traded[i] = 0;
			trade_items.their_gun_traded[i].show = 0;
			trade_items.their_missile_traded[i].show = 0;
		}

		for(i=0;i<10;i++)
		{
			trade_items.our_ship_traded[i] = 0;
			trade_items.their_ship_traded[i].show = 0;
		}

		strcpy(trade_items.username, username);
		strcpy(trade_items.guildname, guildname);

		load_purchase_trade_items();
	}
}

void load_purchase_trade_items()
{
	if(!trade_items.backround)
	{
		trade_items.backround = IMG_Load ( "graphics/trade_itemsback.jpg" );
		trade_items.empty_pod = IMG_Load ( "graphics/empty_pod.jpg" );
		trade_items.empty_pod_half = rotozoomSurface(trade_items.empty_pod, 0, 0.5, 0);
	}

	set_forms_invisible();
	trade_items.visible = 1;

	//clear things out
	clear_display_box ( NULL, &trade_items.chat_display_box );
	clear_text_box ( NULL, &trade_items.text_box[TB_TRADE_ITEMS_CHAT] );
	clear_text_box ( NULL, &trade_items.text_box[TB_TRADE_ITEMS_MONEY] );
	trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected = 1;

	//draw
	trade_items_redraw();
}

void key_trade_items ( int c )
{
	if ( c == 9 ) //tab
	{
		if ( trade_items.text_box[TB_TRADE_ITEMS_MONEY].selected )
		{
			trade_items.text_box[TB_TRADE_ITEMS_MONEY].selected = 0;
			trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected = 1;
		}
		else
		{
			trade_items.text_box[TB_TRADE_ITEMS_MONEY].selected = 1;
			trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected = 0;
		}

		trade_items_draw_money_textbox();
		trade_items_draw_chat_textbox();
		sdl_flip_mutex();
	}
	else if(c == 13) //enter
	{
		if(trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected)
		{
			trade_items_send_chat ( trade_items.text_box[TB_TRADE_ITEMS_CHAT].message );
			clear_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_CHAT] );
			sdl_flip_mutex();
		}
		else if(trade_items.text_box[TB_TRADE_ITEMS_MONEY].selected)
		{
			trade_items_set_trade_money( atoi(trade_items.text_box[TB_TRADE_ITEMS_MONEY].message) );
			clear_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_MONEY] );
			sdl_flip_mutex();
		}
	}
	else if ( c == 280 || c == 281 )
	{
		if ( c == 280 ) scroll_up_display_box ( screen, &trade_items.chat_display_box );
		if ( c == 281 ) scroll_down_display_box ( screen, &trade_items.chat_display_box );

		sdl_flip_mutex();
	}
	else
	{
		//add_text_box ( screen, &bounty.text_box[i], c );
		if ( trade_items.text_box[TB_TRADE_ITEMS_MONEY].selected )
		{
			if ( ( ! ( c >= '0' && c <= '9' ) && ! ( c == 8 || c == 127 || c == 275 || c == 276 ) ) ) return;

			add_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_MONEY], c );
			sdl_flip_mutex();
		}
		else if(trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected)
		{
			add_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_CHAT], c );
			sdl_flip_mutex();
		}
	}
}

void button_trade_items ( int x, int y )
{
	int i;
	const int button_max = B_TRADE_ITEMS_MAX_BUTTONS;
	const int text_box_max = TB_TRADE_ITEMS_MAX_TEXTBOXES;
	char rtn_str[1025];

	//buttons
	for ( i=0;i<button_max;i++ )
		if ( x >= trade_items.button[i].x && x <= trade_items.button[i].x + trade_items.button[i].w && y >= trade_items.button[i].y && y <= trade_items.button[i].y + trade_items.button[i].h )
		{
			switch(i)
			{
			case B_TRADE_ITEMS_EXIT: trade_items_exit_button(); break;
			case B_TRADE_ITEMS_ACCEPT: trade_items_accept_button(); break;
			}
			return;
		}

	//textboxes
	for ( i=0;i<text_box_max;i++ )
		if ( x >= trade_items.text_box[i].location.x && x <= trade_items.text_box[i].location.x + trade_items.text_box[i].location.w && y >= trade_items.text_box[i].location.y && y <= trade_items.text_box[i].location.y + trade_items.text_box[i].location.h )
		{
			int k;

			if ( trade_items.text_box[i].selected ) return;

			//unselect those who are
			for ( k=0;k<text_box_max;k++ )
				if ( trade_items.text_box[k].selected )
					unselect_text_box ( screen, &trade_items.text_box[k] );

			//select the lover
			select_text_box ( screen, &trade_items.text_box[i] );

			sdl_flip_mutex();
			return;
		}

	//our guns
	for ( i=0;i<MAX_HANGER_WEAPONS;i++ )
	{
		SDL_Rect &thebox = trade_items.our_gun_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//send to hub
		sprintf(rtn_str, "71,0,%d", i);
		send_con_hub(rtn_str);

		return;
	}

	//our missiles
	for ( i=0;i<MAX_HANGER_WEAPONS;i++ )
	{
		SDL_Rect &thebox = trade_items.our_missile_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//send to hub
		sprintf(rtn_str, "71,1,%d", i);
		send_con_hub(rtn_str);

		return;
	}

	//our ships
	for ( i=0;i<10;i++ )
	{
		SDL_Rect &thebox = trade_items.our_ship_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//send to hub
		sprintf(rtn_str, "71,2,%d", i);
		send_con_hub(rtn_str);

		return;
	}
}

void motion_trade_items ( int x, int y )
{
	int i;

	//our guns
	for ( i=0;i<MAX_HANGER_WEAPONS;i++ )
	{
		SDL_Rect &thebox = trade_items.our_gun_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//show
		trade_items_draw_item_info(1, 0, i);

		return;
	}

	//our missiles
	for ( i=0;i<MAX_HANGER_WEAPONS;i++ )
	{
		SDL_Rect &thebox = trade_items.our_missile_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//show
		trade_items_draw_item_info(1, 1, i);

		return;
	}

	//our ships
	for ( i=0;i<10;i++ )
	{
		SDL_Rect &thebox = trade_items.our_ship_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//send to hub
		trade_items_draw_item_info(1, 2, i);

		return;
	}

	//their guns
	for ( i=0;i<MAX_HANGER_WEAPONS;i++ )
	{
		SDL_Rect &thebox = trade_items.their_gun_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//show
		trade_items_draw_item_info(0, 0, i);

		return;
	}

	//their missiles
	for ( i=0;i<MAX_HANGER_WEAPONS;i++ )
	{
		SDL_Rect &thebox = trade_items.their_missile_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//show
		trade_items_draw_item_info(0, 1, i);

		return;
	}

	//their ships
	for ( i=0;i<10;i++ )
	{
		SDL_Rect &thebox = trade_items.their_ship_button[i];
		if(x < thebox.x) continue;
		if(y < thebox.y) continue;
		if(x > thebox.x + thebox.w) continue;
		if(y > thebox.y + thebox.h) continue;

		//send to hub
		trade_items_draw_item_info(0, 2, i);

		return;
	}

	trade_items_draw_item_info(-1, -1, -1);
}

void trade_items_exit_button()
{
	load_bar();
	bar_redraw_listing();

	send_cancel_trade_items();
}

void trade_items_accept_button()
{
	char rtn_str[50] = "72,";

	send_con_hub(rtn_str);
}

void send_cancel_trade_items()
{
	char rtn_str[50] = "68,";

	send_con_hub(rtn_str);
}

void hub_close_trade_items_window()
{
	if(!trade_items.visible) return;

	load_bar();
	bar_redraw_listing();
}

void trade_items_redraw()
{
	//the back
	SDL_BlitSurface ( trade_items.backround, NULL, screen, NULL );

	//money
	trade_items_draw_money();

	//textboxes
	trade_items_draw_money_textbox();
	trade_items_draw_chat_textbox();

	//display box
	draw_display_box ( screen, &trade_items.chat_display_box );

	//user labels
	trade_items_draw_our_user_label();
	trade_items_draw_their_user_label();

	//accept trade button
	trade_items_draw_accept_label();

	//static labels
	trade_items_draw_static_labels();

	//money labels
	trade_items_draw_our_money_label();
	trade_items_draw_their_money_label();

	//items
	trade_items_draw_our_guns();
	trade_items_draw_our_missiles();
	trade_items_draw_our_ships();

	sdl_flip_mutex();
}

void trade_items_draw_item_info(int ours, int item_type, int i)
{
	static int last_ours = -1;
	static int last_item_type = -1;
	static int last_i = -1;
	char temp_str[200];
	char sname[200];
	int w, w_id;
	int d, s, a, dboo, sboo, aboo, dp, sp, ap, oap;
	int sh_id, sh_b, sh_t, sh_ref;

	if(last_ours == ours && last_item_type == item_type && last_i == i) return;

	last_ours = ours;
	last_item_type = item_type;
	last_i = i;

	//clear area
	if(ours == -1 || item_type == -1 || i == -1)
	{
		trade_items_draw_item_info_clear();
		return;
	}

	if(ours)
	{
		switch(item_type)
		{
		case 0:
			w = game.hanger_gun[i].w;
			w_id = game.hanger_gun[i].w_id;

			if(w < 0 || w_id < 0) { trade_items_draw_item_info_clear(); return; }

			d = server[w_id].gun[w].damage;
			s = server[w_id].gun[w].speed;
			a = server[w_id].gun[w].accuracy;
			dboo = game.hanger_gun[i].damage_boost;
			sboo = game.hanger_gun[i].speed_boost;
			aboo = game.hanger_gun[i].accuracy_boost;
			if(d) dp = 100 * dboo / d;
			if(100 - s) sp = 100 * sboo / (100 - s);
			if(100 - a) ap = 100 * aboo / (100 - a);
			oap = (dp + sp + ap) / 3;

			sprintf(temp_str, "%s", server[w_id].gun[w].name);
			draw_label ( screen, temp_str, &trade_items.info_label[0], 250, 250, 250 );
			sprintf(temp_str, "Damage: %d +%d%%", d + dboo, dp);
			draw_label ( screen, temp_str, &trade_items.info_label[1], 250, 250, 250 );
			sprintf(temp_str, "Speed: %d +%d%%", s + sboo, sp);
			draw_label ( screen, temp_str, &trade_items.info_label[2], 250, 250, 250 );
			sprintf(temp_str, "Accuracy: %d +%d%%", a + aboo, ap);
			draw_label ( screen, temp_str, &trade_items.info_label[3], 250, 250, 250 );
			sprintf(temp_str, "Overall Boost Percent: %d%%", oap);
			draw_label ( screen, temp_str, &trade_items.info_label[4], 250, 250, 250 );
			break;
		case 1:
			w = game.hanger_missile[i].w;
			w_id = game.hanger_missile[i].w_id;

			if(w < 0 || w_id < 0) { trade_items_draw_item_info_clear(); return; }

			d = server[w_id].missile[w].damage;
			s = server[w_id].missile[w].speed;
			a = server[w_id].missile[w].accuracy;
			dboo = game.hanger_missile[i].damage_boost;
			sboo = game.hanger_missile[i].speed_boost;
			aboo = game.hanger_missile[i].accuracy_boost;
			if(d) dp = 100 * dboo / d;
			if(100 - s) sp = 100 * sboo / (100 - s);
			if(100 - a) ap = 100 * aboo / (100 - a);
			oap = (dp + sp + ap) / 3;

			sprintf(temp_str, "%s", server[w_id].missile[w].name);
			draw_label ( screen, temp_str, &trade_items.info_label[0], 250, 250, 250 );
			sprintf(temp_str, "Damage: %d +%d%%", d + dboo, dp);
			draw_label ( screen, temp_str, &trade_items.info_label[1], 250, 250, 250 );
			sprintf(temp_str, "Speed: %d +%d%%", s + sboo, sp);
			draw_label ( screen, temp_str, &trade_items.info_label[2], 250, 250, 250 );
			sprintf(temp_str, "Accuracy: %d +%d%%", a + aboo, ap);
			draw_label ( screen, temp_str, &trade_items.info_label[3], 250, 250, 250 );
			sprintf(temp_str, "Overall Boost Percent: %d%%", oap);
			draw_label ( screen, temp_str, &trade_items.info_label[4], 250, 250, 250 );
			break;
		case 2:
			sh_id = hanger.ship[i].server_id;
			sh_b = hanger.ship[i].type;
			sh_t = hanger.ship[i].kind;
			sh_ref = hanger.ship[i].ref;

			if(sh_id < 0 || sh_b < 0 || sh_t < 0) { trade_items_draw_item_info_clear(); return; }

			sprintf(temp_str, "%s %s", server[sh_id].ship[sh_b].name, ship_name(sh_t, sname));
			draw_label ( screen, temp_str, &trade_items.info_label[0], 250, 250, 250 );
			sprintf(temp_str, "Ref: %d", sh_ref);
			draw_label ( screen, temp_str, &trade_items.info_label[1], 250, 250, 250 );
			draw_label ( screen,"", &trade_items.info_label[2], 250, 250, 250 );
			draw_label ( screen,"", &trade_items.info_label[3], 250, 250, 250 );
			draw_label ( screen,"", &trade_items.info_label[4], 250, 250, 250 );
			break;
		}
	}
	else
	{
		switch(item_type)
		{
		case 0:
			if(!trade_items.their_gun_traded[i].show) { trade_items_draw_item_info_clear(); return; }

			w = trade_items.their_gun_traded[i].w;
			w_id = trade_items.their_gun_traded[i].w_id;

			if(w < 0 || w_id < 0) { trade_items_draw_item_info_clear(); return; }

			d = server[w_id].gun[w].damage;
			s = server[w_id].gun[w].speed;
			a = server[w_id].gun[w].accuracy;
			dboo = trade_items.their_gun_traded[i].damage_boost;
			sboo = trade_items.their_gun_traded[i].speed_boost;
			aboo = trade_items.their_gun_traded[i].accuracy_boost;
			if(d) dp = 100 * dboo / d;
			if(100 - s) sp = 100 * sboo / (100 - s);
			if(100 - a) ap = 100 * aboo / (100 - a);
			oap = (dp + sp + ap) / 3;

			sprintf(temp_str, "%s", server[w_id].gun[w].name);
			draw_label ( screen, temp_str, &trade_items.info_label[0], 250, 250, 250 );
			sprintf(temp_str, "Damage: %d ... +%d%%", d + dboo, dp);
			draw_label ( screen, temp_str, &trade_items.info_label[1], 250, 250, 250 );
			sprintf(temp_str, "Speed: %d ... +%d%%", s + sboo, sp);
			draw_label ( screen, temp_str, &trade_items.info_label[2], 250, 250, 250 );
			sprintf(temp_str, "Accuracy: %d ... +%d%%", a + aboo, ap);
			draw_label ( screen, temp_str, &trade_items.info_label[3], 250, 250, 250 );
			sprintf(temp_str, "Overall Boost Percent: %d%%", oap);
			draw_label ( screen, temp_str, &trade_items.info_label[4], 250, 250, 250 );
			break;
		case 1:
			if(!trade_items.their_missile_traded[i].show) { trade_items_draw_item_info_clear(); return; }

			w = trade_items.their_missile_traded[i].w;
			w_id = trade_items.their_missile_traded[i].w_id;

			if(w < 0 || w_id < 0) { trade_items_draw_item_info_clear(); return; }

			d = server[w_id].missile[w].damage;
			s = server[w_id].missile[w].speed;
			a = server[w_id].missile[w].accuracy;
			dboo = trade_items.their_missile_traded[i].damage_boost;
			sboo = trade_items.their_missile_traded[i].speed_boost;
			aboo = trade_items.their_missile_traded[i].accuracy_boost;
			if(d) dp = 100 * dboo / d;
			if(100 - s) sp = 100 * sboo / (100 - s);
			if(100 - a) ap = 100 * aboo / (100 - a);
			oap = (dp + sp + ap) / 3;

			sprintf(temp_str, "%s", server[w_id].missile[w].name);
			draw_label ( screen, temp_str, &trade_items.info_label[0], 250, 250, 250 );
			sprintf(temp_str, "Damage: %d ... +%d%%", d + dboo, dp);
			draw_label ( screen, temp_str, &trade_items.info_label[1], 250, 250, 250 );
			sprintf(temp_str, "Speed: %d ... +%d%%", s + sboo, sp);
			draw_label ( screen, temp_str, &trade_items.info_label[2], 250, 250, 250 );
			sprintf(temp_str, "Accuracy: %d ... +%d%%", a + aboo, ap);
			draw_label ( screen, temp_str, &trade_items.info_label[3], 250, 250, 250 );
			sprintf(temp_str, "Overall Boost Percent: %d%%", oap);
			draw_label ( screen, temp_str, &trade_items.info_label[4], 250, 250, 250 );
			break;
		case 2:
			if(!trade_items.their_ship_traded[i].show) { trade_items_draw_item_info_clear(); return; }

			sh_id = trade_items.their_ship_traded[i].sh_id;
			sh_b = trade_items.their_ship_traded[i].sh_b;
			sh_t = trade_items.their_ship_traded[i].sh_t;
			sh_ref = trade_items.their_ship_traded[i].ref;

			if(sh_id < 0 || sh_b < 0 || sh_t < 0) { trade_items_draw_item_info_clear(); return; }

			sprintf(temp_str, "%s %s", server[sh_id].ship[sh_b].name, ship_name(sh_t, sname));
			draw_label ( screen, temp_str, &trade_items.info_label[0], 250, 250, 250 );
			sprintf(temp_str, "Ref: %d", sh_ref);
			draw_label ( screen, temp_str, &trade_items.info_label[1], 250, 250, 250 );
			draw_label ( screen,"", &trade_items.info_label[2], 250, 250, 250 );
			draw_label ( screen,"", &trade_items.info_label[3], 250, 250, 250 );
			draw_label ( screen,"", &trade_items.info_label[4], 250, 250, 250 );
			break;
		}
	}

	sdl_flip_mutex();
}

void trade_items_draw_item_info_clear()
{
	int i;

	for(i=0;i<TRADE_ITEMS_INFO_LABELS_MAX;i++)
		draw_label ( screen,"", &trade_items.info_label[i], 250, 250, 250 );

	sdl_flip_mutex();
}

void trade_items_draw_money()
{
	char temp_str[200];

	sprintf ( temp_str,"%d", game.money );
	draw_right_label ( screen, temp_str, &trade_items.money_label, 107, 216, 210 );
}

void trade_items_draw_money_textbox()
{
	if ( trade_items.text_box[TB_TRADE_ITEMS_MONEY].selected )
		select_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_MONEY] );
	else
		unselect_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_MONEY] );
}

void trade_items_draw_chat_textbox()
{
	if ( trade_items.text_box[TB_TRADE_ITEMS_CHAT].selected )
		select_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_CHAT] );
	else
		unselect_text_box ( screen, &trade_items.text_box[TB_TRADE_ITEMS_CHAT] );
}

void trade_items_draw_our_user_label()
{
	char temp_str[200];

	sprintf(temp_str, "%s : %s", game.username, game.guild.name);

	if(trade_items.our_accept)
		draw_center_label ( screen, temp_str, &trade_items.our_user_label, 250, 0, 0 );
	else
		draw_center_label ( screen, temp_str, &trade_items.our_user_label, 250, 250, 250 );
}

void trade_items_draw_their_user_label()
{
	char temp_str[200];

	sprintf(temp_str, "%s : %s", trade_items.username, trade_items.guildname);

	if(trade_items.their_accept)
		draw_center_label ( screen, temp_str, &trade_items.their_user_label, 250, 0, 0 );
	else
		draw_center_label ( screen, temp_str, &trade_items.their_user_label, 250, 250, 250 );
}

void trade_items_draw_accept_label()
{
	if(trade_items.our_accept)
		draw_center_label ( screen,"Retract", &trade_items.accept_label, 250, 0, 0 );
	else
		draw_center_label ( screen,"Accept", &trade_items.accept_label, 250, 0, 0 );
}

void trade_items_draw_static_labels()
{
	SDL_Rect dest;

	draw_center_label ( screen,"Guns", &trade_items.our_guns_label, 250, 250, 0 );
	draw_center_label ( screen,"Missiles", &trade_items.our_missiles_label, 250, 250, 0 );
	draw_center_label ( screen,"Ships", &trade_items.our_ships_label, 250, 250, 0 );

	draw_center_label ( screen,"Guns", &trade_items.their_guns_label, 250, 250, 0 );
	draw_center_label ( screen,"Missiles", &trade_items.their_missiles_label, 250, 250, 0 );
	draw_center_label ( screen,"Ships", &trade_items.their_ships_label, 250, 250, 0 );
	//draw_raw_label(server_select.backround, server_select.servername[i], destination, 255, 255, 255);
}

void trade_items_draw_our_money_label()
{
	char temp_str[200];

	sprintf(temp_str, "Offered Money : %d", trade_items.our_money);
	draw_center_label ( screen, temp_str, &trade_items.our_money_label, 250, 250, 0 );
}

void trade_items_draw_their_money_label()
{
	char temp_str[200];

	sprintf(temp_str, "Offered Money : %d", trade_items.their_money);
	draw_center_label ( screen, temp_str, &trade_items.their_money_label, 250, 250, 0 );
}

void trade_items_draw_our_guns()
{
	int i;

	for(i=0;i<MAX_HANGER_WEAPONS;i++)
	{
		int w, w_id;
		SDL_Rect *rend_loc;

		rend_loc = &trade_items.our_gun_button[i];

		w = game.hanger_gun[i].w;
		w_id = game.hanger_gun[i].w_id;

		if(w > -1 && w_id > -1)
		{
			if (load_gun_pod_img_specific ( w_id, w ))
				SDL_BlitSurface ( server[w_id].gun[w].gun_pod_img_half, NULL, screen, rend_loc );
			else
				SDL_BlitSurface ( game.nif_image.no_gun_pod_half, NULL, screen, rend_loc );
		}
		else
			SDL_BlitSurface ( trade_items.empty_pod_half, NULL, screen, rend_loc );
	}
}

void trade_items_draw_their_gun(int i)
{
	int w, w_id;
	SDL_Rect *rend_loc;

	if(i<0) return;
	if(i>=MAX_HANGER_WEAPONS) return;

	rend_loc = &trade_items.their_gun_button[i];

	w = trade_items.their_gun_traded[i].w;
	w_id = trade_items.their_gun_traded[i].w_id;

	if(!trade_items.their_gun_traded[i].show)
	{
		SDL_FillRect(screen, rend_loc, SDL_MapRGB ( screen->format, 0, 0, 0 ) );
		return;
	}

	if(w > -1 && w_id > -1)
	{
		if (load_gun_pod_img_specific ( w_id, w ))
			SDL_BlitSurface ( server[w_id].gun[w].gun_pod_img_half, NULL, screen, rend_loc );
		else
			SDL_BlitSurface ( game.nif_image.no_gun_pod_half, NULL, screen, rend_loc );
	}
	else
		SDL_BlitSurface ( trade_items.empty_pod_half, NULL, screen, rend_loc );
}

void trade_items_draw_our_missiles()
{
	int i;

	for(i=0;i<MAX_HANGER_WEAPONS;i++)
	{
		int w, w_id;
		SDL_Rect *rend_loc;

		rend_loc = &trade_items.our_missile_button[i];

		w = game.hanger_missile[i].w;
		w_id = game.hanger_missile[i].w_id;

		if(w > -1 && w_id > -1)
		{
			if (load_missile_pod_img_specific ( w_id, w ))
				SDL_BlitSurface ( server[w_id].missile[w].missile_pod_img_half, NULL, screen, rend_loc );
			else
				SDL_BlitSurface ( game.nif_image.no_missile_pod_half, NULL, screen, rend_loc );
		}
		else
			SDL_BlitSurface ( trade_items.empty_pod_half, NULL, screen, rend_loc );
	}
}

void trade_items_draw_their_missile(int i)
{
	int w, w_id;
	SDL_Rect *rend_loc;

	if(i<0) return;
	if(i>=MAX_HANGER_WEAPONS) return;

	rend_loc = &trade_items.their_missile_button[i];

	w = trade_items.their_missile_traded[i].w;
	w_id = trade_items.their_missile_traded[i].w_id;

	if(!trade_items.their_missile_traded[i].show)
	{
		SDL_FillRect(screen, rend_loc, SDL_MapRGB ( screen->format, 0, 0, 0 ) );
		return;
	}

	if(w > -1 && w_id > -1)
	{
		if (load_missile_pod_img_specific ( w_id, w ))
			SDL_BlitSurface ( server[w_id].missile[w].missile_pod_img_half, NULL, screen, rend_loc );
		else
			SDL_BlitSurface ( game.nif_image.no_missile_pod_half, NULL, screen, rend_loc );
	}
	else
		SDL_BlitSurface ( trade_items.empty_pod_half, NULL, screen, rend_loc );
}

void trade_items_draw_our_ships()
{
	int i;

	for(i=0;i<10;i++)
	{
		int sh_id, sh_t, sh_k;
		SDL_Rect *rend_loc;

		rend_loc = &trade_items.our_ship_button[i];

		sh_id = hanger.ship[i].server_id;
		sh_t = hanger.ship[i].type;
		sh_k = hanger.ship[i].kind;

		if(sh_id < 0) continue;
		if(sh_t < 0) continue;
		if(sh_k < 0) continue;

		if ( load_fship ( sh_id, sh_t, sh_k, 0, server[sh_id].ship[sh_t].name ) )
			SDL_BlitSurface ( server[sh_id].ship[sh_t].fship_img[sh_k][0], NULL, screen, rend_loc );
		else
			SDL_BlitSurface ( hanger.no_fship[sh_k][0], NULL, screen, rend_loc );
	}
}

void trade_items_draw_their_ship(int i)
{
	if(i<0) return;
	if(i>=10) return;

	int sh_id, sh_t, sh_k;
	SDL_Rect *rend_loc;

	rend_loc = &trade_items.their_ship_button[i];

	if(!trade_items.their_ship_traded[i].show)
	{
		SDL_FillRect(screen, rend_loc, SDL_MapRGB ( screen->format, 0, 0, 0 ) );
		return;
	}

	sh_id = trade_items.their_ship_traded[i].sh_id;
	sh_t = trade_items.their_ship_traded[i].sh_b;
	sh_k = trade_items.their_ship_traded[i].sh_t;

	if(sh_id < 0) return;
	if(sh_t < 0) return;
	if(sh_k < 0) return;

	if ( load_fship ( sh_id, sh_t, sh_k, 0, server[sh_id].ship[sh_t].name ) )
		SDL_BlitSurface ( server[sh_id].ship[sh_t].fship_img[sh_k][0], NULL, screen, rend_loc );
	else
		SDL_BlitSurface ( hanger.no_fship[sh_k][0], NULL, screen, rend_loc );
}

void trade_items_send_chat( char *message )
{
	char rtn_str[500];

	sprintf ( rtn_str, "69,%s", message );
	send_con_hub ( rtn_str );
	//add_display_box ( screen, &trade_items.chat_display_box, 0, message );
	//sdl_flip_mutex();
}

void trade_items_set_trade_money( int money )
{
	char rtn_str[500];

	sprintf ( rtn_str, "70,%d", money );
	send_con_hub ( rtn_str );
}

void hub_set_trade_items_money(int our_money, int money_amount)
{
	if(!trade_items.visible) return;

	if(our_money)
	{
		trade_items.our_money = money_amount;
		trade_items_draw_our_money_label();
		sdl_flip_mutex();
	}
	else
	{
		trade_items.their_money = money_amount;
		trade_items_draw_their_money_label();
		sdl_flip_mutex();
	}
}

void hub_set_trade_items_our_item_onoff(int item_type, int item_num, int is_on)
{
	SDL_Rect thebox;
	int x1, y1, x2, y2;

	if(!trade_items.visible) return;

	if(item_num < 0) return;

	switch(item_type)
	{
	case 0: //gun
		if(item_num >= MAX_HANGER_WEAPONS) return;

		trade_items.our_gun_traded[item_num] = is_on;

		thebox = trade_items.our_gun_button[item_num];

		x1 = thebox.x-1;
		y1 = thebox.y-1;
		x2 = thebox.x + thebox.w + 2;
		y2 = thebox.y + thebox.h + 2;

		//SDL_FillRect ( screen, &thebox, SDL_MapRGB ( screen->format, 255, 0, 0 ) );
		if(is_on)
			rectangleRGBA(screen, x1, y1, x2, y2, 255, 0, 0, 255);
		else
			rectangleRGBA(screen, x1, y1, x2, y2, 0, 0, 0, 255);

		sdl_flip_mutex();

		break;
	case 1: //missile
		if(item_num >= MAX_HANGER_WEAPONS) return;

		trade_items.our_missile_traded[item_num] = is_on;

		thebox = trade_items.our_missile_button[item_num];

		x1 = thebox.x-1;
		y1 = thebox.y-1;
		x2 = thebox.x + thebox.w + 2;
		y2 = thebox.y + thebox.h + 2;

		if(is_on)
			rectangleRGBA(screen, x1, y1, x2, y2, 255, 0, 0, 255);
		else
			rectangleRGBA(screen, x1, y1, x2, y2, 0, 0, 0, 255);

		sdl_flip_mutex();

		break;
	case 2: //ship
		if(item_num >= 10) return;

		trade_items.our_ship_traded[item_num] = is_on;

		thebox = trade_items.our_ship_button[item_num];

		x1 = thebox.x-1;
		y1 = thebox.y-1;
		x2 = thebox.x + thebox.w + 2;
		y2 = thebox.y + thebox.h + 2;

		if(is_on)
			rectangleRGBA(screen, x1, y1, x2, y2, 255, 0, 0, 255);
		else
			rectangleRGBA(screen, x1, y1, x2, y2, 0, 0, 0, 255);

		sdl_flip_mutex();

		break;
	}
}

void hub_set_trade_items_their_item_onoff(int item_type, int item_num, int is_on, char *message)
{
	int w, w_id, dboo, sboo, aboo;
	int sh_id, sh_b, sh_t, ref;
	char temp_str[1025];
	int point = 0;

	if(!trade_items.visible) return;

	if(item_num < 0) return;

	switch(item_type)
	{
	case 0: //gun
		if(item_num >= MAX_HANGER_WEAPONS) return;

		trade_items.their_gun_traded[item_num].show = is_on;

		split(temp_str, message, ',', &point);
		w_id = atoi(temp_str);
		split(temp_str, message, ',', &point);
		w = atoi(temp_str);
		split(temp_str, message, ',', &point);
		dboo = atoi(temp_str);
		split(temp_str, message, ',', &point);
		sboo = atoi(temp_str);
		split(temp_str, message, ',', &point);
		aboo = atoi(temp_str);

		trade_items.their_gun_traded[item_num].w = w;
		trade_items.their_gun_traded[item_num].w_id = w_id;
		trade_items.their_gun_traded[item_num].damage_boost = dboo;
		trade_items.their_gun_traded[item_num].speed_boost = sboo;
		trade_items.their_gun_traded[item_num].accuracy_boost = aboo;

		trade_items_draw_their_gun(item_num);
		sdl_flip_mutex();

		break;
	case 1: //missile
		if(item_num >= MAX_HANGER_WEAPONS) return;

		trade_items.their_missile_traded[item_num].show = is_on;

		split(temp_str, message, ',', &point);
		w_id = atoi(temp_str);
		split(temp_str, message, ',', &point);
		w = atoi(temp_str);
		split(temp_str, message, ',', &point);
		dboo = atoi(temp_str);
		split(temp_str, message, ',', &point);
		sboo = atoi(temp_str);
		split(temp_str, message, ',', &point);
		aboo = atoi(temp_str);

		trade_items.their_missile_traded[item_num].w = w;
		trade_items.their_missile_traded[item_num].w_id = w_id;
		trade_items.their_missile_traded[item_num].damage_boost = dboo;
		trade_items.their_missile_traded[item_num].speed_boost = sboo;
		trade_items.their_missile_traded[item_num].accuracy_boost = aboo;

		trade_items_draw_their_missile(item_num);
		sdl_flip_mutex();
		break;
	case 2: //ship
		if(item_num >= 10) return;

		trade_items.their_ship_traded[item_num].show = is_on;

		split(temp_str, message, ',', &point);
		sh_id = atoi(temp_str);
		split(temp_str, message, ',', &point);
		sh_b = atoi(temp_str);
		split(temp_str, message, ',', &point);
		sh_t = atoi(temp_str);
		split(temp_str, message, ',', &point);
		ref = atoi(temp_str);

		trade_items.their_ship_traded[item_num].sh_id = sh_id;
		trade_items.their_ship_traded[item_num].sh_b = sh_b;
		trade_items.their_ship_traded[item_num].sh_t = sh_t;
		trade_items.their_ship_traded[item_num].ref = ref;

		trade_items_draw_their_ship(item_num);
		sdl_flip_mutex();
		break;
	}
}

void hub_set_trade_items_accepted(int is_ours, int accepted)
{
	if(is_ours)
	{
		trade_items.our_accept = accepted;

		trade_items_draw_accept_label();
		trade_items_draw_our_user_label();
	}
	else
	{
		trade_items.their_accept = accepted;

		trade_items_draw_their_user_label();
	}

	sdl_flip_mutex();
}
