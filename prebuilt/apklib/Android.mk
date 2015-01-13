# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := eng optional
LOCAL_PREBUILT_LIBS := libcheckfile.so 
include $(BUILD_MULTI_PREBUILT)

#########################
#######google pinyin#####
#########################

include $(CLEAR_VARS)
LOCAL_MODULE := libjni_googlepinyinime_5.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libjni_googlepinyinime_latinime_5.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libjni_delight.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libjni_hmm_shared_engine.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libgnustl_shared.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#########################
#######BDVideoHD#########
#########################
include $(CLEAR_VARS)
LOCAL_MODULE := libAudiofe_V1.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libcyberplayer.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libffmpeg.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libgetcpuspec.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libp2p-jni.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

#######################

include $(CLEAR_VARS)
LOCAL_MODULE := libstlport_shared.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := lib
include $(BUILD_PREBUILT)

