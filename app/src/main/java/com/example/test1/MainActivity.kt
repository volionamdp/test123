package com.example.test1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.test1.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        // Example of a call to a native method
    }

    /**
     * A native method that is implemented by the 'test1' native library,
     * which is packaged with this application.
     */

    companion object {
        // Used to load the 'test1' library on application startup.
        init {
            System.loadLibrary("native-render")
        }
    }
}