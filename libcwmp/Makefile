_TOPDIR:=$(word 1, $(subst /libcwmp, ,$(shell pwd)))
TOP_DIR:=${_TOPDIR}
include $(TOP_DIR)/rules.mk

OBJ_s = $(patsubst %.c,%.o,$(wildcard ./src/*.c))
FILTER_OUT = 
libcwmp_OBJ = $(filter-out $(FILTER_OUT),$(OBJ_s))
libcwmp_STATIC = libcwmp.a
libcwmp_SHARED = libcwmp.so
LDFLAGS += -l:libpool.a -l:libxmlet.a

ifeq ($(findstring DUSE_CWMP_OPENSSL,DEFS),DUSE_CWMP_OPENSSL)
LDFLAGS += -lssl
endif

CFLAGS += -fPIC -I./include $(DEFS)


all:shared static install

shared:$(libcwmp_SHARED) 
static:$(libcwmp_STATIC) 


%.o:%.c
	@$(TARGET_CC) -o $@ -c $<  $(CFLAGS)

#static libraries
$(libcwmp_STATIC): $(libcwmp_OBJ)
	@$(TARGET_AR) rcs $@ $(libcwmp_OBJ)

#shared libraries 
$(libcwmp_SHARED): $(libcwmp_OBJ)
	@$(TARGET_CC) -shared -o $@ $(libcwmp_OBJ) $(LDFLAGS) $(CFLAGS)


install:
	@$(INSTALL_DIR) $(TOP_DIR)/build/lib
	@$(INSTALL_DIR) $(TOP_DIR)/build/include/cwmp
	@$(CP) $(libcwmp_STATIC) $(TOP_DIR)/build/lib
	@$(CP) $(libcwmp_SHARED) $(TOP_DIR)/build/lib
	@$(CP) include/cwmp/* $(TOP_DIR)/build/include/cwmp/
	@$(call MESSAGE,"Finished!", "libcwmp")

clean:
	@rm -rf src/*.o  $(libcwmp_STATIC) $(libcwmp_SHARED) 
	@$(call MESSAGE,"Clean!", "libcwmp")

