package com.icytown.course.experimentfive.webapi.data.model

import com.google.gson.annotations.SerializedName

data class Repository(
    val id: Int,
    val name: String,
    val description: String,
    @SerializedName("has_issues")
    val openIssue: Boolean,
    @SerializedName("open_issues_count")
    val issuesCount: Int
)
