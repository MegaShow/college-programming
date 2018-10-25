package com.icytown.course.experimentone.repository;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MutableLiveData;
import android.content.Context;
import android.content.res.XmlResourceParser;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.model.FoodItem;

import java.util.ArrayList;
import java.util.List;

public class FoodListRepository {

    private Context mContext;

    public FoodListRepository(Context context) {
        mContext = context;
    }

    public LiveData<List<FoodItem>> getFoodList() {
        final MutableLiveData<List<FoodItem>> data = new MutableLiveData<>();
        final List<FoodItem> foodList;
        try {
            XmlResourceParser xml = mContext.getResources().getXml(R.xml.foods);
            foodList = parse(xml);
            data.setValue(foodList);
            return data;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private List<FoodItem> parse(XmlResourceParser parser) throws Exception {
        List<FoodItem> list = new ArrayList<>();
        FoodItem item = null;
        int eventType = parser.getEventType();
        while (eventType != XmlResourceParser.END_DOCUMENT) {
            switch (eventType) {
                case XmlResourceParser.START_TAG:
                    if (parser.getName().equals("food")) {
                        item = new FoodItem();
                    } else {
                        assert item != null;
                        switch (parser.getName()) {
                            case "name":
                                item.setName(parser.nextText());
                                break;
                            case "type":
                                item.setType(parser.nextText());
                                break;
                            case "detail":
                                item.setDetail(parser.nextText());
                                break;
                            case "color":
                                item.setColor(parser.nextText());
                                break;
                        }
                    }
                    break;
                case XmlResourceParser.END_TAG:
                    if (parser.getName().equals("food")) {
                        list.add(item);
                    }
                    break;
            }
            eventType = parser.next();
        }
        return list;
    }
}
