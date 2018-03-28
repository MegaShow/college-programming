using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace SylToDo {
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class AppMain : Page {
        public static AppMain Current;
        public int Type = 0;

        public AppMain() {
            this.InitializeComponent();
            Current = this;
            contentFrame.Navigate(typeof(TodoMain));
            ApplicationView.GetForCurrentView().SetPreferredMinSize(new Size(420, 300));
        }

        private async void NavigationView_ItemInvoked(NavigationView sender, NavigationViewItemInvokedEventArgs args) {
            //先判断是否选中了setting
            if (args.IsSettingsInvoked) {
                return;
            } else {
                //选中项的内容
                switch (args.InvokedItem) {
                    case "所有":
                        Type = 0;
                        break;
                    case "今天":
                        Type = 1;
                        break;
                    case "最近7天":
                        Type = 2;
                        break;
                    case "已完成":
                        Type = 5;
                        break;
                    default:
                        Type = 0;
                        break;
                }
                TodoList.Current.list.ItemsSource = null;
                TodoList.Current.list.ItemsSource = TodoMain.Current.ViewModel.Collection;
            }
        }
    }
}
