package com.icytown.course.experimentfive.webapi.ui.menu

import com.icytown.course.experimentfive.webapi.databinding.MenuActivityBinding
import com.icytown.course.experimentfive.webapi.ui.bilibili.BilibiliActivity
import com.icytown.course.experimentfive.webapi.ui.github.GithubActivity

class MenuHandler(val activity: MenuActivity, val binding: MenuActivityBinding) {

    fun onClickBilibili() {
        BilibiliActivity.startActivity(activity)
    }

    fun onClickGithub() {
        GithubActivity.startActivity(activity)
    }
}
