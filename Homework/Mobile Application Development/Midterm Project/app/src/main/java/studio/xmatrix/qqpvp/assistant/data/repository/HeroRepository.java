package studio.xmatrix.qqpvp.assistant.data.repository;

import android.arch.lifecycle.LiveData;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.preference.PreferenceManager;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import org.jsoup.nodes.Document;

import java.time.Instant;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.inject.Inject;
import javax.inject.Singleton;

import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.data.common.ApiResponse;
import studio.xmatrix.qqpvp.assistant.data.common.AppExecutors;
import studio.xmatrix.qqpvp.assistant.data.common.JsoupResponse;
import studio.xmatrix.qqpvp.assistant.data.common.NetworkBoundJsoupResource;
import studio.xmatrix.qqpvp.assistant.data.common.NetworkBoundResource;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiHeroListItem;
import studio.xmatrix.qqpvp.assistant.data.service.DataApiService;
import studio.xmatrix.qqpvp.assistant.data.service.DataHtmlService;
import studio.xmatrix.qqpvp.assistant.data.service.DatabaseService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageApiService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageStorageService;

@Singleton
public class HeroRepository {

    private App app;
    private AppExecutors executors;
    private DataApiService dataApiService;
    private ImageApiService imageApiService;
    private DatabaseService databaseService;
    private ImageStorageService imageStorageService;
    private DataHtmlService dataHtmlService;

    @Inject
    HeroRepository(App app, AppExecutors executors, DataApiService dataApiService, ImageApiService imageApiService, DatabaseService databaseService, ImageStorageService imageStorageService, DataHtmlService dataHtmlService) {
        this.app = app;
        this.executors = executors;
        this.dataApiService = dataApiService;
        this.imageApiService = imageApiService;
        this.databaseService = databaseService;
        this.imageStorageService = imageStorageService;
        this.dataHtmlService = dataHtmlService;
    }

    public LiveData<HeroListItem> getHero(int id) {
        return databaseService.getHero(id);
    }

