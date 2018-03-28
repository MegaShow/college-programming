using SylToDo.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media.Imaging;

namespace SylToDo.ViewModels {
    public class TodoItemViewModel {
        private ObservableCollection<TodoItem> collection = new ObservableCollection<TodoItem>();
        public ObservableCollection<TodoItem> Collection {
            get {
                SetFilterCollection();
                return collection;
            }
        }

        public TodoItemViewModel() {
            this.Add("你好，世界", "这是一条已完成已过期的TODO", new DateTime(2018, 1, 1), true);
            this.Add("你好，Mega", "这是一条不知道说什么的TODO", DateTime.Now.Date, false, new BitmapImage(new Uri("ms-appx:///Assets/1.png")));
            this.Add("你好，Ruby & Rust", "我大Ruby~", DateTime.Now.Date + new TimeSpan(3, 0, 0, 0), false, new BitmapImage(new Uri("ms-appx:///Assets/2.jpg")));
            this.Add("你好, Zhenly", "膜一下大佬！", DateTime.Now.Date + new TimeSpan(15, 0, 0, 0));
        }

        public void SetFilterCollection() {
            switch (AppMain.Current.Type) {
                case 0: // 所有
                    foreach (TodoItem item in collection) {
                        item.visibility = Visibility.Visible;
                    }
                    break;
                case 1: // 今天
                    foreach (TodoItem item in collection) {
                        if (item.dueDate.Date == DateTime.Now.Date) {
                            item.visibility = Visibility.Visible;
                        } else {
                            item.visibility = Visibility.Collapsed;
                        }
                    }
                    break;
                case 2: // 最近7天
                    foreach (TodoItem item in collection) {
                        if (item.dueDate.Date > DateTime.Now.Date && item.dueDate.Date - DateTime.Now.Date < new TimeSpan(7, 0, 0, 0)) {
                            item.visibility = Visibility.Visible;
                        } else {
                            item.visibility = Visibility.Collapsed;
                        }
                    }
                    break;
                case 5: // 已完成
                    foreach (TodoItem item in collection) {
                        if (item.isChecked) {
                            item.visibility = Visibility.Visible;
                        } else {
                            item.visibility = Visibility.Collapsed;
                        }
                    }
                    break;
            }
        }

        public void Add(string title, string description, DateTime dueDate, bool isChecked = false, BitmapImage image = null) {
            collection.Add(new TodoItem(title, description, dueDate, isChecked, image));
        }

        public void Remove(int itemIndex) {
            collection.RemoveAt(itemIndex);
        }

        public void Update(int itemIndex, string title, string description, DateTime dueDate, BitmapImage image) {
            bool isChecked = collection[itemIndex].isChecked;
            Remove(itemIndex);
            collection.Insert(itemIndex, new TodoItem(title, description, dueDate, isChecked, image));
        }
    }
}
