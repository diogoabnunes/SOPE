all: examples p07

examples: ackerman.c pi_montecarlo.c hello.c
	gcc -Wall -o ackerman ackerman.c
	gcc -Wall -o pi_montecarlo pi_montecarlo.c
	gcc -Wall -o hello hello.c

p07: p07.c
	gcc -Wall -o p07 p07.c

clean:
	rm ex07 ackerman pi_montecarlo hello