package studio.xmatrix.qqpvp.assistant.data.common.converter;

import java.util.Date;

import io.objectbox.converter.PropertyConverter;

public class TimestampConverter implements PropertyConverter<Date, Long> {

    @Override
    public Date convertToEntityProperty(Long databaseValue) {
        return databaseValue == null ? null : new Date(databaseValue);
    }

    @Override
    public Long convertToDatabaseValue(Date entityProperty) {
        return entityProperty == null ? null : entityProperty.getTime();
    }
}
