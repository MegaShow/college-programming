package studio.xmatrix.qqpvp.assistant.ui.common;

import android.arch.lifecycle.AndroidViewModel;
import android.arch.lifecycle.LiveData;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Pair;
import android.util.SparseArray;

import java.util.List;

import javax.inject.Inject;

import studio.xmatrix.qqpvp.assistant.App;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.InscriptionItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.data.repository.CollectionRepository;
import studio.xmatrix.qqpvp.assistant.data.repository.HeroRepository;
import studio.xmatrix.qqpvp.assistant.data.repository.InscriptionRepository;
import studio.xmatrix.qqpvp.assistant.data.repository.ItemRepository;
import studio.xmatrix.qqpvp.assistant.data.repository.SummonerRepository;

public class ViewModel extends AndroidViewModel {

    private LiveData<Resource<List<HeroListItem>>> heroes;
    private SparseArray<LiveData<Resource<Bitmap>>> heroIcons;
    private int heroDetailId;
    private LiveData<Resource<HeroDetailItem>> heroDetail;
    private SparseArray<LiveData<Resource<Bitmap>>> heroSkinIcons;
    private SparseArray<LiveData<Resource<Bitmap>>> heroSkinPictures;
    private SparseArray<LiveData<Resource<Bitmap>>> heroSkillIcons;

    private LiveData<Resource<List<ItemItem>>> normalItems;
    private LiveData<Resource<List<ItemItem>>> specialItems;
    private SparseArray<LiveData<Resource<Bitmap>>> itemIcons;

    private LiveData<Resource<List<SummonerItem>>> summoners;
    private SparseArray<LiveData<Resource<Bitmap>>> summonerIcons;
    private SparseArray<LiveData<Resource<Bitmap>>> summonerPictures;

    private LiveData<Resource<List<InscriptionItem>>> inscriptions;
    private SparseArray<LiveData<Resource<Bitmap>>> inscriptionIcons;

    private LiveData<List<Pair<CollectionItem, ? extends ListItem>>> collections;

    private HeroRepository heroRepository;
    private ItemRepository itemRepository;
    private SummonerRepository summonerRepository;
    private InscriptionRepository inscriptionRepository;
    private CollectionRepository collectionRepository;

    @Inject
    public ViewModel(App app, HeroRepository heroRepository, ItemRepository itemRepository, SummonerRepository summonerRepository,
                     InscriptionRepository inscriptionRepository, CollectionRepository collectionRepository) {
        super(app);
        this.heroRepository = heroRepository;
        this.itemRepository = itemRepository;
        this.summonerRepository = summonerRepository;
        this.inscriptionRepository = inscriptionRepository;
        this.collectionRepository = collectionRepository;
    }

    public LiveData<Resource<List<HeroListItem>>> getHeroList() {
        if (heroes == null) {
            heroes = heroRepository.getHeroList();
        }
        return heroes;
    }

    public LiveData<Resource<List<HeroListItem>>> getHeroListForcibly(AppCompatActivity activity) {
        if (heroes != null) {
            heroes.removeObservers(activity);
        }
        SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(getApplication()).edit();
        editor.remove("hero-list");
        editor.apply();
        heroes = heroRepository.getHeroList();
        return heroes;
    }

    public LiveData<Resource<Bitmap>> getHeroIcon(int id) {
        if (heroIcons == null) {
            heroIcons = new SparseArray<>();
        }
        if (heroIcons.indexOfKey(id) < 0) {
            heroIcons.put(id, heroRepository.getHeroIcon(id));
        }
        return heroIcons.get(id);
    }

    public void setHeroDetailId(int id) {
        this.heroDetailId = id;
    }

    public LiveData<Resource<HeroDetailItem>> getHeroDetail() {
        if (heroDetail == null) {
            heroDetail = heroRepository.getHeroDetail(heroDetailId);
        }
        return heroDetail;
    }

    public LiveData<Resource<Bitmap>> getHeroSkinIcon(int index) {
        if (heroSkinIcons == null) {
            heroSkinIcons = new SparseArray<>();
        }
        if (heroSkinIcons.indexOfKey(index) < 0) {
            heroSkinIcons.put(index, heroRepository.getHeroSkinIcon(heroDetailId, index));
        }
        return heroSkinIcons.get(index);
    }

    public LiveData<Resource<Bitmap>> getHeroSkinPicture(int index) {
        if (heroSkinPictures == null) {
            heroSkinPictures = new SparseArray<>();
        }
        if (heroSkinPictures.indexOfKey(index) < 0) {
            heroSkinPictures.put(index, heroRepository.getHeroSkinPicture(heroDetailId, index));
        }
        return heroSkinPictures.get(index);
    }

