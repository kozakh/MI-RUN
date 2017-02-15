CC=g++
CFLAGS=-Wall -pedantic -g -O0
DEPS = attribute_info_parser.h common.h constant_type_info_parser.h field_info_parser.h method_info_parser.h types.h 
OBJ = attribute_info_parser.o classFileParser.o common.o constant_type_info_parser.o field_info_parser.o method_info_parser.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cfp: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o cfp
