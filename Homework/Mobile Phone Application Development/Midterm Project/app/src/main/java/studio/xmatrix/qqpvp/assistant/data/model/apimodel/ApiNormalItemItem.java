package studio.xmatrix.qqpvp.assistant.data.model.apimodel;

import com.google.gson.annotations.SerializedName;

import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;

public class ApiNormalItemItem {

    @SerializedName("item_id")
    private int id;
    @SerializedName("item_name")
    private String name;
    @SerializedName("item_type")
    private int type;
    @SerializedName("price")
    private int price;
    @SerializedName("total_price")
    private int totalPrice;
    @SerializedName("des1")
    private String effect;
    @SerializedName("des2")
    private String passiveEffect;

    private String getType() {
        switch (type) {
            case 1:
                return "攻击";
            case 2:
                return "法术";
            case 3:
                return "防御";
            case 4:
                return "移动";
            case 5:
                return "打野";
            case 7:
                return "辅助";
            default:
                return "";
        }
    }

    public ItemItem toItemItem() {
        if (effect != null) {
            effect = effect.replace("\n", "");
            effect = effect.replace(" ", "");
            effect = effect.replace("<p>", "");
            effect = effect.replace("</p>", "");
            effect = effect.replace("<br>", "\n");
        }
        if (passiveEffect != null) {
            passiveEffect = passiveEffect.replace("\n", "");
            passiveEffect = passiveEffect.replace(" ", "");
            passiveEffect = passiveEffect.replace("<p>", "");
            passiveEffect = passiveEffect.replace("</p>", "");
            passiveEffect = passiveEffect.replace("<br>", "\n");
        }
        return new ItemItem(
                id,
                name,
                getType(),
                price,
                totalPrice,
                effect,
                passiveEffect
        );
    }
}
