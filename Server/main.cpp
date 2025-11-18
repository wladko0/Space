#include "main.h"

void init_memory();
void main_loop();

int main()
{
	create_folders();
	init_memory();
	read_all_db();
	//connect_to_hub();
	//start_server();
	init_server_hub();
	init_server_user();
	//start_gun_thread();
	start_bot_threadless();
	//start_sun_thread();
	main_loop();
	return 0;
}

void init_memory()
{
	srand(time(0));

	user_con_top = -1;

	clear_sector_goods();

	clear_all_sat_info();

	set_default_sat_shields();
}

void main_loop()
{
	double next_user_ping_time = 0;
	double next_hub_ping_time = 0;
	double next_bot_clear_goods_time = 0;
	double the_time;
	double next_gun_thread_time = 0;
	double next_bot_thread_time = 0;
	double next_sun_thread_time = 0;

	while(1)
	{
		the_time = current_time();

		//do some packet processing
		server_hub_threadless();
		server_user_threadless();

		//if(the_time - last_user_ping_time >= PING_USER_DELAY_SECONDS)
		if(the_time >= next_user_ping_time)
		{
			ping_all_users();
			next_user_ping_time = the_time + PING_USER_DELAY_SECONDS;
		}

		//if(the_time - last_hub_ping_time >= PING_HUB_DELAY_SECONDS)
		if(the_time >= next_hub_ping_time)
		{
			ping_hub();
			next_hub_ping_time = the_time + PING_HUB_DELAY_SECONDS;
		}

		//if(the_time - last_bot_clear_goods_time >= CLEAR_BOT_GOODS_DELAY_SECONDS)
		if(the_time >= next_hub_ping_time)
		{
			bot_clear_all_bot_goods();
			next_hub_ping_time = the_time + CLEAR_BOT_GOODS_DELAY_SECONDS;
		}

		//old gun thread
		if(the_time >= next_gun_thread_time)
		{
			gun_threadless();
			next_gun_thread_time = the_time + 0.25;
		}

		//old bot thread
		if(the_time >= next_bot_thread_time)
		{
			bot_threadless();
			next_bot_thread_time = the_time + 1.0;
		}

		//old sun thread
		if(the_time >= next_sun_thread_time)
		{
			sun_threadless();
			next_sun_thread_time = the_time + 1.0;
		}

		uni_pause(10);
	}
}