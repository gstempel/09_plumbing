server client: pipe_networking.c server.c client.c
	gcc -o server server.c pipe_networking.c
	gcc -o client client.c pipe_networking.c

clean:
	rm *~