LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image SDL2_ttf
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
LOCAL_CPPFLAGS := -std=c++11 -fexceptions

TINTO_SRC :=    \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/anim/*.cpp)) \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/audio/*.cpp)) \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/easing/*.cpp)) \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/engine/*.cpp)) \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/graphics/*.cpp)) \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/scenes/*.cpp)) \
                $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/utils/*.cpp))

LOCAL_SRC_FILES :=  \
                    $(TINTO_SRC) \
                    SDL_android_main.c \
                    main.cpp

include $(BUILD_SHARED_LIBRARY)