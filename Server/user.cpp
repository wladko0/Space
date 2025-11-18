#include "main.h"
#include <sstream>

void send_user_sector_info ( int con );
void tell_hub_user_payload ( int con );
void *gun_thread ( void *nothing );

//*NEW random stuff need to be generated
//why ???
typedef unsigned int  u4;

#define rot(x,k) (((x)<<(k))|((x)>>(32-(k))))
static u4 ranval( ranctx *x ) {
    u4 e = x->a - rot(x->b, 27);
    x->a = x->b ^ rot(x->c, 17);
    x->b = x->c + x->d;
    x->c = x->d + e;
    x->d = e + x->a;
    return x->d;
}

static void raninit( ranctx *x, u4 seed ) {
    u4 i;
    x->a = 0xf1ea5eed, x->b = x->c = x->d = seed;
    for (i=0; i<20; ++i) {
        (void)ranval(x);
    }
}

//*NEW end random stuff generation

void user_logoff ( int con )
{
	//stuff that may need to be done here
	if ( user_con[con].username[0] )
	{
		int z, s;

		z = user_con[con].zone;
		s = user_con[con].sector;

		//you skimming mother fucker
		check_user_skimmed(con);

		//kill the bastard if need
		if ( !user_con[con].landed )
		{
			if ( z > -1 && s > -1 )
				if ( zone[z].sector[s].planet < 0 )
					if ( current_time() - user_con[con].last_attacked_time <= SAFE_DISCONNECT_TIME )
						destroy_user_disconnecting ( con );
		}

		//leave sector if in it
		if ( !user_con[con].landed && z > -1 && s > -1 )
			relay_user_leave_sector ( con, s, z );

		//leave bar if in it
		if ( user_con[con].landed && user_con[con].inbar )
			user_leave_bar ( con );

		//tell the people
		update_users_on_online_players();
	}

	con_clear_stat ( con );
}

void con_clear_stat ( int con )
{
	//get them off the listsss
	user_remove_from_all_lists ( con );

	user_con[con].username[0]	 = '\0';
	user_con[con].guild[0]	 	= '\0';
	user_con[con].user_id		 = 0;
	user_con[con].has_galaxy_info	 = 0;
	user_con[con].inbar		 = 0;
	user_con[con].landed		 = 1;
	user_con[con].ship.class_name[0] = '\0';
	user_con[con].ship.server_id 	= -1;
	user_con[con].ship.kind 	= -1;
	user_con[con].ship.type 	= -1;
	user_con[con].sector		= -1;
	user_con[con].zone		= -1;
	user_con[con].user_attacking 	= -1;
	user_con[con].attacking_bot 	= 0;
	user_con[con].attacking_sat 	= 0;
	user_con[con].update_hull 	= 0;
	user_con[con].update_missiles 	= 0;
	user_con[con].update_guns 	= 0;
	user_con[con].has_goods 	= 0;
	user_con[con].has_rune 		= -1;
	user_con[con].last_missile_time = 0;
	user_con[con].last_attacker	= -1;
	user_con[con].destroy_on_recv = 0;
	user_con[con].last_jump_dock_time = 0;
}

void con_user_connect ( int con )
{
	 //send client initial stuff upon initial connection
	user_con[con].last_attacked_time = current_time() - ( SAFE_DISCONNECT_TIME + 1 );
    //*NEW implement ranint from begining of this file
    //what is this for ??
	raninit(&user_con[con].rnd, time(NULL));
}

void send_user_galaxy_info ( int con )
{
	int i, k, z;
	char rtn_str[1025], cat_str[50];

	//tell client home class (even though its not needed?)
	sprintf ( rtn_str, "1,0,-5,%d", server_info.home_class );
	send_con_user ( con, rtn_str );

	for ( i=0;i<PLANET_MAX;i++ ) //basicly we send the databases in the same format that they are read from file.
		if ( planet[i].name[0] != '\0' )
		{
			sprintf ( rtn_str, "1,%d,%d,%d,%s,%s,%d,%s,%d,%d,%d,%d,%d,%d",
					i,
					planet[i].is_gate,
					planet[i].is_home,
					planet[i].name,
					planet[i].guild,
					planet[i].home_class,
					planet[i].bar_name,
					planet[i].has_guild_halls,
					planet[i].is_server_gate,
					planet[i].ship_plan,
					planet[i].ship_plan_cost,
					planet[i].ship_plan_exp,
					planet[i].ship_plan_kills);
			send_con_user ( con, rtn_str );

			for ( k=0;k<SHIP_MAX;k++ )
				if ( planet[i].ship[k].have )
				{
					sprintf ( rtn_str, "1,%d,-1,%d,%d", i, k, planet[i].ship[k].max );

					for ( z=0;z<8;z++ )
					{
						sprintf ( cat_str, ",%d", planet[i].ship[k].exclude[z] );
						strcat ( rtn_str, cat_str );
					}

					send_con_user ( con, rtn_str );
				}

			for ( k=0;k<GUN_MAX;k++ )
				if ( planet[i].gun[k] )
				{
					sprintf ( rtn_str, "1,%d,-2,%d", i, k );
					send_con_user ( con, rtn_str );
				}

			for ( k=0;k<MISSILE_MAX;k++ )
				if ( planet[i].missile[k] )
				{
					sprintf ( rtn_str, "1,%d,-3,%d", i, k );
					send_con_user ( con, rtn_str );
				}

			sprintf ( rtn_str, "1,%d,-6,", i );
			for ( k=0;k<PLANET_TRADE_MAX;k++ )
			{
				sprintf ( cat_str, "%d,", planet[i].trade_planet[k] );
				strcat ( rtn_str,cat_str );
			}
			send_con_user ( con, rtn_str );
		}

	for ( i=0;i<ZONE_MAX;i++ )
		if ( zone[i].name[0] != '\0' ) //zone,sector,planet,shield,x,y,sec1,2,3,4,5,connectingzone
		{
			sprintf ( rtn_str, "2,%d,-1,%s,%d,%d", i, zone[i].name, zone[i].home_class, zone[i].free_scan );
			send_con_user ( con, rtn_str );
			for ( k=0;k<SECTOR_MAX;k++ )
				if ( zone[i].sector[k].x )
				{
					sprintf ( rtn_str, "2,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
							i,
							k,
							zone[i].sector[k].planet,
							zone[i].sector[k].shield,
							zone[i].sector[k].x,
							zone[i].sector[k].y,
							zone[i].sector[k].sector[0],
							zone[i].sector[k].sector[1],
							zone[i].sector[k].sector[2],
							zone[i].sector[k].sector[3],
							zone[i].sector[k].sector[4],
							zone[i].sector[k].range,
							zone[i].sector[k].is_sun,
							zone[i].sector[k].is_nebula,
							zone[i].sector[k].free_scan,
					          13 );

					send_con_user ( con, rtn_str );
				}
		}

	for ( i=0;i<GUN_MAX;i++ )
		if ( gun[i].name[0] != '\0' ) //gun#,name,cost,damage,speed,accuracy
		{
			sprintf ( rtn_str, "3,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d",
			          i,
			          gun[i].name,
			          gun[i].cost,
			          gun[i].damage,
			          gun[i].speed,
			          gun[i].accuracy,
			          gun[i].exp_static,
			          gun[i].exp_added,
			          gun[i].tech_level,
			          gun[i].type );
			send_con_user ( con, rtn_str );
		}

	for ( i=0;i<MISSILE_MAX;i++ )
		if ( missile[i].name[0] != '\0' ) //gun#,name,cost,damage,speed,accuracy
		{
			sprintf ( rtn_str, "4,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d",
			          i,
			          missile[i].name,
			          missile[i].cost,
			          missile[i].damage,
			          missile[i].speed,
			          missile[i].accuracy,
			          missile[i].exp_static,
			          missile[i].exp_added,
			          missile[i].tech_level,
			          missile[i].type );
			send_con_user ( con, rtn_str );
		}


	for ( i=0;i<SHIP_MAX;i++ )
		if ( ship[i].name[0] != '\0' ) //zone,sector,planet,shield,x,y,sec1,2,3,4,5,connectingzone
		{
			sprintf ( rtn_str, "5,%d,-1,%s,%f", i, ship[i].name, ship[i].damage_amount );
			send_con_user ( con, rtn_str );
			for ( k=0;k<8;k++ )
			{
				sprintf ( rtn_str, "5,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", i, k, ship[i].cost[k], ship[i].exp[k], ship[i].hull[k], ship[i].shield[k], ship[i].evasion[k], ship[i].speed[k], ship[i].range[k], ship[i].cargo[k], ship[i].gun_ammount[k], ship[i].missile_ammount[k], ship[i].misc_ammount[k] );
				send_con_user ( con, rtn_str );
			}
		}

}

void user_enter_bar ( int con )
{
	int i, temp_size;
	char rtn_str[1024], temp_str[200], temp_str2[200];

	if ( user_con[con].inbar ) return; //already in the bar
	if ( !user_con[con].landed ) return; //not landed

	user_con[con].inbar = 1;

	sprintf ( temp_str2,"8,%s,%s,%s,%d%c",
	          user_con[con].username,
	          user_con[con].guild,
	          user_con[con].guild_rank_name,
	          user_con[con].guild_rank_id,
	          13 );
	strcpy ( rtn_str,"7" );
	temp_size = 2;
	//collect ful bar list and send to client
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if ( !user_con[i].inbar ) continue; //not in bar
		if ( !user_con[i].landed ) continue; //not landed

		//*NEW universal bar
		//if ( user_con[i].last_planet != user_con[con].last_planet ) continue; //not on the same planet

		sprintf ( temp_str,",%s,%s,%s,%d",
		          user_con[i].username,
		          user_con[i].guild,
		          user_con[i].guild_rank_name,
		          user_con[i].guild_rank_id );
		temp_size += strlen ( temp_str ); //dont want a bar overload crashing the server...
		if ( temp_size < 1020 ) strcat ( rtn_str,temp_str );

		//now tell this client of con's arival.
		if ( i != con ) //dont send to self..
			raw_send_con_user ( i,temp_str2 );
	}
	send_con_user ( con, rtn_str );
}

void user_leave_bar ( int con )
{
	int i;
	char temp_str[30];

	if ( !user_con[con].inbar ); //can't leave what your not in.

	user_con[con].inbar = 0;

	sprintf ( temp_str,"9,%s%c", user_con[con].username, 13 );

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].inbar ) continue; //not in bar
		if ( !user_con[i].landed ) continue; //not landed

		//*NEW universal bar
		//if ( user_con[i].last_planet != user_con[con].last_planet ) continue; //not on the same planet

		//tell the folks con left
		raw_send_con_user ( i,temp_str );
	}


}

void user_send_public_chat ( int con, int color, char *message )
{
	char temp_str[1025];

	sprintf ( temp_str,"10,%d,%s", color, message );
	send_con_user ( con,temp_str );
}

void user_send_public_chat_to_sector ( int color, char *message, int z, int s )
{
	char temp_str[1025];
	int i;

	//nevermind
	if(z < 0) return;
	if(s < 0) return;

	sprintf ( temp_str,"10,%d,%s%c", color, message, 13 );

	for ( i=0;i<=user_con_top;i++ )
	{
		if(!user_con[i].username[0]) continue;
		if(user_con[i].landed) continue;
		if(user_con[i].zone != z) continue;
		if(user_con[i].sector != s) continue;

		raw_send_con_user ( i,temp_str );
	}
}

//*NEW admin commands, etc ...
static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool process_admin_commands(int con, const std::string &message, std::string &response)
{
    // add new admins here
    const char *admin_names[] = {"Admin", "Administrator"}; // check admin names v2.0 (client -> con -> send_server_packet)
    bool name_found = false; // default admin check = no admin

    for(int i=0;i<sizeof(admin_names)/sizeof(char*);++i) // need to get character size
    {
        if (strcmp(user_con[con].username, admin_names[i]) == 0) name_found = true; // check character size, output value (either true or false)
    }

    if(!name_found) return false; // not an admin ? return false ...

    if(message.empty()) return false;
    if(message[0] != '@') return false;

    std::vector<std::string> params = split(message, ',');

    if(params[0] == "@node")
    {
        std::stringstream ss;
        ss << "Current Zone:" << user_con[con].zone << " Sector:" << user_con[con].sector;
        response = ss.str();
        return true;
    }
    else if(params[0] == "@warp")
    {
        if(params.size() != 3)
        {
            response = "Usage: @warp,zone,sector";
            return true;
        }

        int old_sector = user_con[con].sector;
        int was_landed = user_con[con].landed;

        user_con[con].zone = atoi(params[1].c_str());
        user_con[con].sector = atoi(params[2].c_str());
        user_con[con].landed = 0;

        //well stop the attacking
        user_con[con].user_attacking = -1;

        //tell user
        send_user_sector_info ( con );

        //tell everyone you left
        //if(was_landed)
        //{
            relay_user_leave_sector ( con,old_sector,user_con[con].zone );
        //}

        //tell everyone you entered
        //ship id,type,kind,class_name,user_name,user_guild
        relay_user_enter_sector (
            user_con[con].zone,
            user_con[con].sector,
            user_con[con].ship.server_id,
            user_con[con].ship.type,
            user_con[con].ship.kind,
            user_con[con].ship.class_name,
            user_con[con].username,
            user_con[con].guild,
            con );

        //tell their maps
        update_users_sector_userlist(user_con[con].zone, user_con[con].sector);

        //set jump time
        user_con[con].last_jump_time = current_time();
        user_con[con].last_enter_sector_time = user_con[con].last_jump_time;

        //check for the children
        user_check_worthy_launch_time(con);

        return true;
    }

    if (params[0] == "@rep")
    {
        user_con[con].ship.hull = user_con[con].ship.hull_max;
        user_con[con].update_hull = 1;
      response = "Success!";
      return true;
    }

    if (params[0] == "@hull")
    {
    user_con[con].ship.hull = atoi(params[1].c_str());
    response = "Success!";
    return true;
    }

    return false;
}

/* bool process_user_commands(int con, const std::string &message, std::string &response)
{
    if(message.empty()) return false;
    if(message[0] != '$') return false;

    std::vector<std::string> params = split(message, ',');

    if (params[0] == "!rtd")
    {
    // need to implement code that rolls random number ship class and kind, put it in garage and took some ds!
    bot_drop_db drop;
    drop.drop_type = is_ship;
    drop.ship_class = rand() %7;
    drop.ship_kind = rand() %7;
    drop.weapon = 0;
    drop.chance = 0;
    send_hub_user_kill_bot_random_drop(user_con[con].user_id, drop);
   return true;
    }

    return false;
} */
//*NEW end admin commands, etc ..

