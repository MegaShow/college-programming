package studio.xmatrix.qqpvp.assistant.data.model.apimodel;

import com.google.gson.annotations.SerializedName;

import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;

public class ApiHeroListItem {

    @SerializedName("ename")
    private int id;
    // @SerializedName("skin_name")
    // private String skin;
    // pay_type: 10 - 周免英雄, 11 - 新手推荐
    @SerializedName("pay_type")
    private PayType payType;
    // new_type: 0 - 旧英雄, 1 - 新英雄
    @SerializedName("new_type")
    private int newType;
    // type: 3 - 坦克, 1 - 战士, 4 - 刺客, 2 - 法师, 5 - 射手, 6 - 辅助
    @SerializedName("hero_type")
    private int heroType;
    @SerializedName("hero_type2")
    private int heroType2;
    @SerializedName("cname")
    private String name;
    @SerializedName("title")
    private String title;

    public static class PayType {
        public String ctx;
    }

    private String getTypeName(int i) {
        switch (i) {
            case 1:
                return "战士";
            case 2:
                return "法师";
            case 3:
                return "坦克";
            case 4:
                return "刺客";
            case 5:
                return "射手";
            case 6:
                return "辅助";
            default:
                return null;
        }
    }

    private String getTypes() {
        String types = null;
        if (heroType != 0) {
            types = getTypeName(heroType);
        }
        if (heroType2 != 0) {
            if (types == null) {
                types = getTypeName(heroType2);
            } else {
                types += "|" + getTypeName(heroType2);
            }
        }
        return types;
    }

    public HeroListItem toHeroListItem() {
        boolean isFree, isRecommend;
        if (payType == null || payType.ctx == null) {
            isFree = isRecommend = false;
        } else {
            isFree = payType.ctx.contains("10");
            isRecommend = payType.ctx.contains("11");
        }
        return new HeroListItem(
                id,
                name,
                title,
                getTypes(),
                isFree,
                newType == 1,
                isRecommend
        );
    }
}
