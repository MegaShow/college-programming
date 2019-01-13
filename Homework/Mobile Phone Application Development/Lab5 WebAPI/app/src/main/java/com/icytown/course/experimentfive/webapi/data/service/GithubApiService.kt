package com.icytown.course.experimentfive.webapi.data.service

import com.icytown.course.experimentfive.webapi.data.model.CreateIssueRequestBody
import com.icytown.course.experimentfive.webapi.data.model.Issue
import com.icytown.course.experimentfive.webapi.data.model.Repository
import io.reactivex.Observable
import io.reactivex.schedulers.Schedulers
import okhttp3.ResponseBody
import retrofit2.Retrofit
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.*

interface GithubApiService {

    companion object {

        const val BASE_URL = "https://api.github.com/"

        @Volatile
        private var instance: GithubApiService? = null

        fun getService(): GithubApiService? {
            if (instance == null) {
                synchronized(GithubApiService::class.java) {
                    if (instance == null) {
                        val retrofit = Retrofit.Builder()
                            .addCallAdapterFactory(RxJava2CallAdapterFactory.createWithScheduler(Schedulers.io()))
                            .addConverterFactory(GsonConverterFactory.create())
                            .baseUrl(BASE_URL)
                            .build()
                        instance = retrofit.create(GithubApiService::class.java)
                    }
                }
            }
            return instance
        }
    }

    @GET("users/{owner}/repos")
    fun GetRepositories(@Path("owner") owner: String): Observable<List<Repository>>

    @GET("repos/{owner}/{repoName}/issues")
    fun GetIssues(@Path("owner") owner: String, @Path("repoName") repoName: String): Observable<List<Issue>>

    @Headers("Authorization: token OAUTH-TOKEN")
    @POST("repos/{owner}/{repoName}/issues")
    fun CreateIssue(@Path("owner") owner: String, @Path("repoName") repoName: String, @Body body: CreateIssueRequestBody): Observable<ResponseBody>
}
