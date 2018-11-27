package studio.xmatrix.qqpvp.assistant.data.service;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MutableLiveData;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Locale;

import javax.inject.Inject;
import javax.inject.Singleton;

import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.data.common.AppExecutors;

@Singleton
public class ImageStorageService {

    private App app;
    private AppExecutors executors;

    public final static String HERO_ICON_PATH = "hero/icon/";
    public final static String HERO_SKIN_ICON_PATH = "hero/skin/icon/";
    public final static String HERO_SKIN_PICTURE_PATH = "hero/skin/picture/";
    public final static String HERO_SKILL_ICON_PATH = "hero/skill/icon/";
    public final static String ITEM_ICON_PATH = "item/icon/";
    public final static String SUMMONER_ICON_PATH = "summoner/icon/";
    public final static String SUMMONER_PICTURE_PATH = "summoner/picture/";
    public final static String INSCRIPTION_ICON_PATH = "inscription/icon/";

    public final static String ID_FORMAT = "%d.jpg";
    public final static String ID_INDEX_FORMAT = "%d-%d.jpg";


    @Inject
    public ImageStorageService(App app, AppExecutors executors) {
        this.app = app;
        this.executors = executors;
    }

    public void save(Bitmap bitmap, String path, String format, Object... args) {
        saveToInternalCacheStorage(path, String.format(Locale.getDefault(), format, args), bitmap);
    }

    public LiveData<Bitmap> load(String path, String format, Object... args) {
        return loadFromInternalCacheStorage(path, String.format(Locale.getDefault(), format, args));
    }

    private void saveToInternalCacheStorage(String path, String filename, Bitmap bitmap) {
        File folder = new File(app.getCacheDir(), "/images/" + path);
        if (!folder.exists()) {
            if (!folder.mkdirs()) {
                return;
            }
        }
        File file = new File(folder, filename);
        try (FileOutputStream outputStream = new FileOutputStream(String.valueOf(file))) {
            bitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private LiveData<Bitmap> loadFromInternalCacheStorage(String path, String filename) {
        MutableLiveData<Bitmap> data = new MutableLiveData<>();
        executors.diskIO().execute(()->{
            File folder = new File(app.getCacheDir(), "/images/" + path);
            File file = new File(folder, filename);
            try {
                BitmapFactory.Options options = new BitmapFactory.Options();
                options.inPreferredConfig = Bitmap.Config.ARGB_4444;
                Bitmap bitmap = BitmapFactory.decodeStream(new FileInputStream(file), null, options);
                data.postValue(bitmap);
            } catch (Exception e) {
                data.postValue(null);
            }
        });
        return data;
    }
}
