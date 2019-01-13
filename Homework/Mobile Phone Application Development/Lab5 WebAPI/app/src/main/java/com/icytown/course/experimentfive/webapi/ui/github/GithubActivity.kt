package com.icytown.course.experimentfive.webapi.ui.github

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.databinding.GithubActivityBinding

class GithubActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val binding = DataBindingUtil.setContentView<GithubActivityBinding>(this, R.layout.github_activity)
        binding.handler = GithubHandler(this, binding)
    }

    companion object {
        fun startActivity(activity: AppCompatActivity) {
            val intent = Intent(activity, GithubActivity::class.java)
            activity.startActivity(intent)
        }
    }
}
