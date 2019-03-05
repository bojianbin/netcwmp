_TOPDIR:=$(word 1, $(subst /libpool, ,$(shell pwd)))
TOP_DIR:=${_TOPDIR}
include $(TOP_DIR)/rules.mk

OBJ_s = $(patsubst %.c,%.o,$(wildcard ./src/*.c))
FILTER_OUT = 
pool_OBJ = $(filter-out $(FILTER_OUT),$(OBJ_s))
pool_STATIC = libpool.a
pool_SHARED = libpool.so
LDFLAGS += 
#test_LDFLAGS += -L. -l:libeventbase.a
CFLAGS += -fPIC -I./include


all:shared static install

shared:$(pool_SHARED) 
static:$(pool_STATIC) 


%.o:%.c
	@$(TARGET_CC) -o $@ -c $<  $(CFLAGS)

#static libraries
$(pool_STATIC): $(pool_OBJ)
	@$(TARGET_AR) rcs $@ $(pool_OBJ)

#shared libraries 
$(pool_SHARED): $(pool_OBJ)
	@$(TARGET_CC) -shared -o $@ $(pool_OBJ) $(LDFLAGS) $(CFLAGS)


install:
	@$(INSTALL_DIR) $(TOP_DIR)/build/lib
	@$(INSTALL_DIR) $(TOP_DIR)/build/include/cwmp
	@$(CP) $(pool_STATIC) $(TOP_DIR)/build/lib
	@$(CP) $(pool_SHARED) $(TOP_DIR)/build/lib
	@$(CP) include/cwmp/*.h $(TOP_DIR)/build/include/cwmp/
	@$(call MESSAGE,"Finished!", "libpool")

clean:
	@rm -rf src/*.o  $(pool_STATIC) $(pool_SHARED) 
	@$(call MESSAGE,"Clean!", "libpool")

