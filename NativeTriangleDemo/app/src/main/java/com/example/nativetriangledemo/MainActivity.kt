package com.example.nativetriangledemo

import android.os.Bundle
import android.widget.FrameLayout
import android.widget.SeekBar
import android.widget.TextView
import androidx.activity.ComponentActivity
import com.example.nativetriangledemo.opengl.TriangleDemoGLSurfaceView

class MainActivity : ComponentActivity() {
    private lateinit var surfaceView: TriangleDemoGLSurfaceView
    private lateinit var seekBar: SeekBar
    private lateinit var angleTextView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        surfaceView = TriangleDemoGLSurfaceView(context = this)
        seekBar = findViewById(R.id.seekBar)
        angleTextView = findViewById(R.id.angleTextView)

        val container: FrameLayout = findViewById(R.id.container)
        container.addView(surfaceView)
        val resources = resources
        val angleString = resources.getString(R.string.rotation_angle_caption)

        angleTextView.text = String.format(angleString, 0);

        seekBar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                surfaceView.updateRotation(progress.toFloat())
                angleTextView.text = String.format(angleString, progress.toString());
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {
            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {
            }
        })
    }
}