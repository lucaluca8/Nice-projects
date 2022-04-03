using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Markup;
using System.Xml;
using System.Xml.Linq;
using Tema2.Model;
using Tema2.View;

namespace Tema2.Services
{
    class Service:INotifyPropertyChanged
    {
        //----------------------------------------------------------
        //-----------SERVICES FOR LOG IN/REGISTER MENU-------------
        Player player;

        public event PropertyChangedEventHandler PropertyChanged;

        private int _score;
        public int score
        {
            get { return _score; }
            set
            {
                _score = value;
                OnPropertyChanged("score");
            }
        }

        private ObservableCollection<Users> _users;
        public ObservableCollection<Users> users
        {
            get { return _users; }
            set
            {
                _users = value;
                OnPropertyChanged("users");
            }
        }
        private int _currentSelected;
        public int CurrentSelected
        {
            get { return _currentSelected; }
            set
            {
                _currentSelected = value;
                OnPropertyChanged("CurrentSelected");
            }
        }
        public Service()
        {
            users = new ObservableCollection<Users>();
            loadImages();
            score = 0;
            timerStarted = false;
            currentHangmanImage = hangmanImages[0];
            hangmanImagesIndex = 0;
            currentWord = "";
            selectedWord = "";
            
            lives = 5;
            aWasPressed = false;
            bWasPressed = false;
            cWasPressed = false;
            dWasPressed = false;
            eWasPressed = false;
            fWasPressed = false;
            gWasPressed = false;
            hWasPressed = false;
            iWasPressed = false;
            jWasPressed = false;
            kWasPressed = false;
            lWasPressed = false;
            mWasPressed = false;
            nWasPressed = false;
            oWasPressed = false;
            pWasPressed = false;
            rWasPressed = false;
            sWasPressed = false;
            tWasPressed = false;
            uWasPressed = false;
            vWasPressed = false;
            wWasPressed = false;
            xWasPressed = false;
            yWasPressed = false;
            zWasPressed = false;
            Load();
        }
        //CONSTRUCTORS AND INTIALISATIONS TO DISPLAY THE REGISTERED USERS AND THE CURRENT SELECTED USER

        //--------------------------------------------------------------------
        internal void Load()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/UsersStorage.xml");
            foreach(XmlNode nod in doc.DocumentElement.ChildNodes)
            {
                string text = nod.InnerText;
                string name = nod.Attributes["Name"]?.InnerText;
                string image = nod.Attributes["Image"]?.InnerText;
                Users u = new Users(name, image);
                users.Add(u);
                OnPropertyChanged("users");
            }
        }
        public void Save()
        {
            
            XmlDocument doc = new XmlDocument();           
            doc.Load("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/UsersStorage.xml");
            doc.DocumentElement.RemoveAll();
            for (int i = 0; i < users.Count; i++)
            {
                Users u = users[i];
                string name = u.Username;
                string image = u.Image;
                XmlElement user = doc.CreateElement("User");
                user.SetAttribute("Name", name);
                user.SetAttribute("Image", image);
                doc.DocumentElement.AppendChild(user);               
            }
            doc.Save("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/UsersStorage.xml");
        }
        //COMMANDS THAT LOAD AND SAVE ANY MODIFICATIONS TO USER STORAGE XML FILE
        //-------------------------------------------
        ICommand m_newUser;
        public ICommand AddUserCommand
        {
            get
            {
                if (m_newUser == null)
                    m_newUser = new RelayCommand(AddUser);
                return m_newUser;
            }
        }
        private void AddUser(object parameter)
        {
            string name = "";
            string image = "";
            var dialog = new User();

            dialog.ShowDialog();
            if (dialog.Image.Text != "")
            {
                name = dialog.Input.Text;
                image = dialog.Image.Text;
                XmlDocument doc = new XmlDocument();
                doc.Load("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/UsersStorage.xml");
                XmlElement user = doc.CreateElement("User");
                user.SetAttribute("Name", name);
                user.SetAttribute("Image", image);
                doc.DocumentElement.AppendChild(user);
                doc.Save("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/UsersStorage.xml");
                Console.WriteLine(name);
                Users u = new Users(name, image);
                users.Add(u);
                Player player = new Player(name, 0, 0);
                string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/PlayerStatistics.txt";
                string[] anotherTextFile = File.ReadAllLines(path);
                using (StreamWriter outputFile = new StreamWriter(path))
                {
                    foreach (string line in anotherTextFile)
                    {
                        Console.WriteLine(line);
                        outputFile.WriteLine(line);
                    }
                    outputFile.WriteLine(name);
                    outputFile.WriteLine(0);
                    outputFile.WriteLine(0);
                }
                OnPropertyChanged("users");
            }
            else
            {
                MessageBox.Show("Please upload an image", "Warning", MessageBoxButton.OK);
            }


        }


