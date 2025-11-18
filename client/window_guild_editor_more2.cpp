#include "main.h"

void init_form_guild_editor_more2()
{
	int i;

	guild_editor_more2.backround = NULL;
	guild_editor_more2.visible = 0;
	guild_editor_more2.button[B_GEM2_EXIT].x = 530;
	guild_editor_more2.button[B_GEM2_EXIT].y = 415;
	guild_editor_more2.button[B_GEM2_EXIT].w = 63;
	guild_editor_more2.button[B_GEM2_EXIT].h = 20;
	guild_editor_more2.button[B_GEM2_SAVE_SETTINGS].x = 217;
	guild_editor_more2.button[B_GEM2_SAVE_SETTINGS].y = 418;
	guild_editor_more2.button[B_GEM2_SAVE_SETTINGS].w = 326 - 217;
	guild_editor_more2.button[B_GEM2_SAVE_SETTINGS].h = 436 - 418;
	guild_editor_more2.gexp_label.location.x = 188;
	guild_editor_more2.gexp_label.location.y = 92;
	guild_editor_more2.gexp_label.location.w = 144 - 188;
	guild_editor_more2.gexp_label.location.h = 17;
	guild_editor_more2.gexp_label.message[0] = '\0';
	guild_editor_more2.gexp_label.location.x += ( 400 - ( 480 / 2 ) );
	guild_editor_more2.gexp_label.location.y += ( 300 - ( 360 / 2 ) );
	for(i=B_GEM2_SETTING0;i<=B_GEM2_SETTING6;i++)
	{
		guild_editor_more2.button[i].x = 74;
		guild_editor_more2.button[i].y = 263 - ((i-B_GEM2_SETTING0)*21);
		guild_editor_more2.button[i].w = 20;
		guild_editor_more2.button[i].h = 20;

		guild_editor_more2.button[i].x += ( 400 - ( 480 / 2 ) );
		guild_editor_more2.button[i].y += ( 300 - ( 360 / 2 ) );
	}
	for(i=0;i<MAX_GEM2_SETTINGS;i++)
	{
		guild_editor_more2.exp_label[i].location.x = 110;
		guild_editor_more2.exp_label[i].location.y = guild_editor_more2.button[i+B_GEM2_SETTING0].y;
		guild_editor_more2.exp_label[i].location.w = 144 - 110;
		guild_editor_more2.exp_label[i].location.h = 17;
		guild_editor_more2.exp_label[i].message[0] = '\0';

		guild_editor_more2.desc_label[i].location.x = 158;
		guild_editor_more2.desc_label[i].location.y = guild_editor_more2.button[i+B_GEM2_SETTING0].y;
		guild_editor_more2.desc_label[i].location.w = 420 - 158;
		guild_editor_more2.desc_label[i].location.h = 17;
		guild_editor_more2.desc_label[i].message[0] = '\0';

		guild_editor_more2.exp_label[i].location.x += ( 400 - ( 480 / 2 ) );
		guild_editor_more2.exp_label[i].location.y += 3;

		guild_editor_more2.desc_label[i].location.x += ( 400 - ( 480 / 2 ) );
		guild_editor_more2.desc_label[i].location.y += 3;
	}
}

void load_guild_editor_more2()
{
	SDL_Rect destination;

	if ( !guild_editor_more2.backround )
	{
		guild_editor_more2.backround = IMG_Load ( "graphics/guildeditor_more2.jpg" );
		guild_editor_more2.on = IMG_Load ( "graphics/guild_on.jpg" );
		guild_editor_more2.off = IMG_Load ( "graphics/guild_off.jpg" );
	}

	destination.x = 400 - ( 480 / 2 );
	destination.y = 300 - ( 360 / 2 );

	set_forms_invisible();
	guild_editor_more2.visible = 1;
	SDL_BlitSurface ( guild_editor_more2.backround, NULL, screen, &destination );

	//draw
	guild_editor_more2_draw_choices();
	guild_editor_more2_draw_exp();
	//guild_editor_more2_draw_labels();

	sdl_flip_mutex();
}

void button_guild_editor_more2 ( int x, int y )
{
	int i;

	for ( i=0;i<B_GEM2_MAX_BUTTONS;i++ )
	{
		if(x < guild_editor_more2.button[i].x) continue;
		if(x > guild_editor_more2.button[i].x + guild_editor_more2.button[i].w) continue;
		if(y < guild_editor_more2.button[i].y) continue;
		if(y > guild_editor_more2.button[i].y + guild_editor_more2.button[i].h) continue;

		switch(i)
		{
		case B_GEM2_EXIT:
			load_guild_editor_more();
			break;
		case B_GEM2_SAVE_SETTINGS:
			guild_editor_more2_save_settings();
			break;
		case B_GEM2_SETTING0:
		case B_GEM2_SETTING1:
		case B_GEM2_SETTING2:
		case B_GEM2_SETTING3:
		case B_GEM2_SETTING4:
		case B_GEM2_SETTING5:
		case B_GEM2_SETTING6:
			guild_editor_more2_change_setting(i);
			break;
		}

		break;
	}
	
}

void guild_editor_more2_change_setting(int setting)
{
	int m;
	char rtn_str[1025];

	m = (setting + 1) - B_GEM2_SETTING0;

	sprintf(rtn_str, "73,%d", m);
	send_con_hub(rtn_str);
}

void guild_editor_more2_save_settings()
{
	//printf("guild_editor_more2_save_settings\n");
}

void guild_editor_more2_draw_choices()
{
	int i, m;

	for(i=B_GEM2_SETTING0;i<=B_GEM2_SETTING6;i++)
	{
		m = (i + 1) - B_GEM2_SETTING0;

		if(game.guild.mode == m)
			SDL_BlitSurface ( guild_editor_more2.on, NULL, screen, &guild_editor_more2.button[i] );
		else if(game.guild.exp >= guild_mode_exp(m))
			SDL_BlitSurface ( guild_editor_more2.off, NULL, screen, &guild_editor_more2.button[i] );
		else
			SDL_FillRect ( screen, &guild_editor_more2.button[i], SDL_MapRGB ( screen->format, 0, 0, 0 ) );
	}
}

void guild_editor_more2_draw_exp()
{
	char temp_str[50];

	sprintf(temp_str, "%d", game.guild.exp);
	draw_label ( screen, temp_str, &guild_editor_more2.gexp_label, 107, 216, 210 );
}

void guild_editor_more2_draw_labels()
{
	int i;
	char temp_str[1000];

	for(i=0;i<MAX_GEM2_SETTINGS;i++)
	{
		sprintf(temp_str, "%d", guild_mode_exp(i+1));
		draw_right_label ( screen, temp_str, &guild_editor_more2.exp_label[i], 107, 216, 210 );
		draw_label ( screen, guild_mode_desc(i+1, temp_str), &guild_editor_more2.desc_label[i], 107, 216, 210 );
	}
}
