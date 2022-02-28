import Competition.DAO.ContestantDAO;
import Competition.DAO.TeamDAO;

public class Pair {
    public ContestantDAO c;
    public Integer score;
    public TeamDAO team;

    public Pair()
    {
        this.c = null;
        this.score = 0;
        this.team = null;
    }
    public Pair(Integer score, ContestantDAO c)
    {
        this.score = score;
        this.c = c;
    }
    public Pair(Integer score, TeamDAO t)
    {
        this.score = score;
        this.team = t;
    }

}
