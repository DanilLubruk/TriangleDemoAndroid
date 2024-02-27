package com.example.nativetriangledemo.opengl

import android.content.Context
import android.opengl.GLES30
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import com.example.nativetrianglehelper.NativeTriangleHelper
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class TriangleDemoGLSurfaceView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null
) : GLSurfaceView(context, attrs), GLSurfaceView.Renderer {
    private var rotationAngle: Float = 0f

    fun updateRotation(rotationAngle: Float) {
        this.rotationAngle = rotationAngle
        requestRender()
    }

    init {
        // Create an OpenGL ES 3.0 context
        setEGLContextClientVersion(3)
        setRenderer(this)
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        // Set the background color of the renderer
        GLES30.glClearColor(1.0f, 1.0f, 1.0f, 1.0f)
    }

    override fun onDrawFrame(gl: GL10?) {
        // Clear the color buffer
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT)
        NativeTriangleHelper().drawTriangle(rotationAngle)
        //NativeTriangleHelper.drawTriangle(rotationAngle = rotationAngle)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        // Adjust the viewport based on the screen resolution
        //GLES30.glViewport(0, 0, width, height)
    }
}