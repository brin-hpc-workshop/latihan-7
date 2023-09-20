CC = mpicc
CFLAGS = 

hello_world: hello_world.c
	$(CC) $(CFLAGS) -o $@ $<

komunikasi_sederhana: komunikasi_sederhana.c
	$(CC) $(CFLAGS) -o $@ $<

komunikasi_bermasalah: komunikasi_bermasalah.c
	$(CC) $(CFLAGS) -o $@ $<

komunikasi_masal: komunikasi_masal.c
	$(CC) $(CFLAGS) -o $@ $<

all: hello_world komunikasi_sederhana komunikasi_bermasalah komunikasi_masal

clean:
	rm -f hello_world
	rm -f komunikasi_sederhana
	rm -f komunikasi_bermasalah
	rm -f komunikasi_masal