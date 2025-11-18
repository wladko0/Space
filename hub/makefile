pdiaspora:
	g++ -g -o hubserver main.c sock.c database.c database_common.c database_mysql.c database_auto.c common.c protocal.c admin.c user.c server.c memory.c -lmysqlclient

zip:
	zip pdiaspora_hub_src *.c *.h makefile

send:
	cp -f pdiaspora_hub.zip /mnt/removable

zip_database:
	zip -r pdiaspora_hub_databases *.db server