        ICommand m_deleteUser;
        public ICommand DeleteUserCommand
        {
            get
            {
                if (m_deleteUser == null)
                    m_deleteUser = new RelayCommand(DeleteUser);
                return m_deleteUser;
            }
        }
        private void DeleteUser(object obj)
        {
            Player p = new Player(users[CurrentSelected].Username, 0, 0);
            DeletePlayerStatistics(p);
            users.Remove(users[CurrentSelected]);
            Save();
            OnPropertyChanged("users");
        }
        //USER MANAGEMENT COMMANDS---------------

        //------------------------------------------------
        ICommand m_gameStart;
        public ICommand GameStartCommand
        {
            get
            {
                if (m_gameStart == null)
                    m_gameStart = new RelayCommand(GameStart);
                return m_gameStart;
            }
        }
        private void GameStart(object obj)
        {
            player = new Player();
            Game game = new Game(users[CurrentSelected].Username);
            player.username = users[CurrentSelected].Username;
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/PlayerStatistics.txt";
            string[] textFile = File.ReadAllLines(path);
            for (int i = 0; i < textFile.Length; i += 3)
            {
                string aux = textFile[i];
                if (aux.Equals(player.username))
                {
                    player.gamesPlayed = Int32.Parse(textFile[i + 1]);
                    player.gamesWon = Int32.Parse(textFile[i + 2]);
                    break;
                }
            }
            path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
            using (StreamWriter outputFile = new StreamWriter(path))
            {
                outputFile.WriteLine(player.username);
                outputFile.WriteLine(player.gamesPlayed);
                outputFile.WriteLine(player.gamesWon);
            }
            game.Show();
        }
        //COMMAND TO START THE GAME TIMER AND INITIALISE THE CURRENT PLAYER

