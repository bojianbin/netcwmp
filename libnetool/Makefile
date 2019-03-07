_TOPDIR:=$(word 1, $(subst /libnetool, ,$(shell pwd)))
TOP_DIR:=${_TOPDIR}

include $(TOP_DIR)/rules.mk

TARGET = libnetool.a
BUILD_DIR = $(TOP_DIR)/build

OBJ = $(patsubst %.c,%.o,$(wildcard ./*.c))

%.o:%.c
	@$(TARGET_CC) -o $@ -c $<   $(DEFS)
	
all:$(OBJ)
	@$(TARGET_AR) rcs $(TARGET) $(OBJ)
	@$(INSTALL_DIR) $(BUILD_DIR)/include
	@$(INSTALL_DIR) $(BUILD_DIR)/lib
	@$(CP)  $(TARGET) $(BUILD_DIR)/lib
	@$(CP) anet.h $(BUILD_DIR)/include
	@$(CP) netTool.h $(BUILD_DIR)/include

	
clean:
	@rm -rf *.o $(TARGET)