void user_chat ( int con, char *message )
{
	int i;
	char temp_str[1025];
	message[1001] = '\0'; //cap at 1000 becuase a full message will create an oversized packet

	//*NEW process commands in chat
	std::string response = "Success";

	if(process_admin_commands(con, message, response))
    {
        sprintf ( temp_str,"10,0,%s : %s%c", "Command", response.c_str(), 13 );
	}
	else
	{
        sprintf ( temp_str,"10,0,%s : %s%c", user_con[con].username, message, 13 );
	}


	if ( user_con[con].landed )
	{
		if ( !user_con[con].inbar ) return; //gotta be in bar if landed

		for ( i=0;i<=user_con_top;i++ )
		{
			if ( !user_con[i].username[0] || !user_con[i].inbar ) continue; //already in the bar
			if ( !user_con[i].landed ) continue; //not landed
			//universal bar
			//if ( user_con[i].last_planet != user_con[con].last_planet ) continue; //not on the same planet

			raw_send_con_user ( i,temp_str );
		}

	}
	else //space chat
	{
		for ( i=0;i<=user_con_top;i++ )
		{
			if ( !user_con[i].username[0] || user_con[i].landed ) continue; //if connected and launched
			if ( user_con[i].sector != user_con[con].sector || user_con[i].zone != user_con[con].zone ) continue; //same sector

			raw_send_con_user ( i,temp_str );
		}
	}
}

void user_special_chat ( int con, int message_type, char *message )
{
	char rtn_str[1225];

	sprintf ( rtn_str,"11,%d,%s", message_type, message );
	send_con_user ( con,rtn_str );
}

void user_special_chat_all ( int message_type, char *message )
{
	char rtn_str[1225];
	int i;

	sprintf ( rtn_str,"11,%d,%s%c", message_type, message, 13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0])
			raw_send_con_user ( i, rtn_str );
}

void user_relay_ldm ( int con, char *to_user, char *message )
{
	int victom_con;
	char rtn_str[1225];

	to_user[20] = '\0';
	victom_con = user_to_con_miscase ( to_user );

	if ( victom_con != -1 )
	{
		sprintf ( rtn_str,"11,2,LDM : %s :: %s", user_con[con].username, message );
		send_con_user ( victom_con,rtn_str );

		if ( user_con[victom_con].landed )
		{
			strcpy ( rtn_str, "11,2,.. LONG DISTANCE RECIPIENT LANDED .." );
			send_con_user ( con,rtn_str );
		}
		else
		{
			strcpy ( rtn_str, "11,2,.. LONG DISTANCE MESSAGE SENT .." );
			send_con_user ( con,rtn_str );
		}
	}
	else
	{
		strcpy ( rtn_str, "11,2,.. LONG DISTANCE RECIPIENT NOT FOUND .." );
		send_con_user ( con,rtn_str );
	}
}

void launch_user ( int con, int the_zone )
{
	char rtn_str[128];
	int i, j, found = 0;

    if ( !user_has_hull(con)) return;
	//if ( !user_con[con].landed ) {printd ( "Launching: !landed\n" ); return;}
	if ( user_con[con].ship.server_id < 0 ) {printd ( "Launching: !ship_id\n" ); return;}
	if ( user_con[con].ship.kind < 0 ) {printd ( "Launching: !ship_kind\n" ); return;}
	if ( user_con[con].ship.type < 0 ) {printd ( "Launching: !ship_type\n" ); return;}

	//set sector/zone
	if ( the_zone < 0 ) //normal launch
	{
		//launch user
		if ( user_con[con].sector == -1 ) //need to set sector and zone.
		{
			set_user_zone_sector ( con );
			if ( user_con[con].sector == -1 ) {printd ( "Launching: !sector\n" ); return;}
			//still not set?
		}
	}
	else //gate launch
	{
		if ( the_zone >= ZONE_MAX ) {printf ( "usr-err-%d: launch: zone>=zone max\n" ); return;}

		for ( j=0;j<SECTOR_MAX;j++ )
			if ( zone[the_zone].sector[j].planet == user_con[con].last_planet )
				break;

		if ( j==SECTOR_MAX ) {printd ( "Launching: !sector in zone\n" ); return;} //akward, planet not found.

		user_con[con].zone = the_zone;
		user_con[con].sector = j;
	}

	//launch user
	user_con[con].landed = 0;

	//tell hub
	sprintf ( rtn_str, "6,%d,0", user_con[con].user_id );
	send_con_hub ( rtn_str );

	//tell user
	send_user_sector_info ( con );

	//tell everyone else
	//ship id,type,kind,class_name,user_name,user_guild
	relay_user_enter_sector (
	    user_con[con].zone,
	    user_con[con].sector,
	    user_con[con].ship.server_id,
	    user_con[con].ship.type,
	    user_con[con].ship.kind,
	    user_con[con].ship.class_name,
	    user_con[con].username,
	    user_con[con].guild,
	    con );

	//tell their maps
	update_users_sector_userlist(user_con[con].zone, user_con[con].sector);

	//set jump time
	user_con[con].last_jump_time = current_time();
	user_con[con].last_enter_sector_time = user_con[con].last_jump_time;

	//tell everyone the count
	update_users_on_zone_players();

	//check for the children
	user_check_worthy_launch_time(con);
}

void land_user ( int con )
{
	int i;
	int z, s;
	char rtn_str[128];

    z = user_con[con].zone;
    s = user_con[con].sector;

	if ( user_con[con].landed ) return;
	if ( user_con[con].sector < 0 ) return; //eh?
	if ( user_con[con].zone < 0 ) return; //eh?
	if ( zone[user_con[con].zone].sector[user_con[con].sector].planet < 0 ) return;

    user_con[con].landed = 1;

	user_con[con].last_planet = zone[user_con[con].zone].sector[user_con[con].sector].planet;

	//*NEW UseGate
    // Gen - Universal
	if(user_con[con].last_planet == 3 || user_con[con].last_planet == 4 || user_con[con].last_planet == 5) //check gate #
    {
        if(user_con[con].zone == 0) //which zone are we comming from?
        {
            launch_user(con,2); //well, warp to next zone
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1); //update guild members on sector
        }
    else
        {
            launch_user(con,0);
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);
        }
	}

		// Gen - Elite
	else if(user_con[con].last_planet == 22) {

        if(user_con[con].zone == 0) {
            launch_user(con,4); //well, warp to next zone
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1); //update guild members on sector
        } else {
            launch_user(con,0);
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);
        }
	}

    //Universal - Velic
    else if(user_con[con].last_planet == 18 || user_con[con].last_planet == 19 || user_con[con].last_planet == 20)
    {
        if(user_con[con].zone == 2)
        {
            launch_user(con,1);
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);
        }
        else
        {
            launch_user(con,2);
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);
        }
    }
    //Universal - Forbidden
     else if(user_con[con].last_planet == 21)
     {
        if(user_con[con].zone == 2)
        {
            launch_user(con,3);
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);
        }
        else
        {
            launch_user(con,2);
            annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);
        }
     }

	else //normal land
    {

	//tell hub user hull if it changed
	user_send_hub_hull ( con );

	if ( user_con[con].update_missiles )
	{
		user_con[con].update_missiles = 0;
		tell_hub_user_payload ( con );
	}

    //only for testing purposes
	//printf("cur planet: %d\n", user_con[con].last_planet);

	//tell hub we landed
	sprintf ( rtn_str, "6,%d,1,%d", user_con[con].user_id, user_con[con].last_planet );
	send_con_hub ( rtn_str );

	//tell everyone else
	relay_user_leave_sector ( con, user_con[con].sector, user_con[con].zone );

	//give good ammounts for the planet
	send_user_con_to_planet ( con, user_con[con].last_planet );

	//tell everyone the count
	update_users_on_zone_players();

	//check for the children
	user_check_worthy_launch_time(con);
	}
}

void send_user_sector_info ( int con )
{
	char rtn_str[3072], temp_str[128];
	int i, s, z, aprox_size = 3;
	int p;

	//dir
	s = user_con[con].sector;
	z = user_con[con].zone;

	//eh test
	if ( s<0 ) return;
	if ( z<0 ) return;
	if ( s>=SECTOR_MAX ) return;
	if ( z>=ZONE_MAX ) return;

	//setup intial sector info
	sprintf ( rtn_str, "12,%d,%d", z, s );

	p = zone[z].sector[s].planet;

	//we got a sat here?
	if ( p > -1 && !planet[p].is_gate )
	{
		if ( planet[p].sat.guild_name[0] && planet[p].sat.hull )
		{
			aprox_size += sprintf ( temp_str, ",-1,0,0,,Satellite,%s", planet[p].sat.guild_name );

			strcat ( rtn_str, temp_str );
		}
		else //if ( !planet[p].is_gate )
		{
			aprox_size += sprintf ( temp_str, ",-1,0,1,,Satellite,Not Owned" );

			strcat ( rtn_str, temp_str );
		}
	}

	//append all users in sector
	for ( i=0;i<=user_con_top && aprox_size < 3050;i++ )
	{
		if ( !user_con[i].username[0] || user_con[i].landed ) continue; //if connected and launched
		if ( user_con[i].sector != s || user_con[i].zone != z ) continue; //same sector
		if ( i == con ) continue; //not same person

		aprox_size += sprintf ( temp_str, ",%d,%d,%d,%s,%s,%s", user_con[i].ship.server_id, user_con[i].ship.type, user_con[i].ship.kind, user_con[i].ship.class_name, user_con[i].username, user_con[i].guild );

		strcat ( rtn_str, temp_str );
	}

	add_bots_from_sector ( rtn_str, z, s );

	send_con_user ( con, rtn_str );

	//now for all those attacking fools
	send_user_sector_user_war_info ( con );
	send_user_sector_bot_war_info ( con );

	//tell the user the sector good info
	user_update_good_amount_sector ( con );
}

void send_user_sector_user_war_info ( int con )
{
	int u;
	int s, z;
	char rtn_str[1000];

	s = user_con[con].sector;
	z = user_con[con].zone;

	for ( u=0;u<=user_con_top;u++ )
	{
		int v_u, b_t;

		if ( !user_con[u].username[0] ) continue;
		if ( user_con[u].landed ) continue;
		if ( user_con[u].zone != z ) continue;
		if ( user_con[u].sector != s ) continue;

		//well the player is connected and is in the same sector....
		v_u = user_con[u].user_attacking;
		b_t = user_con[u].bot_type_attacking;
		if ( v_u < 0 ) continue;

		//so what exactly are we attacking then...
		if ( user_con[u].attacking_sat )
			sprintf ( rtn_str,"20,%s,Satellite", user_con[u].username );
		else if ( user_con[u].attacking_bot )
			sprintf ( rtn_str,"20,%s,%s", user_con[u].username, bot_type[b_t].bot[v_u].name );
		else
			sprintf ( rtn_str,"20,%s,%s", user_con[u].username, user_con[v_u].username );

		send_con_user ( con,rtn_str );
	}
}

//probably here
void send_user_was_hit ( int con, char *enemy_name )
{
	char rtn_str[100] = "26,";

	strcat ( rtn_str,enemy_name );

	send_con_user ( con, rtn_str );
}

void relay_user_leave_sector ( int con, int s, int z )
{
	char rtn_str[128];
	int i;

	sprintf ( rtn_str, "14,%s%c", user_con[con].username, 13 );
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] || user_con[i].landed ) continue; //if connected and launched
		if ( s != user_con[i].sector || user_con[i].zone != z ) continue; //same sector
		if ( i == con ) continue; //not same person

		raw_send_con_user ( i, rtn_str );
	}

	recalculate_sector_free_scan ( z,s,0 );

	if(!user_con[con].has_bot_guild)
		annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);

	update_users_sector_userlist(z, s);
}

void move_to_sector ( int con, int new_sector )
{
	int i, j, found = 0, old_sector;
    const char *admin_names[] = {"Admin", "Administrator"};
    bool name_found = false;

    for(int us=0;us<sizeof(admin_names)/sizeof(char*);++us)
    {
        if (strcmp(user_con[con].username, admin_names[us]) == 0) name_found = true;
    }

	if ( new_sector < 0 || new_sector >= SECTOR_MAX ) return;
	if ( user_con[con].landed ) return;
	if ( user_con[con].ship.server_id < 0 ) return;
	if ( user_con[con].ship.type < 0 ) return;
	if ( user_con[con].ship.kind < 0 ) return;
	if ( !user_has_hull(con)) return;
	if ( user_con[con].zone == 0 && new_sector == 58 && !user_con[con].activated ) return;

	//check if jump is charged
	if (!name_found) {
	if ( !user_jump_is_charged ( con ) ) return;
	}

	//check if valid sector
	for ( i=0;i<5;i++ )
		if ( zone[user_con[con].zone].sector[user_con[con].sector].sector[i] == new_sector )
			break;

	if ( i==5 ) return; //sector not found

	//check if ship meets range requirements
	if ( user_con[con].ship.range < zone[user_con[con].zone].sector[new_sector].range ) return;

	//check if deactivated user...
	//if ( !user_con[con].activated && zone[user_con[con].zone].sector[new_sector].range > DEACTIVATED_RANGE_LIMIT ) return;

	//well stop the attacking
	user_con[con].user_attacking = -1;

	//set sector
	old_sector = user_con[con].sector;
	user_con[con].sector = new_sector;

	//tell user
	send_user_sector_info ( con );

	//tell everyone you left
	relay_user_leave_sector ( con,old_sector,user_con[con].zone );

	//tell everyone you entered
	//ship id,type,kind,class_name,user_name,user_guild
	relay_user_enter_sector (
	    user_con[con].zone,
	    user_con[con].sector,
	    user_con[con].ship.server_id,
	    user_con[con].ship.type,
	    user_con[con].ship.kind,
	    user_con[con].ship.class_name,
	    user_con[con].username,
	    user_con[con].guild,
	    con );

	//tell their maps
	update_users_sector_userlist(user_con[con].zone, user_con[con].sector);

	//set jump time
	user_con[con].last_jump_time = current_time();
	user_con[con].last_enter_sector_time = user_con[con].last_jump_time;

	//check for the children
	user_check_worthy_launch_time(con);
}

