#include "main.h"

void read_host_info()
{
	FILE *ifp; //declare file pointer, its just how this stuff works
	char cur_line[1024] = "", temp_str[3][21];
	int i = 0; //use this as the length of the line read

	ifp = fopen("rizla.txt","r");  //read server ip from external txt file

	if (!ifp) //if txt file doesn't exist, connect to the IP below
	{
		strcpy(game.hub_address,"localhost"); //playddox.ddns.net
	}
}

void read_config_info()
{
	FILE *ifp; //declare file pointer, its just how this stuff works
	char cur_line[1024] = "", temp_str[3][21];
	int i = 0; //use this as the length of the line read

	ifp = fopen("config.txt","r");  //setup this declared file to open user.db to read from

	if (!ifp) //if the file doesnt exist, then create it. and setup standard locations
	{
		game.sound_on = 1;
		game.engine_on = 0;

		return;
	}

	fscanf(ifp,"%d %d", &(game.sound_on), &(game.engine_on));

	fclose(ifp);
}

void write_config_info()
{
	FILE *ofp;

	ofp = fopen("config.txt","w");

	fprintf(ofp, "%d %d", game.sound_on, game.engine_on);

	fclose(ofp);
}
