ifeq ($(SW_MODEM_PRODUCT),yuga_cwm600)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	yugarilplugin.c\
    ygatpipe.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils libutils  libbinder libhardware

LOCAL_CFLAGS := -D_GNU_SOURCE
LOCAL_C_INCLUDES := \
        $(KERNEL_HEADERS)\
	$(LOCAL_PATH)/include \
	hardware/audio \
	hardware/modem/audio_ril

LOCAL_PRELINK_MODULE := false

ifeq ($(TARGET_DEVICE),sooner)
  LOCAL_CFLAGS += -DOMAP_CSMI_POWER_CONTROL -DUSE_TI_COMMANDS
endif
ifeq ($(TARGET_DEVICE),surf)
  LOCAL_CFLAGS += -DPOLL_CALL_STATE -DUSE_QMI
endif
ifeq ($(TARGET_DEVICE),dream)
  LOCAL_CFLAGS += -DPOLL_CALL_STATE -DUSE_QMI
endif
LOCAL_LDLIBS += -lpthread
LOCAL_CFLAGS += -DRIL_SHLIB
LOCAL_MODULE:= libygplugin
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

endif