void relay_user_enter_sector ( int z, int s, int sh_id, int sh_t, int sh_k, char *sh_name, char *username, char *userguild, int except_i )
{
	char rtn_str[128];
	int i;

	sprintf ( rtn_str, "13,%d,%d,%d,%s,%s,%s%c",
	          sh_id,
	          sh_t,
	          sh_k,
	          sh_name,
	          username,
	          userguild,
	          13 );

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] || user_con[i].landed ) continue; //if connected and launched
		if ( s != user_con[i].sector || user_con[i].zone != z ) continue; //same sector
		if ( i == except_i ) continue; //not same person

		raw_send_con_user ( i, rtn_str );
	}

	recalculate_sector_free_scan ( z, s, 1 );

	annouce_guild_member_enter_sector(z,s,userguild,-1);
}

void set_average_gun_speed ( int con )
{
	int i, k=0;
	double sum = 0;

	for ( i=0;i<user_con[con].ship.gun_ammount;i++ ) //show those gun pods
		if ( user_con[con].ship.gun[i].speed > 0 )
		{
			//gar checks
			if ( user_con[con].ship.gun[i].destroyed ) continue;

			if ( user_con[con].ship.gun[i].type==4 )
				sum += 100 - ( ( 100 - user_con[con].ship.gun[i].speed ) / 4 );
			else
				sum += user_con[con].ship.gun[i].speed;

			k++;
		}

	//make average and turn it into seconds
	user_con[con].attack_speed = sum / k;
	user_con[con].attack_speed = 100 - user_con[con].attack_speed;
	user_con[con].attack_speed *= .1;
}

void set_missile_time ( int con, int missile_number )
{
	user_con[con].ship.missile[missile_number].previous_time = current_time();

	user_con[con].ship.missile[missile_number].time = 100 - user_con[con].ship.missile[missile_number].speed;
	user_con[con].ship.missile[missile_number].time *= 0.1;
}

void user_do_shield_time_dock ( int con, double int_time )
{
	user_con[con].last_jump_time += int_time * user_con[con].ship.shield_level / 4.0;
}

//void start_gun_thread()
//{
//	pthread_t the_thread;
//	void *nothing = NULL;
//
//	pthread_create_always ( &the_thread, NULL, gun_thread, nothing );
//}

double damage_ship_ref_reduction(int aref, int vref)
{
	double reduction_amount;

    // ref level
	aref += 20000;
	vref += 20000;

	if(aref >= vref) return 1.0;

	if(vref <= 0) return 1.0;
	if(aref < 0) return 1.0;
	// damage reduction
	if(vref > 0 && aref == 0) return 0.75;//0.85;

	reduction_amount = 1.0 * aref / vref;

    // max damage reduction
	if(reduction_amount < 0.75) reduction_amount = 0.75; //0.85

	return reduction_amount;
}

int user_deserves_evasion_boost(int u)
{
	return user_con[u].user_attacking == -1;
}

void gun_threadless()
{
	int i, j, k, u_s, u_z, victom_con, dam_percent, done_some_damage, bot_type_num, bot_num, guns_hit;
	int sat_s, sat_z, sat_p, z, s;
	static double the_time, int_time = 0, last_time = 0;
	char die_str[24], blowup_str[25] = "15,", damage_str[16], endchar[2] = {13,'\0'}, destroy_you[5] = {'1', '8', ',', 13, '\0'};
	double damage_delt;
	int s_k, s_t, s_s;
	int v_s_k, v_s_t, v_s_s, v_s_e;

	//set new "time"
	the_time = current_time();

    int random_number = rand() %100 + 1;
    int random_hit = rand() %10 + 1;

	//loop through all connected and see if we have any attackers that are ready
	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
		{
			if ( !user_con[i].landed && ( the_time - user_con[i].last_jump_time < user_con[i].jump_time ) && ( user_con[i].ship.shield_level > 0 ) )
			{
				user_do_shield_time_dock ( i, int_time );
			}

			if ( user_con[i].user_attacking > -1 )
			{
				//need this to update snappy like
				notify_attacker_of_enemy_jump ( i );

				//not yet time?
				if ( the_time - user_con[i].attack_time < user_con[i].attack_speed ) continue;

				//shit that should keep this person from attacking anyone
				if ( user_con[i].landed ) 	{user_con[i].user_attacking = -1; continue;}
				if ( user_con[i].ship.hull <= 0 ) {user_con[i].user_attacking = -1; continue;}
				if ( user_con[i].destroy_on_recv ) {user_con[i].user_attacking = -1; continue;}

				if ( !user_con[i].attacking_bot && !user_con[i].attacking_sat )
				{
					victom_con = user_con[i].user_attacking;
                    std::string peace = "PEACE"; //*NEW guild name var
					std::string gadmin = "Admin"; //case-sensitive !!!
					std::string gadmin2 = "Agdministrator"; //case-sensitive !!!
					//first make sure we should still be attacking this fool
					if ( user_con[victom_con].username[0] == '\0' ) 	{user_con[i].user_attacking = -1; continue;}
					if ( user_con[victom_con].landed ) 		{user_con[i].user_attacking = -1; continue;}
					if ( user_con[victom_con].ship.hull <= 0 ) 		{user_con[i].user_attacking = -1; continue;}
					if ( user_con[i].sector != user_con[victom_con].sector || user_con[i].zone != user_con[victom_con].zone )
					{user_con[i].user_attacking = -1; continue;}
					//*NEW users can't fight in Gen Zone until they are in PEACE guild
					if ( user_con[i].zone == 0 ) {
					if ( user_con[i].guild == peace || user_con[victom_con].guild == peace )
                        {
                            char rtn_str[1000];
                            sprintf(rtn_str, "Guns disabled by PEACE guild.");
                            user_send_public_chat(i, 3, rtn_str);
                            user_con[i].user_attacking = -1; continue;
                        }
                    }

						if ( user_con[victom_con].guild == gadmin || user_con[victom_con].guild == gadmin2 )
                        {
                            char rtn_str[1000];
                            sprintf(rtn_str, "%s is invulnerable.", user_con[victom_con].username);
                            user_send_public_chat(i, 3, rtn_str);
                            user_con[i].user_attacking = -1;
							continue;
                        }

					s_s = user_con[i].ship.server_id;
					s_t = user_con[i].ship.type;
					s_k = user_con[i].ship.kind;

					v_s_s = user_con[victom_con].ship.server_id;
					v_s_t = user_con[victom_con].ship.type;
					v_s_k = user_con[victom_con].ship.kind;
					v_s_e = user_con[victom_con].ship.evasion * 2;


					//set new time
					user_con[i].attack_time = the_time;

					//CAD protection
					user_con[victom_con].last_attacked_time = the_time;
					user_con[victom_con].last_attacker = i;

					//try for some damage
					for ( k=done_some_damage=guns_hit=0;k<user_con[i].ship.gun_ammount;k++ ) //show those gun pods
						if ( user_con[i].ship.gun[k].speed > 0 )
						{
							int gun_type;

							gun_type = user_con[i].ship.gun[k].type;

							//one we didnt think of hmm
							//if ( user_con[i].ship.gun[k].destroyed ) continue;

							//check chance
							if ( random_number < calculate_gun_accuracy ( victom_con, user_con[i].ship.gun[k].accuracy, gun_type ) ) continue;

							//calc extra dmg
                            double shipexp = user_con[i].ship.exp;
                            double coeff = 1.0/(1.0 + exp(-shipexp/3000.0))-0.5; //0 - 0.5
                            double extradmg = coeff*10; // tweak this

                            //printf("exp %d\n", user_con[i].ship.exp);

                            //count em
							guns_hit++;

							//do damage
							damage_delt = extradmg + calculate_gun_damage ( victom_con, user_con[i].ship.gun[k].damage, gun_type ) * sector_damage_reduction ( user_con[i].zone, user_con[i].sector );
							damage_delt = ship_damage_difference ( s_k, damage_delt );
							damage_delt = ship_damage_defense ( v_s_k, damage_delt );
							damage_delt = (int)(damage_delt * (damage_ship_ref_reduction(user_con[i].ship.ref, user_con[victom_con].ship.ref)));
							damage_delt *= ( 100 - v_s_e ) * 0.01;

                            if ( user_con[i].ship.gun[k].speed == 95 )
                                damage_delt = damage_delt * 0.35;
							//if(user_deserves_evasion_boost(victom_con)) damage_delt = ship_damage_evasion_boost ( s_k, v_s_k, damage_delt );
							//*NEW ref calculation test
							//printf("a:%d v:%d aref:%d vref:%d reduct:%lf\n",
							//	i,
							//	victom_con,
							//	user_con[i].ship.ref,
							//	user_con[victom_con].ship.ref,
							//	damage_ship_ref_reduction(user_con[i].ship.ref, user_con[victom_con].ship.ref));

							user_con[victom_con].ship.hull -= ( int ) damage_delt;
							done_some_damage = 1;

							//is the gun a jump disabler?
							if ( gun_type == 1 )
								user_dock_jump ( victom_con );

							//shield disabler?
							if ( gun_type == 2 )
							{
								if ( user_try_disable_shield ( victom_con ) )
									user_notify_attackee_of_shield ( victom_con );
							}

							//set the update flag
							user_con[victom_con].update_hull = 1;

							//check if we need to bring happyness to our kind friend
							if ( user_con[victom_con].ship.hull <= 0 )
							{
								//ah peanuts, he's dead.
								destroy_user ( victom_con, i );

								//let dead dogs lie
								user_con[i].user_attacking = -1;

								//send us back to good
								break;
							}

							//try to destroy a weapon of theirs
							//attempt_destroy_random_user_gun ( victom_con, user_con[i].ship.gun[k].accuracy, 0 );
						}

						//tell the freedom fighter her constalation prize
						//ooo her little prize
						if ( done_some_damage && user_con[victom_con].ship.hull > 0 )
						{
							dam_percent = ( int ) ( ( 1.0 * user_con[victom_con].ship.hull / user_con[victom_con].ship.hull_max ) * 100.0 );
							if ( dam_percent > 100 ) dam_percent = 100; //wtf?

							//send 'er
							sprintf ( damage_str,"16,%d,%d", dam_percent,guns_hit );
							send_con_user ( i,damage_str );

							//and him
							send_user_hull ( victom_con );

							//and this...
							send_user_was_hit ( victom_con,user_con[i].username );

							//reset
							done_some_damage = 0;
						}
				}
				else if ( user_con[i].attacking_bot ) //attacking a bot
				{
					int bot_shield, bot_evasion;

					bot_num = user_con[i].user_attacking;
					bot_type_num = user_con[i].bot_type_attacking;

					bot_shield = bot_type[bot_type_num].bot[bot_num].shield;
					bot_evasion = bot_type[bot_type_num].bot[bot_num].evasion;

					//first make sure we should still be attacking this fool
					if ( user_con[i].sector != bot_type[bot_type_num].bot[bot_num].sector || user_con[i].zone != bot_type[bot_type_num].zone )
					{user_con[i].user_attacking = -1; continue;}
					if ( bot_type[bot_type_num].bot[bot_num].hull <= 0 ) {user_con[i].user_attacking = -1; continue;};

					s_s = user_con[i].ship.server_id;
					s_t = user_con[i].ship.type;
					s_k = user_con[i].ship.kind;

					v_s_s = 0;
					v_s_t = bot_type[bot_type_num].bot[bot_num].ship_class;
					v_s_k = bot_type[bot_type_num].bot[bot_num].ship_kind;

					//set new time
					user_con[i].attack_time = the_time;

					for ( k=done_some_damage=guns_hit=0;k<user_con[i].ship.gun_ammount;k++ ) //show those gun pods
						if ( user_con[i].ship.gun[k].speed > 0 )
						{
							int gun_type;

							gun_type = user_con[i].ship.gun[k].type;

							//one we didnt think of hmm
							//if ( user_con[i].ship.gun[k].destroyed ) continue;

                            //check chance
							if ( random_number < calc_gun_acc ( bot_evasion, bot_shield, user_con[i].ship.gun[k].accuracy, gun_type ) ) continue;

							//calc extra dmg
                            double shipexp = user_con[i].ship.exp;
                            double coeff = 1.0/(1.0 + exp(-shipexp/3000.0))-0.5; //0 - 0.5
                            double extradmg = coeff*10; // tweak this

                            //printf("exp %d\n", user_con[i].ship.exp);

							//do count
							guns_hit++;

							//jump disabler?
							if ( gun_type == 1 )
								bot_dock_jump ( bot_type_num, bot_num );

							//shield disabler?
							if ( gun_type == 2 )
								bot_try_disable_shield ( bot_type_num, bot_num );

							//do damage
							//*NEW set random mis-damage hit
							//if ( random_hit >= 4 ) {
							damage_delt = extradmg + calc_gun_dam ( bot_evasion, bot_shield, user_con[i].ship.gun[k].damage, gun_type )  * sector_damage_reduction ( user_con[i].zone, user_con[i].sector );
							damage_delt = ship_damage_defense ( v_s_k, damage_delt );
							damage_delt = guild_mode_att ( user_con[i].guild_mode, damage_delt );

							if ( bot_type[bot_type_num].field_type && user_con[i].ship.gun[k].type == 5 )
								damage_delt = damage_delt * 8;

                            if ( user_con[i].ship.gun[k].speed == 95 )
                                damage_delt = damage_delt * 0.35;

							damage_delt = ship_damage_difference ( s_k, damage_delt );
							//}
							//else
                            //{ //set low damage for miss hits
							//damage_delt *= 0.40;
							//}

                            bot_type[bot_type_num].bot[bot_num].hull -= ( int ) damage_delt;
							done_some_damage = 1;

                            //printf("money: %d\n", user_con[i].ship.money);
                            //printf("exp: %d\n", user_con[i].ship.exp);

							//check if we need to bring happyness to our kind friend
							if ( bot_type[bot_type_num].bot[bot_num].hull <= 0 )
							{
								struct bot_drop_db drop_item;
								//ah peanuts, he's dead.

								//now for the chat stuff
								relay_destroy_user_msg ( bot_type[bot_type_num].bot[bot_num].sector, bot_type[bot_type_num].zone, bot_type[bot_type_num].bot[bot_num].name );

								//better tell the folks
								//tell hub if it deserve a reward
								send_hub_user_kill_bot_exp ( user_con[i].user_id, bot_type[bot_type_num].bot[bot_num].exp, bot_type[bot_type_num].bot_class, bot_type[bot_type_num].guild );

								//give uesr an item?
								drop_item = bot_drop_item ( bot_type_num, bot_num, guild_mode_drop(user_con[i].guild_mode) );
								if ( drop_item.drop_type != no_type )
									send_hub_user_kill_bot_random_drop ( user_con[i].user_id, drop_item );

								//upgrade a user weapon?
								check_send_hub_user_kill_bot_random_upgrade_weapon(user_con[i].user_id, bot_type_num, bot_num, guild_mode_drop(user_con[i].guild_mode));

								//upgrade a mk2?
								check_send_hub_user_kill_bot_random_upgrade_mk2(user_con[i].user_id, bot_type_num, bot_num, guild_mode_drop(user_con[i].guild_mode));

								//tell everyone else
								relay_player_blow_up ( bot_type[bot_type_num].bot[bot_num].sector, bot_type[bot_type_num].zone, bot_type[bot_type_num].bot[bot_num].name );

								//let dead dogs lie
								user_con[i].user_attacking = -1;

								//Get them out of here?
								bot_destroy ( bot_type_num,bot_num );

								//send us back to good
								break;
							}
						}

						//tell the freedom fighter her constalation prize
						//ooo her little prize
						if ( done_some_damage && bot_type[bot_type_num].bot[bot_num].hull > 0 )
						{
							dam_percent = ( int ) ( ( 1.0 * bot_type[bot_type_num].bot[bot_num].hull / bot_type[bot_type_num].bot[bot_num].hull_max ) * 100.0 );
							if ( dam_percent > 100 ) dam_percent = 100; //wtf?

							//send 'er
							sprintf ( damage_str,"16,%d,%d", dam_percent, guns_hit );
							send_con_user ( i,damage_str );

							//reset
							done_some_damage = 0;
						}
				}
				else if ( user_con[i].attacking_sat )
				{
					gun_thread_user_attack_sat ( i );
				}
			}
		}

	int_time = the_time - last_time;
	last_time = the_time;
}