        //------------------------------------------------------------------
        ICommand m_saveGame;      
        public ICommand SaveGameCommand
        {
            get
            {
                if (m_saveGame == null)
                    m_saveGame = new RelayCommand(SaveGame);
                return m_saveGame;
            }
        }
        private void SaveGame(object obj)
        {
            SaveFileDialog saveFile = new SaveFileDialog();
            saveFile.Filter = "Text file|*.txt";
            string[] dataToSave = new string[100];
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
            string[] textFile = File.ReadAllLines(path);
            player = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));
            dataToSave[0] = player.username;
            dataToSave[1] = selectedWord;
            dataToSave[2] = currentWord;
            dataToSave[3] = lives.ToString();
            dataToSave[4] = score.ToString();
            for (int i = 0; i < words.Length; i++)
            {
                dataToSave[i + 5] = words[i];
            }
            string content = "";
            for (int i = 0; i < dataToSave.Length; i++)
            {
                content += dataToSave[i];
                content += "\n";
            }
            if (saveFile.ShowDialog() == true)
            {
                System.IO.File.WriteAllText(saveFile.FileName, content);
            }

        }
        //SAVE THE CURRENT GAME TO A TXT COMMAND---------------------------
        
        //---------------------------------------------------------------------
        private ICommand m_loadGame;
        public ICommand LoadGameCommand {
            get
            {
                if (m_loadGame == null)
                    m_loadGame = new RelayCommand(LoadGame);
                return m_loadGame;
            }
        }
        private void LoadGame(object obj)
        {
            OpenFileDialog open = new OpenFileDialog();
            words = new string[100];
            open.Filter = "Text file|*.txt";
            open.DefaultExt = ".txt";
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
            string[] textFile = File.ReadAllLines(path);
            player = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));
            if (open.ShowDialog() == true)
            {
                string[] content = File.ReadAllLines(open.FileName);
                if(player.username == content[0])
                {
                    selectedWord = content[1];
                    currentWord = content[2];
                    lives = Int32.Parse(content[3]);
                    score = Int32.Parse(content[4]);
                    for (int i = 5;i<content.Length;i++)
                    {
                        words[i - 5] = content[i];
                    }                   
                }
                else
                {
                    System.Windows.MessageBox.Show("This is not your save file.Please try again", "Error", MessageBoxButton.OK);
                }
            }
            else
            {
                System.Windows.MessageBox.Show("Eror 403: You need to open a save file to play", "Error", MessageBoxButton.OK);
            }
            
        }
        //LOAD A SAVED GAME COMMAND---------------------------------------

        //----------------------------------------------------------------
        
        private void updateCurrentPlayerStatistics(Player p,int won,int game)
        {
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
            string[] textFile = File.ReadAllLines(path);
            p = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));
            p.gamesPlayed += game;
            p.gamesWon += won;
            using (StreamWriter outputFile = new StreamWriter(path))
            {
                outputFile.WriteLine(player.username);             
                outputFile.WriteLine(player.gamesWon);
                outputFile.WriteLine(player.gamesPlayed);
            }
        }

        private void SaveStatistics(Player player)
        {
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/PlayerStatistics.txt";
            string[] anotherTextFile = File.ReadAllLines(path);
            this.player = player;
            using (StreamWriter outputFile = new StreamWriter(path))
            {
                int counter = 4;
                foreach (string line in anotherTextFile)
                {
                    if (line == this.player.username)
                        counter = 3;
                    if (counter == 3)
                    {
                        outputFile.WriteLine(line);
                        counter -= 1;
                    }
                    else if(counter == 2)
                    {
                        outputFile.WriteLine(this.player.gamesWon);
                        counter -= 1;
                    }
                    else if (counter == 1)
                    {
                        outputFile.WriteLine(this.player.gamesPlayed);
                        counter -= 1;
                    }
                    else
                    {
                        Console.WriteLine(line);
                        outputFile.WriteLine(line);
                    }
                }
                    
            }
        }
     
        private void DeletePlayerStatistics(Player p)
        {
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/PlayerStatistics.txt";
            string[] anotherTextFile = File.ReadAllLines(path);
            using (StreamWriter outputFile = new StreamWriter(path))
            {
                int counter = 4;
                foreach (string line in anotherTextFile)
                {
                    if (line == p.username)
                        counter = 3;
                    if (counter == 3)
                    {
                        counter -= 1;
                    }
                    else if (counter == 2)
                    {
                        counter -= 1;
                    }
                    else if (counter == 1)
                    {
                        counter -= 1;
                    }
                    else
                    {
                        Console.WriteLine(line);
                        outputFile.WriteLine(line);
                    }
                }

            }
        }
        //METHODS TO MANAGE PLAYER STATISTICS-----------------------------------

        
        //----------------------------------------------------------------------
        //------------------------------------------------------------------------
        //-------------------SERVICES FOR GAME ENGINE MENU------------------------
        //-----------------THIS ARE THE METHODS THAT THE PLAYER WILL USE TO INTERACT WITH THE GAME---------------
        //-----------------AND METHODS THAT ALLOW THE GAME TO DISPLAY DIFFERENT IMAGES TO THE PLAYER BASED ON THE STAGES OF THE GAME

        //-----------------------------------------------
        public ICommand m_statistics;
        public ICommand StatisticsCommand
        {
            get
            {
                if (m_statistics == null)
                    m_statistics = new RelayCommand(ShowStatistics);
                return m_statistics;
            }
        }
        private void ShowStatistics(object obj)
        {
            
            string path = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
            string[]textFile = File.ReadAllLines(path);
            player = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));               
            System.Windows.MessageBox.Show("Games played: "+ player.gamesPlayed.ToString()+"\n"+"Games won: "+player.gamesWon, "Lose message", MessageBoxButton.OK);
        }
        //COMMAND TO SEE THE CURRENT PLAYER STATISTICS--------------------

        //-------------------------------------------------------------------
        
        public bool timerStarted;

        public ICommand m_start;
        public ICommand StartCommand
        {
            get
            {
                if (m_start == null)
                    m_start = new RelayCommand(StartGame);
                return m_start;

            }
        }
        private void StartGame(object obj)
        {
            timerStarted = true;
        }
        //COMMANDS FOR THE START GAME BUTTON TO START THE GAME TIMER------------------------


        //----------------------------------------------------------------------------
        public string[] hangmanImages;

        public int hangmanImagesIndex;

        private string _currentHangmanImage;
        public string currentHangmanImage
        {
            get
            {
                return _currentHangmanImage;
            }
            set
            {
                _currentHangmanImage = value;
                OnPropertyChanged("currentHangmanImage");

            }
        }
        public void loadImages()
        {
            hangmanImages = new string[5];
            hangmanImages[0] = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Images/Hangman1.jpg";
            hangmanImages[1] = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Images/Hangman2.jpg";
            hangmanImages[2] = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Images/Hangman3.jpg";
            hangmanImages[3] = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Images/Hangman4.jpg";
            hangmanImages[4] = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Images/Hangman5.jpg";
        }
        //THIS IS THE PART WHERE THE HANGMAN IMAGES ARE LOADED -----------------

        //-----------------------------------------------------------------
        private int _lives;
        public int lives
        {
            get
            {
                return _lives;
            }
            set
            {
                _lives = value;
                OnPropertyChanged("lives");
            }
        }

        public string[] words;

        private string _currentWord;
        public string currentWord
        {
            get { return _currentWord; }
            set
            {
                _currentWord = value;
                OnPropertyChanged("currentWord");
            }
        }


        private string _selectedWord;
        public string selectedWord
        {
            get { return _selectedWord; }
            set
            {
                _selectedWord = value;
                OnPropertyChanged("selectedWord");
            }
        }
        //THESE ARE THE CURRENT GAME INFORMATIONS THAT THE PLAYER WILL NEED TO PLAY


        //----------------------------------------------------------------------
        private void LoadTemplate(string path)
        {
            words = File.ReadAllLines(path);
            Random random = new Random();
            int randWordIndex = random.Next(words.Length);
            selectedWord = words[randWordIndex];
            words = words.Where((source, index) => index != randWordIndex).ToArray();
            currentWord = MakeCurrentWord(selectedWord);
            Console.WriteLine(selectedWord);
        }
        private string MakeCurrentWord(string selectedWord)
        {
            currentWord = "";
            for (int i = 0; i < selectedWord.Length; i++)
            {
                if (selectedWord[i].ToString() != " ")
                {
                    currentWord += "_";
                }
                else
                {
                    currentWord += " ";
                }
            }
            return currentWord;
        }
        private void GetNextSelected()
        {
            Random random = new Random();
            int randWordIndex = random.Next(words.Length);
            selectedWord = words[randWordIndex];
            words = words.Where((source, index) => index != randWordIndex).ToArray();
            currentWord = MakeCurrentWord(selectedWord);
            Console.WriteLine(selectedWord);
            aWasPressed = false;
            bWasPressed = false;
            cWasPressed = false;
            dWasPressed = false;
            eWasPressed = false;
            fWasPressed = false;
            gWasPressed = false;
            hWasPressed = false;
            iWasPressed = false;
            jWasPressed = false;
            kWasPressed = false;
            lWasPressed = false;
            mWasPressed = false;
            nWasPressed = false;
            oWasPressed = false;
            pWasPressed = false;
            rWasPressed = false;
            sWasPressed = false;
            tWasPressed = false;
            uWasPressed = false;
            vWasPressed = false;
            wWasPressed = false;
            xWasPressed = false;
            yWasPressed = false;
            zWasPressed = false;
        }

        ICommand m_loadMovies;
        public ICommand LoadMoviesCommand
        {
            get
            {
                if (m_loadMovies == null)
                    m_loadMovies = new RelayCommand(LoadMovies);
                return m_loadMovies;

            }
        }
        public void LoadMovies(object obj)
        {
            Console.WriteLine("Loading movies");
            LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/Movies.txt");
        }


        ICommand m_loadSongs;
        public ICommand LoadSongsCommand
        {
            get
            {
                if (m_loadSongs == null)
                    m_loadSongs = new RelayCommand(LoadSongs);
                return m_loadSongs;

            }
        }
        public void LoadSongs(object obj)
        {
            Console.WriteLine("Loading songs");
            LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/Songs.txt");

        }


        ICommand m_loadProgramming;
        public ICommand LoadProgrammingCommand
        {
            get
            {
                if (m_loadProgramming == null)
                    m_loadProgramming = new RelayCommand(LoadProgramming);
                return m_loadProgramming;

            }
        }
        public void LoadProgramming(object obj)
        {
            Console.WriteLine("Loading programming");
            LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/ProgrammingConcepts.txt");
        }


        ICommand m_loadArtists;
        public ICommand LoadArtistsCommand
        {
            get
            {
                if (m_loadArtists == null)
                    m_loadArtists = new RelayCommand(LoadArtists);
                return m_loadArtists;

            }
        }
        public void LoadArtists(object obj)
        {
            Console.WriteLine("Loading artists");
            LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/Artists.txt");
        }

        ICommand m_loadAll;
        public ICommand LoadAllCommand
        {
            get
            {
                if (m_loadAll == null)
                    m_loadAll = new RelayCommand(LoadAll);
                return m_loadAll;

            }
        }
        public void LoadAll(object obj)
        {
            Console.WriteLine("Loading all");
            Random random = new Random();
            int fileNumber = random.Next(4);
            if (fileNumber == 0)
                LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/Artists.txt");
            else if (fileNumber == 1)
                LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/Movies.txt");
            else if (fileNumber == 2)
                LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/ProgrammingConcepts.txt");
            else if (fileNumber == 3)
                LoadTemplate("C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Words/ProgrammingConcepts.txt");
        }
        //THIS IS THE PART WHERE THE CURRENT GAME DATA WILL BE LOADED

        //--------------------------------------------------------------------------------
        private void ButtonTemplate(ref bool wasPressed, string lower, string upper)
        {
            if (timerStarted == true)
            {
                if (wasPressed == false)
                {
                    if (selectedWord.Contains(lower) || selectedWord.Contains(upper))
                    {
                        wasPressed = true;
                        for (int i = 0; i < selectedWord.Length; i++)
                        {
                            if (selectedWord[i] == lower[0])
                            {
                                currentWord = currentWord.Remove(i, 1).Insert(i, lower);
                                OnPropertyChanged("currentWord");

                            }
                            else if (selectedWord[i] == upper[0])
                            {
                                currentWord = currentWord.Remove(i, 1).Insert(i, upper);
                                OnPropertyChanged("currentWord");
                            }
                            Console.WriteLine(currentWord);
                            CheckForWin();
                        }
                    }
                    else
                    {
                        wasPressed = true;
                        lives -= 1;
                        if (lives <= 0)
                        {
                            string path2 = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
                            string[] textFile = File.ReadAllLines(path2);
                            player = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));
                            player.gamesPlayed += 1;
                            SaveStatistics(player);
                            updateCurrentPlayerStatistics(player, 0, 1);
                            System.Windows.MessageBox.Show("YOU LOSE.Press EXIT to continue", "Lose message", MessageBoxButton.OK);
                        }
                        else if (lives > 0)
                        {

                            hangmanImagesIndex += 1;
                            currentHangmanImage = hangmanImages[hangmanImagesIndex];
                            OnPropertyChanged("currentHangmanImage");
                        }
                        OnPropertyChanged("lives");
                    }
                }
                else
                {
                    System.Windows.MessageBox.Show("This button was pressed already.Please choose another letter", "Error", MessageBoxButton.OK);
                }
            }
            else if (timerStarted == false)
            {
                System.Windows.MessageBox.Show("You need to press the start button to play the game", "Error", MessageBoxButton.OK);
            }
        }
        private void CheckForWin()
        {
            if (currentWord == selectedWord)
            {
                System.Windows.MessageBox.Show("YOU WIN THIS ROUND!", "WIN", MessageBoxButton.OK);
                GetNextSelected();
                score += 1;
                OnPropertyChanged("score");
            }
            if (score == 5)
            {
                System.Windows.MessageBox.Show("YOU WON THE GAME! \n Press exit to continue", "WIN", MessageBoxButton.OK);
                currentWord = "";
                selectedWord = "";
                string path2 = "C:/Users/OMEN_PC1/source/repos/Tema2/Tema2/Model/CurrentPlayerData.txt";
                string[] textFile = File.ReadAllLines(path2);
                player = new Player(textFile[0], Int32.Parse(textFile[1]), Int32.Parse(textFile[2]));
                player.gamesPlayed += 1;
                player.gamesWon += 1;
                updateCurrentPlayerStatistics(player, 1, 1);
                SaveStatistics(player);
            }
        }
        //THIS IS THE PART WHERE THE TEMPLATE FOR EVERY LETTER BUTTON IS INITIALISED AND
        //WHERE THE GAME WILL CHECK IF THE CURRENT PLAYER WON THE GAME

        //BELLOW WE GET EVERY LETTER BUTTON COMMAND---------------------------------

        bool aWasPressed;
        ICommand m_A;
        public ICommand Acommand
        {
            get
            {
                if (m_A == null)
                    m_A = new RelayCommand(A);
                return m_A;
            }
        }
        private void A(object obj)
        {
            ButtonTemplate(ref aWasPressed, "a", "A");
        }


        bool bWasPressed;
        ICommand m_B;
        public ICommand Bcommand
        {
            get
            {
                if (m_B == null)
                    m_B = new RelayCommand(B);
                return m_B;
            }
        }
        private void B(object obj)
        {
            ButtonTemplate(ref bWasPressed, "b", "B");
        }


        bool cWasPressed;
        ICommand m_C;
        public ICommand Ccommand
        {
            get
            {
                if (m_C == null)
                    m_C = new RelayCommand(C);
                return m_C;
            }
        }
        private void C(object obj)
        {
            ButtonTemplate(ref cWasPressed, "c", "C");
        }


        bool dWasPressed;
        ICommand m_D;
        public ICommand Dcommand
        {
            get
            {
                if (m_D == null)
                    m_D = new RelayCommand(D);
                return m_D;
            }
        }
        private void D(object obj)
        {
            ButtonTemplate(ref dWasPressed, "d", "D");
        }


        bool eWasPressed;
        ICommand m_E;
        public ICommand Ecommand
        {
            get
            {
                if (m_E == null)
                    m_E = new RelayCommand(E);
                return m_E;
            }
        }
        private void E(object obj)
        {
            ButtonTemplate(ref eWasPressed, "e", "E");
        }


        bool fWasPressed;
        ICommand m_F;
        public ICommand Fcommand
        {
            get
            {
                if (m_F == null)
                    m_F = new RelayCommand(F);
                return m_F;
            }
        }
        private void F(object obj)
        {
            ButtonTemplate(ref fWasPressed, "f", "F");
        }


        bool gWasPressed;
        ICommand m_G;
        public ICommand Gcommand
        {
            get
            {
                if (m_G == null)
                    m_G = new RelayCommand(G);
                return m_G;
            }
        }
        private void G(object obj)
        {
            ButtonTemplate(ref gWasPressed, "g", "G");
        }


        bool hWasPressed;
        ICommand m_H;
        public ICommand Hcommand
        {
            get
            {
                if (m_H == null)
                    m_H = new RelayCommand(H);
                return m_H;
            }
        }
        private void H(object obj)
        {
            ButtonTemplate(ref hWasPressed, "h", "H");
        }


        bool iWasPressed;
        ICommand m_I;
        public ICommand Icommand
        {
            get
            {
                if (m_I == null)
                    m_I = new RelayCommand(I);
                return m_I;
            }
        }
        private void I(object obj)
        {
            ButtonTemplate(ref iWasPressed, "i", "I");
        }


        bool jWasPressed;
        ICommand m_J;
        public ICommand Jcommand
        {
            get
            {
                if (m_J == null)
                    m_J = new RelayCommand(J);
                return m_J;
            }
        }
        private void J(object obj)
        {
            ButtonTemplate(ref jWasPressed, "j", "J");
        }


        bool kWasPressed;
        ICommand m_K;
        public ICommand Kcommand
        {
            get
            {
                if (m_K == null)
                    m_K = new RelayCommand(K);
                return m_K;
            }
        }
        private void K(object obj)
        {
            ButtonTemplate(ref kWasPressed, "k", "K");
        }


        bool lWasPressed;
        ICommand m_L;
        public ICommand Lcommand
        {
            get
            {
                if (m_L == null)
                    m_L = new RelayCommand(L);
                return m_L;
            }
        }
        private void L(object obj)
        {
            ButtonTemplate(ref lWasPressed, "l", "L");
        }


        bool mWasPressed;
        ICommand m_M;
        public ICommand Mcommand
        {
            get
            {
                if (m_M == null)
                    m_M = new RelayCommand(M);
                return m_M;
            }
        }
        private void M(object obj)
        {
            ButtonTemplate(ref mWasPressed, "m", "M");
        }


        bool nWasPressed;
        ICommand m_N;
        public ICommand Ncommand
        {
            get
            {
                if (m_N == null)
                    m_N = new RelayCommand(N);
                return m_N;
            }
        }
        private void N(object obj)
        {
            ButtonTemplate(ref nWasPressed, "n", "N");
        }


        bool oWasPressed;
        ICommand m_O;
        public ICommand Ocommand
        {
            get
            {
                if (m_O == null)
                    m_O = new RelayCommand(O);
                return m_O;
            }
        }
        private void O(object obj)
        {
            ButtonTemplate(ref oWasPressed, "o", "O");

        }


        bool pWasPressed;
        ICommand m_P;
        public ICommand Pcommand
        {
            get
            {
                if (m_P == null)
                    m_P = new RelayCommand(P);
                return m_P;
            }
        }
        private void P(object obj)
        {
            ButtonTemplate(ref pWasPressed, "p", "P");
        }


        bool qWasPressed;
        ICommand m_Q;
        public ICommand Qcommand
        {
            get
            {
                if (m_Q == null)
                    m_Q = new RelayCommand(Q);
                return m_Q;
            }
        }
        private void Q(object obj)
        {
            ButtonTemplate(ref qWasPressed, "q", "Q");
        }


        bool rWasPressed;
        ICommand m_R;
        public ICommand Rcommand
        {
            get
            {
                if (m_R == null)
                    m_R = new RelayCommand(R);
                return m_R;
            }
        }
        private void R(object obj)
        {
            ButtonTemplate(ref rWasPressed, "r", "R");
        }


        bool sWasPressed;
        ICommand m_S;
        public ICommand Scommand
        {
            get
            {
                if (m_S == null)
                    m_S = new RelayCommand(S);
                return m_S;
            }
        }
        private void S(object obj)
        {
            ButtonTemplate(ref sWasPressed, "s", "S");
        }


        bool tWasPressed;
        ICommand m_T;
        public ICommand Tcommand
        {
            get
            {
                if (m_T == null)
                    m_T = new RelayCommand(T);
                return m_T;
            }
        }
        private void T(object obj)
        {
            ButtonTemplate(ref tWasPressed, "t", "T");
        }


        bool uWasPressed;
        ICommand m_U;
        public ICommand Ucommand
        {
            get
            {
                if (m_U == null)
                    m_U = new RelayCommand(U);
                return m_U;
            }
        }
        private void U(object obj)
        {
            ButtonTemplate(ref uWasPressed, "u", "U");
        }


        bool vWasPressed;
        ICommand m_V;
        public ICommand Vcommand
        {
            get
            {
                if (m_V == null)
                    m_V = new RelayCommand(V);
                return m_V;
            }
        }
        private void V(object obj)
        {
            ButtonTemplate(ref vWasPressed, "v", "V");

        }


        bool wWasPressed;
        ICommand m_W;
        public ICommand Wcommand
        {
            get
            {
                if (m_W == null)
                    m_W = new RelayCommand(W);
                return m_W;
            }
        }
        private void W(object obj)
        {
            ButtonTemplate(ref wWasPressed, "w", "W");

        }


        bool xWasPressed;
        ICommand m_X;
        public ICommand Xcommand
        {
            get
            {
                if (m_X == null)
                    m_X = new RelayCommand(X);
                return m_X;
            }
        }
        private void X(object obj)
        {
            ButtonTemplate(ref xWasPressed, "x", "X");
        }


        bool yWasPressed;
        ICommand m_Y;
        public ICommand Ycommand
        {
            get
            {
                if (m_Y == null)
                    m_Y = new RelayCommand(Y);
                return m_Y;
            }
        }
        private void Y(object obj)
        {
            ButtonTemplate(ref yWasPressed, "y", "Y");

        }


        bool zWasPressed;
        ICommand m_Z;
        public ICommand Zcommand
        {
            get
            {
                if (m_Z == null)
                    m_Z = new RelayCommand(Z);
                return m_Z;
            }
        }
        private void Z(object obj)
        {
            ButtonTemplate(ref zWasPressed, "z", "Z");
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
