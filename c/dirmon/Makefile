DIR_MONIT	:= dir_monit
DIR_SYNC	:= dir_sync

CFLAGS		:= -Wall -Wextra
CC		:= gcc $(CFLAGS)

all: $(DIR_MONIT) $(DIR_SYNC)

$(DIR_MONIT):	$(DIR_MONIT).c
		$(CC) -o $@ $<

$(DIR_SYNC):	$(DIR_SYNC).c
		$(CC) -o $@ $<

clean:
	$(RM) $(DIR_MONIT) $(DIR_SYNC)
