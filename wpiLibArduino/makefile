LIB_DIR=/cygdrive/d/Documents/Arduino/libraries
LIB_NAME=WpiLib-Arduino

all: clean project

clean:
	rm -r $(LIB_DIR)/$(LIB_NAME)

project: *.h *.cpp library.properties
	mkdir $(LIB_DIR)/$(LIB_NAME)
	cp *.h *.cpp library.properties $(LIB_DIR)/$(LIB_NAME)
	cp -r adafruit $(LIB_DIR)/$(LIB_NAME)
