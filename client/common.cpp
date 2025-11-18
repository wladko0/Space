#include "common.h"
#include "database_common.h"

void split(char *dest, char *message, char char_spliter, int *initial)
{
        char temp[80];
        int i, a = 0;

    	for(i = *initial; i < 100100100; i++)
        {
	        if (message[i] == 0) // check to see if at end of string
	                break;

        	if (message[i] != char_spliter) //check to see if at the split mark
	        {
	        	dest[a] = message[i];
                        a++;
        	}
                else
                        break;
        }

        dest[a] = '\0';          //"cap" return string
	if (message[i] == 0) //return point to continue search
		*initial = i;
	else
		*initial = ++i;
        return;			//return
}

int str_match(char *str1, char *str2)
{
	if(str1[0] == '\0' || str2[0] == '\0')
	{
		if(str1[0] == str2[0])
			return 1;
		else
			return 0;
	}

	if (strcmp(str1,str2) == 0)
		return 1;
	else
		return 0;
}

int str_match_lcase(char *str1, char *str2)
{
	char l_str1[20000], l_str2[20000];

	lcase(l_str1, str1);
	lcase(l_str2, str2);

	if(str1[0] == '\0' || str2[0] == '\0')
	{
		if(str1[0] == str2[0])
			return 1;
		else
			return 0;
	}

	if (strcmp(l_str1,l_str2) == 0)
		return 1;
	else
		return 0;
}

void lcase(char *dest, char *src)
{
	int i;

	for(i=0;src[i] != '\0';i++)
	{
		if (src[i] >= 'A' && src[i] <= 'Z')
			dest[i] = src[i] + 32;
		else
			dest[i] = src[i];
	}

	dest[i] = '\0';
}

void left ( char *dest, char *src, int point )
{
	int i=0;
	for ( i=0;src[i] != '\0' && i != point;i++ )
		dest[i] = src[i];

	dest[i] = '\0';
}

void right(char *dest, char *src, int point)
{
	int i = 0;
	while(src[point] != '\0')
	{
		dest[i] = src[point];
		point++;
		i++;
	}

	dest[i] = '\0';
}

void uni_pause(int m_sec)
{
#ifdef _WIN32 //if windows
	Sleep(m_sec);	//win version
#else
	usleep(m_sec * 1000);	//lin version
#endif
}

extern int misc_pod_value(int misc_pod_number)
{
	switch (misc_pod_number)
	{
	case MK1_HULL: return 50;
	case MK1_SHIELD: return 5;
	case MK1_CARGO: return 50;
	case MK1_JUMP: return 2;
	case MK2_HULL: return 100;
	case MK2_SHIELD: return 7;
	case MK2_CARGO: return 75;
	case MK2_JUMP: return 3;
	case MK3_HULL: return 150;
	case MK3_SHIELD: return 10;
	case MK3_CARGO: return 100;
	case MK3_JUMP: return 4;
	}

	return 0;
}

extern int misc_pod_exp(int misc_pod_number)
{
	switch (misc_pod_number)
	{
	case MK1_HULL: return 0;
	case MK1_SHIELD: return 0;
	case MK1_CARGO: return 0;
	case MK1_JUMP: return 0;
	case MK2_HULL: return 200;
	case MK2_SHIELD: return 250;
	case MK2_CARGO: return 100;
	case MK2_JUMP: return 300;
	case MK3_HULL: return 300;
	case MK3_SHIELD: return 400;
	case MK3_CARGO: return 200;
	case MK3_JUMP: return 500;
	}

	return 0;
}

extern int misc_pod_cost(int misc_pod_number)
{
	switch (misc_pod_number)
	{
	case MK1_HULL: return 5000;
	case MK1_SHIELD: return 4000;
	case MK1_CARGO: return 2000;
	case MK1_JUMP: return 2000;
	case MK2_HULL: return 250000;
	case MK2_SHIELD: return 500000;
	case MK2_CARGO: return 100000;
	case MK2_JUMP: return 750000;
	case MK3_HULL: return 330000;
	case MK3_SHIELD: return 660000;
	case MK3_CARGO: return 130000;
	case MK3_JUMP: return 1000000;
	}

	return 0;
}