void *gun_thread ( void *nothing )
{


	while ( 1 )
	{
		gun_threadless();

		//sleep alittle
#ifdef _WIN32 //if windows
		Sleep ( 250 );
#else
		usleep ( 250000 );
#endif
	}

	//pthread_exit ( NULL );
	return 0;
}

void gun_thread_user_attack_sat ( int i )
{
	int s,z,sat_s,sat_z,sat_p;
	int k;
	int done_some_damage, guns_hit, dam_percent;
	char damage_str[16];
	double damage_delt;
	int s_s, s_t, s_k;

	//set stuff
	sat_s = user_con[i].attacking_sat_sector;
	sat_z = user_con[i].attacking_sat_zone;
	sat_p = user_con[i].user_attacking;

	s = user_con[i].sector;
	z = user_con[i].zone;

	s_s = user_con[i].ship.server_id;
	s_t = user_con[i].ship.type;
	s_k = user_con[i].ship.kind;

	//make sure we should still be attacking the machinery
	if ( user_con[i].landed ) {user_con[i].user_attacking = -1; return;}
	if ( sat_s != s ) {user_con[i].user_attacking = -1; return;}
	if ( sat_z != z ) {user_con[i].user_attacking = -1; return;}
	if ( !planet[sat_p].sat.guild_name[0] ) {user_con[i].user_attacking = -1; return;}
	if ( planet[sat_p].sat.level < 0 ) {user_con[i].user_attacking = -1; return;}
	if ( planet[sat_p].sat.hull <= 0 ) {user_con[i].user_attacking = -1; return;}

	//set new time
	user_con[i].attack_time = current_time();

	printf("att time: %d\n", user_con[i].attack_time);
	printf("cur time: %d\n", current_time());

	for ( k=done_some_damage=guns_hit=0;k<user_con[i].ship.gun_ammount;k++ ) //show those gun pods
		if ( user_con[i].ship.gun[k].speed > 0 )
		{
			int &gun_type = user_con[i].ship.gun[k].type;

			//one we didnt think of hmm
			if ( user_con[i].ship.gun[k].destroyed ) continue;

			//check chance
			if ( rand() %100 + 1 < calc_gun_acc ( SAT_DEFAULT_EVASION, planet[sat_p].sat.shield, user_con[i].ship.gun[k].accuracy, gun_type ) ) continue;

			//do count
			guns_hit++;

			//do damage
			//damage_delt = user_con[i].ship.gun[k].damage * sat_default_gun_reduction;
			damage_delt = calc_gun_dam ( SAT_DEFAULT_EVASION, planet[sat_p].sat.shield, user_con[i].ship.gun[k].damage, gun_type );
			damage_delt = ship_damage_difference ( s_k, damage_delt );
			planet[sat_p].sat.hull -= ( int ) damage_delt;
			done_some_damage = 1;

			//try to destroy a weapon of theirs
			//attempt_destroy_random_sat_gun ( sat_p, user_con[i].ship.gun[k].accuracy, 0 );

			//shield disabler?
			if ( gun_type == 2 ) sat_try_disable_shield ( sat_p );

			//check if we need to bring happyness to our kind friend
			if ( planet[sat_p].sat.hull <= 0 ) break;
		}

	if ( !done_some_damage )
		return;

	if ( planet[sat_p].sat.hull <= 0 )
	{
		//tell everyone
		relay_destroy_user_msg ( s,z,"Satellite" );
		relay_player_blow_up ( s,z,"Satellite" );

		destroy_sat ( sat_p );

		//end our attack
		user_con[i].user_attacking = -1;
	}
	else //hurting but still alive
	{
		//tell the shooter what the hull is at, etc
		dam_percent = ( int ) ( 100.0 * planet[sat_p].sat.hull / ( planet[sat_p].sat.level * SAT_HULL_INC ) );
		if ( dam_percent > 100 ) dam_percent = 100; //wtf?

		//send 'er
		sprintf ( damage_str,"16,%d,%d", dam_percent, guns_hit );
		send_con_user ( i,damage_str );
	}

	//tell the hub
	send_hub_sat_hull ( sat_p );

	//tell the players
	relay_planet_sat_hull ( sat_p );
}

void fix_sat_shields()
{
	int p;

	for ( p=0;p<PLANET_MAX;p++ )
	{
		//it can only be 0 or 4 so is it 4?
		if ( planet[p].sat.shield_level ) continue;

		//it not have a name?
		if ( !planet[p].name[0] ) continue;

		//time ok?
		if ( sat_shield_is_disabled ( p ) ) continue;

		//ok set it to 4
		set_sat_shield ( p, 4 );
	}
}

void sat_try_disable_shield ( int p )
{
	if ( rand() % 100 + 1 > SHIELD_DISABLE_CHANCE ) return;

	//set to zero
	set_sat_shield ( p, 0 );

	planet[p].sat.shield_disable_time = current_time();
}

void set_sat_shield ( int p, int level )
{
	if ( level == planet[p].sat.shield_level ) return;

	//disable?
	if ( sat_shield_is_disabled ( p ) ) return;

	//set the level
	planet[p].sat.shield_level = level;

	//set the shield
	planet[p].sat.shield = ( int ) ( SAT_DEFAULT_SHIELD * level / 4.0 );

	//tell anyone who might be attacking this fool of the change
	sat_notify_attackers_of_shield ( p );
}

int sat_shield_is_disabled ( int p )
{
	return ( current_time() < planet[p].sat.shield_disable_time + SHIELD_DISABLE_TIME );
}

void sat_init_shields()
{
	int p;

	for ( p=0;p<PLANET_MAX;p++ )
	{
		planet[p].sat.shield_disable_time = -SHIELD_DISABLE_TIME;
		planet[p].sat.shield = SAT_DEFAULT_SHIELD;
		planet[p].sat.shield_level = 4;
	}
}

void sat_notify_attackers_of_shield ( int p )
{
	char rtn_str[1000];
	int z, s, i;

	//should we be doing this?
	if ( planet[p].sat.hull <= 0 ) return;

	//make shit
	sprintf ( rtn_str,"37,%d%c", planet[p].sat.shield_level, 13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
		{
			//this person suposedly attacking us?
			if ( !user_con[i].attacking_sat ) continue;
			if ( user_con[i].user_attacking != p ) continue;

			//should they be?
			if ( user_con[i].landed ) continue;

			//well tell them
			raw_send_con_user ( i,rtn_str );
		}
}

void send_user_hull ( int con )
{
	char damage_str[200];

	sprintf ( damage_str,"17,%d", user_con[con].ship.hull );
	send_con_user ( con,damage_str );
}

void destroy_user_disconnecting ( int con )
{
	int s, z;
	char die_str[1000];
	int k_con;

	//going to need this
	s = user_con[con].sector;
	z = user_con[con].zone;
	k_con = user_con[con].last_attacker;

	//now for the chat stuff
	relay_destroy_user_msg ( s, z, user_con[con].username );

	//tell everyone else he died
	relay_player_blow_up ( s,z,user_con[con].username );

	//Get them out of here?
	user_con[con].landed = 1;
	user_con[con].sector = -1;
	user_con[con].zone = -1;

	//free scan stuff
	recalculate_sector_free_scan(z,s,0);
	annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);

	//better tell the folks
	if ( k_con > -1 && user_con[k_con].username[0] )
	{
		sprintf ( die_str, "28,%s,%d,%d,%d,%d",
		          user_con[con].username,
		          user_con[con].ship.destroy_code,
		          z, s,
		          user_con[k_con].user_id );
	}
	else
	{
		sprintf ( die_str, "28,%s,%d,%d,%d,0",
		          user_con[con].username,
		          user_con[con].ship.destroy_code,
		          z, s );
	}

	send_con_hub ( die_str );
}

void destroy_user ( int con, int k_con )
{
	int s, z;
	char destroy_you_str[10] = "18,", die_str[1000];

	//going to need this
	s = user_con[con].sector;
	z = user_con[con].zone;

	//give the hub a notify on the sector......
	send_hub_user_zone_sector ( con );

	//now for the chat stuff
	relay_destroy_user_msg ( s, z, user_con[con].username );

	//tell that player he died
	send_con_user ( con, destroy_you_str );

	//tell everyone else he died
	relay_player_blow_up ( s,z,user_con[con].username );

	//Get them out of here?
	user_con[con].landed = 1;
	user_con[con].sector = -1;
	user_con[con].zone = -1;

	//do freescan stuff
	recalculate_sector_free_scan(z,s,0);
	annouce_guild_member_leave_sector(z,s,user_con[con].guild,-1);

	//better tell the folks
	if ( k_con > -1 )
		sprintf ( die_str, "7,%d,%d",user_con[con].user_id,user_con[k_con].user_id );
	else
		sprintf ( die_str, "7,%d,0",user_con[con].user_id );
	send_con_hub ( die_str );

	//check for the children
	user_check_worthy_launch_time(con);
}

int calc_gun_acc ( int evasion, int shield, int accuracy, int type )
{
	double eva;

	eva = ( 100 - evasion ) * 0.01;
	eva /= 2;
	eva += .2;

	if ( type==4 )
		eva = 1;

	//ship evasion
	accuracy = ( int ) ( accuracy * eva );

	//shields
	if ( 100 - shield > 0 )
		accuracy = ( int ) ( accuracy * ( 100 - ( shield / 2 ) ) * 0.01 );

	return accuracy;
}

int calc_gun_dam ( int evasion, int shield, int damage, int type )
{
	//double eva;

	if ( !damage ) return 0;

	//ok
	if ( type==3 )
	{
		shield += shield;
		if ( shield > 95 )
			shield = 95;
	}

	//eva = ( 100 - evasion ) * 0.01;
	//eva /= 2;
	//eva += .2;
	//eva *= 0.15;

	if ( type==4 )
	{
		//eva = 1;
		damage /= 8;
	}

	if ( type==5 )
		damage /= 2;

	if ( type==3 )
		damage = ( int ) ( damage * 1.5 );

	//ship evasion, max eva reduction is 90%
	//damage = ( int ) ( damage * eva );

	//ship shields, max reduction is 50%
	//shield / 2 ??
	damage = ( int ) ( damage * ( ( 100 - ( shield * 0.10 ) ) * 0.01 ) );

	//normal diaspora gun stats and ship stats need a major reducer
	damage = ( int ) ( damage * 0.50 );

	if ( damage < 1 )
		damage = 1;

	return damage;
}

int calc_missile_acc ( int evasion, int shield, int accuracy, int type )
{
	double ratio;

	//ship evasion
	accuracy = ( int ) ( accuracy * ( 100 - ( evasion / 4 ) ) * 0.01 );

	//shields
	ratio = shield / 30.0;

	if ( ratio > 1 ) ratio = 1;

	ratio = 1 - ratio;
	ratio *= .9;

	if ( type==3 )
		ratio = 1;

	if ( type==5 )
		ratio *= 0.5;

	return ( int ) ( accuracy * ratio );
}

int calc_missile_dam ( int evasion, int shield, int damage, int type )
{
	double ratio;

	if ( !damage ) return 0;

	ratio = ( int ) ( shield / 50.0 );

	if ( ratio > 1 ) ratio = 1;

	ratio = 1 - ratio;
	ratio *= .9;

	if ( type==5 )
		ratio *= 2;

	damage = ( int ) ( damage * ratio );

	//normal diaspora gun stats and ship stats need a major reducer
	damage = ( int ) ( damage * 0.70 );

	if ( damage < 1 )
		damage = 1;

	return damage;
}


int calculate_gun_accuracy ( int con, int accuracy, int type )
{
	return calc_gun_acc ( user_con[con].ship.evasion, user_con[con].ship.shield, accuracy, type );
}

int calculate_gun_damage ( int con, int damage, int type )
{
	return calc_gun_dam ( user_con[con].ship.evasion, user_con[con].ship.shield, damage, type );
}

int calculate_missile_accuracy ( int con, int accuracy, int type )
{
	return calc_missile_acc ( user_con[con].ship.evasion, user_con[con].ship.shield, accuracy, type );
}

int calculate_missile_damage ( int con, int damage, int type )
{
	return calc_missile_dam ( user_con[con].ship.evasion, user_con[con].ship.shield, damage, type );
}

