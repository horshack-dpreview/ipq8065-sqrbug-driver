#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=ipq8065-sqrbug-driver
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0
TARGET_CFLAGS+= -Wno-format

include $(INCLUDE_DIR)/package.mk

define KernelPackage/ipq8065-sqrbug-driver
  SUBMENU:=Other modules
  TITLE:=ipq8065-sqrbug-driver
  FILES:=$(PKG_BUILD_DIR)/ipq8065-sqrbug-driver.ko
  AUTOLOAD:=$(call AutoLoad,30,ipq8065-sqrbug-driver,1)
  KCONFIG:=
endef

define KernelPackage/ipq8065-sqrbug-driver/description
 Kernel module to reproduce CPU data load but on my Netgear X4S R7800 router 
endef

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	M="$(PKG_BUILD_DIR)"

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,ipq8065-sqrbug-driver))
