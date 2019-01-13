package studio.xmatrix.qqpvp.assistant.data.model;

// SearchItem 搜索项目
public class SearchItem {
    
    private int id;
    private String name;
    private String title;
    private ItemType type;

    // 1 - 英雄， 2 - 召唤师技能， 3 - 道具， 4 - 边境突围道具
    public enum ItemType {
        HERO,
        SKILL,
        ITEM,
        SPITEM
    }

    public SearchItem(int id, String name, String title, ItemType type) {
        this.id = id;
        this.name = name;
        this.title = title;
        this.type = type;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getTitle() {
        return title;
    }

    public ItemType getType() {
        return type;
    }

}
