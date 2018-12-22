package com.icytown.course.experimentfive.webapi.ui.bilibili

import android.content.Context
import android.net.ConnectivityManager
import android.net.NetworkInfo
import android.widget.Toast
import androidx.recyclerview.widget.LinearLayoutManager
import com.icytown.course.experimentfive.webapi.data.service.BilibiliApiService
import com.icytown.course.experimentfive.webapi.databinding.BilibiliActivityBinding
import io.reactivex.rxkotlin.subscribeBy

class BilibiliHandler(val activity: BilibiliActivity, val binding: BilibiliActivityBinding) {

    private val adapter = RecyclerViewAdapter()

    init {
        binding.recyclerView.layoutManager = LinearLayoutManager(activity)
        binding.recyclerView.adapter = adapter
    }

    fun onClick() {
        if (binding.editText.text.isEmpty()) {
            Toast.makeText(activity, "用户Id不得为空", Toast.LENGTH_SHORT).show()
            return
        }
        val userId = binding.editText.text.toString().toIntOrNull()
        when {
            userId == null -> Toast.makeText(activity, "非法输入", Toast.LENGTH_SHORT).show()
            userId < 1 || userId > 40 -> Toast.makeText(activity, "用户Id必须在1~40之间", Toast.LENGTH_SHORT).show()
            else -> {
                if (!checkNetwork()) {
                    Toast.makeText(activity, "网络连接失败", Toast.LENGTH_SHORT).show()
                    return
                }
                BilibiliApiService.getTop(userId).subscribeBy(
                    onNext = {
                        if (it.status) {
                            Toast.makeText(activity, "获取数据成功", Toast.LENGTH_SHORT).show()
                            adapter.add(it)
                        } else {
                            Toast.makeText(activity, "数据库中不存在记录", Toast.LENGTH_SHORT).show()
                        }
                    },
                    onError = {
                        Toast.makeText(activity, "连接超时", Toast.LENGTH_SHORT).show()
                    }
                )
            }
        }
    }

    private fun checkNetwork(): Boolean {
        val connectivityManager = activity.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val activeNetwork: NetworkInfo? = connectivityManager.activeNetworkInfo
        return activeNetwork?.isConnected ?: false
    }
}
