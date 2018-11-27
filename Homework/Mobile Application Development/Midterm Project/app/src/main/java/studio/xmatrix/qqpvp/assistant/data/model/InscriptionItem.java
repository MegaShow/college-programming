package studio.xmatrix.qqpvp.assistant.data.model;

import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;
import io.objectbox.annotation.Index;
import io.objectbox.annotation.Unique;

@Entity
public class InscriptionItem {

    @Id
    long _id;

    @Unique
    @Index
    int id;
    String name;
    String description;

    public InscriptionItem() {}

    public InscriptionItem(int id, String name, String description) {
        this.id = id;
        this.name = name;
        this.description = description;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }
}
