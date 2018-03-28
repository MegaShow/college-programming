using SylToDo.ViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace SylToDo {
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class TodoMain : Page {
        public static TodoMain Current;
        public TodoItemViewModel ViewModel = null;

        private string state;
        public string State {
            get { return state; }
            set { state = value; }
        }

        public TodoMain() {
            this.InitializeComponent();
            Current = this;
            if (ViewModel == null) {
                ViewModel = new TodoItemViewModel();
            }
            this.SizeChanged += (s, e) => {
                if (e.NewSize.Width >= 0 && e.NewSize.Width < 960) {
                    if (state != "OnlyDetailState") {
                        state = "OnlyListState";
                    }
                } else if (e.NewSize.Width >= 960) {
                    SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Collapsed;
                    if (state == "OnlyListState") {
                        if (TodoList.Current.SelectItem == -1) {
                            TodoDetail.Current.Hide();
                        } else {
                            TodoDetail.Current.Show();
                            TodoDetail.Current.Update(TodoList.Current.SelectItem);
                        }
                    }
                    state = "ListAndDetailState";
                }
                this.UpdateState();
            };
            listFrame.Navigate(typeof(TodoList));
            detailFrame.Navigate(typeof(TodoDetail));

            SystemNavigationManager.GetForCurrentView().BackRequested += OnBackRequested;
        }

        public void UpdateState() {
            VisualStateManager.GoToState(this, state, true);
        }

        private void OnBackRequested(object sender, BackRequestedEventArgs e) {
            if (listFrame != null) {
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Collapsed;
                TodoDetail.Current.Clear();
                state = "OnlyListState";
                this.UpdateState();
            }
        }

        private void AppBarButton_Click(object sender, RoutedEventArgs e) {
            double width = Window.Current.Bounds.Width;
            if (width > 0 && width < 960) {
                state = "OnlyDetailState";
                this.UpdateState();
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                        AppViewBackButtonVisibility.Visible;
            }
            TodoDetail.Current.SetNewStateOrNot(true);
            TodoDetail.Current.Clear();
        }
    }
}
