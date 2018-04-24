using Newtonsoft.Json;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Net.Http;
using System.Runtime.CompilerServices;
using System.Xml;
using ThisIsOnlyBing.Models;
using ThisIsOnlyBing.Services;
using Windows.System;
using Windows.UI.Xaml.Controls;

namespace ThisIsOnlyBing.Views {
    public sealed partial class WeatherPage : Page, INotifyPropertyChanged {
        private bool isWeatherTypeXml = true;
        private string apiKey = "616fcd1e6f444c0d8682192de79e4f00";

        public WeatherPage() {
            GetWeatherInfo();
            InitializeComponent();
        }

        public ObservableCollection<Weather> Source {
            get {
                return WeatherDataService.Data;
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

        private void TextBox_KeyDown(object sender, Windows.UI.Xaml.Input.KeyRoutedEventArgs e) {
            TextBox textBox = sender as TextBox;
            if (e.Key == VirtualKey.Enter && textBox.Text.Length != 0) {
                GetWeatherInfo(textBox.Text);
                textBox.Text = String.Empty;
            }
        }

        private async void GetWeatherInfo(string city = "广州") {
            if (isWeatherTypeXml == true) {
                try {
                    var httpClient = new HttpClient();
                    Uri uri = new Uri("http://api.avatardata.cn/Weather/Query?dtype=xml&key=" + apiKey + "&cityname=" + city);
                    HttpResponseMessage httpResponse = await httpClient.GetAsync(uri);
                    httpResponse.EnsureSuccessStatusCode();
                    string responseBody = await httpResponse.Content.ReadAsStringAsync();
                    var xml = new XmlDocument();
                    xml.LoadXml(responseBody);
                    XmlNodeList nodeList = xml.GetElementsByTagName("WeatherDetailObj");
                    WeatherDataService.WeatherInfo = new WeatherInfo();
                    WeatherDataService.WeatherInfo.result = new WeatherInfo.Result();
                    WeatherDataService.WeatherInfo.result.weather = new Weather[nodeList.Count];
                    for (int i = 0; i < nodeList.Count; i++) {
                        WeatherDataService.WeatherInfo.result.weather[i] = new Weather();
                        foreach (XmlNode node in nodeList[i].ChildNodes) {
                            switch (node.Name) {
                                case "date":
                                    WeatherDataService.WeatherInfo.result.weather[i].date = node.InnerText;
                                    break;
                                case "week":
                                    WeatherDataService.WeatherInfo.result.weather[i].week = node.InnerText;
                                    break;
                                case "nongli":
                                    WeatherDataService.WeatherInfo.result.weather[i].nongli = node.InnerText;
                                    break;
                                case "info":
                                    WeatherDataService.WeatherInfo.result.weather[i].info = new Weather.Info();
                                    XmlNodeList info = node.ChildNodes;
                                    foreach (XmlNode infoNode in info) {
                                        if (infoNode.Name == "day") {
                                            WeatherDataService.WeatherInfo.result.weather[i].info.day = new string[6];
                                            WeatherDataService.WeatherInfo.result.weather[i].info.day[1] = infoNode.ChildNodes[1].InnerText;
                                            WeatherDataService.WeatherInfo.result.weather[i].info.day[2] = infoNode.ChildNodes[2].InnerText;
                                        } else if (infoNode.Name == "night") {
                                            WeatherDataService.WeatherInfo.result.weather[i].info.night = new string[6];
                                            WeatherDataService.WeatherInfo.result.weather[i].info.night[2] = infoNode.ChildNodes[2].InnerText;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                } catch (Exception e) {
                    Debug.WriteLine($"{e.ToString()}");
                }
                UpdateData(city);
                return;
            }
            try {
                var httpClient = new HttpClient();
                Uri uri = new Uri("http://api.avatardata.cn/Weather/Query?key=" + apiKey + "&cityname=" + city);
                HttpResponseMessage httpResponse = await httpClient.GetAsync(uri);
                httpResponse.EnsureSuccessStatusCode();
                string responseBody = await httpResponse.Content.ReadAsStringAsync();
                WeatherDataService.WeatherInfo = JsonConvert.DeserializeObject<WeatherInfo>(responseBody);
            } catch (Exception e) {
                Debug.WriteLine($"{e.ToString()}");
            }
            UpdateData(city);
        }

        private void UpdateData(string city) {
            WeatherDataService.UpdateData();
            if (Source.Count == 0) {
                textBlock.Text = $"找不到 \"{city}\" 的信息";
            } else {
                textBlock.Text = city;
            }
        }
    }
}
