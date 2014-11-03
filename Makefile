CC=gcc
FILES=tema26.c
TARGET=gene
build:$(FILES)
	$(CC) -o $(TARGET) $(FILES)
clean:
	rm -f $(TARGET)
