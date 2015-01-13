# There is no GPS in this device
# The gps config appropriate for this device
# $(call inherit-product, device/common/gps/gps_us_supl.mk)

# Does not exist
# $(call inherit-product-if-exists, vendor/aliexpress2/polaris_p1/polaris_p1-vendor.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_mini_tablet_wifionly.mk)

# All languages
$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

LOCAL_PATH := device/aliexpress2/polaris_p1

DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

ifeq ($(TARGET_PREBUILT_KERNEL),)
	LOCAL_KERNEL := $(LOCAL_PATH)/kernel
else
	LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

PRODUCT_COPY_FILES += \
    $(LOCAL_KERNEL):kernel

$(call inherit-product, build/target/product/full_base.mk)

include $(call all-makefiles-under,$(LOCAL_PATH))

# WiFi
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml

PRODUCT_PROPERTY_OVERRIDES += \
	wifi.interface=wlan0 \
	wifi.supplicant_scan_interval=15

# Camera
PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
	frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
	frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml
#	frameworks/native/data/etc/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml

# Gps
PRODUCT_PACKAGES += gps.polaris
BOARD_USES_GPS_TYPE := simulator
PRODUCT_COPY_FILES += frameworks/native/data/etc/android.hardware.location.xml:system/etc/permissions/android.hardware.location.xml

# 3G Data Card Packages
PRODUCT_PACKAGES += \
	u3gmonitor \
	chat \
	rild \
	pppd

	
# Sensors
PRODUCT_PACKAGES += \
   lights.polaris \
   camera.polaris \
   sensors.polaris \
   hwcomposer.polaris \
   libion

PRODUCT_PACKAGES += \
	audio.a2dp.default \
	audio.usb.default \
	audio.primary.polaris \
	audio.r_submix.default

# Looks like chineese shit...

# # preinstall apk
# # PRODUCT_PACKAGES += \
	# flashplayer.apk \
	# DragonFire.apk \
	# DragonPhone.apk \
	# VideoTest.apk

# # softwinner
# PRODUCT_PACKAGES +=  \
   # android.softwinner.framework.jar \
   # SoftWinnerService.apk \
   # backup/SoftWinnerService.apk \
   # libsoftwinner_servers.so \
   # libupdatesoftwinner.so \
   # updatesoftwinner
	
# #install apk to system/app
# PRODUCT_PACKAGES +=  \
   # Update \
   # Google_maps \
   # FileExplore \
   # libjni_mosaic \
   # libjni_eglfence \
   # com.android.future.usb.accessory

   # #com.google.android.inputmethod.pinyin_403232 \
   # #4KPlayer \
   # #AWGallery \
   # #BDVideoHD \
# #install apk's lib to system/lib
# PRODUCT_PACKAGES +=  \
   # libjni_googlepinyinime_latinime_5.so \
   # libjni_googlepinyinime_5.so \
   # libjni_delight.so \
   # libjni_hmm_shared_engine.so \
   # libgnustl_shared.so \
   # libcyberplayer.so \
   # libffmpeg.so \
   # libgetcpuspec.so \
   # libp2p-jni.so \
   # libstlport_shared.so

	
	
# ext4 filesystem utils
PRODUCT_PACKAGES += \
	e2fsck \
	libext2fs \
	libext2_blkid \
	libext2_uuid \
	libext2_profile \
	libext2_com_err \
	libext2_e2p \
	make_ext4fs

# Libraries
PRODUCT_PACKAGES += \
	libcedarxbase \
	libcedarxosal \
	libcedarv \
	libcedarv_base \
	libcedarv_adapter \
	libve \
	libaw_audio \
	libaw_audioa \
	libswdrm \
	libstagefright_soft_cedar_h264dec \
	libfacedetection \
	libthirdpartstream \
	libcedarxsftstream \
	libsunxi_alloc \
	libsrec_jni \
	libjpgenc \
	libstagefrighthw \
	libOmxCore \
	libOmxVdec \
	libOmxVenc \
	libaw_h264enc \
	libI420colorconvert \
	libion_alloc
	
# include $(LOCAL_PATH)/prebuild/google/products/gms.mk
# include $(LOCAL_PATH)/prebuild/tools/tools.mk

# System Configuration
PRODUCT_PROPERTY_OVERRIDES += \
	persist.sys.timezone=Europe/Warsaw \
	persist.sys.language=pl \
	persist.sys.country=PL

PRODUCT_PROPERTY_OVERRIDES += \
	persist.sys.usb.config=mass_storage,adb \
	ro.udisk.lable=Polaris \
	ro.font.scale=1.0 \
	ro.hwa.force=true \
	rw.logger=0 \
	ro.sys.bootfast=true\
	ro.mem.opt=true \
	ro.sf.lcd_density=160 \
	ro.product.firmware=v1.0 \
	ro.kernel.android.checkjni=0 \
	ro.opengles.version=131072 \
	persist.sys.strictmode.visual=0 \
	persist.sys.strictmode.disable=1 \
	ro.reversion.aw_sdk_tag=C \
	ro.sys.cputype=DualCore-A23 \
	keyguard.no_require_sim=true \
	persist.demo.hdmirotationlock=0

PRODUCT_TAGS += dalvik.gc.type-precise
# Copy required files to ramdisk
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/disp.ko:disp.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/sunxi-keyboard.ko:sunxi-keyboard.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/lcd.ko:lcd.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/gt82x.ko:gt82x.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/ft5x_ts.ko:ft5x_ts.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/gt9xx_ts.ko:gt9xx_ts.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/gslX680.ko:gslX680.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/gslX680new.ko:gslX680new.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/gt818_ts.ko:gt818_ts.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/gt9xxf_ts.ko:gt9xxf_ts.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/aw5306_ts.ko:aw5306_ts.ko \
    $(LOCAL_PATH)/_prebuilt/system/vendor/modules/sw-device.ko:sw-device.ko

# Copy all files from prebuilts
$(shell $(LOCAL_PATH)/create_prebuilt_files_mk.sh > $(LOCAL_PATH)/PrebuiltFiles.mk)
include $(LOCAL_PATH)/PrebuiltFiles.mk

# Copy files extracted from prebuilts
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/recovery.fstab:recovery.fstab \
	$(LOCAL_PATH)/system.prop:system.prop

# APP CONFIGS
PRODUCT_CHARACTERISTICS := tablet
PRODUCT_AAPT_CONFIG := ldpi mdpi hdpi
PRODUCT_AAPT_PREF_CONFIG := mdpi

# Build
PRODUCT_BUILD_PROP_OVERRIDES += BUILD_UTC_DATE=0
PRODUCT_DEVICE := polaris_p1
PRODUCT_NAME := cm_polaris_p1
PRODUCT_BRAND := aliexpress2
PRODUCT_MODEL := polaris_p1
PRODUCT_MANUFACTURER := aliexpress2
PRODUCT_RELEASE_NAME := polaris_p1

BUILD_NUMBER := $(shell date +%Y%m%d)
BUILD_FINGERPRINT := $BUILD_NUMBER
