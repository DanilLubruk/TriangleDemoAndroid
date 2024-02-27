package com.example.nativetrianglehelper

class NativeTriangleHelper {
    external fun drawTriangle(rotationAngle: Float)

    companion object {
        init {
            System.loadLibrary("triangle-native-library")
        }
    }
}