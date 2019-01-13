package studio.xmatrix.qqpvp.assistant.data.service;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MutableLiveData;
import android.util.Pair;

import java.util.ArrayList;
import java.util.List;

import javax.inject.Inject;
import javax.inject.Singleton;

import io.objectbox.Box;
import io.objectbox.android.ObjectBoxLiveData;
import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.data.common.AppExecutors;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem_;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem_;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem_;
import studio.xmatrix.qqpvp.assistant.data.model.InscriptionItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem_;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem_;

@Singleton
public class DatabaseService {

    private App app;
    private AppExecutors executors;

    @Inject
    public DatabaseService(App app, AppExecutors executors) {
        this.app = app;
        this.executors = executors;
    }

    public LiveData<List<HeroListItem>> getHeroList() {
        MutableLiveData<List<HeroListItem>> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(HeroListItem.class).getAll())
        );
        return data;
    }

    public void setHeroList(List<HeroListItem> heroes) {
        app.getBoxStore().boxFor(HeroListItem.class).removeAll();
        app.getBoxStore().boxFor(HeroListItem.class).put(heroes);
    }

    public LiveData<HeroListItem> getHero(int id) {
        MutableLiveData<HeroListItem> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(HeroListItem.class).query().equal(HeroListItem_.id, id).build().findFirst())
        );
        return data;
    }

    public LiveData<List<ItemItem>> getNormalItemList() {
        MutableLiveData<List<ItemItem>> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(ItemItem.class).query().equal(ItemItem_.special, false).build().find())
        );
        return data;
    }

    public LiveData<List<ItemItem>> getSpecialItemList() {
        MutableLiveData<List<ItemItem>> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(ItemItem.class).query().equal(ItemItem_.special, true).build().find())
        );
        return data;
    }

    public void setNormalItemList(List<ItemItem> items) {
        app.getBoxStore().boxFor(ItemItem.class).query().equal(ItemItem_.special, false).build().remove();
        app.getBoxStore().boxFor(ItemItem.class).put(items);
    }

    public void setSpecialItemList(List<ItemItem> items) {
        app.getBoxStore().boxFor(ItemItem.class).query().equal(ItemItem_.special, true).build().remove();
        app.getBoxStore().boxFor(ItemItem.class).put(items);
    }

    public LiveData<ItemItem> getItem(int id) {
        MutableLiveData<ItemItem> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(ItemItem.class).query().equal(ItemItem_.id, id).build().findFirst())
        );
        return data;
    }

    public LiveData<List<SummonerItem>> getSummonerList() {
        MutableLiveData<List<SummonerItem>> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(SummonerItem.class).getAll())
        );
        return data;
    }

    public void setSummonerList(List<SummonerItem> items) {
        app.getBoxStore().boxFor(SummonerItem.class).removeAll();
        app.getBoxStore().boxFor(SummonerItem.class).put(items);
    }

    public LiveData<SummonerItem> getSummoner(int id) {
        MutableLiveData<SummonerItem> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(SummonerItem.class).query().equal(SummonerItem_.id, id).build().findFirst())
        );
        return data;
    }

    public LiveData<List<InscriptionItem>> getInscriptionList() {
        MutableLiveData<List<InscriptionItem>> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(InscriptionItem.class).getAll())
        );
        return data;
    }

    public void setInscriptionList(List<InscriptionItem> items) {
        app.getBoxStore().boxFor(InscriptionItem.class).removeAll();
        app.getBoxStore().boxFor(InscriptionItem.class).put(items);
    }

    public LiveData<HeroDetailItem> getHeroDetailItem(int id) {
        MutableLiveData<HeroDetailItem> data = new MutableLiveData<>();
        executors.diskIO().execute(() ->
                data.postValue(app.getBoxStore().boxFor(HeroDetailItem.class).query().equal(HeroDetailItem_.id, id).build().findFirst())
        );
        return data;
    }

    public void setHeroDetailItem(HeroDetailItem item) {
        app.getBoxStore().boxFor(HeroDetailItem.class).query().equal(HeroDetailItem_.id, item.getId()).build().remove();
        app.getBoxStore().boxFor(HeroDetailItem.class).put(item);
    }

    public LiveData<List<CollectionItem>> getCollectionList() {
        return new ObjectBoxLiveData<>(app.getBoxStore().boxFor(CollectionItem.class).query().build());
    }

    public List<Pair<CollectionItem, ? extends ListItem>> getCollectionListSync() {
        List<CollectionItem> list = app.getBoxStore().boxFor(CollectionItem.class).getAll();
        List<Pair<CollectionItem, ? extends ListItem>> data = new ArrayList<>();
        Box<HeroListItem> heroBox = app.getBoxStore().boxFor(HeroListItem.class);
        Box<ItemItem> itemBox = app.getBoxStore().boxFor(ItemItem.class);
        Box<SummonerItem> summonerBox = app.getBoxStore().boxFor(SummonerItem.class);
        for (CollectionItem item : list) {
            switch (item.getType()) {
                case Hero:
                    data.add(new Pair<>(item, heroBox.query().equal(HeroListItem_.id, item.getId()).build().findFirst()));
                    break;
                case Item:
                case SpecialItem:
                    data.add(new Pair<>(item, itemBox.query().equal(ItemItem_.id, item.getId()).build().findFirst()));
                    break;
                case Summoner:
                    data.add(new Pair<>(item, summonerBox.query().equal(SummonerItem_.id, item.getId()).build().findFirst()));
                    break;
            }
        }
        return data;
    }

    public boolean isExistCollection(int id) {
        return app.getBoxStore().boxFor(CollectionItem.class).query().equal(CollectionItem_.id, id).build().find().size() != 0;
    }

    public boolean addCollection(CollectionItem item) {
        long id = app.getBoxStore().boxFor(CollectionItem.class).put(item);
        return id != 0;
    }

    public boolean updateCollection(CollectionItem item) {
        long id = app.getBoxStore().boxFor(CollectionItem.class).put(item);
        return id == item.getObjectId();
    }

    public void removeCollection(int id) {
        app.getBoxStore().boxFor(CollectionItem.class).query().equal(CollectionItem_.id, id).build().remove();
    }
}
