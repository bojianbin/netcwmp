PKG_SUBDIRS +=libpool
PKG_SUBDIRS +=libxmlet
PKG_SUBDIRS +=libcwmp
PKG_SUBDIRS +=cwmpd

include default.mk

extra_all:
extra_clean:
	@rm -rf build