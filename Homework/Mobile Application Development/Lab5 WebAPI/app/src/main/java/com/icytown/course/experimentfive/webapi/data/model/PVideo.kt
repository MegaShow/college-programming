package com.icytown.course.experimentfive.webapi.data.model

import com.google.gson.annotations.SerializedName
import java.util.*

data class PVideo(
    val code: Int,
    val message: String,
    val ttl: Int,
    val data: Data?
) {

    constructor() : this(0, "", 0, null)

    data class Data(
        val pvdata: String,
        @SerializedName("img_x_len")
        val xLen: Int,
        @SerializedName("img_y_len")
        val yLen: Int,
        @SerializedName("img_x_size")
        val xSize: Int,
        @SerializedName("img_y_size")
        val ySize: Int,
        @SerializedName("image")
        val images: Array<String>,
        @SerializedName("index")
        val indices: Array<Int>
    ) {
        override fun equals(other: Any?): Boolean {
            if (this === other) return true
            if (javaClass != other?.javaClass) return false

            other as Data

            if (pvdata != other.pvdata) return false
            if (xLen != other.xLen) return false
            if (yLen != other.yLen) return false
            if (xSize != other.xSize) return false
            if (ySize != other.ySize) return false
            if (!Arrays.equals(images, other.images)) return false
            if (!Arrays.equals(indices, other.indices)) return false

            return true
        }

        override fun hashCode(): Int {
            var result = pvdata.hashCode()
            result = 31 * result + xLen
            result = 31 * result + yLen
            result = 31 * result + xSize
            result = 31 * result + ySize
            result = 31 * result + Arrays.hashCode(images)
            result = 31 * result + Arrays.hashCode(indices)
            return result
        }
    }
}
