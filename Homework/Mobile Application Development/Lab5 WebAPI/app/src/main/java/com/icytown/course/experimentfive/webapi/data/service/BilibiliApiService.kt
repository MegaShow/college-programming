package com.icytown.course.experimentfive.webapi.data.service

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import com.google.gson.Gson
import com.google.gson.JsonSyntaxException
import com.icytown.course.experimentfive.webapi.data.model.PVideo
import com.icytown.course.experimentfive.webapi.data.model.Top
import io.reactivex.Observable
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers
import java.net.HttpURLConnection
import java.net.URL
import javax.net.ssl.HttpsURLConnection

class BilibiliApiService {

    companion object {

        fun getTop(userId: Int): Observable<Top> {
            val observable: Observable<Top> = Observable.create { emitter ->
                val url = URL("https://space.bilibili.com/ajax/top/showTop?mid=$userId")
                val connection = url.openConnection() as HttpsURLConnection
                connection.requestMethod = "GET"
                connection.connectTimeout = 5000
                connection.readTimeout = 5000
                val inputStream = connection.inputStream
                val response = inputStream.bufferedReader().use { it.readText() }
                val top = try {
                    Gson().fromJson(response, Top::class.java)
                } catch (e: JsonSyntaxException) {
                    Top(false, null)
                }
                emitter.onNext(top)
                emitter.onComplete()
            }
            return observable
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
        }

        fun getPVideo(aid: Int): Observable<PVideo> {
            val observable: Observable<PVideo> = Observable.create { emitter ->
                val url = URL("https://api.bilibili.com/pvideo?aid=$aid")
                val connection = url.openConnection() as HttpsURLConnection
                connection.requestMethod = "GET"
                connection.connectTimeout = 5000
                connection.readTimeout = 5000
                val inputStream = connection.inputStream
                val response = inputStream.bufferedReader().use { it.readText() }
                val pVideo = try {
                    Gson().fromJson(response, PVideo::class.java)
                } catch (e: JsonSyntaxException) {
                    PVideo()
                }
                emitter.onNext(pVideo)
                emitter.onComplete()
            }
            return observable
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
        }

        fun getBitmap(urlstr: String): Observable<Bitmap> {
            val observable: Observable<Bitmap> = Observable.create { emitter ->
                val url = URL(urlstr)
                val connection = url.openConnection() as HttpURLConnection
                connection.requestMethod = "GET"
                connection.connectTimeout = 5000
                connection.readTimeout = 5000
                val inputStream = connection.inputStream
                emitter.onNext(BitmapFactory.decodeStream(inputStream))
                emitter.onComplete()
            }
            return observable
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
        }
    }
}
