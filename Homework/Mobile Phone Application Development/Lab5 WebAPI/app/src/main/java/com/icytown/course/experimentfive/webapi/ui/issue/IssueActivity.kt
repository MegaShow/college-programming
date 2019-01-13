package com.icytown.course.experimentfive.webapi.ui.issue

import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.databinding.IssueActivityBinding

class IssueActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val binding = DataBindingUtil.setContentView<IssueActivityBinding>(this, R.layout.issue_activity)
        binding.handler = IssueHandler(this, binding, getOwner(), getRepoName())
    }

    private fun getOwner(): String {
        return intent.getStringExtra("owner")
    }

    private fun getRepoName(): String {
        return intent.getStringExtra("repoName")
    }

    companion object {
        fun startActivity(activity: AppCompatActivity, owner: String, repoName: String) {
            val intent = Intent(activity, IssueActivity::class.java)
            intent.putExtra("owner", owner)
            intent.putExtra("repoName", repoName)
            activity.startActivity(intent)
        }
    }
}