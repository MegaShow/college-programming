package com.icytown.course.experimentfive.webapi.data.model

import com.google.gson.annotations.SerializedName

data class Top(
    val status: Boolean,
    val data: Data?
) {

    data class Data(
        val aid: Int,
        val state: Int,
        val cover: String,
        val title:String,
        val content:String,
        val play:Int,
        val duration:String,
        @SerializedName("video_review")
        val videoReview: Int,
        val create: String,
        val rec: String,
        val count: Int
    )
}