void attack_user ( int con, char *victom )
{
	int victom_con, i, bot_type_num, bot_num;
	char attack_face[40], attacking_you[25] = "19,";

	victom[20] = 0;

	victom_con = user_to_con ( victom );

	if ( victom_con != -1 )
	{
		if ( !user_con[victom_con].username[0] ) 		return;
		if ( !user_con[victom_con].user_id ) 		return;
		if ( user_con[victom_con].landed ) 		return;
		if ( !user_con[con].username[0] ) 		return;
		if ( !user_con[con].user_id ) 			return;
		if ( user_con[con].landed ) 			return;
		if ( !user_has_hull(con)) return;
		if ( user_con[con].sector != user_con[victom_con].sector || user_con[con].zone != user_con[victom_con].zone )
			return;

		//set new "time"
		user_con[con].attack_time = current_time();

		//set CAD protection stuff
		user_con[victom_con].last_attacked_time = user_con[con].attack_time;
		user_con[victom_con].last_attacker = con;

		//haven't received this yet so
		user_con[con].received_enemy_jump_status_as_full = 0;

		//set attacking target
		user_con[con].user_attacking = victom_con;
		user_con[con].attacking_bot = 0;
		user_con[con].attacking_sat = 0;

		//tell everyone!
		relay_user_attack_user (
		    user_con[con].zone,
		    user_con[con].sector,
		    user_con[con].username,
		    user_con[victom_con].username,
		    con,
		    victom_con );

		//tell the victom
		strcat ( attacking_you, user_con[con].username );
		send_con_user ( victom_con, attacking_you );

		//add to a friendly bot list?
		bot_user_add_to_any_list ( con,user_con[con].zone,user_con[con].sector );

		//now as it states
		notify_attacker_of_victom_shield ( con );
		notify_attacker_of_enemy_jump ( con );
		notify_attacker_of_ref_ratio(con);
	}
	else //check for bot
	{
		//check for it being a sat first
		if ( str_match_lcase ( victom, "Satellite" ) )
		{
			attack_sat ( con );

			//set new "time"
			user_con[con].attack_time = current_time();

			//now as it states
			notify_attacker_of_victom_shield ( con );
			//notify_attacker_of_enemy_jump(con);

			return;
		}

		bot_name_to_reference ( &bot_type_num, &bot_num, victom );

		if ( bot_type_num == -1 )   return;
		if ( user_con[con].landed ) return;
		if ( user_con[con].sector != bot_type[bot_type_num].bot[bot_num].sector || user_con[con].zone != bot_type[bot_type_num].zone )
			return;

		//set new "time"
		user_con[con].attack_time = current_time();

		//haven't received this yet so
		user_con[con].received_enemy_jump_status_as_full = 0;

		//set attacking target
		user_con[con].user_attacking = bot_num;
		user_con[con].bot_type_attacking = bot_type_num;
		user_con[con].attacking_bot = 1;
		user_con[con].attacking_sat = 0;

		//tell everyone!
		relay_user_attack_user (
		    user_con[con].zone,
		    user_con[con].sector,
		    user_con[con].username,
		    bot_type[bot_type_num].bot[bot_num].name,
		    con,
		    -1 );

		//add to bot list hmm?
		user_add_to_bot_list ( con, bot_type_num );

		//now as it states
		notify_attacker_of_victom_shield ( con );
		notify_attacker_of_enemy_jump ( con );
	}

}

void relay_user_attack_user ( int z, int s, char *attacker_name, char *victom_name, int except_i_1, int except_i_2 )
{
	int i;
	char attack_face[200];

	sprintf ( attack_face,"20,%s,%s%c", attacker_name, victom_name, 13 );
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if ( user_con[i].sector != s ) continue;
		if ( user_con[i].zone != z ) continue;
		if ( user_con[i].landed ) continue;
		if ( i == except_i_1 ) continue;
		if ( i == except_i_2 ) continue;

		raw_send_con_user ( i, attack_face );
	}
}

void relay_fire_missile ( int z, int s, char *attacker_name, int skip_i )
{
	int i;
	char attack_face[200];

	sprintf ( attack_face,"41,%s%c", attacker_name, 13 );
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if ( user_con[i].sector != s ) continue;
		if ( user_con[i].zone != z ) continue;
		if ( user_con[i].landed ) continue;
		if ( i == skip_i ) continue;

		raw_send_con_user ( i, attack_face );
	}
}

void attack_sat ( int con )
{
	int z, s, p;

	//simple check
	if ( !user_con[con].username[0] ) return;
	if ( !user_con[con].user_id ) return;
	if ( user_con[con].landed ) return;

	z = user_con[con].zone;
	s = user_con[con].sector;

	//dumb check
	if ( z<0 || z>=ZONE_MAX ) return;
	if ( s<0 || s>=SECTOR_MAX ) return;

	p = zone[z].sector[s].planet;

	//a check
	if ( p<0 || p>=PLANET_MAX ) return;

	//the check
	if ( !planet[p].sat.guild_name[0] || planet[p].sat.hull <= 0 || planet[p].sat.level <= 0 ) return;

	//lets get the attacking on!
	user_con[con].attacking_bot = 0;
	user_con[con].attacking_sat = 1;

	//for the remembering
	user_con[con].user_attacking = p;
	user_con[con].attacking_sat_zone = z;
	user_con[con].attacking_sat_sector = s;

	//now maybe that sat wants to attack you hmmmmmm?
	sat_attack_user ( p,con );

	//tell everyone!
	relay_user_attack_user (
	    z,
	    s,
	    user_con[con].username,
	    "Satellite",
	    con,
	    -1 );
}

void disengage_user ( int con )
{
	int i;
	char disengage_str[25];

	user_con[con].user_attacking = -1;
	user_con[con].attacking_bot = 0;
	user_con[con].attacking_sat = 0;

	//tell everyone!
	relay_user_disengage ( user_con[con].sector,user_con[con].zone,user_con[con].username,con );
}

void relay_user_disengage ( int s, int z, char *username, int except_i )
{
	int i;
	char disengage_str[200];

	sprintf ( disengage_str,"21,%s%c", username, 13 );
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( user_con[i].username[0] == '\0' ) continue;
		if ( user_con[i].sector != s ) continue;
		if ( user_con[i].zone != z ) continue;
		if ( user_con[i].landed ) continue;
		if ( i == except_i ) continue;

		raw_send_con_user ( i, disengage_str );
	}
}

int userid_to_con ( int userid )
{
	int i;

	//fucking arround.........
	if ( !userid ) return -1;

	for ( i=0;i<=user_con_top;i++ )
		if ( userid == user_con[i].user_id )
			return i;

	return -1; //not found
}

int user_to_con ( char *username )
{
	int i;

	for ( i=0;i<=user_con_top;i++ )
		if ( str_match ( username, user_con[i].username ) )
			return i;

	return -1; //not found
}

int user_to_con_miscase ( char *username )
{
	int i;
	char temp_name[21];

	lcase ( username,username );

	for ( i=0;i<=user_con_top;i++ )
	{
		lcase ( temp_name,user_con[i].username );
		if ( str_match ( username, temp_name ) )
			return i;
	}

	return -1; //not found
}

void give_users_boss_bot_reward(int z, int s, int boss_val)
{
	int i;
	char rtn_str[2000];

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].sector == s && user_con[i].zone == z )
		{
			//other checks
			if ( !user_con[i].username[0] ) continue;
			if ( user_con[i].landed ) continue;
			if ( user_con[i].ship.hull <= 0 ) continue;

			sprintf(rtn_str, "37,%d,%d", user_con[i].user_id, boss_val);

			send_con_hub ( rtn_str );
		}
}

void tell_hub_user_payload ( int con )
{
	int i;
	char rtn_str[64], temp_str[4];

	sprintf ( rtn_str,"10,%d", user_con[con].user_id );

	for ( i=0;i<user_con[con].ship.missile_ammount;i++ )
	{
		sprintf ( temp_str, ",%d", user_con[con].ship.missile[i].left );
		strcat ( rtn_str,temp_str );
	}

	send_con_hub ( rtn_str );
}

void scan_user ( int con, char *user_name )
{
	int victom_con, bot_type_num, bot_num;
	char rtn_str[128];

	if ( user_con[con].landed ) return;

	user_name[20] = '\0';
	victom_con = user_to_con_miscase ( user_name );

	if ( victom_con == -1 )
	{
		//check for bot
		bot_name_to_reference ( &bot_type_num, &bot_num, user_name );

		//well neither bot or player found
		if ( bot_type_num == -1 || !bot_type[bot_type_num].bot[bot_num].hull )
		{
			sprintf ( rtn_str, "22,-1,%s not found", user_name );
			send_con_user ( con, rtn_str );
			return;
		}

		if(!bot_type[bot_type_num].bot[bot_num].scannable) //lil test
		{
			sprintf ( rtn_str, "22,-1,%s's location unknown", bot_type[bot_type_num].bot[bot_num].name );
			send_con_user ( con, rtn_str );
			return;
		}

		if ( bot_type[bot_type_num].zone == user_con[con].zone )
		{
			sprintf ( rtn_str, "22,%d,%s found", bot_type[bot_type_num].bot[bot_num].sector, bot_type[bot_type_num].bot[bot_num].name );
			send_con_user ( con, rtn_str );
			return;
		}
		else
		{
			//sprintf(rtn_str, "22,%d,%s found in the %s zone", bot_type[bot_type_num].bot[bot_num].name, zone[bot_type[bot_type_num].zone].name);
			sprintf ( rtn_str, "22,-1,%s found in the %s zone", bot_type[bot_type_num].bot[bot_num].name, zone[bot_type[bot_type_num].zone].name );
			send_con_user ( con, rtn_str );
			return;
		}
	}

	if ( user_con[victom_con].zone == user_con[con].zone )
	{
		int s, z;

		s = user_con[victom_con].sector;
		z = user_con[victom_con].zone;

		if ( s>-1 && z>-1 && zone[z].sector[s].is_nebula )
		{
			sprintf ( rtn_str, "22,-1,%s not found", user_name );
			send_con_user ( con, rtn_str );
			return;
		}

		if ( user_con[victom_con].landed )
		{
			sprintf ( rtn_str, "22,%d,%s landed on %s", user_con[victom_con].sector, user_con[victom_con].username, planet[user_con[victom_con].last_planet].name );
			send_con_user ( con, rtn_str );
		}
		else
		{
			sprintf ( rtn_str, "22,%d,%s found", user_con[victom_con].sector, user_con[victom_con].username );
			send_con_user ( con, rtn_str );
		}
	}
	else
	{
		//sprintf(rtn_str, "22,%d,%s found in the %s zone", user_con[victom_con].sector, user_con[victom_con].username, zone[user_con[victom_con].zone].name);
		sprintf ( rtn_str, "22,-1,%s found in the %s zone", user_con[victom_con].username, zone[user_con[victom_con].zone].name );
		send_con_user ( con, rtn_str );
	}


}

void set_user_zone_sector ( int con )
{
	int i, j, found;

	for ( i=found=0;i<ZONE_MAX;i++ )
	{
		for ( j=0;j<SECTOR_MAX;j++ )
			if ( zone[i].sector[j].planet == user_con[con].last_planet )
			{
				found = 1;
				break;
			}

		if ( found ) break;
	}

	if ( i==ZONE_MAX ) return; //akward, planet not found.

	user_con[con].zone = i;
	user_con[con].sector = j;
}

void set_user_shield ( int con, int level )
{
	//check
	if ( user_shield_is_disabled ( con ) ) return;

	if ( level < 0 ) level = 0;
	if ( level > 4 ) level = 4;

	//set stuff
	user_con[con].ship.shield_level = level;
	user_con[con].ship.shield = user_con[con].ship.shield_max * level / 4;

	//now tell anyone who attacking this fool
	user_notify_attackee_of_shield ( con );
}

void send_good_price_info ( int con, int planet_number )
{
	char rtn_str[1024];

	sprintf ( rtn_str, "23,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	          planet_number,
	          planet[planet_number].good_price[0],
	          planet[planet_number].good_price[1],
	          planet[planet_number].good_price[2],
	          planet[planet_number].good_price[3],
	          planet[planet_number].good_price[4],
	          planet[planet_number].good_price[5],
	          planet[planet_number].good_price[6],
	          planet[planet_number].good_price[7],
	          planet[planet_number].good_price[8],
	          planet[planet_number].good_price[9] );

	send_con_user ( con, rtn_str );
}

void send_good_ammount_info ( int con, int planet_number )
{
	char rtn_str[1024];

	sprintf ( rtn_str, "24,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
	          planet_number,
	          planet[planet_number].good_ammount[0],
	          planet[planet_number].good_ammount[1],
	          planet[planet_number].good_ammount[2],
	          planet[planet_number].good_ammount[3],
	          planet[planet_number].good_ammount[4],
	          planet[planet_number].good_ammount[5],
	          planet[planet_number].good_ammount[6],
	          planet[planet_number].good_ammount[7],
	          planet[planet_number].good_ammount[8],
	          planet[planet_number].good_ammount[9] );

	send_con_user ( con, rtn_str );
}

void send_all_good_price_info ( int con )
{
	int i;
	char rtn_str[1024];

	for ( i=0;i<PLANET_MAX;i++ )
		if ( planet[i].name[0] != '\0' )
		{
			sprintf ( rtn_str, "23,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			          i,
			          planet[i].good_price[0],
			          planet[i].good_price[1],
			          planet[i].good_price[2],
			          planet[i].good_price[3],
			          planet[i].good_price[4],
			          planet[i].good_price[5],
			          planet[i].good_price[6],
			          planet[i].good_price[7],
			          planet[i].good_price[8],
			          planet[i].good_price[9] );

			send_con_user ( con, rtn_str );
		}

	//continue on little man
	send_all_trade_disasters ( con );
}

void send_all_trade_disasters ( int con )
{
	int i, d;
	char rtn_str[1024];
	char clr_str[50] = "35,";

	//tell the to clear what they know
	send_con_user ( con, clr_str );

	for ( i=0;i<PLANET_MAX;i++ )
		if ( planet[i].name[0] != '\0' )
			for ( d=0;d<planet[i].trade_disaster_max;d++ )
			{
				sprintf ( rtn_str, "36,%d,%d,%d,%d",
				          i,
				          planet[i].trade_disaster[d].g,
				          planet[i].trade_disaster[d].is_low,
				          planet[i].trade_disaster[d].i );

				send_con_user ( con, rtn_str );
			}

}

void user_update_good_ammount ( int con, int planet_num, int good_num )
{
	char rtn_str[1000];

	sprintf ( rtn_str,"25,%d,%d,%d",planet_num,good_num,planet[planet_num].good_ammount[good_num] );
	send_con_user ( con,rtn_str );
}

void user_update_single_good_amount_sector ( int con, int g )
{
	char rtn_str[1000];
	int s,z;

	s = user_con[con].sector;
	z = user_con[con].zone;

	sprintf ( rtn_str,"29,%d,%d",g,zone[z].sector[s].good_amount[g] );
	send_con_user ( con,rtn_str );
}

