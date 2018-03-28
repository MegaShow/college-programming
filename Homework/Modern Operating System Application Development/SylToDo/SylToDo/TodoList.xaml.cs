using SylToDo.Models;
using SylToDo.ViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace SylToDo {
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class TodoList : Page {
        public static TodoList Current;
        public int SelectItem = -1;

        private TodoItemViewModel ViewModel {
            get { return TodoMain.Current.ViewModel; }
        }

        public TodoList() {
            this.InitializeComponent();
            Current = this;
            this.SizeChanged += (s, e) => {
                string state;
                if (list.ActualWidth > 0 && list.ActualWidth < 420) {
                    state = "MinListState";
                } else {
                    state = "FullListState";
                }
                VisualStateManager.GoToState(this, state, true);
            };
        }

        private void ListSelect(object sender, SelectionChangedEventArgs e) {
            // TodoItem item = list.SelectedItem as TodoItem;
            SelectItem = list.SelectedIndex;
            if (SelectItem == -1) {
                TodoDetail.Current.Hide();
                return;
            }
            double width = Window.Current.Bounds.Width;
            if (width > 0 && width < 960) {
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Visible;
                TodoMain.Current.State = "OnlyDetailState";
                TodoMain.Current.UpdateState();
            }
            TodoDetail.Current.SetNewStateOrNot(false);
            TodoDetail.Current.Update(SelectItem);
        }
    }
}
