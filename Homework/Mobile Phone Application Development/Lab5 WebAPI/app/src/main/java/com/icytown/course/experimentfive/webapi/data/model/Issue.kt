package com.icytown.course.experimentfive.webapi.data.model

import com.google.gson.annotations.SerializedName

data class Issue(
    val title: String,
    @SerializedName("created_at")
    val create: String,
    val state: String,
    val body: String
)
