package studio.xmatrix.qqpvp.assistant.data.model.apimodel;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;

public class ApiSpecialItemList {

    @SerializedName("bjtwzbsy_ba")
    private List<ApiSpecialItemItem> items;

    public List<ItemItem> toItemList() {
        List<ItemItem> list = new ArrayList<>();
        for (ApiSpecialItemItem item : items) {
            list.add(item.toItemItem());
        }
        return list;
    }

    private static class ApiSpecialItemItem {

        @SerializedName("itemidzbid_4a")
        private int id;
        @SerializedName("itemnamezwm_cd")
        private String name;
        @SerializedName("itemtypezbfl_30")
        private int type;
        @SerializedName("itemlvzbdj_96")
        private String level;
        @SerializedName("des1zbsx_a6")
        private String effect;
        @SerializedName("des2fszx_cc")
        private String passiveEffect;

        private String getType() {
            switch (type) {
                case 1:
                    return "装备";
                case 2:
                    return "道具";
                case 3:
                    return "额外技能";
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
            int index = this.level.indexOf("级");
            int level;
            try {
                if (index < 0) {
                    level = Integer.parseInt(this.level);
                } else {
                    level = Integer.parseInt(this.level.substring(0, index));
                }
            } catch (NumberFormatException e) {
                level = 0;
            }
            return new ItemItem(
                    id,
                    name,
                    getType(),
                    level,
                    effect,
                    passiveEffect
            );
        }
    }
}
