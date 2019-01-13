package studio.xmatrix.qqpvp.assistant.data.repository;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MediatorLiveData;
import android.support.v7.app.AppCompatActivity;
import android.util.Pair;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

import javax.inject.Inject;
import javax.inject.Singleton;

import studio.xmatrix.qqpvp.assistant.data.common.AppExecutors;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.data.service.DatabaseService;

@Singleton
public class CollectionRepository {

    private AppExecutors executors;
    private DatabaseService databaseService;

    private HeroRepository heroRepository;
    private ItemRepository itemRepository;
    private SummonerRepository summonerRepository;

    @Inject
    public CollectionRepository(DatabaseService databaseService, HeroRepository heroRepository, ItemRepository itemRepository, SummonerRepository summonerRepository) {
        this.databaseService = databaseService;
        this.heroRepository = heroRepository;
        this.itemRepository = itemRepository;
        this.summonerRepository = summonerRepository;
    }

    public LiveData<List<Pair<CollectionItem, ? extends ListItem>>> getCollectionList(AppCompatActivity activity) {
        MediatorLiveData<List<Pair<CollectionItem, ? extends ListItem>>> data = new MediatorLiveData<>();
        AtomicInteger counter = new AtomicInteger();
        data.addSource(databaseService.getCollectionList(), list -> {
            if (list != null) {
                counter.getAndIncrement();
                if (counter.get() >= 5) {
                    data.postValue(databaseService.getCollectionListSync());
                }
            }
        });
        heroRepository.getHeroList().observe(activity, resource -> {
            if (resource != null && resource.status == Resource.Status.SUCCESS) {
                counter.getAndIncrement();
                if (counter.get() == 5) {
                    data.postValue(databaseService.getCollectionListSync());
                }
            }
        });
        itemRepository.getNormalItemList().observe(activity, resource -> {
            if (resource != null && resource.status == Resource.Status.SUCCESS) {
                counter.getAndIncrement();
                if (counter.get() == 5) {
                    data.postValue(databaseService.getCollectionListSync());
                }
            }
        });
        itemRepository.getSpecialItemList().observe(activity, resource -> {
            if (resource != null && resource.status == Resource.Status.SUCCESS) {
                counter.getAndIncrement();
                if (counter.get() == 5) {
                    data.postValue(databaseService.getCollectionListSync());
                }
            }
        });
        summonerRepository.getSummonerList().observe(activity, resource -> {
            if (resource != null && resource.status == Resource.Status.SUCCESS) {
                counter.getAndIncrement();
                if (counter.get() == 5) {
                    data.postValue(databaseService.getCollectionListSync());
                }
            }
        });
        return data;
    }

    public boolean isExistCollection(int id) {
        return databaseService.isExistCollection(id);
    }

    public boolean addCollection(CollectionItem item) {
        if (item.getObjectId() != 0) {
            return false;
        }
        return databaseService.addCollection(item);
    }

    public boolean updateCollection(CollectionItem item) {
        if (item.getObjectId() == 0) {
            return false;
        }
        return databaseService.updateCollection(item);
    }

    public boolean removeCollection(int id) {
        databaseService.removeCollection(id);
        return true;
    }
}
