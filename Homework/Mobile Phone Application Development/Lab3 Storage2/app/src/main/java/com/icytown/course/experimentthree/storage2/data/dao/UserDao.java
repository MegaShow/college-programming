package com.icytown.course.experimentthree.storage2.data.dao;

import android.arch.persistence.room.Dao;
import android.arch.persistence.room.Insert;
import android.arch.persistence.room.Query;

import com.icytown.course.experimentthree.storage2.data.model.User;


@Dao
public interface UserDao {

    @Query("SELECT * FROM User WHERE User.name = :name")
    User getUserByNameSync(String name);

    @Insert
    void createUser(User user);
}
