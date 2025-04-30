all: compile remove-object-files

compile: args.o parser.o ip_info.o main.o
	gcc -o build/ipinfo args.o parser.o ip_info.o main.o

main.o:
	gcc -c src/main.c

args.o:
	gcc -c src/args.c

parser.o:
	gcc -c src/parser.c

ip_info.o:
	gcc -c src/ip_info.c

remove-object-files:
	rm *.o

clean:
	rm -r ./build *.o
