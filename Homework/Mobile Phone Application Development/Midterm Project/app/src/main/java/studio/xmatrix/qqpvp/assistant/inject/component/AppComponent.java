package studio.xmatrix.qqpvp.assistant.inject.component;

import javax.inject.Singleton;

import dagger.BindsInstance;
import dagger.Component;
import dagger.android.AndroidInjectionModule;
import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.inject.module.ServiceModule;
import studio.xmatrix.qqpvp.assistant.inject.module.ViewModelModule;
import studio.xmatrix.qqpvp.assistant.ui.activity.collection.CollectionHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.search.SearchHandler;

@Singleton
@Component(modules = {
        AndroidInjectionModule.class,
        ServiceModule.class,
        ViewModelModule.class
})
public interface AppComponent {

    @Component.Builder
    interface Builder {

        @BindsInstance
        Builder app(App app);

        AppComponent build();
    }

    void inject(ListHandler handler);

    void inject(SearchHandler handler);

    void inject(CollectionHandler handler);

    void inject(HeroDetailHandler handler);
}
