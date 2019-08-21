all:	application

INCLUDE=/usr/include/gdbm
LIBS= -lgdbm_compat
#On some distributions you may need to change the above line to include
#the compatability library, as shown below.
#LIBS= -lgdbm_compat -lgdbm
CFLAGS=
app_ui.o: app_ui.c cd_data.h
	gcc $(CFLAGS) $(LIBS) -g -c app_ui.c

access.o: access.c cd_data.h
	gcc $(CFLAGS) $(LIBS) -g -c access.c

application: app_ui.o access.o
	gcc $(CFLAGS) -g -o application app_ui.o access.o $(LIBS)

clean:
	rm -f application *.o

nodbmfiles:
	rm -f *.dir *.pag
