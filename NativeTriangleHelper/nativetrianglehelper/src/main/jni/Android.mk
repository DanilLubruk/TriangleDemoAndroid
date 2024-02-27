LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_PLATFORM := android-32
LOCAL_MODULE := triangle-native-library
LOCAL_SRC_FILES := Triangle.cpp
LOCAL_LDLIBS := -lGLESv3
include $(BUILD_SHARED_LIBRARY)