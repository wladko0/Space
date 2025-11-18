#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <math.h>

#ifdef _WIN32 //if windows
	#include <windows.h>		//win for Sleep(1000)
	#include <direct.h>
#else
	#include <unistd.h>
	#include <sys/stat.h>
#endif

//prototypes
extern void split(char *dest, char *message, char char_spliter, int *initial);
extern int str_match(char *str1, char *str2);
extern int str_match_lcase(char *str1, char *str2);
extern void lcase(char *dest, char *src);
extern void left ( char *dest, char *src, int point );
extern void right(char *dest, char *src, int point);
extern int misc_pod_value(int misc_pod_number);
extern int misc_pod_exp(int misc_pod_number);
extern int misc_pod_cost(int misc_pod_number);
extern char *misc_pod_name ( int misc_pod_number, char *dest );
extern int guild_mode_exp(int mode);
extern char *guild_mode_desc ( int mode, char *dest );
extern double guild_mode_def(int mode, double damage);
extern double guild_mode_att(int mode, double damage);
extern double guild_mode_drop(int mode);
extern void uni_pause(int m_sec);
extern char *file_date(char *foldername, char *filename, char *dest);
extern void printd(char *message);
extern void printd_gen(char *folder, char *filename, char *message);
extern void printd_death(char *message);
extern void printd_admin(char *message);
extern void printd_ds(char *message);
extern double current_time();
extern char *ship_name(int ship_number, char *dest);
extern int add_will_overflow(int a, int b);
extern char *good_name ( int good_number, char *dest );
extern char *good_mini_name ( int good_number, char *dest );
extern char *contra_name ( int contra_number, char *dest );
extern char *good_description ( int good_number, char *dest );
extern int distance ( int x1, int y1, int x2, int y2 );
extern double random_chance();
extern double ship_damage_defense ( int s_k, double damage );
extern double ship_damage_difference ( int s_k, double damage );
extern double ship_damage_evasion_boost ( int a_s_k, int v_s_k, double damage );
extern double ship_total_seconds ( int speed, int s_k );
extern void clean_newline ( char *message, int size );
extern void make_dir(char *foldername);
extern void encrypt_login(std::string &name, std::string &pass);

#endif