void user_update_single_contra_amount_sector ( int con, int g )
{
	char rtn_str[1000];
	int s,z;

	s = user_con[con].sector;
	z = user_con[con].zone;

	sprintf ( rtn_str,"30,%d,%d",g,zone[z].sector[s].contra_amount[g] );
	send_con_user ( con,rtn_str );
}

void user_update_good_amount_sector ( int con )
{
	int s, z;
	char rtn_str[1000];

	s = user_con[con].sector;
	z = user_con[con].zone;

	//goods
	sprintf ( rtn_str,"27,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",s,z,
	          zone[z].sector[s].good_amount[0],
	          zone[z].sector[s].good_amount[1],
	          zone[z].sector[s].good_amount[2],
	          zone[z].sector[s].good_amount[3],
	          zone[z].sector[s].good_amount[4],
	          zone[z].sector[s].good_amount[5],
	          zone[z].sector[s].good_amount[6],
	          zone[z].sector[s].good_amount[7],
	          zone[z].sector[s].good_amount[8],
	          zone[z].sector[s].good_amount[9] );
	send_con_user ( con,rtn_str );

	//contras
	sprintf ( rtn_str,"28,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",s,z,
	          zone[z].sector[s].contra_amount[0],
	          zone[z].sector[s].contra_amount[1],
	          zone[z].sector[s].contra_amount[2],
	          zone[z].sector[s].contra_amount[3],
	          zone[z].sector[s].contra_amount[4],
	          zone[z].sector[s].contra_amount[5],
	          zone[z].sector[s].contra_amount[6],
	          zone[z].sector[s].contra_amount[7],
	          zone[z].sector[s].contra_amount[8],
	          zone[z].sector[s].contra_amount[9] );
	send_con_user ( con,rtn_str );
}

void relay_single_good_amount_sector ( int s, int z, int g )
{
	int i;
	char rtn_str[1000];

	sprintf ( rtn_str,"29,%d,%d,%d,%d%c",s,z,g,zone[z].sector[s].good_amount[g],13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].sector == s && user_con[i].zone == z )
		{
			//other checks
			if ( user_con[i].landed ) continue;

			raw_send_con_user ( i, rtn_str );
		}
}

void relay_single_contra_amount_sector ( int s, int z, int g )
{
	int i;
	char rtn_str[1000];

	sprintf ( rtn_str,"30,%d,%d,%d,%d%c",s,z,g,zone[z].sector[s].contra_amount[g],13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].sector == s && user_con[i].zone == z )
		{
			//other checks
			if ( user_con[i].landed ) continue;

			raw_send_con_user ( i, rtn_str );
		}
}

void relay_update_good_amount_sector ( int s, int z )
{
	int i;
	char good_str[1000], contra_str[1000];

	//goods
	sprintf ( good_str,"27,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%c",s,z,
	          zone[z].sector[s].good_amount[0],
	          zone[z].sector[s].good_amount[1],
	          zone[z].sector[s].good_amount[2],
	          zone[z].sector[s].good_amount[3],
	          zone[z].sector[s].good_amount[4],
	          zone[z].sector[s].good_amount[5],
	          zone[z].sector[s].good_amount[6],
	          zone[z].sector[s].good_amount[7],
	          zone[z].sector[s].good_amount[8],
	          zone[z].sector[s].good_amount[9], 13 );

	//contras
	sprintf ( contra_str,"28,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d%c",s,z,
	          zone[z].sector[s].contra_amount[0],
	          zone[z].sector[s].contra_amount[1],
	          zone[z].sector[s].contra_amount[2],
	          zone[z].sector[s].contra_amount[3],
	          zone[z].sector[s].contra_amount[4],
	          zone[z].sector[s].contra_amount[5],
	          zone[z].sector[s].contra_amount[6],
	          zone[z].sector[s].contra_amount[7],
	          zone[z].sector[s].contra_amount[8],
	          zone[z].sector[s].contra_amount[9], 13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].sector == s && user_con[i].zone == z )
		{
			//other checks
			if ( user_con[i].landed ) continue;

			raw_send_con_user ( i, good_str );
			raw_send_con_user ( i, contra_str );
		}
}

void relay_destroy_user_msg ( int s, int z, char *victom_name )
{
	int i;
	char temp_str[1025];

	sprintf ( temp_str,"10,1,%s Has Been Destroyed %c", victom_name, 13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].sector == s && user_con[i].zone == z )
		{
			//other checks
			if ( user_con[i].landed ) continue;

			raw_send_con_user ( i, temp_str );
		}
}

void user_pick_up_sector_good ( int con, int g, int amount )
{
	char rtn_str[1000];
	int s, z;

	//stuff good?
	if ( g<0 ) return;
	if ( g>9 ) return;
	if ( amount <= 0 ) return;

	//set some stuff...
	s = user_con[con].sector;
	z = user_con[con].zone;

	if(z < 0) return;
	if(z >= ZONE_MAX) return;
	if(s < 0) return;
	if(s >= SECTOR_MAX) return;

	//other stuff?
	if ( user_con[con].landed ) return;
	if ( zone[z].sector[s].good_amount[g] < amount ) return;
	if ( !user_has_hull(con)) return;

	//well ok
	sprintf ( rtn_str,"20,%d,%d,%d,%d,%d",user_con[con].user_id, s, z, g, amount );
	send_con_hub ( rtn_str );
}

void user_pick_up_sector_contra ( int con, int g, int amount )
{
	char rtn_str[1000];
	int s, z;

	//stuff good?
	if ( g<0 ) return;
	if ( g>9 ) return;
	if ( amount <= 0 ) return;

	//set some stuff...
	s = user_con[con].sector;
	z = user_con[con].zone;

	if(z < 0) return;
	if(z >= ZONE_MAX) return;
	if(s < 0) return;
	if(s >= SECTOR_MAX) return;

	//other stuff?
	if ( user_con[con].landed ) return;
	if ( zone[z].sector[s].contra_amount[g] < amount ) return;
	if ( !user_has_hull(con)) return;

	//well ok
	sprintf ( rtn_str,"21,%d,%d,%d,%d,%d",user_con[con].user_id, s, z, g, amount );
	send_con_hub ( rtn_str );
}

void user_drop_sector_good ( int con, int g, int amount )
{
	char rtn_str[1000];
	int s, z;
	int elium_smith_taken;

	//stuff good?
	if ( g<0 ) return;
	if ( g>9 ) return;
	if ( amount <= 0 ) return;

	//set some stuff...
	s = user_con[con].sector;
	z = user_con[con].zone;

	if(z < 0) return;
	if(z >= ZONE_MAX) return;
	if(s < 0) return;
	if(s >= SECTOR_MAX) return;

	//other stuff?
	if ( user_con[con].landed ) return;
	if ( !user_has_hull(con)) return;

	//at a planet?
	//if( zone[z].sector[s].planet != -1 )
	//{
    //    sprintf(rtn_str, "Can Not Drop Goods at a Planet");
    //    user_send_public_chat(con, 1, rtn_str);
    //    return;
    //}

	elium_smith_taken = get_elium_smith_taken(z,s,g);

	//well ok
	sprintf ( rtn_str,"22,%d,%d,%d,%d,%d,%d",user_con[con].user_id, s, z, g, amount, elium_smith_taken );
	send_con_hub ( rtn_str );
}

void user_drop_sector_contra ( int con, int g, int amount )
{
	char rtn_str[1000];
	int s, z, p;
	int contra_price;
	int ran_col = rand() %9;

	char lcase_user_guild[21], lcase_planet_guild[21];

	//stuff good?
	if ( g<0 ) return;
	if ( g>9 ) return;
	if ( amount <= 0 ) return;

	//set some stuff...
	s = user_con[con].sector;
	z = user_con[con].zone;
    p = zone[z].sector[s].planet;

    lcase ( lcase_user_guild, user_con[con].guild );
    lcase ( lcase_planet_guild, planet[p].sat.guild_name );

	if(z < 0) return;
	if(z >= ZONE_MAX) return;
	if(s < 0) return;
	if(s >= SECTOR_MAX) return;

	//other stuff?
	if ( user_con[con].landed ) return;
	if ( !user_has_hull(con)) return;

	//at a planet?
        if( zone[z].sector[s].planet != -1 && !str_match ( lcase_planet_guild, lcase_user_guild ) )
        {
            sprintf(rtn_str, "Can Not Drop Contraband at a Planet");
            user_send_public_chat(con, 1, rtn_str);
            return;
        }

	contra_price = get_smuggler_sector_contra_worth ( z,s,g );

	//well ok
	sprintf ( rtn_str,"23,%d,%d,%d,%d,%d,%d",user_con[con].user_id, s, z, g, amount, contra_price );
	send_con_hub ( rtn_str );

	//collector is comming..
	if (!existing_collector(z,s)) //check for collector / smuggler on this sector
	if ( z == 3 && rand() %10 + 1 >= 4) //check for FZ, check chance
    bot_move_to_sector(21,ran_col,s); //well, do it...
}

void relay_player_blow_up ( int s, int z, char *user_name )
{
	int i;
	char blowup_str[25] = "15,";

	sprintf ( blowup_str,"15,%s%c",user_name,13 );
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( user_con[i].sector != s || user_con[i].zone != z ) continue;
		if ( user_con[i].landed ) continue;

		raw_send_con_user ( i, blowup_str );
	}
}

void relay_public_entry ( int con )
{
	int i;
	char temp_str[300];

	//sprintf(temp_str,"11,3,... %s Has Entered The Diaspora ..%c", user_con[con].username, 13);
	//sprintf ( temp_str,"11,3,A Player Has Entered The Diadoxx %c", 13 );

	for ( i=0;i<=user_con_top;i++ )
        {
        	//so are we in the same guild or not ?
            if ( !strcmp ( user_con[con].guild, user_con[i].guild ) )
                sprintf(temp_str,"11,3,%s Has Entered The Diadoxx %c", user_con[con].username, 13);
            else //not the same guild
                sprintf ( temp_str,"11,3,A Player Has Entered The Diadoxx %c", 13 );

            if ( user_con[i].username[0] && i != con )
                raw_send_con_user ( i,temp_str );
        }
}

int users_online()
{
	int i;
	int dem_online = 0;

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
			dem_online++;

	return dem_online;
}

void user_send_sat_info ( int con, int p )
{
	char lcase_user_guild[21], lcase_planet_guild[21];
	char rtn_str[1025], append_str[200];
	int i;

	//check
	if ( p<0 ) return;
	if ( p>=PLANET_MAX ) return;

	lcase ( lcase_user_guild, user_con[con].guild );
	lcase ( lcase_planet_guild, planet[p].sat.guild_name );

	//so we own this planet or not?
	if ( str_match ( lcase_planet_guild, lcase_user_guild ) || !planet[p].sat.level )
	{
		//standard stuff
		sprintf ( rtn_str,"31,%d,%d,%s,%d,%d",
		          p,
		          planet[p].sat.level,
		          planet[p].sat.guild_name,
		          planet[p].sat.money,
		          planet[p].sat.money_collected );

		//guns
		for ( i=0;i<SAT_LEVEL_MAX * SAT_GUN_INC;i++ )
		{
			sprintf ( append_str, ",%d,%d", planet[p].sat.gun[i], planet[p].sat.gun_destroyed[i] );
			strcat ( rtn_str, append_str );
		}

		//missile
		for ( i=0;i<SAT_LEVEL_MAX * SAT_MISSILE_INC;i++ )
		{
			sprintf ( append_str, ",%d,%d", planet[p].sat.missile[i], planet[p].sat.missile_left[i] );
			strcat ( rtn_str, append_str );
		}

		//now the hull
		sprintf ( append_str, ",%d", planet[p].sat.hull );
		strcat ( rtn_str, append_str );
	}
	else //we don't deserve to know this information
	{
		sprintf ( rtn_str,"31,%d,-1,%s,0,0",
		          p,
		          planet[p].sat.guild_name );

		//guns
		for ( i=0;i<SAT_LEVEL_MAX * SAT_GUN_INC;i++ )
			strcat ( rtn_str, ",0,0" );

		//missile
		for ( i=0;i<SAT_LEVEL_MAX * SAT_MISSILE_INC;i++ )
			strcat ( rtn_str, ",0,0" );

		//now the hull
		strcat ( rtn_str, ",0" );
	}

	send_con_user ( con, rtn_str );
}

void relay_planet_sat_info ( int p )
{
	int i;

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
		{
			//checks
			//same planet, landed
			if ( !user_con[i].landed ) continue;
			if ( user_con[i].last_planet != p ) continue;

			//send it
			user_send_sat_info ( i,p );
		}
}

