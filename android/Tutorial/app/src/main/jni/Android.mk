LOCAL_PATH_ROOT := $(call my-dir)
include $(CLEAR_VARS)

include $(LOCAL_PATH_ROOT)/SDL2/Android.mk
include $(LOCAL_PATH_ROOT)/smpeg/Android.mk
include $(LOCAL_PATH_ROOT)/libmikmod/Android.mk
include $(LOCAL_PATH_ROOT)/SDL2_mixer/Android.mk
include $(LOCAL_PATH_ROOT)/libwebp/Android.mk
include $(LOCAL_PATH_ROOT)/SDL2_image/Android.mk
include $(LOCAL_PATH_ROOT)/SDL2_ttf/Android.mk
include $(LOCAL_PATH_ROOT)/src/Android.mk
