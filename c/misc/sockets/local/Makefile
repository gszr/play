CLIENT := local_client
SERVER := local_server

all: $(CLIENT) $(SERVER)

$(CLIENT):	$(CLIENT).c
	$(CC) -o $@ $<

$(SERVER):	$(SERVER).c
	$(CC) -o $@ $<

clean:
	$(RM) $(CLIENT) $(SERVER)
