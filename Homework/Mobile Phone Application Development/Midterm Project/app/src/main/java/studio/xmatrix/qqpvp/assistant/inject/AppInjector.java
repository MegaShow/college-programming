package studio.xmatrix.qqpvp.assistant.inject;


import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.inject.component.AppComponent;
import studio.xmatrix.qqpvp.assistant.inject.component.DaggerAppComponent;
import studio.xmatrix.qqpvp.assistant.ui.activity.collection.CollectionHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.search.SearchHandler;

public class AppInjector {

    private AppInjector() {}

    private static AppComponent component;

    public static void init(App app) {
        component = DaggerAppComponent.builder().app(app).build();
    }

    public static void inject(Injectable injectable) {
        if (injectable instanceof ListHandler) {
            component.inject((ListHandler) injectable);
        } else if (injectable instanceof SearchHandler) {
            component.inject((SearchHandler) injectable);
        } else if (injectable instanceof CollectionHandler) {
            component.inject((CollectionHandler) injectable);
        } else if (injectable instanceof HeroDetailHandler) {
            component.inject((HeroDetailHandler) injectable);
        } else {
            throw new IllegalArgumentException("Class not found in AppComponent");
        }
    }
}
