package studio.xmatrix.qqpvp.assistant.data.model;

import java.util.Date;

import io.objectbox.annotation.Convert;
import io.objectbox.annotation.Entity;
import io.objectbox.annotation.Id;
import io.objectbox.annotation.Index;
import io.objectbox.annotation.Unique;
import studio.xmatrix.qqpvp.assistant.data.common.converter.CollectionTypeConverter;
import studio.xmatrix.qqpvp.assistant.data.common.converter.TimestampConverter;

@Entity
public class CollectionItem {

    @Id
    long _id;

    @Unique
    @Index
    int id;

    public enum Type {
        Hero, Item, SpecialItem, Summoner
    }

    @Convert(converter = CollectionTypeConverter.class, dbType = Integer.class)
    Type type;
    String remark;
    @Convert(converter = TimestampConverter.class, dbType = Long.class)
    Date time;

    public CollectionItem() {}

    public CollectionItem(int id, Type type, String remark, Date time) {
        this.id = id;
        this.type = type;
        this.remark = remark;
        this.time = time;
    }

    public long getObjectId() {
        return _id;
    }

    public int getId() {
        return id;
    }

    public Type getType() {
        return type;
    }

    public String getRemark() {
        return remark;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public Date getTime() {
        return time;
    }
}
