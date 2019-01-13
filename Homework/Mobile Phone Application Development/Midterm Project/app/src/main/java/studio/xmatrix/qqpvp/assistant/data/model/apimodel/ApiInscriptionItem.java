package studio.xmatrix.qqpvp.assistant.data.model.apimodel;

import com.google.gson.annotations.SerializedName;

import studio.xmatrix.qqpvp.assistant.data.model.InscriptionItem;

public class ApiInscriptionItem {

    @SerializedName("ming_id")
    private int id;

    @SerializedName("ming_name")
    private String name;
    @SerializedName("ming_des")
    private String description;

    public InscriptionItem toInscriptionItem() {
        description = description.replace("<p>", "");
        description = description.replace("</p>", "\n");
        if (description.lastIndexOf('\n') == description.length() - 1) {
            description = description.substring(0, description.length() - 1);
        }
        return new InscriptionItem(id, name, description);
    }
}
