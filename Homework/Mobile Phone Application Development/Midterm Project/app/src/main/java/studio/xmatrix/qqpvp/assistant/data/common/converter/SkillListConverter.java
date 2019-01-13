package studio.xmatrix.qqpvp.assistant.data.common.converter;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.util.List;

import io.objectbox.converter.PropertyConverter;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;

public class SkillListConverter implements PropertyConverter<List<HeroDetailItem.Skill>, String> {

    private Gson gson = new Gson();

    @Override
    public List<HeroDetailItem.Skill> convertToEntityProperty(String databaseValue) {
        return gson.fromJson(databaseValue, new TypeToken<List<HeroDetailItem.Skill>>() {
        }.getType());
    }

    @Override
    public String convertToDatabaseValue(List<HeroDetailItem.Skill> entityProperty) {
        return gson.toJson(entityProperty);
    }
}