char *misc_pod_name ( int misc_pod_number, char *dest )
{
	switch ( misc_pod_number )
	{
		case MK1_HULL: strcpy ( dest,"Mk1 Hull Booster" ); break;
		case MK1_SHIELD: strcpy ( dest,"Mk1 Shield Generator" ); break;
		case MK1_CARGO: strcpy ( dest,"Mk1 Cargo Pod" ); break;
		case MK1_JUMP: strcpy ( dest,"Mk1 Jump Drive" ); break;
		case MK2_HULL: strcpy ( dest,"Mk2 Hull Booster" ); break;
		case MK2_SHIELD: strcpy ( dest,"Mk2 Shield Generator" ); break;
		case MK2_CARGO: strcpy ( dest,"Mk2 Cargo Pod" ); break;
		case MK2_JUMP: strcpy ( dest,"Mk2 Jump Drive" ); break;
		case MK3_HULL: strcpy ( dest,"Mk3 Hull Booster" ); break;
		case MK3_SHIELD: strcpy ( dest,"Mk3 Shield Generator" ); break;
		case MK3_CARGO: strcpy ( dest,"Mk3 Cargo Pod" ); break;
		case MK3_JUMP: strcpy ( dest,"Mk3 Jump Drive" ); break;
	}

	return dest;
}

char *file_date(char *foldername, char *filename, char *dest)
{
	time_t curtime;
	struct tm *loctime;
	char buf[200];
	char the_true[200];

	/* Get the current time.  */
	curtime = time (NULL);

	/* Convert it to local time representation.  */
	loctime = localtime (&curtime);

	strftime (buf, 20, "%y-%m-%d_", loctime);

	the_true[0] = 0;
	strcat(the_true,foldername);
	strcat(the_true,buf);
	strcat(the_true,filename);
	strcpy(dest,the_true);

	return dest;
}

void printd(char *message)
{
	FILE *ofp;

	ofp = fopen("debug.txt","a");

	fprintf(ofp, "%s\n", message);

	fclose(ofp);
}

void printd_gen(char *folder, char *gen_filename, char *message)
{
	FILE *ofp;
	struct tm *ptr;
	time_t lt;
	char filename[200];
	char timebuf[200];

	lt = time(NULL);
	ptr = localtime(&lt);

	file_date(folder, gen_filename, filename);

	ofp = fopen(filename,"a");

	strcpy(timebuf, asctime(ptr));
	clean_newline(timebuf, 200);

	fprintf(ofp, "%s :: %s\n", timebuf, message);

	fclose(ofp);
}

void printd_death(char *message)
{
	FILE *ofp;
	struct tm *ptr;
	time_t lt;
	char filename[200];
	char timebuf[200];

	lt = time(NULL);
	ptr = localtime(&lt);

	file_date("logs/", "death.txt", filename);

	ofp = fopen(filename,"a");

	strcpy(timebuf, asctime(ptr));
	clean_newline(timebuf, 200);

	fprintf(ofp, "%s :: %s\n", timebuf, message);

	fclose(ofp);
}

void printd_admin(char *message)
{
	FILE *ofp;

	ofp = fopen("admin_log.txt","a");

	fprintf(ofp, "%s\n", message);

	fclose(ofp);
}

void printd_ds(char *message)
{
	FILE *ofp;
	struct tm *ptr;
	time_t lt;

	lt = time(NULL);
	ptr = localtime(&lt);

	ofp = fopen("ds_log.txt","a");

	fprintf(ofp, "%s ^^:: %s\n", asctime(ptr), message);

	fclose(ofp);
}

double current_time()
{
	static int first_sec = 0;
	static int first_msec = 0;
	struct timeb new_time;

	//set current time
	ftime(&new_time);

	//set if not set
	if(!first_sec)
	{
		first_sec = new_time.time;
		first_msec = new_time.millitm;
	}

	return (new_time.time - first_sec) + ((new_time.millitm - first_msec) * 0.001);
}

char *ship_name(int ship_number, char *dest)
{
	switch (ship_number)
	{
		case 0: strcpy(dest,"Seeker"); break;
		case 1: strcpy(dest,"Fighter"); break;
		case 2: strcpy(dest,"Carrier"); break;
		case 3: strcpy(dest,"Hunter"); break;
		case 4: strcpy(dest,"Freighter"); break;
		case 5: strcpy(dest,"Attacker"); break;
		case 6: strcpy(dest,"Destroyer"); break;
		case 7: strcpy(dest,"Behemoth"); break;
	}

	return dest;
}

int add_will_overflow(int a, int b)
{
    int c;

    if(!a) return 0;
    if(!b) return 0;

    c = a + b;

    //both positive and the result negative?
    if(a > 0 && b > 0 && c < 0) return 1;

    //both negative and the result positive?
    if(a < 0 && b < 0 && c > 0) return 1;

    return 0;

}

int distance ( int x1, int y1, int x2, int y2 )
{
	return ( int ) pow ( (double)(pow ( (double)(x1 - x2),2 ) + pow ( (double)(y1 - y2),2 )),0.5 );
}

double random_chance()
{
	return ( rand() % 10000 ) / 10000.0;
}

double ship_damage_defense ( int s_k, double damage )
{
	switch ( s_k )
	{
		case ATTACKER: return damage * 0.50; // 1.5
		case DESTROYER: return damage * 0.70; // 0.95
		case BEHEMOTH: return damage * 0.80; //0.7
	}

	return damage;
}

