using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media.Imaging;

namespace SylToDo.Models {
    public class TodoItem : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;

        protected bool SetProperty<T>(ref T storage, T value, [CallerMemberName] String propertyName = null) {
            if (object.Equals(storage, value)) return false;
            storage = value;
            OnPropertyChanged(propertyName);
            return true;
        }

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


        public string title;
        public string description;
        public DateTime dueDate;
        public BitmapImage image;

        public Visibility visibility;

        public bool isChecked;

        public TodoItem(string title, string description, DateTime dueDate, bool isChecked, BitmapImage image) {
            if (image == null) {
                this.image = new BitmapImage(new Uri("ms-appx:///Assets/Square150x150Logo.scale-200.png"));
            } else {
                this.image = image;
            }

            this.title = title;
            this.description = description;
            this.dueDate = dueDate;
            this.isChecked = isChecked;
        }
    }
}
