CC=g++
CFLAGS=-Wall -g -O0
DEPS = constantpool.h frame.h heap.h instruction.h variable.h 
OBJ = constantpool.o frame.o heap.o instruction.o main.o variable.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

runtime: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o runtime

run: runtime
	./runtime
