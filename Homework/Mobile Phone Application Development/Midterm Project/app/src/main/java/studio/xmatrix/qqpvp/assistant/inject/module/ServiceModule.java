package studio.xmatrix.qqpvp.assistant.inject.module;

import com.google.gson.GsonBuilder;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import studio.xmatrix.qqpvp.assistant.data.common.converter.BitmapConverterFactory;
import studio.xmatrix.qqpvp.assistant.data.common.converter.LiveDataCallAdapterFactory;
import studio.xmatrix.qqpvp.assistant.data.common.converter.PayTypeAdapter;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiHeroListItem;
import studio.xmatrix.qqpvp.assistant.data.service.DataApiService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageApiService;

@Module
public class ServiceModule {

    @Singleton
    @Provides
    DataApiService provideDataApiService() {
        GsonBuilder builder = new GsonBuilder();
        builder.registerTypeAdapter(ApiHeroListItem.PayType.class, new PayTypeAdapter());
        Retrofit retrofit = new Retrofit.Builder()
                .addCallAdapterFactory(new LiveDataCallAdapterFactory())
                .addConverterFactory(GsonConverterFactory.create(builder.create()))
                .baseUrl(DataApiService.BASE_URL)
                .build();
        return retrofit.create(DataApiService.class);
    }

    @Singleton
    @Provides
    ImageApiService provideImageApiService() {
        Retrofit retrofit = new Retrofit.Builder()
                .addCallAdapterFactory(new LiveDataCallAdapterFactory())
                .addConverterFactory(BitmapConverterFactory.create())
                .baseUrl(ImageApiService.BASE_URL)
                .build();
        return retrofit.create(ImageApiService.class);
    }
}
