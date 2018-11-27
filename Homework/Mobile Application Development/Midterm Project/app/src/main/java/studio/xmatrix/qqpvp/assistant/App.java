package studio.xmatrix.qqpvp.assistant;

import android.app.Application;

import io.objectbox.BoxStore;
import studio.xmatrix.qqpvp.assistant.data.model.MyObjectBox;
import studio.xmatrix.qqpvp.assistant.inject.AppInjector;

public class App extends Application {

    private BoxStore boxStore;

    @Override
    public void onCreate() {
        super.onCreate();

        boxStore = MyObjectBox.builder().androidContext(App.this).build();
//        if (BuildConfig.DEBUG) {
//            Timber.plant(new Timber.DebugTree());
//            new AndroidObjectBrowser(boxStore).start(this);
//        }

        AppInjector.init(this);
    }

    public BoxStore getBoxStore() {
        return boxStore;
    }
}
