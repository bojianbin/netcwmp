_TOPDIR:=$(word 1, $(subst /libxmlet, ,$(shell pwd)))
TOP_DIR:=${_TOPDIR}
include $(TOP_DIR)/rules.mk

OBJ_s = $(patsubst %.c,%.o,$(wildcard ./src/*.c))
FILTER_OUT = 
libxmlet_OBJ = $(filter-out $(FILTER_OUT),$(OBJ_s))
libxmlet_STATIC = libxmlet.a
libxmlet_SHARED = libxmlet.so
LDFLAGS += -l:libpool.a
#test_LDFLAGS += -L. -l:libeventbase.a
CFLAGS += -fPIC -I./include -Isrc/inc $(DEFS)


all:shared static install

shared:$(libxmlet_SHARED) 
static:$(libxmlet_STATIC) 


%.o:%.c
	@$(TARGET_CC) -o $@ -c $<  $(CFLAGS)

#static libraries
$(libxmlet_STATIC): $(libxmlet_OBJ)
	@$(TARGET_AR) rcs $@ $(libxmlet_OBJ)

#shared libraries 
$(libxmlet_SHARED): $(libxmlet_OBJ)
	@$(TARGET_CC) -shared -o $@ $(libxmlet_OBJ) $(LDFLAGS) $(CFLAGS)


install:
	@$(INSTALL_DIR) $(TOP_DIR)/build/lib
	@$(INSTALL_DIR) $(TOP_DIR)/build/include/cwmp
	@$(CP) $(libxmlet_STATIC) $(TOP_DIR)/build/lib
	@$(CP) $(libxmlet_SHARED) $(TOP_DIR)/build/lib
	@$(CP) include/cwmp/*.h $(TOP_DIR)/build/include/cwmp/
	@$(call MESSAGE,"Finished!", "libxmlet")

clean:
	@rm -rf src/*.o  $(libxmlet_STATIC) $(libxmlet_SHARED)
	@$(call MESSAGE,"Clean!", "libxmlet")