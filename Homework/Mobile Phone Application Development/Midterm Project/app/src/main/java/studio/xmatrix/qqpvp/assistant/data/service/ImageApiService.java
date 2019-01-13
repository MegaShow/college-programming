package studio.xmatrix.qqpvp.assistant.data.service;

import android.arch.lifecycle.LiveData;
import android.graphics.Bitmap;

import javax.inject.Singleton;

import retrofit2.http.GET;
import retrofit2.http.Path;
import studio.xmatrix.qqpvp.assistant.data.common.ApiResponse;

@Singleton
public interface ImageApiService {

    String BASE_URL = "http://game.gtimg.cn/images/yxzj/img201606/";

    @GET("heroimg/{id}/{id}.jpg")
    LiveData<ApiResponse<Bitmap>> getHeroIcon(@Path("id") int id);

    // index从1开始
    @GET("heroimg/{id}/{id}-smallskin-{index}.jpg")
    LiveData<ApiResponse<Bitmap>> getHeroSkinIcon(@Path("id") int id, @Path("index") int index);

    // index从1开始
    @GET("skin/hero-info/{id}/{id}-bigskin-{index}.jpg")
    LiveData<ApiResponse<Bitmap>> getHeroSkinBigPicture(@Path("id") int id, @Path("index") int index);

    // index从1开始
    @GET("heroimg/{id}/{id}-mobileskin-{index}.jpg")
    LiveData<ApiResponse<Bitmap>> getHeroSkinPicture(@Path("id") int id, @Path("index") int index);

    // index从0开始
    @GET("heroimg/{id}/{id}{index}0.png")
    LiveData<ApiResponse<Bitmap>> getHeroSkillIcon(@Path("id") int id, @Path("index") int index);

    @GET("itemimg/{id}.jpg")
    LiveData<ApiResponse<Bitmap>> getItemIcon(@Path("id") int id);

    @GET("summoner/{id}.jpg")
    LiveData<ApiResponse<Bitmap>> getSummonerIcon(@Path("id") int id);

    @GET("summoner/{id}-big.jpg")
    LiveData<ApiResponse<Bitmap>> getSummonerPicture(@Path("id") int id);

    @GET("mingwen/{id}.png")
    LiveData<ApiResponse<Bitmap>> getInscriptionIcon(@Path("id") int id);
}
