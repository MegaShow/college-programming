package com.icytown.course.experimentthree.storage2.data.database;

import android.app.Application;
import android.arch.persistence.room.Database;
import android.arch.persistence.room.Room;
import android.arch.persistence.room.RoomDatabase;

import com.icytown.course.experimentthree.storage2.data.dao.CommentDao;
import com.icytown.course.experimentthree.storage2.data.dao.LikeDao;
import com.icytown.course.experimentthree.storage2.data.dao.UserDao;
import com.icytown.course.experimentthree.storage2.data.model.Comment;
import com.icytown.course.experimentthree.storage2.data.model.CommentLike;
import com.icytown.course.experimentthree.storage2.data.model.User;

@Database(entities = {User.class, Comment.class, CommentLike.class}, version = 1, exportSchema = false)
public abstract class StorageDatabase extends RoomDatabase {
    
    public abstract UserDao userDao();
    public abstract CommentDao commentDao();
    public abstract LikeDao likeDao();

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
