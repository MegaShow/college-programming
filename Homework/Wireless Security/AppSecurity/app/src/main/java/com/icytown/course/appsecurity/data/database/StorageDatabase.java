package com.icytown.course.appsecurity.data.database;

import android.app.Application;
import android.arch.persistence.room.Database;
import android.arch.persistence.room.Room;
import android.arch.persistence.room.RoomDatabase;

import com.icytown.course.appsecurity.data.dao.UserDao;
import com.icytown.course.appsecurity.data.model.User;


@Database(entities = {User.class}, version = 1, exportSchema = false)
public abstract class StorageDatabase extends RoomDatabase {
    
    public abstract UserDao userDao();

    public static class Helper {

        private static volatile StorageDatabase database;

        public static StorageDatabase getDatabase(Application app) {
            if (database == null) {
                synchronized (Helper.class) {
                    if (database == null) {
                        database = Room.databaseBuilder(app, StorageDatabase.class, "database.db").allowMainThreadQueries().build();
                    }
                }
            }
            return database;
        }
    }
}
