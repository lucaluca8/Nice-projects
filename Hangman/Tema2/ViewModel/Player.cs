using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema2.Model
{
    class Player
    {
        public int gamesPlayed { get; set; }
        public int gamesWon { get; set; }
        public string username { get; set; }
        public int lives { get; set; }
        public Player()
        {
            username = "";
            gamesPlayed = 0;
            gamesWon = 0;
        }
        public Player(string name,int won,int played)
        {
            username = name;
            gamesWon = won;
            gamesPlayed = played;           
        }
    }
}
