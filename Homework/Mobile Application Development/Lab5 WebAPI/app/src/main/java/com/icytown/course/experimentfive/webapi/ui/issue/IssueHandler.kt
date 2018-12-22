package com.icytown.course.experimentfive.webapi.ui.issue

import android.annotation.SuppressLint
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import com.icytown.course.experimentfive.webapi.data.model.CreateIssueRequestBody
import com.icytown.course.experimentfive.webapi.data.service.GithubApiService
import com.icytown.course.experimentfive.webapi.databinding.IssueActivityBinding
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.rxkotlin.subscribeBy
import timber.log.Timber

class IssueHandler(val activity: IssueActivity, val binding: IssueActivityBinding, val owner: String, val repoName: String) {

    private val adapter = RecyclerViewAdapter()

    init {
        binding.recyclerView.layoutManager = LinearLayoutManager(activity)
        binding.recyclerView.adapter = adapter

        getIssue()
    }

    @SuppressLint("CheckResult")
    fun onClick() {
        val title = binding.editTitle.text.toString()
        val body = binding.editBody.text.toString()
        if (title.isEmpty()) {
            Toast.makeText(activity, "ISSUE标题不得为空", Toast.LENGTH_SHORT).show()
            return
        }
        val request = GithubApiService.getService()?.CreateIssue(owner, repoName, CreateIssueRequestBody(title, body))
        request?.observeOn(AndroidSchedulers.mainThread())?.subscribeBy(
            onNext = {
                Toast.makeText(activity, "创建ISSUE成功", Toast.LENGTH_SHORT).show()
                getIssue()
            },
            onError = {
                Toast.makeText(activity, "创建ISSUE失败", Toast.LENGTH_SHORT).show()
            }
        )
    }

    @SuppressLint("CheckResult")
    private fun getIssue() {
        val request = GithubApiService.getService()?.GetIssues(owner, repoName)
        request?.observeOn(AndroidSchedulers.mainThread())?.subscribeBy(
            onNext = {
                adapter.reset(it)
                if (it.isEmpty()) {
                    Toast.makeText(activity, "该仓库无任何开启状态的ISSUE", Toast.LENGTH_SHORT).show()
                }
            },
            onError = {
                Timber.d(it)
                Toast.makeText(activity, "获取ISSUE失败", Toast.LENGTH_SHORT).show()
            }
        )
    }
}
