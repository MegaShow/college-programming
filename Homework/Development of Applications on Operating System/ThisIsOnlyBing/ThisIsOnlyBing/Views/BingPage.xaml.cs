using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Xml;
using ThisIsOnlyBing.Models;
using ThisIsOnlyBing.Services;
using Windows.System;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Web.Http;

namespace ThisIsOnlyBing.Views {
    public sealed partial class BingPage : Page, INotifyPropertyChanged {
        private bool isBackgroundTypeXml = false;

        public BingPage() {
            InitializeComponent();
            GetBackgroundUri();
        }

        public async void GetBackgroundUri() {
            if (isBackgroundTypeXml == true) {
                try {
                    var httpClient = new HttpClient();
                    Uri uri = new Uri("https://www.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1");
                    HttpResponseMessage httpResponse = await httpClient.GetAsync(uri);
                    httpResponse.EnsureSuccessStatusCode();
                    string responseBody = await httpResponse.Content.ReadAsStringAsync();
                    var xml = new XmlDocument();
                    xml.LoadXml(responseBody);
                    XmlNode node = xml.GetElementsByTagName("url")[0];
                    var image = new BitmapImage(new Uri("https://cn.bing.com" + node.InnerText));
                    background.ImageSource = image;
                } catch (Exception e) {
                    Debug.WriteLine($"{e.ToString()}");
                }
                return;
            }
            try {
                var httpClient = new HttpClient();
                Uri uri = new Uri("https://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1");
                HttpResponseMessage httpResponse = await httpClient.GetAsync(uri);
                httpResponse.EnsureSuccessStatusCode();
                string responseBody = await httpResponse.Content.ReadAsStringAsync();
                BingPicture bingPicture = JsonConvert.DeserializeObject<BingPicture>(responseBody);
                var image = new BitmapImage(new Uri("https://cn.bing.com" + bingPicture.images[0].url));
                background.ImageSource = image;
            } catch (Exception e) {
                Debug.WriteLine($"{e.ToString()}");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void Set<T>(ref T storage, T value, [CallerMemberName]string propertyName = null) {
            if (Equals(storage, value)) {
                return;
            }

            storage = value;
            OnPropertyChanged(propertyName);
        }

        private void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));

        private void AppBarButton_Click_Browser(object sender, Windows.UI.Xaml.RoutedEventArgs e) {
            NavigationService.Frame.Navigate(typeof(WeatherPage));
        }

        private void TextBox_KeyDown_Search(object sender, Windows.UI.Xaml.Input.KeyRoutedEventArgs e) {
            TextBox textBox = sender as TextBox;
            if (e.Key == VirtualKey.Enter && textBox.Text.Length != 0) {
                NavigationService.Frame.Navigate(typeof(BrowserPage), textBox.Text);
            }
        }
    }
}
