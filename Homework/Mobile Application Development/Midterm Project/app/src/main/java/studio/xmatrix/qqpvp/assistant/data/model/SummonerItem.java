package studio.xmatrix.qqpvp.assistant.data.model;

import android.support.annotation.NonNull;

import com.google.gson.annotations.SerializedName;

import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;
import io.objectbox.annotation.Index;
import io.objectbox.annotation.Unique;

@Entity
public class SummonerItem implements ListItem  {

    @Id
    long _id;

    @Unique
    @Index
    @SerializedName("summoner_id")
    int id;
    @SerializedName("summoner_name")
    String name;
    @SerializedName("summoner_rank")
    String rank;
    @SerializedName("summoner_description")
    String description;

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getRank() {
        return rank;
    }

    public String getDescription() {
        return description;
    }

    @NonNull
    public String toString() {
        return "id:" + id + ", name:" + name + ", rank:" + rank + ", description:" + description;
    }

}
