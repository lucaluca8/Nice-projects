using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Tema2.View
{
    /// <summary>
    /// Interaction logic for Gallery.xaml
    /// </summary>
    public partial class Gallery : Window
    {
        public string selected = "C:/Users/OMEN_PC1/source/repos" +
            "/Tema2/Tema2/Images/";
        public Gallery()
        {
            InitializeComponent();
        }
        private void Ok(object sender, RoutedEventArgs e)
        {
            if (Img1.IsChecked == true)
            {
                selected += "Img1.png";
            }
            else
            {
                if (Img2.IsChecked == true)
                {
                    selected += "Img2.jpg";
                }
                else
                {
                    if (Img3.IsChecked == true)
                    {
                        selected += "Img3.png";
                    }
                    else
                    {
                        if (Img4.IsChecked == true)
                        {
                            selected += "Img4.jpg";
                        }
                        else
                        {
                            if (Img5.IsChecked == true)
                            {
                                selected += "Img5.jpg";
                            }
                        }
                    }
                }
            }

            Close();
        }
    }
}
