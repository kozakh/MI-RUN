CC=g++
CFLAGS=-Wall -pedantic
DEPS = common.h CONSTANT_Type.h constant_type_info.h constant_type_info_parser.h 
OBJ = classFileParser.o common.o constant_type_info_parser.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cfp: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o cfp


