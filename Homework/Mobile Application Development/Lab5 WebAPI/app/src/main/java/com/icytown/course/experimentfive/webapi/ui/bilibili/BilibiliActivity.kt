package com.icytown.course.experimentfive.webapi.ui.bilibili

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.databinding.BilibiliActivityBinding

class BilibiliActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val binding = DataBindingUtil.setContentView<BilibiliActivityBinding>(this, R.layout.bilibili_activity)
        binding.handler = BilibiliHandler(this, binding)
    }

    companion object {
        fun startActivity(activity: AppCompatActivity) {
            val intent = Intent(activity, BilibiliActivity::class.java)
            activity.startActivity(intent)
        }
    }
}
