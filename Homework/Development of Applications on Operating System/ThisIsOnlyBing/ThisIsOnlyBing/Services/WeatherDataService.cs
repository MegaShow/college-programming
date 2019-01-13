using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using ThisIsOnlyBing.Models;

using Windows.UI.Xaml.Controls;
using Windows.Web.Http;

namespace ThisIsOnlyBing.Services {
    public static class WeatherDataService {
        public static WeatherInfo WeatherInfo { get; set; }
        public static ObservableCollection<Weather> Data = new ObservableCollection<Weather>();

        public static void UpdateData() {
            Data.Clear();
            foreach (Weather item in WeatherInfo.result.weather) {
                Data.Add(item);
            }
        }
    }
}