    public LiveData<Resource<Bitmap>> getHeroSkillIcon(int index) {
        if (heroSkillIcons == null) {
            heroSkillIcons = new SparseArray<>();
        }
        if (heroSkillIcons.indexOfKey(index) < 0) {
            heroSkillIcons.put(index, heroRepository.getHeroSkillIcon(heroDetailId, index));
        }
        return heroSkillIcons.get(index);
    }

    public LiveData<Resource<List<ItemItem>>> getNormalItemList() {
        if (normalItems == null) {
            normalItems = itemRepository.getNormalItemList();
        }
        return normalItems;
    }

    public LiveData<Resource<List<ItemItem>>> getNormalItemListForcibly(AppCompatActivity activity) {
        if (normalItems != null) {
            normalItems.removeObservers(activity);
        }
        SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(getApplication()).edit();
        editor.remove("item-list");
        editor.apply();
        normalItems = itemRepository.getNormalItemList();
        return normalItems;
    }

    public LiveData<Resource<List<ItemItem>>> getSpecialItemList() {
        if (specialItems == null) {
            specialItems = itemRepository.getSpecialItemList();
        }
        return specialItems;
    }

    public LiveData<Resource<List<ItemItem>>> getSpecialItemListForcibly(AppCompatActivity activity) {
        if (specialItems != null) {
            specialItems.removeObservers(activity);
        }
        SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(getApplication()).edit();
        editor.remove("item-sp-list");
        editor.apply();
        specialItems = itemRepository.getSpecialItemList();
        return specialItems;
    }

    public LiveData<Resource<Bitmap>> getItemIcon(int id) {
        if (itemIcons == null) {
            itemIcons = new SparseArray<>();
        }
        if (itemIcons.indexOfKey(id) < 0) {
            itemIcons.put(id, itemRepository.getItemIcon(id));
        }
        return itemIcons.get(id);
    }

    public LiveData<Resource<List<SummonerItem>>> getSummonerList() {
        if (summoners == null) {
            summoners = summonerRepository.getSummonerList();
        }
        return summoners;
    }

    public LiveData<Resource<List<SummonerItem>>> getSummonerListForcibly(AppCompatActivity activity) {
        if (summoners != null) {
            summoners.removeObservers(activity);
        }
        SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(getApplication()).edit();
        editor.remove("summoner-list");
        editor.apply();
        summoners = summonerRepository.getSummonerList();
        return summoners;
    }

    public LiveData<Resource<Bitmap>> getSummonerIcon(int id) {
        if (summonerIcons == null) {
            summonerIcons = new SparseArray<>();
        }
        if (summonerIcons.indexOfKey(id) < 0) {
            summonerIcons.put(id, summonerRepository.getSummonerIcon(id));
        }
        return summonerIcons.get(id);
    }

    public LiveData<Resource<Bitmap>> getSummonerPicture(int id) {
        if (summonerPictures == null) {
            summonerPictures = new SparseArray<>();
        }
        if (summonerPictures.indexOfKey(id) < 0) {
            summonerPictures.put(id, summonerRepository.getSummonerPicture(id));
        }
        return summonerPictures.get(id);
    }

    public LiveData<Resource<List<InscriptionItem>>> getInscriptionList() {
        if (inscriptions == null) {
            inscriptions = inscriptionRepository.getInscriptionList();
        }
        return inscriptions;
    }

    public LiveData<Resource<Bitmap>> getInscriptionIcon(int id) {
        if (inscriptionIcons == null) {
            inscriptionIcons = new SparseArray<>();
        }
        if (inscriptionIcons.indexOfKey(id) < 0) {
            inscriptionIcons.put(id, inscriptionRepository.getInscriptionIcon(id));
        }
        return inscriptionIcons.get(id);
    }

    public LiveData<List<Pair<CollectionItem, ? extends ListItem>>> getCollectionList(AppCompatActivity activity) {
        collections = collectionRepository.getCollectionList(activity);
        return collections;
    }


    public boolean isExistCollection(int id) {
        return collectionRepository.isExistCollection(id);
    }

    public boolean addCollection(CollectionItem item) {
        return collectionRepository.addCollection(item);
    }

    public boolean updateCollection(CollectionItem item) {
        return collectionRepository.updateCollection(item);
    }

    public boolean removeCollection(int id) {
        return collectionRepository.removeCollection(id);
    }
}
