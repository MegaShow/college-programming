package studio.xmatrix.qqpvp.assistant.data.common.converter;

import io.objectbox.converter.PropertyConverter;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;

public class CollectionTypeConverter implements PropertyConverter<CollectionItem.Type, Integer>{

    @Override
    public CollectionItem.Type convertToEntityProperty(Integer databaseValue) {
        switch(databaseValue) {
            case 0: return CollectionItem.Type.Hero;
            case 1: return CollectionItem.Type.Item;
            case 2: return CollectionItem.Type.Summoner;
            case 3: return CollectionItem.Type.SpecialItem;
            default: return null;
        }
    }

    @Override
    public Integer convertToDatabaseValue(CollectionItem.Type entityProperty) {
        switch(entityProperty) {
            case Hero: return 0;
            case Item: return 1;
            case Summoner: return 2;
            case SpecialItem: return 3;
            default: return null;
        }
    }
}
