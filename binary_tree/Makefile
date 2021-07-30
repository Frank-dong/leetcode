
TARGET=test.bin

SOURCE=$(wildcard *.c)
OBJ=$(addsuffix .o, $(basename $(SOURCE)))

$(TARGET):$(OBJ)
	gcc -o $@ $^

%o:%.c
	gcc -o $@ -c $< 

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf $(OBJ)
