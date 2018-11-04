package com.icytown.course.experimenttwo.data.model;

import android.databinding.BaseObservable;
import android.databinding.Bindable;
import android.graphics.Color;
import android.os.Parcel;
import android.os.Parcelable;

import com.icytown.course.experimenttwo.BR;

public class FoodItem extends BaseObservable implements Parcelable {

    private String name;
    private String type;
    private String detail;
    private int color;
    private boolean isStar = false;
    private boolean isCollect = false;

    public FoodItem() {
    }

    private FoodItem(Parcel source) {
        name = source.readString();
        type = source.readString();
        detail = source.readString();
        color = source.readInt();
        setStar(source.readByte() == 1);
        isCollect = source.readByte() == 1;
    }

    public FoodItem(String name, String type) {
        this.name = name;
        this.type = type;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getDetail() {
        return detail;
    }

    public void setDetail(String detail) {
        this.detail = detail;
    }

    public int getColor() {
        return color;
    }

    public void setColor(String colorString) {
        this.color = Color.parseColor(colorString);
    }

    @Bindable
    public boolean isStar() {
        return isStar;
    }

    public void setStar(boolean star) {
        isStar = star;
        notifyPropertyChanged(BR.star);
    }

    public boolean isCollect() {
        return isCollect;
    }

    public void setCollect(boolean collect) {
        isCollect = collect;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(name);
        dest.writeString(type);
        dest.writeString(detail);
        dest.writeInt(color);
        dest.writeByte((byte) (isStar ? 1 : 0));
        dest.writeByte((byte) (isCollect ? 1 : 0));
    }

    public static final Parcelable.Creator<FoodItem> CREATOR = new Parcelable.Creator<FoodItem>() {
        @Override
        public FoodItem createFromParcel(Parcel source) {
            return new FoodItem(source);
        }

        @Override
        public FoodItem[] newArray(int size) {
            return new FoodItem[size];
        }
    };
}
