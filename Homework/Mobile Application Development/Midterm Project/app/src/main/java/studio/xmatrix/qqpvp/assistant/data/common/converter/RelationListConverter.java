package studio.xmatrix.qqpvp.assistant.data.common.converter;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.util.List;

import io.objectbox.converter.PropertyConverter;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;

public class RelationListConverter implements PropertyConverter<List<HeroDetailItem.Relation>, String> {

    private Gson gson = new Gson();

    @Override
    public List<HeroDetailItem.Relation> convertToEntityProperty(String databaseValue) {
        return gson.fromJson(databaseValue, new TypeToken<List<HeroDetailItem.Relation>>() {
        }.getType());
    }

    @Override
    public String convertToDatabaseValue(List<HeroDetailItem.Relation> entityProperty) {
        return gson.toJson(entityProperty);
    }
}
