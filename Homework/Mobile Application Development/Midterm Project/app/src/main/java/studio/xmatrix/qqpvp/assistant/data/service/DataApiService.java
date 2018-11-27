package studio.xmatrix.qqpvp.assistant.data.service;

import android.arch.lifecycle.LiveData;

import java.util.List;

import javax.inject.Singleton;

import okhttp3.ResponseBody;
import retrofit2.http.GET;
import retrofit2.http.Path;
import studio.xmatrix.qqpvp.assistant.data.common.ApiResponse;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiHeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiInscriptionItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiNormalItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiSpecialItemList;

@Singleton
public interface DataApiService {

    String BASE_URL = "http://pvp.qq.com/";

    @GET("web201605/js/herolist.json")
    LiveData<ApiResponse<List<ApiHeroListItem>>> getHeroList();

    @GET("web201605/js/item.json")
    LiveData<ApiResponse<List<ApiNormalItemItem>>> getNormalItemList();

    @GET("zlkdatasys/data_zlk_bjtwitem.json")
    LiveData<ApiResponse<ApiSpecialItemList>> getSpecialItemList();

    @GET("web201605/js/summoner.json")
    LiveData<ApiResponse<List<SummonerItem>>> getSummonerList();

    @GET("web201605/js/ming.json")
    LiveData<ApiResponse<List<ApiInscriptionItem>>> getInscriptionList();

    @GET("web201605/herodetail/{id}.shtml")
    LiveData<ApiResponse<ResponseBody>> getHeroDetail(@Path("id") int id);
}
