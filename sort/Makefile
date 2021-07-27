
TARGET=test.bin

SOURCE=$(wildcard *.c)
OBJS=$(addsuffix .o, $(basename $(SOURCE)))


$(TARGET):$(OBJS)
	gcc -o $@ $^

%.o:%.c
	gcc -g -o $@ -c $<

.PHONY:clean
clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)
