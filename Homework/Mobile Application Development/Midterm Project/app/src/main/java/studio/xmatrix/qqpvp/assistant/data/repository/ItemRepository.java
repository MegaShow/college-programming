package studio.xmatrix.qqpvp.assistant.data.repository;

import android.arch.lifecycle.LiveData;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.preference.PreferenceManager;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import java.time.Instant;
import java.util.ArrayList;
import java.util.List;

import javax.inject.Inject;
import javax.inject.Singleton;

import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.data.common.ApiResponse;
import studio.xmatrix.qqpvp.assistant.data.common.AppExecutors;
import studio.xmatrix.qqpvp.assistant.data.common.NetworkBoundResource;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiNormalItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiSpecialItemList;
import studio.xmatrix.qqpvp.assistant.data.service.DataApiService;
import studio.xmatrix.qqpvp.assistant.data.service.DatabaseService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageApiService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageStorageService;

@Singleton
public class ItemRepository {

    private App app;
    private AppExecutors executors;
    private DataApiService dataApiService;
    private ImageApiService imageApiService;
    private DatabaseService databaseService;
    private ImageStorageService imageStorageService;

    @Inject
    ItemRepository(App app, AppExecutors executors, DataApiService dataApiService, ImageApiService imageApiService, DatabaseService databaseService, ImageStorageService imageStorageService) {
        this.app = app;
        this.executors = executors;
        this.dataApiService = dataApiService;
        this.imageApiService = imageApiService;
        this.databaseService = databaseService;
        this.imageStorageService = imageStorageService;
    }

    public LiveData<ItemItem> getItem(int id) {
        return databaseService.getItem(id);
    }

    public LiveData<Resource<List<ItemItem>>> getNormalItemList() {
        return new NetworkBoundResource<List<ItemItem>, List<ApiNormalItemItem>>(executors) {
            @Override
            protected void saveCallResult(@NonNull List<ApiNormalItemItem> items) {
                List<ItemItem> newItems = new ArrayList<>();
                for (ApiNormalItemItem item : items) {
                    newItems.add(item.toItemItem());
                }
                databaseService.setNormalItemList(newItems);
                SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(app).edit();
                editor.putLong("item-list", Instant.now().getEpochSecond());
                editor.apply();
            }

            @Override
            protected boolean shouldFetch(@Nullable List<ItemItem> data) {
                if (data == null || data.size() == 0) {
                    return true;
                }
                SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(app);
                Instant instant = Instant.ofEpochSecond(pref.getLong("item-list", 0));
                return instant.plusSeconds(12 * 60 * 60).isBefore(Instant.now());
            }

            @NonNull
            @Override
            protected LiveData<List<ItemItem>> loadFromDb() {
                return databaseService.getNormalItemList();
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<List<ApiNormalItemItem>>> createCall() {
                return dataApiService.getNormalItemList();
            }
        }.asLiveData();
    }

    public LiveData<Resource<List<ItemItem>>> getSpecialItemList() {
        return new NetworkBoundResource<List<ItemItem>, ApiSpecialItemList>(executors) {
            @Override
            protected void saveCallResult(@NonNull ApiSpecialItemList items) {
                databaseService.setSpecialItemList(items.toItemList());
                SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(app).edit();
                editor.putLong("item-sp-list", Instant.now().getEpochSecond());
                editor.apply();
            }

            @Override
            protected boolean shouldFetch(@Nullable List<ItemItem> data) {
                if (data == null || data.size() == 0) {
                    return true;
                }
                SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(app);
                Instant instant = Instant.ofEpochSecond(pref.getLong("item-sp-list", 0));
                return instant.plusSeconds(12 * 60 * 60).isBefore(Instant.now());
            }

            @NonNull
            @Override
            protected LiveData<List<ItemItem>> loadFromDb() {
                return databaseService.getSpecialItemList();
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<ApiSpecialItemList>> createCall() {
                return dataApiService.getSpecialItemList();
            }
        }.asLiveData();
    }

    public LiveData<Resource<Bitmap>> getItemIcon(int id) {
        return new NetworkBoundResource<Bitmap, Bitmap>(executors) {
            @Override
            protected void saveCallResult(@NonNull Bitmap item) {
                imageStorageService.save(item, ImageStorageService.ITEM_ICON_PATH, ImageStorageService.ID_FORMAT, id);
            }

            @Override
            protected boolean shouldFetch(@Nullable Bitmap data) {
                return data == null;
            }

            @NonNull
            @Override
            protected LiveData<Bitmap> loadFromDb() {
                return imageStorageService.load(ImageStorageService.ITEM_ICON_PATH, ImageStorageService.ID_FORMAT, id);
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<Bitmap>> createCall() {
                return imageApiService.getItemIcon(id);
            }
        }.asLiveData();
    }
}
