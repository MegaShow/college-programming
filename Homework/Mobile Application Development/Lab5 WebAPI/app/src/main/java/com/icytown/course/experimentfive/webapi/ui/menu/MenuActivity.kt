package com.icytown.course.experimentfive.webapi.ui.menu

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.databinding.MenuActivityBinding

class MenuActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val binding = DataBindingUtil.setContentView<MenuActivityBinding>(this, R.layout.menu_activity)
        binding.handler = MenuHandler(this, binding)
    }
}
