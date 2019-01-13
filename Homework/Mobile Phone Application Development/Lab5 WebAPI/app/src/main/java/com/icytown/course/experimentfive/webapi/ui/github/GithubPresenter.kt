package com.icytown.course.experimentfive.webapi.ui.github

import android.content.Context
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.icytown.course.experimentfive.webapi.data.model.Repository
import com.icytown.course.experimentfive.webapi.ui.issue.IssueActivity

object GithubPresenter {

    fun onClick(context: Context, owner: String, repository: Repository) {
        val activity = context as AppCompatActivity
        if (repository.openIssue) {
            IssueActivity.startActivity(activity, owner, repository.name)
        } else {
            Toast.makeText(activity, "该仓库禁止提交ISSUE", Toast.LENGTH_SHORT).show()
        }
    }
}
