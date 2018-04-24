using System;

using Windows.UI.Xaml.Controls;

namespace ThisIsOnlyBing.Models {
    public class WeatherInfo {
        public class Result {
            public Object realtime { get; set; }
            public Object life { get; set; }
            public Weather[] weather { get; set; }
            public Object pm25 { get; set; }
            public Object isForeign { get; set; }

        }

        public Result result { get; set; }
        public int error_code { get; set; }
        public string reason { get; set; }
    }

    public class Weather {
        public class Info {
            public string[] dawn { get; set; }
            public string[] day { get; set; }
            public string[] night { get; set; }
        }

        public string date { get; set; }
        public string week { get; set; }
        public string nongli { get; set; }
        public Info info { get; set; }
    }
}
