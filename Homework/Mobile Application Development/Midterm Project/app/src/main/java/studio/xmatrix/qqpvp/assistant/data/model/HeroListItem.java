package studio.xmatrix.qqpvp.assistant.data.model;

import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;
import io.objectbox.annotation.Index;
import io.objectbox.annotation.Unique;

@Entity
public class HeroListItem implements ListItem {

    @Id
    long _id;

    @Unique
    @Index
    int id;
    String name;
    String defaultSkin;
    String types;
    boolean freeHero;
    boolean newHero;
    boolean recommendHero;

    public HeroListItem() {}

    public HeroListItem(int id, String name, String defaultSkin, String types, boolean freeHero, boolean newHero, boolean recommendHero) {
        this.id = id;
        this.name = name;
        this.defaultSkin = defaultSkin;
        this.types = types;
        this.freeHero = freeHero;
        this.newHero = newHero;
        this.recommendHero = recommendHero;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDefaultSkin() {
        return defaultSkin;
    }

    public String getTypes() {
        return types;
    }

    public boolean isRecommendHero() {
        return recommendHero;
    }

    public boolean isFreeHero() {
        return freeHero;
    }

    public boolean isNewHero() {
        return newHero;
    }
}
