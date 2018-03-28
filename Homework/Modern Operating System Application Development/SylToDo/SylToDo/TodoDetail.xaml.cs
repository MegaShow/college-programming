using SylToDo.Models;
using SylToDo.ViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace SylToDo {
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class TodoDetail : Page {
        public static TodoDetail Current;
        public bool isNew = true;
        
        private TodoItemViewModel ViewModel = TodoMain.Current.ViewModel;

        public TodoDetail() {
            this.InitializeComponent();
            Current = this;
        }

        public void Show() {
            blank.Visibility = Visibility.Collapsed;
            edit.Visibility = Visibility.Visible;
        }

        public void Hide() {
            blank.Visibility = Visibility.Visible;
            edit.Visibility = Visibility.Collapsed;
        }

        public void Update(int itemIndex) {
            image.Source = ViewModel.Collection[itemIndex].image;
            title.Text = ViewModel.Collection[itemIndex].title;
            description.Text = ViewModel.Collection[itemIndex].description;
            dueDate.Date = ViewModel.Collection[itemIndex].dueDate.Date;
        }

        public void Clear() {
            image.Source = new BitmapImage(new Uri("ms-appx:///Assets/Square150x150Logo.scale-200.png"));
            title.Text = String.Empty;
            description.Text = String.Empty;
            dueDate.Date = DateTime.Now.Date;
        }

        public void SetNewStateOrNot(bool isNewOrNot) {
            Show();
            isNew = isNewOrNot;
            if (isNew == true) {
                button_create_edit.Content = "Create";
                button_cancel_delete.Content = "Cancel";
            } else {
                button_create_edit.Content = "Edit";
                button_cancel_delete.Content = "Delete";
            }
        }

        private async void Button_Upload_Image(object sender, RoutedEventArgs e) {
            FileOpenPicker picker = new FileOpenPicker();
            picker.ViewMode = PickerViewMode.Thumbnail;
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            picker.FileTypeFilter.Add(".jpg");
            picker.FileTypeFilter.Add(".jpeg");
            picker.FileTypeFilter.Add(".png");

            StorageFile file = await picker.PickSingleFileAsync();
            if (file != null) {
                // Application now has read/write access to the picked file
                try {
                    BitmapImage bitmapImage = new BitmapImage();
                    FileRandomAccessStream stream = (FileRandomAccessStream)await file.OpenAsync(FileAccessMode.Read);
                    bitmapImage.SetSource(stream);
                    image.Source = bitmapImage;
                } catch (Exception) {
                    MessageDialog msg = new MessageDialog("发生了些小问题，稍后试试吧", "Oops!");
                    await msg.ShowAsync();
                }
            }
        }

        private async void Button_Click_Create_Update(object sender, RoutedEventArgs e) {
            string output;
            if (title.Text.Length == 0) {
                output = "Title不能为空";
            } else if (description.Text.Length == 0) {
                output = "Description不能为空";
            } else if (dueDate.Date < DateTime.Now.Date) {
                output = "dueDate不合法";
            } else {
                if (isNew == true) {
                    ViewModel.Add(title.Text, description.Text, dueDate.Date.Date);
                    output = "创建TODO成功";
                } else {
                    ViewModel.Update(TodoList.Current.SelectItem, title.Text, description.Text, dueDate.Date.Date, image.Source as BitmapImage);
                    output = "修改TODO成功";
                }
                MessageDialog tMsg = new MessageDialog(output);
                await tMsg.ShowAsync();
                double width = Window.Current.Bounds.Width;
                if (width > 0 && width < 960) {
                    TodoMain.Current.State = "OnlyListState";
                    TodoMain.Current.UpdateState();
                    SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Collapsed;
                } else {
                    Hide();
                }
                return;
            }
            MessageDialog msg = new MessageDialog(output);
            await msg.ShowAsync();
        }

        private void Button_Click_Cancel_Delete(object sender, RoutedEventArgs e) {
            if (isNew == true) {
                this.Clear();
            } else {
                ViewModel.Remove(TodoList.Current.SelectItem);
            }
        }
    }
}