    public LiveData<Resource<List<HeroListItem>>> getHeroList() {
        return new NetworkBoundResource<List<HeroListItem>, List<ApiHeroListItem>>(executors) {
            @Override
            protected void saveCallResult(@NonNull List<ApiHeroListItem> items) {
                List<HeroListItem> newItems = new ArrayList<>();
                for (ApiHeroListItem item : items) {
                    newItems.add(item.toHeroListItem());
                }
                Collections.reverse(newItems);
                databaseService.setHeroList(newItems);
                SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(app).edit();
                editor.putLong("hero-list", Instant.now().getEpochSecond());
                editor.apply();
            }

            @Override
            protected boolean shouldFetch(@Nullable List<HeroListItem> data) {
                if (data == null || data.size() == 0) {
                    return true;
                }
                SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(app);
                Instant instant = Instant.ofEpochSecond(pref.getLong("hero-list", 0));
                return instant.plusSeconds(12 * 60 * 60).isBefore(Instant.now());
            }

            @NonNull
            @Override
            protected LiveData<List<HeroListItem>> loadFromDb() {
                return databaseService.getHeroList();
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<List<ApiHeroListItem>>> createCall() {
                return dataApiService.getHeroList();
            }
        }.asLiveData();
    }

    public LiveData<Resource<Bitmap>> getHeroIcon(int id) {
        return new NetworkBoundResource<Bitmap, Bitmap>(executors) {
            @Override
            protected void saveCallResult(@NonNull Bitmap item) {
                imageStorageService.save(item, ImageStorageService.HERO_ICON_PATH, ImageStorageService.ID_FORMAT, id);
            }

            @Override
            protected boolean shouldFetch(@Nullable Bitmap data) {
                return data == null;
            }

            @NonNull
            @Override
            protected LiveData<Bitmap> loadFromDb() {
                return imageStorageService.load(ImageStorageService.HERO_ICON_PATH, ImageStorageService.ID_FORMAT, id);
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<Bitmap>> createCall() {
                return imageApiService.getHeroIcon(id);
            }
        }.asLiveData();
    }

    public LiveData<Resource<HeroDetailItem>> getHeroDetail(int id) {
        return new NetworkBoundJsoupResource<HeroDetailItem, Document>(executors) {
            @Override
            protected void saveCallResult(@NonNull Document item) {
                databaseService.setHeroDetailItem(new HeroDetailItem(id, item));
                SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(app).edit();
                editor.putLong("hero-detail-" + id, Instant.now().getEpochSecond());
                editor.apply();
            }

            @Override
            protected boolean shouldFetch(@Nullable HeroDetailItem data) {
                if (data == null) {
                    return true;
                }
                SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(app);
                Instant instant = Instant.ofEpochSecond(pref.getLong("hero-detail-" + id, 0));
                return instant.plusSeconds(12 * 60 * 60).isBefore(Instant.now());
            }

            @NonNull
            @Override
            protected LiveData<HeroDetailItem> loadFromDb() {
                return databaseService.getHeroDetailItem(id);
            }

            @NonNull
            @Override
            protected LiveData<JsoupResponse<Document>> createCall() {
                return dataHtmlService.getHeroDetail(id);
            }
        }.asLiveData();
    }

    public LiveData<Resource<Bitmap>> getHeroSkinIcon(int id, int index) {
        return new NetworkBoundResource<Bitmap, Bitmap>(executors) {
            @Override
            protected void saveCallResult(@NonNull Bitmap item) {
                imageStorageService.save(item, ImageStorageService.HERO_SKIN_ICON_PATH, ImageStorageService.ID_INDEX_FORMAT, id, index);
            }

            @Override
            protected boolean shouldFetch(@Nullable Bitmap data) {
                return data == null;
            }

            @NonNull
            @Override
            protected LiveData<Bitmap> loadFromDb() {
                return imageStorageService.load(ImageStorageService.HERO_SKIN_ICON_PATH, ImageStorageService.ID_INDEX_FORMAT, id, index);
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<Bitmap>> createCall() {
                return imageApiService.getHeroSkinIcon(id, index + 1);
            }
        }.asLiveData();
    }

    public LiveData<Resource<Bitmap>> getHeroSkinPicture(int id, int index) {
        return new NetworkBoundResource<Bitmap, Bitmap>(executors) {
            @Override
            protected void saveCallResult(@NonNull Bitmap item) {
                imageStorageService.save(item, ImageStorageService.HERO_SKIN_PICTURE_PATH, ImageStorageService.ID_INDEX_FORMAT, id, index);
            }

            @Override
            protected boolean shouldFetch(@Nullable Bitmap data) {
                return data == null;
            }

            @NonNull
            @Override
            protected LiveData<Bitmap> loadFromDb() {
                return imageStorageService.load(ImageStorageService.HERO_SKIN_PICTURE_PATH, ImageStorageService.ID_INDEX_FORMAT, id, index);
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<Bitmap>> createCall() {
                return imageApiService.getHeroSkinBigPicture(id, index + 1);
            }
        }.asLiveData();
    }

    public LiveData<Resource<Bitmap>> getHeroSkillIcon(int id, int index) {
        return new NetworkBoundResource<Bitmap, Bitmap>(executors) {
            @Override
            protected void saveCallResult(@NonNull Bitmap item) {
                imageStorageService.save(item, ImageStorageService.HERO_SKILL_ICON_PATH, ImageStorageService.ID_INDEX_FORMAT, id, index);
            }

            @Override
            protected boolean shouldFetch(@Nullable Bitmap data) {
                return data == null;
            }

            @NonNull
            @Override
            protected LiveData<Bitmap> loadFromDb() {
                return imageStorageService.load(ImageStorageService.HERO_SKILL_ICON_PATH, ImageStorageService.ID_INDEX_FORMAT, id, index);
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<Bitmap>> createCall() {
                return imageApiService.getHeroSkillIcon(id, index);
            }
        }.asLiveData();
    }
}
