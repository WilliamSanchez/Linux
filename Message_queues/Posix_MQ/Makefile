NCLUDE_DIRS = 
LIB_DIRS = 

CDEFS= 
CFLAGS= -O3 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lpthread -lrt

PRODUCT=pmsg_create pmsg_getattr pmsg_unlink pmsg_send pmsg_receive

HFILES=
CFILES= pmsg_create.c pmsg_getattr.c pmsg_unlink.c pmsg_send.c pmsg_receive.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

pmsg_create:	pmsg_create.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmsg_create.o $(LIBS)

pmsg_getattr:	pmsg_getattr.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmsg_getattr.o $(LIBS)

pmsg_unlink:	pmsg_unlink.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmsg_unlink.o $(LIBS)
	
pmsg_send:	pmsg_send.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmsg_send.o $(LIBS)
	
pmsg_receive:	pmsg_receive.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pmsg_receive.o $(LIBS)


depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
