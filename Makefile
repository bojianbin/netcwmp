PKG_SUBDIRS +=libpool
PKG_SUBDIRS +=libxmlet
PKG_SUBDIRS +=libcwmp
PKG_SUBDIRS +=libcJSON
PKG_SUBDIRS +=libnetool

PKG_SUBDIRS +=cwmpd
PKG_SUBDIRS +=test_http


include default.mk

extra_all:

extra_clean:
	@rm -rf build
	
install:
	cp -rf conf/cwmp.conf /etc/
	cp -rf conf/device.xml /etc/
	cp -rf build/bin/* /usr/local/bin/