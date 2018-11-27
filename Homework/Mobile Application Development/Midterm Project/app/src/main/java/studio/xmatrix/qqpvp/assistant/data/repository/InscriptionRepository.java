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
import studio.xmatrix.qqpvp.assistant.data.model.InscriptionItem;
import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiInscriptionItem;
import studio.xmatrix.qqpvp.assistant.data.service.DataApiService;
import studio.xmatrix.qqpvp.assistant.data.service.DatabaseService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageApiService;
import studio.xmatrix.qqpvp.assistant.data.service.ImageStorageService;

@Singleton
public class InscriptionRepository {

    private App app;
    private AppExecutors executors;
    private DataApiService dataApiService;
    private ImageApiService imageApiService;
    private DatabaseService databaseService;
    private ImageStorageService imageStorageService;

    @Inject
    InscriptionRepository(App app, AppExecutors executors, DataApiService dataApiService, ImageApiService imageApiService, DatabaseService databaseService, ImageStorageService imageStorageService) {
        this.app = app;
        this.executors = executors;
        this.dataApiService = dataApiService;
        this.imageApiService = imageApiService;
        this.databaseService = databaseService;
        this.imageStorageService = imageStorageService;
    }

    public LiveData<Resource<List<InscriptionItem>>> getInscriptionList() {
        return new NetworkBoundResource<List<InscriptionItem>, List<ApiInscriptionItem>>(executors) {
            @Override
            protected void saveCallResult(@NonNull List<ApiInscriptionItem> items) {
                List<InscriptionItem> newItems = new ArrayList<>();
                for (ApiInscriptionItem item : items) {
                    newItems.add(item.toInscriptionItem());
                }
                databaseService.setInscriptionList(newItems);
                SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(app).edit();
                editor.putLong("inscription-list", Instant.now().getEpochSecond());
                editor.apply();
            }

            @Override
            protected boolean shouldFetch(@Nullable List<InscriptionItem> data) {
                if (data == null || data.size() == 0) {
                    return true;
                }
                SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(app);
                Instant instant = Instant.ofEpochSecond(pref.getLong("inscription-list", 0));
                return instant.plusSeconds(12 * 60 * 60).isBefore(Instant.now());
            }

            @NonNull
            @Override
            protected LiveData<List<InscriptionItem>> loadFromDb() {
                return databaseService.getInscriptionList();
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<List<ApiInscriptionItem>>> createCall() {
                return dataApiService.getInscriptionList();
            }
        }.asLiveData();
    }

    public LiveData<Resource<Bitmap>> getInscriptionIcon(int id) {
        return new NetworkBoundResource<Bitmap, Bitmap>(executors) {
            @Override
            protected void saveCallResult(@NonNull Bitmap item) {
                imageStorageService.save(item, ImageStorageService.INSCRIPTION_ICON_PATH, ImageStorageService.ID_FORMAT, id);
            }

            @Override
            protected boolean shouldFetch(@Nullable Bitmap data) {
                return data == null;
            }

            @NonNull
            @Override
            protected LiveData<Bitmap> loadFromDb() {
                return imageStorageService.load(ImageStorageService.INSCRIPTION_ICON_PATH, ImageStorageService.ID_FORMAT, id);
            }

            @NonNull
            @Override
            protected LiveData<ApiResponse<Bitmap>> createCall() {
                return imageApiService.getInscriptionIcon(id);
            }
        }.asLiveData();
    }
}