void relay_planet_sat_hull ( int p )
{
	int i;
	char rtn_str[50];

	sprintf ( rtn_str,"32,%d%c",planet[p].sat.hull,13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
		{
			//checks
			//same planet, landed
			if ( !user_con[i].landed ) continue;
			if ( user_con[i].last_planet != p ) continue;
			if ( strcmp ( user_con[i].guild, planet[p].sat.guild_name ) ) continue;

			//send it
			raw_send_con_user ( i,rtn_str );
		}
}

void relay_planet_sat_money ( int p )
{
	int i;
	char rtn_str[50];

	sprintf ( rtn_str,"33,%d%c",planet[p].sat.money,13 );

	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
		{
			//checks
			//same planet, landed
			if ( !user_con[i].landed ) continue;
			if ( user_con[i].last_planet != p ) continue;

			//send it
			raw_send_con_user ( i,rtn_str );
		}
}

void send_user_getting_attacked_from ( int con, char *attacker_name )
{
	char attacking_you[25];

	sprintf ( attacking_you,"19,%s",attacker_name );
	send_con_user ( con, attacking_you );
}

int sat_should_attack_user ( int p, int i )
{
	int u;

	//set it
	u = planet[p].sat.user_attacking[i];

	//exists?
	if ( u<0 ) return 0;
	//online?
	if ( !user_con[u].username[0] ) return 0;
	//alive?
	if ( user_con[u].ship.hull <= 0 ) return 0;
	//landed?
	if ( user_con[u].landed ) return 0;
	//not in same sector or zone?
	if ( user_con[u].sector != planet[p].sat.sector ) return 0;
	if ( user_con[u].zone != planet[p].sat.zone ) return 0;

	//well then ok
	return 1;
}

int sat_should_attack_bot ( int p, int i )
{
	int b_t, b_u;

	//set it
	b_t = planet[p].sat.bot_type_attacking[i];
	b_u = planet[p].sat.bot_attacking[i];

	//exists?
	if ( b_t<0 ) return 0;
	if ( b_u<0 ) return 0;
	//alive?
	if ( bot_type[b_t].bot[b_u].hull <= 0 ) return 0;
	//not in same sector or zone?
	if ( bot_type[b_t].bot[b_u].sector != planet[p].sat.sector ) return 0;
	if ( bot_type[b_t].zone != planet[p].sat.zone ) return 0;

	//well then ok
	return 1;
}

void sat_attack_user ( int p, int u )
{
	int i;
	int already_attacking_the_fool;

	//already attacking this fool?
	already_attacking_the_fool = 0;
	for ( i=0;i<planet[p].sat.user_attacking_max;i++ )
		if ( planet[p].sat.user_attacking[i] == u )
			{already_attacking_the_fool = 1; break;}

	if ( already_attacking_the_fool ) return;

	//find an empty slot
	for ( i=0;i<planet[p].sat.user_attacking_max && i<MAX_USER_CON;i++ )
		if ( planet[p].sat.user_attacking[i] < 0 )
			break;

	//already attacking the whole game
	if ( i==MAX_USER_CON ) return;

	//welp attack the user
	planet[p].sat.user_attacking[i] = u;

	//do a little check...
	if ( !sat_should_attack_user ( p,i ) )
	{
		//cancel that shit
		planet[p].sat.user_attacking[i] = -1;
		return ;
	}

	//set new user_max if need be
	if ( i==planet[p].sat.user_attacking_max )
		planet[p].sat.user_attacking_max++;

	//tell everyone
	relay_user_attack_user ( user_con[u].zone, user_con[u].sector, "Satellite", user_con[u].username, u, -1 );

	//tell that player
	send_user_getting_attacked_from ( u, "Satellite" );
}

void sat_attack_bot ( int p, int b_t, int b_u )
{
	int i;
	int already_attacking_the_fool;

	//already attacking this fool?
	already_attacking_the_fool = 0;
	for ( i=0;i<planet[p].sat.bot_attacking_max;i++ )
		if ( planet[p].sat.bot_type_attacking[i] == b_t && planet[p].sat.bot_attacking[i] == b_u )
			{already_attacking_the_fool = 1; break;}

	if ( already_attacking_the_fool ) return;

	//find an empty slot
	for ( i=0;i<planet[p].sat.bot_attacking_max && i<BOT_TOTAL_MAX;i++ )
		if ( planet[p].sat.bot_attacking[i] < 0 )
			break;

	//already attacking the whole game
	if ( i==BOT_TOTAL_MAX ) return;

	//welp attack the user
	planet[p].sat.bot_type_attacking[i] = b_t;
	planet[p].sat.bot_attacking[i] = b_u;

	//do a little check...
	if ( !sat_should_attack_bot ( p,i ) )
	{
		//cancel that shit
		planet[p].sat.bot_type_attacking[i] = -1;
		planet[p].sat.bot_attacking[i] = -1;
		return ;
	}

	//set new user_max if need be
	if ( i==planet[p].sat.bot_attacking_max )
		planet[p].sat.bot_attacking_max++;

	//tell everyone
	relay_user_attack_user ( bot_type[b_t].zone, bot_type[b_t].bot[b_u].sector, "Satellite", bot_type[b_t].bot[b_u].name, -1, -1 );
}

void sat_disengage_user ( int p, int i )
{
	//simple
	planet[p].sat.user_attacking[i] = -1;

	//reset the max
	if ( i + 1 == planet[p].sat.user_attacking_max )
		planet[p].sat.user_attacking_max--;

	//tell everybody
	relay_user_disengage ( planet[p].sat.zone,planet[p].sat.sector,"Satellite",-1 );
}

void sat_disengage_bot ( int p, int i )
{
	//simple
	planet[p].sat.bot_attacking[i] = -1;
	planet[p].sat.bot_type_attacking[i] = -1;

	//reset the max
	if ( i + 1 == planet[p].sat.bot_attacking_max )
		planet[p].sat.bot_attacking_max--;

	//tell everybody
	relay_user_disengage ( planet[p].sat.zone,planet[p].sat.sector,"Satellite",-1 );
}

double destroy_gun_chance ( double percent_hull_left, int wep_accuracy, int is_missile )
{
	double max_chance;

	if ( is_missile )
		max_chance = 0.04;
	else
		max_chance = 0.01;

	if ( wep_accuracy >= 80 ) max_chance *= 2;

	return max_chance * ( 1.5 - percent_hull_left );
}

void attempt_destroy_gun ( int *gun_destroyed_loc, double percent_hull_left, int wep_accuracy, int is_missile )
{
	//already destroyed
	if ( *gun_destroyed_loc ) return;

	if ( rand() %10000 < destroy_gun_chance ( percent_hull_left, wep_accuracy, is_missile ) * 10000 )
		*gun_destroyed_loc = 1;
}

void attempt_destroy_random_sat_gun ( int p, int wep_accuracy, int is_missile )
{
	int random_choice;

	random_choice = rand() % ( SAT_LEVEL_MAX * SAT_GUN_INC );

	//already destroyed?
	if ( planet[p].sat.gun_destroyed[random_choice] ) return;

	//attempt the destroy
	attempt_destroy_gun (
	    & ( planet[p].sat.gun_destroyed[random_choice] ),
	    1.0 * planet[p].sat.hull / ( planet[p].sat.level * SAT_HULL_INC ),
	    wep_accuracy,
	    is_missile );

	//if destroyed tell the hub
	if ( planet[p].sat.gun_destroyed[random_choice] )
	{
		hub_set_sat_gun_destroyed ( p,random_choice );

		//and all the clients
		relay_planet_sat_info ( p );
	}
}

void attempt_destroy_random_user_gun ( int u, int wep_accuracy, int is_missile )
{
	int random_choice;

	random_choice = rand() % user_con[u].ship.gun_ammount;

	//have a gun at all?
	if ( user_con[u].ship.gun[random_choice].speed <= 0 ) return;

	//already destroyed?
	if ( user_con[u].ship.gun[random_choice].destroyed ) return;

	//attempt the destroy
	attempt_destroy_gun (
	    & ( user_con[u].ship.gun[random_choice].destroyed ),
	    1.0 * user_con[u].ship.hull / user_con[u].ship.hull_max,
	    wep_accuracy,
	    is_missile );

	//if destroyed tell the hub
	if ( user_con[u].ship.gun[random_choice].destroyed )
		relay_user_destroy_gun ( u,random_choice );

	set_average_gun_speed ( u ); //might want to do this
}

void relay_user_destroy_gun ( int u, int g )
{
	char rtn_str[200];

	//tell a hub
	sprintf ( rtn_str,"9,%d,%d", user_con[u].user_id, g );
	send_con_hub ( rtn_str );

	//tell a user
	sprintf ( rtn_str,"34,%d", g );
	send_con_user ( u,rtn_str );

	//now give them a little chat peice too
	//	sprintf(temp_str,"10,1,... %s Has Been Destroyed ..%c", victom_name, 13);
	sprintf ( rtn_str,"Warning :  Gun Pod %d Destroyed", g+1 );
	user_send_public_chat ( u,1,rtn_str );
}

double sector_damage_reduction ( int z, int s )
{
	if ( zone[z].sector[s].shield )
		return FIELD_REDUCTION;
	else
		return 1;
}

void user_notify_attackee_of_shield ( int u )
{
	int i;
	int z,s;
	char send_str[200];

	//dumb checks
	if ( user_con[u].landed ) return;
	if ( user_con[u].ship.server_id < 0 ) return;
	if ( user_con[u].ship.type < 0 ) return;
	if ( user_con[u].ship.kind < 0 ) return;

	z = user_con[u].zone;
	s = user_con[u].sector;

	sprintf ( send_str,"37,%d%c",user_con[u].ship.shield_level,13 );

	//find everyone attacking this fool
	for ( i=0;i<=user_con_top;i++ )
		if ( user_con[i].username[0] )
		{
			//checks
			if ( i==u ) continue;

			//this person suposedly attacking us?
			if ( user_con[i].user_attacking != u ) continue;
			if ( user_con[i].attacking_bot ) continue;
			if ( user_con[i].attacking_sat ) continue;

			//should they be?
			if ( user_con[i].landed ) continue;
			if ( user_con[i].zone != z ) continue;
			if ( user_con[i].sector != s ) continue;

			//well tell them
			raw_send_con_user ( i,send_str );
		}
}

void notify_attacker_of_enemy_jump ( int u )
{
	char rtn_str[100] = "40,1";

	//they already know?
	if ( user_con[u].received_enemy_jump_status_as_full ) return;

	//so what are we attacking exactly?
	if ( !user_con[u].attacking_sat && !user_con[u].attacking_bot )
	{
		int v_u;

		v_u = user_con[u].user_attacking;

		//check?
		if ( v_u<0 ) return;
		if ( !user_jump_is_charged ( v_u ) ) return;

		user_con[u].received_enemy_jump_status_as_full = 1;
		//sprintf(rtn_str,"40,%d", user_jump_is_charged(v_u));

		send_con_user ( u, rtn_str );
	}
	else if ( user_con[u].attacking_sat )
	{
		//you never need to send this because the client defaults 0

		//might as well just set this..
		user_con[u].received_enemy_jump_status_as_full = 1;

		//sprintf(rtn_str,"40,0");

		//send_con_user(u, rtn_str);
	}
	else if ( user_con[u].attacking_bot )
	{
		int b_t, b_u;

		b_t = user_con[u].bot_type_attacking;
		b_u = user_con[u].user_attacking;

		//check?
		if ( b_t<0 ) return;
		if ( b_u<0 ) return;

		//is this bot a field type and need to be ignored?
		if ( bot_type[b_t].field_type )
		{
			user_con[u].received_enemy_jump_status_as_full = 1;
			return;
		}

		//ready?
		if ( !bot_jump_is_charged ( b_t, b_u ) ) return;

		//sprintf(rtn_str,"40,%d", bot_jump_is_charged(b_t, b_u));

		user_con[u].received_enemy_jump_status_as_full = 1;

		send_con_user ( u, rtn_str );
	}
}

void notify_attacker_of_victom_shield ( int u )
{
	char rtn_str[200];

	//so what are we attacking exactly?
	if ( !user_con[u].attacking_sat && !user_con[u].attacking_bot )
	{
		int v_u;

		v_u = user_con[u].user_attacking;

		//check?
		if ( v_u<0 ) return;

		sprintf ( rtn_str,"37,%d", user_con[v_u].ship.shield_level );

		send_con_user ( u, rtn_str );
	}
	else if ( user_con[u].attacking_sat )
	{
		sprintf ( rtn_str,"37,4" );

		send_con_user ( u, rtn_str );
	}
	else if ( user_con[u].attacking_bot )
	{
		int b_t, b_u;

		b_t = user_con[u].bot_type_attacking;
		b_u = user_con[u].user_attacking;

		//check?
		if ( b_t<0 ) return;
		if ( b_u<0 ) return;

		sprintf ( rtn_str,"37,%d",bot_type[b_t].bot[b_u].shield_level );

		send_con_user ( u, rtn_str );
	}
}

void notify_attacker_of_ref_ratio( int con )
{
	char rtn_str[200];
	float their_defense = 1.0, our_defense = 1.0;
	int victom_con;

	if ( user_con[con].user_attacking == -1 ) return;

	victom_con = user_con[con].user_attacking;

	if ( !user_con[con].attacking_bot && !user_con[con].attacking_sat )
	{
		their_defense = damage_ship_ref_reduction(user_con[con].ship.ref, user_con[victom_con].ship.ref);
		our_defense = damage_ship_ref_reduction(user_con[victom_con].ship.ref, user_con[con].ship.ref);
	}

	sprintf ( rtn_str,"49,%f,%f", our_defense, their_defense );
	send_con_user ( con, rtn_str );
}

void user_dock_jump ( int con )
{
	double cur_time;
	char rtn_str[200] = "38,";

	cur_time = current_time();

	//we aloud to do another docking?
	if ( cur_time - user_con[con].last_jump_dock_time < JUMP_DOCK_TIME ) return;

	//check
	if ( cur_time - user_con[con].last_jump_time > user_con[con].jump_time ) return;

	//set the time
	user_con[con].last_jump_dock_time = cur_time;

	//reduce their jump
	user_con[con].last_jump_time += JUMP_DOCK_TIME;

	//ehh
	if ( user_con[con].last_jump_time > cur_time )
		user_con[con].last_jump_time = cur_time;

	//tell them
	send_con_user ( con, rtn_str );
}

void set_user_jump_time ( int con )
{
	user_con[con].jump_time = ship_total_seconds ( user_con[con].ship.speed, user_con[con].ship.kind );
}

int user_try_disable_shield ( int con )
{
	if ( rand() %100 + 1 > SHIELD_DISABLE_CHANCE ) return 0;
	if ( user_shield_is_disabled ( con ) ) return 0;

	//and set
	set_user_shield ( con, 0 );

	//set
	user_con[con].ship.shield_disable_time = current_time();

	//notify
	user_notify_shield_disabled ( con );

	return 1;
}

int user_shield_is_disabled ( int con )
{
	return ( current_time() < user_con[con].ship.shield_disable_time + SHIELD_DISABLE_TIME );
}

void user_notify_shield_disabled ( int con )
{
	char rtn_str[200] = "39,";

	send_con_user ( con, rtn_str );
}

int planet_to_id ( char *planetname )
{
	int p;
	int const planet_max_len = 21;
	char lcase_planet[planet_max_len];

	if ( strlen ( planetname ) > planet_max_len - 1 ) return -1;

	lcase ( lcase_planet, planetname );

	for ( p=0;p<PLANET_MAX;p++ )
		if ( planet[p].name[0] )
		{
			char lcase_thisplanet[planet_max_len];

			lcase ( lcase_thisplanet, planet[p].name );

			if ( !strcmp ( lcase_thisplanet, lcase_planet ) )
				return p;
		}

	return -1;
}

void user_request_goodprices ( int con, char *planetname )
{
	char rtn_str[500];
	int p, g;

	p = planet_to_id ( planetname );

	if ( p==-1 )
	{
		sprintf ( rtn_str,"Planet not found" );
		user_send_public_chat ( con,1,rtn_str );

		return;
	}

	if ( planet[p].is_gate )
	{
		sprintf ( rtn_str,"%s does not trade goods", planet[p].name );
		user_send_public_chat ( con,1,rtn_str );

		return;
	}

	//do the goods
	for ( g=9;g>=0;g-- )
	{
		char goodname[30];


		sprintf ( rtn_str,"%.20s: %d", good_name ( g, goodname ), planet[p].good_price[g] );
		user_send_public_chat ( con,1,rtn_str );
	}

	//say the news
	sprintf ( rtn_str,"Base good prices for: %s", planet[p].name );
	user_send_public_chat ( con,1,rtn_str );
}

void reset_rune ( int i )
{
	int s, z;
	int s_z[ZONE_MAX * SECTOR_MAX], s_s[ZONE_MAX * SECTOR_MAX];
	int s_max;
	int c, u;

	if ( i<0 ) return;
	if ( i>3 ) return;

	//make sure no players have it
	for ( u=0;u<=user_con_top;u++ )
		if ( user_con[u].has_rune == i )
			user_con[u].has_rune = -1;

	//make sure no sectors have it
	s_max = 0;
	for ( z=0;z<ZONE_MAX;z++ )
		if ( zone[z].name[0] )
			for ( s=0;s<SECTOR_MAX;s++ )
				if ( zone[z].sector[s].x )
				{
					//set sector
					s_z[s_max] = z;
					s_s[s_max] = s;
					s_max++;

					//rape the sector
					zone[z].sector[s].has_rune[i] = 0;
				}

	//place it somewhere
	c = rand() % s_max;
	z = s_z[c];
	s = s_s[c];

	zone[z].sector[s].has_rune[i] = 1;

	//now tell people
}

int user_jump_is_charged ( int con )
{
	return ( current_time() - user_con[con].last_jump_time >= user_con[con].jump_time );
}

void do_pings()
{
	static int last_user_ping_time = 0;
	static int last_hub_ping_time = 0;
	int the_time;

	the_time = time ( 0 );

	if ( !last_user_ping_time )
	{
		last_user_ping_time = the_time;
		last_hub_ping_time = the_time;
	}

	if ( the_time - last_user_ping_time >= PING_USER_DELAY_SECONDS )
	{

		last_user_ping_time = the_time;
	}

	if ( the_time - last_hub_ping_time >= PING_HUB_DELAY_SECONDS )
	{

		last_hub_ping_time = the_time;
	}
}

void ping_user_con ( int con )
{
	char send_str[20] = "42,";
	send_con_user ( con, send_str );
}


void ping_all_users()
{
	int i;
	char send_str[5] = {'4', '2', ',', 13, 0};

	for ( i=0;i<=user_con_top;i++ )
		raw_send_con_user ( i, send_str );
}

void user_ping_response ( int con )
{

}

void user_set_for_bot_death ( int u )
{
	user_con[u].ship.hull = 1;

	user_con[u].destroy_on_recv = 1;

	user_send_hub_hull ( u );

	ping_user_con ( u );
}

void user_do_destroy_on_recv ( int u )
{
	user_con[u].destroy_on_recv = 0;

	if ( !user_con[u].username[0] ) return;
	if ( user_con[u].landed ) return;

	destroy_user ( u,-1 );

	user_con[u].destroy_on_recv = 0;
}

void user_send_hub_hull ( int con )
{
	char rtn_str[200];

	if ( user_con[con].update_hull )
	{
		user_con[con].update_hull = 0;
		sprintf ( rtn_str, "8,%d,%d", user_con[con].user_id, user_con[con].ship.hull );
		send_con_hub ( rtn_str );
	}
}

int sector_has_users ( int z, int s )
{
	int i;

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if ( user_con[i].sector != s ) continue;
		if ( user_con[i].zone != z ) continue;
		if ( user_con[i].landed ) continue;

		//well there is someone here
		return 1;
	}

	//well we didn't find anyone
	return 0;
}

