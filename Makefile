TARGET=libwritedoc.so
OBJ_PATH=objs
PREFIX_BIN=install 

CC=g++
INCLUDES=-Iinclude -Isrc -Ithrift -Igen-cpp
LIBS=-L/home/yqpt2/lib -L lib
CFLAGS=-Wall -Werror -g -fpic -DHAVE_NETINET_IN_H -DHAVE_INTTYPES_H
LINKS=-lcachetube -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -lboost_system -lzookeeper_mt
SRCDIR=src/json src src/util gen-cpp src/utils
CPP_SRCDIR=$(SRCDIR)
CPP_SOURCES=$(foreach d,$(CPP_SRCDIR),$(wildcard $(d)/*.cpp))
CPP_OBJS=$(patsubst %.cpp,$(OBJ_PATH)/%.o,$(CPP_SOURCES))

default:init compile 
init:	
	$(foreach d,$(SRCDIR), mkdir -p $(OBJ_PATH)/$(d))
compile:$(CPP_OBJS)	
	$(CC)	$^   -shared -o $(TARGET)  $(LIBS) $(LINKS)	
	cp $(TARGET) ~/lib
	cp $(TARGET) lib
	strip libwritedoc.so
	tar czvf libwritedoc.tar.gz libwritedoc.so
	
	
$(CPP_OBJS):$(OBJ_PATH)/%.o:%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
rebuild: clean compile
install:$(TARGET)
	cp $(TARGET) $(PREFIX_BIN)
	cp example.cpp $(PREFIX_BIN)
	cp src/WriteDoc.h $(PREFIX_BIN)
	cp client.conf $(PREFIX_BIN)
	tar czvf $(PREFIX_BIN).tar.gz $(PREFIX_BIN)
uninstall:
	rm -f $(PREFIX_BIN)/$(TARGET)
clean:
	rm -rf $(OBJ_PATH)
	rm -f $(TARGET)
test:
	@echo CPP_OBJS $(CPP_OBJS)
	@echo CPP_SOURCES $(CPP_SOURCES)
	@echo $(SRCDIR)
example: a/example.cpp $(TARGET)
	g++ -o example a/example.cpp $(INCLUDES) -L ~/lib  -lwritedoc  
#st is stresstest for short
st: test.cpp $(TARGET)
	g++ -g -o st test.cpp $(INCLUDES) $(LIBS) -lwritedoc
mit:mit.cpp
	g++ -g -o mit mit.cpp $(INCLUDES) $(LIBS) -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options -lboost_system
