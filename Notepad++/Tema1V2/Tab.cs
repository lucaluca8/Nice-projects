using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema1V2
{
    public class Tab : INotifyPropertyChanged
    {

        private string _header;
        public string header
        {
            get { return _header; }
            set
            {
                _header = value;
                OnPropertyChanged(nameof(header));
            }
        }

        private string _content;
        public string content
        {
            get { return _content; }
            set
            {
                _content = value;
                if (header.Contains("*") == false)
                    header += "*";
                OnPropertyChanged("textbox");
            }
        }
        public string fullPath { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
