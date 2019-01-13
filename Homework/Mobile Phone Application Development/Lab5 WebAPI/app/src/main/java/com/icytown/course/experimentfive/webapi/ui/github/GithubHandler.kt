package com.icytown.course.experimentfive.webapi.ui.github

import android.annotation.SuppressLint
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import com.icytown.course.experimentfive.webapi.data.model.Repository
import com.icytown.course.experimentfive.webapi.data.service.GithubApiService
import com.icytown.course.experimentfive.webapi.databinding.GithubActivityBinding
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.rxkotlin.subscribeBy
import timber.log.Timber

class GithubHandler(val activity: GithubActivity, val binding: GithubActivityBinding) {

    private val adapter = RecyclerViewAdapter()

    init {
        binding.recyclerView.layoutManager = LinearLayoutManager(activity)
        binding.recyclerView.adapter = adapter
    }

    @SuppressLint("CheckResult")
    fun onClick() {
        val owner = binding.editText.text.toString()
        if (owner.isEmpty()) {
            Toast.makeText(activity, "用户名不得为空", Toast.LENGTH_SHORT).show()
            return
        }
        val request = GithubApiService.getService()?.GetRepositories(owner)
        request?.observeOn(AndroidSchedulers.mainThread())?.subscribeBy(
            onNext = {
                val items = ArrayList<Repository>()
                it.forEach { item ->
                    if (item.openIssue) {
                        items += item
                    }
                }
                adapter.reset(owner, items)
                if (it.isEmpty()) {
                    Toast.makeText(activity, "该用户无任何仓库", Toast.LENGTH_SHORT).show()
                }
            },
            onError = {
                Timber.d(it)
                Toast.makeText(activity, "获取仓库失败", Toast.LENGTH_SHORT).show()
            }
        )
    }
}
