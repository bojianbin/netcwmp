_TOPDIR:=$(word 1, $(subst /cwmpd, ,$(shell pwd)))
TOP_DIR:=${_TOPDIR}

include ${TOP_DIR}/rules.mk

TARGET = cwmpd

FILTER_OUT = 
OBJ_s = $(patsubst %.c,%.o,$(wildcard src/*.c))
OBJ_s += $(patsubst %.c,%.o,$(wildcard src/modules/*.c))
CFLAGS += -Iinclude/ -Isrc/modules $(DEFS)
LDFLAGS +=  -l:libpool.a -l:libxmlet.a -l:libcwmp.a -l:libcjson.a -lpthread
ifeq ($(findstring USE_CWMP_OPENSSL,$(DEFS)),USE_CWMP_OPENSSL)
LDFLAGS += -lssl -lcrypto
endif
OBJ=$(filter-out $(FILTER_OUT),$(OBJ_s))



all:target install

%.o:%.c
	@$(TARGET_CC) -o $@ -c $<  $(CFLAGS) 
	
target:$(OBJ)
	@$(TARGET_CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LDFLAGS)
	


install:
	@$(INSTALL_DIR) $(TOP_DIR)/build/bin
	@$(CP) $(TARGET) $(TOP_DIR)/build/bin
	@$(call MESSAGE,"Finished!", $(TARGET))
	
clean:
	@rm -rf src/*.o src/modules/*.o $(TARGET) 
	@$(call MESSAGE,"Clean!", $(TARGET))

