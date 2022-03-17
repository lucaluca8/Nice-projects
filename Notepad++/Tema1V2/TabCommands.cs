using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using static Tema1V2.MainWindow;


namespace Tema1V2
{
    class TabCommands: INotifyPropertyChanged
    {       
        public event PropertyChangedEventHandler PropertyChanged;

        private ObservableCollection<Tab> _tabs;
        public ObservableCollection<Tab> tabs
        {
            get { return _tabs; }
            set
            {
                _tabs = value;
                
                OnPropertyChanged("tabs");
            }
        }

        private int _currentSelected;
        public int currentSelected 
        {
            get { return _currentSelected; }
            set 
            { 
               _currentSelected = value;
                OnPropertyChanged("currentSelected");
            }
        }
        
        public TabCommands()
        {
            tabs = new ObservableCollection<Tab>();
            currentSelected = 0;
        }


        ICommand m_newTab;
        ICommand m_openTab;
        ICommand m_saveAsTab;
        ICommand m_saveTab;
        ICommand m_remove;
        ICommand m_about;
        ICommand m_find;
        ICommand m_replace;
        ICommand m_replaceAll;
        

        public ICommand AddTabComand
        {
            get
            {
                if (m_newTab == null)
                    m_newTab = new RelayCommand(AddTab);
                return m_newTab;
            }
        }
        public ICommand OpenTabCommand
        {
            get
            {
                if (m_openTab == null)
                    m_openTab = new RelayCommand(OpenTab);
                return m_openTab;
            }
        }
        public ICommand SaveAsTabCommand
        {
            get
            {
                if (m_saveAsTab == null)
                    m_saveAsTab = new RelayCommand(SaveAsTab);
                return m_saveAsTab;
            }
        }
        public ICommand SaveTabCommand
        {
            get
            {
                if (m_saveTab == null)
                    m_saveTab = new RelayCommand(RemoveTab);
                return m_saveTab;
            }
        }      
        public ICommand RemoveTabCommand
        {
            get
            {
                if (m_remove == null)
                    m_remove = new RelayCommand(RemoveTab);
                return m_remove;
            }
        }
        public ICommand AboutCommand
        {
            get
            {
                if (m_about == null)
                    m_about = new RelayCommand(AboutTab);
                return m_about;
            }
        }
        public ICommand FindCommand
        {
            get
            {
                if (m_find == null)
                    m_find = new RelayCommand(FindTab);
                return m_find;
            }
        }
        public ICommand ReplaceCommand
        {
            get
            {
                if (m_replace == null)
                    m_replace = new RelayCommand(ReplaceTab);
                return m_replace;
            }
        }
        public ICommand ReplaceAllCommand
        {
            get
            {
                if (m_replaceAll == null)
                    m_replaceAll = new RelayCommand(ReplaceAllTab);
                return m_replaceAll;
            }
        }

        private void ReplaceAllTab(object obj)
        {
            if (tabs[currentSelected] != null)
            {
                var dialog = new DialogBox();
                string toReplace = "";
                string newWord = "";
                if (dialog.ShowDialog() == true)
                {
                    toReplace = dialog.ResponseText;
                    newWord = dialog.InputText;
                }
                string text = tabs[currentSelected].content;
                var regex = new Regex(Regex.Escape(newWord));
                string newText = regex.Replace(text, toReplace);
                Console.WriteLine(newText);

                Tab t = new Tab()
                {
                    header = tabs[currentSelected].header,
                    fullPath = tabs[currentSelected].fullPath,
                    content = newText
                };
                tabs.Remove(tabs[currentSelected]);
                tabs.Add(t);
                OnPropertyChanged("tabs");
            }
        }

        private void ReplaceTab(object obj)
        {
            if (tabs[currentSelected] != null)
            {
                var dialog = new DialogBox();
                string toReplace = "";
                string newWord = "";
                if (dialog.ShowDialog() == true)
                {
                    toReplace = dialog.ResponseText;
                    newWord = dialog.InputText;
                }
                string text = tabs[currentSelected].content;
                var regex = new Regex(Regex.Escape(newWord));
                string newText = regex.Replace(text, toReplace, 1);
                Console.WriteLine(newText);

                Tab t = new Tab()
                {
                    header = tabs[currentSelected].header,
                    fullPath = tabs[currentSelected].fullPath,
                    content = newText
                };
                tabs.Remove(tabs[currentSelected]);
                tabs.Add(t);
                OnPropertyChanged("tabs");
            }
        }

        private void FindTab(object obj)
        {
            if (tabs[currentSelected] != null)
            {
                var dialog = new DialogBox();
                string toFind = "";
                if (dialog.ShowDialog() == true)
                {
                    toFind = dialog.ResponseText;
                }
                if (toFind != null)
                {
                    string text = tabs[currentSelected].content;
                    Console.WriteLine(text.IndexOf(toFind));
                }
            }
        }

        private void AboutTab(object obj)
        {
            MessageBox.Show("Nume: Lazar\nPrenume: " +
               "Luca\nEmail: lazar.luca@student.unitbv.ro", "About", MessageBoxButton.OK);
        }

        private void RemoveTab(object obj)
        {
            if (tabs[currentSelected].header.Contains("*"))
                SaveAsTab(obj);
            tabs.Remove(tabs[currentSelected]);

        }

        private void SaveTab(object obj)
        {
            SaveFileDialog savefile = new SaveFileDialog();
            savefile.Filter = "Text file|*.txt";
            if (tabs[currentSelected].fullPath != "")
            {
                tabs[currentSelected].header = Path.GetFileName(tabs[currentSelected].fullPath);
                System.IO.File.WriteAllText(tabs[currentSelected].fullPath, tabs[currentSelected].content);
            }
            else
            {
                SaveAsTab(obj);
            }
        }

        private void SaveAsTab(object obj)
        {
            SaveFileDialog savefile = new SaveFileDialog();
            savefile.Filter = "Text file|*.txt";
            if (savefile.ShowDialog() == true)
            {
                Tab t = tabs[currentSelected];
                t.header = Path.GetFileName(savefile.FileName);
                t.fullPath = savefile.FileName;
                System.IO.File.WriteAllText(savefile.FileName,t.content);
            }

        }

        private void OpenTab(object obj)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            open.DefaultExt = ".txt";
            if (open.ShowDialog() == true)
            {
                Tab t = new Tab
                {
                    header = Path.GetFileName(open.FileName),
                    content = File.ReadAllText(open.FileName),
                    fullPath = open.FileName
                };
                tabs.Add(t);
                OnPropertyChanged("tabs");
            }                      
        }
        
        private void AddTab(object parameter)
        {
            Tab t = new Tab
            {   header = "NewTab",
                content ="" ,
                fullPath = ""
            };
            tabs.Add(t);
            OnPropertyChanged("tabs");
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