double ship_damage_difference ( int s_k, double damage )
{
	switch ( s_k )
	{
		case CARRIER: return damage * 0.80;
		case FREIGHTER: return damage * 0.85;
		case ATTACKER: return damage * 0.90;
		case DESTROYER: return damage * 0.95;
		case BEHEMOTH: return damage * 1;
	}

	return damage;
}

double ship_damage_evasion_boost ( int a_s_k, int v_s_k, double damage )
{
	switch(v_s_k)
	{
	case SEEKER:
		switch(a_s_k)
		{
		case HUNTER:    return damage * 0.9;
		case ATTACKER:  return damage * 0.8;
		case DESTROYER: return damage * 0.6;
		case BEHEMOTH:  return damage * 0.6;
		}
		break;
	case FIGHTER:
		switch(a_s_k)
		{
		case HUNTER:    return damage * 0.95;
		case ATTACKER:  return damage * 0.85;
		case DESTROYER: return damage * 0.65;
		case BEHEMOTH:  return damage * 0.65;
		}
		break;
	case HUNTER:
		switch(a_s_k)
		{
		case ATTACKER:  return damage * 0.8;
		case DESTROYER: return damage * 0.6;
		case BEHEMOTH:  return damage * 0.6;
		}
		break;
    case FREIGHTER:
		switch(a_s_k)
		{
		case ATTACKER:  return damage * 0.7;
		case DESTROYER: return damage * 0.5;
		case BEHEMOTH:  return damage * 0.5;
		}
    case CARRIER:
		switch(a_s_k)
		{
		case ATTACKER:  return damage * 0.7;
        case DESTROYER: return damage * 0.65;
		case BEHEMOTH:  return damage * 0.65;
		}
	}

	return damage;
}

int ship_speed_difference ( int s_k )
{
	switch ( s_k )
	{
		case SEEKER: return -1;
		case CARRIER: return 1;
		case FREIGHTER: return 1; //2
		case ATTACKER: return -2;
		case BEHEMOTH: return -2; //1
	}

	return 0;
}

double ship_total_seconds ( int speed, int s_k )
{
	double seconds;

	if ( speed>26 ) speed = 26;
	if ( speed<0 ) speed = 0;

	seconds = 26 - speed;
	seconds = seconds / 2.0;
	seconds += 8;
	seconds += ship_speed_difference ( s_k );

	return seconds;
}

void clean_newline ( char *message, int size )
{
	int i;

	for ( i=0;i<size;i++ )
	{
		if ( message[i] == '\r' )
		{
			message[i] = 0;
			break;
		}
		else if ( message[i] == '\n' )
		{
			message[i] = 0;
			break;
		}
		else if ( !message[i] )
			break;
	}
}

char *good_name ( int good_number, char *dest )
{
	switch ( good_number )
	{
		case 0: strcpy ( dest,"Tynosine" ); break;
		case 1: strcpy ( dest,"Gryn Stone" ); break;
		case 2: strcpy ( dest,"Cryonite" ); break;
		case 3: strcpy ( dest,"Kengo Weed" ); break;
		case 4: strcpy ( dest,"Paralium" ); break;
		case 5: strcpy ( dest,"Zynine" ); break;
		case 6: strcpy ( dest,"Medical Goods" ); break;
		case 7: strcpy ( dest,"Vensium" ); break;
		case 8: strcpy ( dest,"Gen Synth" ); break;
		case 9: strcpy ( dest,"Gen Elium" ); break;
	}

	return dest;
}

char *good_mini_name ( int good_number, char *dest )
{
	switch ( good_number )
	{
		case 0: strcpy ( dest,"Ts" ); break;
		case 1: strcpy ( dest,"Gs" ); break;
		case 2: strcpy ( dest,"Cn" ); break;
		case 3: strcpy ( dest,"Kw" ); break;
		case 4: strcpy ( dest,"Pa" ); break;
		case 5: strcpy ( dest,"Zy" ); break;
		case 6: strcpy ( dest,"Mg" ); break;
		case 7: strcpy ( dest,"Ve" ); break;
		case 8: strcpy ( dest,"Gs" ); break;
		case 9: strcpy ( dest,"Ge" ); break;
	}

	return dest;
}

char *contra_name ( int contra_number, char *dest )
{
	switch ( contra_number )
	{
		case 0: strcpy ( dest,"Guns" ); break;
		case 1: strcpy ( dest,"Kaos Germ" ); break;
		case 2: strcpy ( dest,"Kytrilium" ); break;
		case 3: strcpy ( dest,"Terraform Capsules" ); break;
		case 4: strcpy ( dest,"Blood Packets" ); break;
		case 5: strcpy ( dest,"Carnivore Pods" ); break;
		case 6: strcpy ( dest,"Red Boosters" ); break;
		case 7: strcpy ( dest,"Oxy Pills" ); break;
		case 8: strcpy ( dest,"Net Infectors" ); break;
		case 9: strcpy ( dest,"Body Parts" ); break;
	}

	return dest;
}