void recalculate_sector_free_scan ( int z, int s, int entering )
{
	int i;
	char rtn_str[100];

	//this sector allow free scanning?
	if ( !zone[z].free_scan && !zone[z].sector[s].free_scan ) return;

	//are we adding a user into a sector that already has users?
	if ( zone[z].sector[s].has_player == entering ) return;

	//set has players
	zone[z].sector[s].has_player = sector_has_users ( z,s );

	//relay that info - 43
	sprintf ( rtn_str, "43,%d,%d,%d%c", z, s, zone[z].sector[s].has_player, 13 );

	//tell all connected players
	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;

		//well there is someone here
		raw_send_con_user ( i, rtn_str );
	}
}

void user_send_free_scan_list(int con)
{
	int i;
	int z, s;
	char rtn_str[100];

	for(z=0;z<ZONE_MAX;z++)
	{
		if(!zone[z].name[0]) continue;

		if(zone[z].free_scan)
		{
			for(s=0;s<SECTOR_MAX;s++)
				if(zone[z].sector[s].x)
			{
				sprintf ( rtn_str, "43,%d,%d,%d%c", z, s, zone[z].sector[s].has_player, 13 );
				raw_send_con_user ( con, rtn_str );
			}
		}
		else
		{
			for(s=0;s<SECTOR_MAX;s++)
				if(zone[z].sector[s].x && zone[z].sector[s].free_scan)
			{
				sprintf ( rtn_str, "43,%d,%d,%d%c", z, s, zone[z].sector[s].has_player, 13 );
				raw_send_con_user ( con, rtn_str );
			}
		}

	}
}

int is_bot_guild(char *the_guild)
{
	int p;

	if(!strcmp(the_guild, "Rogue")) return 1;

	for(p=0;p<PLANET_MAX;p++)
		if(planet[p].name[0] && planet[p].guild[0] && !strcmp(the_guild, planet[p].guild))
			return 1;

	return 0;
}

int sector_has_guild_member(int z, int s, char *the_guild, int exclude_con)
{
	int i;

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if(user_con[i].sector != s) continue;
		if(user_con[i].zone != z) continue;
		if(user_con[i].landed) continue;
		if(user_con[i].has_bot_guild) continue;
		if(i == exclude_con) continue;

		if(!strcmp(the_guild, user_con[i].guild)) return 1;

	}
	return 0;
}

void annouce_guild_member_enter_sector(int z, int s, char *the_guild, int exclude_con)
{
	int i;
	char rtn_str[100];

	//preperatize the packetr
	sprintf(rtn_str, "44,%d,%d,1%c", z, s, 13);

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if(user_con[i].has_bot_guild) continue;
		if(strcmp(the_guild, user_con[i].guild)) continue;

		raw_send_con_user ( i, rtn_str );
	}
}

void annouce_guild_member_leave_sector(int z, int s, char *the_guild, int exclude_con)
{
	int i;
	char rtn_str[100];

	//does it still have members?
	if(sector_has_guild_member(z,s,the_guild,exclude_con)) return;

	//preperatize the packetr
	sprintf(rtn_str, "44,%d,%d,0%c", z,s, 13);

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if(user_con[i].has_bot_guild) continue;
		if(strcmp(the_guild, user_con[i].guild)) continue;

		raw_send_con_user ( i, rtn_str );
	}
}

void user_clear_has_member_sectors(int con)
{
	char rtn_str[100] = "45,";

	send_con_user ( con, rtn_str );
}

void user_resend_has_member_sectors(int con)
{
	char rtn_str[100];
	int i;
	int z, s;

	if(user_con[con].has_bot_guild) return;

	for ( i=0;i<=user_con_top;i++ )
	{
		if ( !user_con[i].username[0] ) continue;
		if(user_con[i].landed) continue;
		if(strcmp(user_con[con].guild, user_con[i].guild)) continue;

		sprintf(rtn_str, "44,%d,%d,1%c", user_con[i].zone, user_con[i].sector, 13);

		send_con_user ( con, rtn_str );
	}
}

bool user_has_hull(int con)
{
    if(user_con[con].ship.server_id < 0) return false;
    if(user_con[con].ship.type < 0) return false;
    if(user_con[con].ship.kind < 0) return false;

    return user_con[con].ship.hull > 0;
}

void update_users_on_online_players()
{
	int i;
	int players_online = 0;
	char rtn_str[1025];

	for(i=0;i<=user_con_top;i++)
		if (user_con[i].username[0])
			players_online++;

	//preperatize the packetr
	sprintf(rtn_str, "46,%d%c", players_online, 13);

	//send
	for(i=0;i<=user_con_top;i++)
		if (user_con[i].username[0])
			raw_send_con_user ( i, rtn_str );

	//needs to happen too if the total player count has changed
	update_users_on_zone_players();
}

void update_users_on_zone_players()
{
	int i;
	int players_in_zone[ZONE_MAX];
	int players_launched_in_zone[ZONE_MAX];
	char rtn_str[1025];
	char cat_str[1025];

	for(i=0;i<ZONE_MAX;i++)
	{
		players_in_zone[i] = 0;
		players_launched_in_zone[i] = 0;
	}

	for(i=0;i<=user_con_top;i++)
		if (user_con[i].username[0])
		{
			if(user_con[i].zone < 0) continue;
			if(user_con[i].zone >= ZONE_MAX) continue;

			players_in_zone[user_con[i].zone]++;

			if(!user_con[i].landed) players_launched_in_zone[user_con[i].zone]++;
		}

	//preperatize the packetr
	sprintf(rtn_str, "47");
	for(i=0;i<ZONE_MAX;i++)
	{
		sprintf(cat_str, ",%d,%d", players_in_zone[i], players_launched_in_zone[i]);
		strcat(rtn_str, cat_str);
	}
	cat_str[0] = 13;
	cat_str[1] = 0;
	strcat(rtn_str, cat_str);

	//send
	for(i=0;i<=user_con_top;i++)
		if (user_con[i].username[0])
			raw_send_con_user ( i, rtn_str );
}

class zone_sector
{
public:
	zone_sector(int z_, int s_, int i)
	{
		z = z_;
		s = s_;
		user_list.push_back(i);
	}

	int z, s;
	vector<int> user_list;
};

void send_user_sector_userlists(int con)
{
	int i;
	vector<zone_sector> sector_list;

	for(i=0;i<=user_con_top;i++)
		if (user_con[i].username[0] && !strcmp(user_con[i].guild, user_con[con].guild))
		{
			if(user_con[i].zone < 0) continue;
			if(user_con[i].sector < 0) continue;
			if(user_con[i].landed) continue;

			for(vector<zone_sector>::iterator s=sector_list.begin(); s!=sector_list.end(); s++)
				if(s->z == user_con[i].zone && s->s == user_con[i].sector)
				{
					s->user_list.push_back(i);
					continue;
				}

			sector_list.push_back(zone_sector(user_con[i].zone, user_con[i].sector, i));
		}

	for(vector<zone_sector>::iterator s=sector_list.begin(); s!=sector_list.end(); s++)
	{
		char rtn_str[1025];
		char cat_str[1025];

		sprintf(rtn_str, "48,%d,%d", s->z, s->s);

		for(vector<int>::iterator u=s->user_list.begin(); u!=s->user_list.end(); u++)
		{
			sprintf(cat_str, ",%s,%s", user_con[*u].username, user_con[*u].guild);
			if(strlen(rtn_str) + strlen(cat_str) < 1020)
				strcat(rtn_str, cat_str);
		}

		send_con_user ( con, rtn_str );
	}
}

void update_users_sector_userlist(int z, int s)
{
	int i;
	vector<string> guild_list;
	char rtn_str[1025];
	char cat_str[1025];

	if(z < 0) return;
	if(s < 0) return;

	//build send_str
	sprintf(rtn_str, "48,%d,%d", z, s);

	for(i=0;i<=user_con_top;i++)
		if (user_con[i].username[0])
		{
			if(user_con[i].landed) continue;
			if(user_con[i].zone != z) continue;
			if(user_con[i].sector != s) continue;

			//send_str
			sprintf(cat_str, ",%s,%s", user_con[i].username, user_con[i].guild);
			if(strlen(rtn_str) + strlen(cat_str) < 1020)
				strcat(rtn_str, cat_str);

			//it already in the list?
			for(vector<string>::iterator g=guild_list.begin(); g!=guild_list.end(); g++)
				if(user_con[i].guild == *g)
					continue;

			guild_list.push_back(user_con[i].guild);
		}

	if(!guild_list.size()) return;

	//send_str
	cat_str[0] = 13;
	cat_str[1] = 0;
	strcat(rtn_str, cat_str);

	for(vector<string>::iterator g=guild_list.begin(); g!=guild_list.end(); g++)
		for(i=0;i<=user_con_top;i++)
			if (user_con[i].username[0] && user_con[i].guild == *g)
				raw_send_con_user ( i, rtn_str );
}

void user_check_worthy_launch_time(int con)
{
	int s, z, range, planet;

	if(user_con[con].landed)
	{
		user_send_worthy_launch_time(con);
		return;
	}

	s = user_con[con].sector;
	z = user_con[con].zone;

	if(s < 0 || z < 0)
	{
		user_con[con].last_worthy_launch_time = 0;
		return;
	}

	range = zone[z].sector[s].range;
	planet = zone[z].sector[s].planet;

	if(range > 0 && planet == -1)
	{
		if(!user_con[con].last_worthy_launch_time)
			user_con[con].last_worthy_launch_time = time(0);
	}
	else
	{
		user_send_worthy_launch_time(con);
	}
}

void user_send_worthy_launch_time(int con)
{
	char rtn_str[1025];

	if(user_con[con].last_worthy_launch_time)
	{
		int new_time = time(0) - user_con[con].last_worthy_launch_time;

		sprintf(rtn_str, "36,%d,%d", user_con[con].user_id, new_time);
		send_con_hub(rtn_str);
	}

	user_con[con].last_worthy_launch_time = 0;
}

void check_user_skimmed(int con)
{
	int z, s;
	char message[1000];
	unsigned long our_s_addr;
	int i;
	string similar_ip_usernames;

	if(user_con[con].landed) return;
	if(current_time() > user_con[con].last_enter_sector_time + SKIM_TIME) return;

	z = user_con[con].zone;
	s = user_con[con].sector;

	if(z < 0) return;
	if(s < 0) return;

	//are there other users in this sector?

	sprintf(message, "%s has skimmed the sector", user_con[con].username);

	user_send_public_chat_to_sector(1, message, z, s);

	our_s_addr = get_user_s_addr(con);

	for ( i=0;i<=user_con_top;i++ )
		if(get_user_s_addr(i) == our_s_addr && con != i)
		{
			sprintf(message, "%s has the same IP as %s", user_con[con].username, user_con[i].username);

			user_send_public_chat_to_sector(1, message, z, s);

			if(similar_ip_usernames.size()) similar_ip_usernames += ", ";
			similar_ip_usernames += user_con[i].username;
		}

	//write log
	{
		sprintf(message, "skimmed: '%-20s' similar IPs: %s ..", user_con[con].username, similar_ip_usernames.c_str());
		printd_gen("logs/","skim.txt", message);
	}
}
