using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema2.Model
{
    class Users: INotifyPropertyChanged
    {

        public event PropertyChangedEventHandler PropertyChanged;
        private string _Username;
        public string Username 
        { get 
            { 
                return _Username;
            }
            set 
            { 
                _Username = value;
                OnPropertyChanged(nameof(Username)); 
            } 
        }

        private string _Image;
        public string Image {
            get
            {
                return _Image;
            }
            set
            {
                _Image = value;
            }
        }
        public Users(string name, string image)
        {
            this.Username = name;
            this.Image = image;
        }
        private void OnPropertyChanged(string propertyName)
        {
            VerifyPropertyName(propertyName);
            var handler = PropertyChanged;
            handler?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        private void VerifyPropertyName(string propertyName)
        {
            if (TypeDescriptor.GetProperties(this)[propertyName] == null)
                throw new ArgumentNullException(GetType().Name + " does not contain property: " + propertyName);
        }

    }
}