char *good_description ( int good_number, char *dest )
{
	switch ( good_number )
	{
		case 0: strcpy ( dest,"Tynosine is a birefringent, tetragonal, scheelite-type crystal. It does form naturally but is now manufactured to increase availability and quality. Different dopants dramatically change its optical and electrical properties. For this reason it is widely used in circuitry ." ); break;
		case 1: strcpy ( dest,"This mineral is highly radioactive and so is a valuable source of energy. It is used on spacecraft and installations through the galaxy as a core heating system." ); break;
		case 2: strcpy ( dest,"A valuable naturally-occurring oil used as a fuel source. Demand for Cryonite has recently grown greater than its ability for self-recycling, leading to higher prices and environmental concerns." ); break;
		case 3: strcpy ( dest,"Kengo Weed was found to have amazing nutritional properties with its high levels of protein, vitamins and rehydration capacity. It is now harvested and is the known planets' main food resource." ); break;
		case 4: strcpy ( dest,"This is the strongest and most resilient metal on the known planets and so is widely used for manufacturing, especially in ship construction." ); break;
		case 5: strcpy ( dest,"An inert liquid metal, Zynine is mainly used for manufacturing and lubrication. Its beauty means that it is also used as a display of wealth." ); break;
		case 6: strcpy ( dest,"In these war-ridden times medical goods have become a valuable commodity. Hoarding of medicines is frequent, leading to prices fluctuating wildly. A war will always push the price up." ); break;
		case 7: strcpy ( dest,"Archaeological excavations have shown that this stone was used as a form of currency on some planets. It has found new value as a precious metal and is used for jewellry and sculpture." ); break;
		case 8: strcpy ( dest,"Despite ongoing research, it is a poor substitute for Gen Elium, but can still be useful in industry." ); break;
		case 9: strcpy ( dest,"This is the material extracted from the relics by Bai Genko and named after his son and Peleus captain Bai Gen. Research into its properties has lead to improvements of jump drives and shielding. It is not found on any of the known planets, but mining conglomerates are investing heavily in the search for the planet it originated from." ); break;
	}

	return dest;
}

int guild_mode_exp(int mode)
{
	switch(mode)
	{
	case GM_NONE: return 0;
	case GM_50_GREWARDS: return 40;
	case GM_5_DROPS: return 100;
	case GM_5_ATTDEF: return 180;
	case GM_100_GREWARDS: return 300;
	case GM_10_DROPS: return 500;
	case GM_10_ATTDEF: return 700;
	case GM_ULTIMATE: return 2000;
	}

	return 0;
}

char *guild_mode_desc ( int mode, char *dest )
{
	dest[0] = 0;

	switch ( mode )
	{
		case GM_NONE: strcpy(dest, ""); break;
		case GM_50_GREWARDS: strcpy(dest, "+50% Guild Rewards"); break;
		case GM_5_DROPS: strcpy(dest, "+5% Chance of Drops"); break;
		case GM_5_ATTDEF: strcpy(dest, "+5% Damage / Defense vs Bots"); break;
		case GM_100_GREWARDS: strcpy(dest, "+100% Guild Rewards"); break;
		case GM_10_DROPS: strcpy(dest, "+10% Chance of Drops"); break;
		case GM_10_ATTDEF: strcpy(dest, "+10% Damage / Defense vs Bots"); break;
		case GM_ULTIMATE: strcpy(dest, "+12% Damage / Defense vs Bots, +12% Drops"); break;
	}

	return dest;
}

double guild_mode_def(int mode, double damage)
{
	switch(mode)
	{
	case GM_5_ATTDEF: damage *= 0.95; break;
	case GM_10_ATTDEF: damage *= 0.9; break;
	case GM_ULTIMATE: damage *= 0.88; break;
	}

	return damage;
}

double guild_mode_att(int mode, double damage)
{
	switch(mode)
	{
	case GM_5_ATTDEF: damage *= 1.05; break;
	case GM_10_ATTDEF: damage *= 1.1; break;
	case GM_ULTIMATE: damage *= 1.12; break;
	}

	return damage;
}

double guild_mode_drop(int mode)
{
	switch(mode)
	{
	case GM_5_DROPS: return 1.05;
	case GM_10_DROPS: return 1.1;
	case GM_ULTIMATE: return 1.12;
	}

	return 1.0;
}

void make_dir(char *foldername)
{
#ifdef WIN32 //if windows
	mkdir ( foldername );
#else
	mkdir ( foldername,-1 );
#endif
}
