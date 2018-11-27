package studio.xmatrix.qqpvp.assistant.data.model;

import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;
import io.objectbox.annotation.Index;
import io.objectbox.annotation.Unique;

@Entity
public class ItemItem implements ListItem  {

    @Id
    long _id;

    @Unique
    @Index
    int id;
    String name;
    boolean special;
    String type;
    int price;
    int totalPrice;
    int level;
    String effect;
    String passiveEffect;

    public ItemItem() {
    }

    public ItemItem(int id, String name, String type, int price, int totalPrice, String effect, String passiveEffect) {
        this.id = id;
        this.name = name;
        this.special = false;
        this.type = type;
        this.price = price;
        this.totalPrice = totalPrice;
        this.level = 0;
        this.effect = effect;
        this.passiveEffect = passiveEffect;
    }

    public ItemItem(int id, String name, String type, int level, String effect, String passiveEffect) {
        this.id = id;
        this.name = name;
        this.special = true;
        this.type = type;
        this.price = 0;
        this.totalPrice = 0;
        this.level = level;
        this.effect = effect;
        this.passiveEffect = passiveEffect;
    }


    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public boolean getSpecial() {
        return special;
    }

    public String getType() {
        return type;
    }

    public int getPrice() {
        return price;
    }

    public int getTotalPrice() {
        return totalPrice;
    }

    public int getLevel() {
        return level;
    }

    public String getEffect() {
        return effect;
    }

    public String getPassiveEffect() {
        return passiveEffect;
    }


    public String toString() {
        String tEffect = effect == null ? null : effect.replace("\n", "\\n");
        String tPassiveEffect = passiveEffect == null ? null : passiveEffect.replace("\n", "\\n");
        return "id:" + id + ", name:" + name + ", special: " + special + ". type:" + type + ", price:" + price
                + ", totalPrice:" + totalPrice + ", level:" + level + ", effect:" + tEffect + ", passiveEffect:" + tPassiveEffect;
    }
}
