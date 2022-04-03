using System;
using System.Collections.Generic;
using System.IO;
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
using System.Windows.Threading;
using Tema2.Model;

namespace Tema2.View
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Window
    {
        DispatcherTimer timer;
        private int time = 100;
        public string playerName;
        public Game(string playerName)
        {
            this.playerName = playerName;
            InitializeComponent();
            Username.Text = playerName;
            System.Windows.MessageBox.Show("Choose a category from the Categories menu");
        }
        private void MenuItem_About(object sender, RoutedEventArgs e)
        {
            System.Windows.MessageBox.Show("Nume: Lazar\nPrenume: " +
               "Luca\nEmail: luca.lazar@student.unitbv.ro", "About", MessageBoxButton.OK);
        }

        //------------------------------------------------------------------
        //-------------------------------------------------------------------
        private void Start_Click(object sender, RoutedEventArgs e)
        {
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Ticker;
            timer.Start();
        }
        private void Ticker(object sender, EventArgs e)
        {
            time--;
            if (time > 0)
            {
                TimerLabel.Content = string.Format("0{0}:{1}", time / 60, time % 60);
            }
            else
            {
                timer.Stop();
                MessageBox.Show("Time's out.You lose", "About", MessageBoxButton.OK);
                string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/PlayerStatistics.txt";
                string[] anotherTextFile = File.ReadAllLines(path);
                string path1 = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
                string[] textFile = File.ReadAllLines(path1);
                Player player = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));               
                using (StreamWriter outputFile = new StreamWriter(path))
                {
                    int counter = 4;
                    foreach (string line in anotherTextFile)
                    {
                        if (line == player.username)
                            counter = 3;
                        if (counter == 3)
                        {
                            outputFile.WriteLine(line);
                            counter -= 1;
                        }
                        else if (counter == 2)
                        {
                            outputFile.WriteLine(player.gamesPlayed+1);
                            counter -= 1;
                        }
                        else if (counter == 1)
                        {
                            outputFile.WriteLine(player.gamesWon);
                            counter -= 1;
                        }
                        else
                        {
                            Console.WriteLine(line);
                            outputFile.WriteLine(line);
                        }
                    }
                }
                Close();   
            }
        }
        //THIS IS WHERE THE TIMER IS INITILISED------------------------------------------
        //-------------------------------------------------------------------------------
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}

