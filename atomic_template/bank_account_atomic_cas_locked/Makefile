
all:
	clang++ main.cpp -pthread -latomic -o main

test:
	clang++ main.cpp -pthread -latomic -fsanitize=thread -o main


clean:
	rm -f *~ main 
