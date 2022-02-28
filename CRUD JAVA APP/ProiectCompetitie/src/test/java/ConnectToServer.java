import Competition.DAO.ContestantDAO;
import Competition.DAO.DbConnection;
import Competition.DAO.StageDAO;
import Competition.DAO.TeamDAO;

import java.sql.*;
import java.util.*;

public class ConnectToServer {
    //Containers where the server will store data from DB
    private final StageDAO stageObj = new StageDAO();
    private final ContestantDAO contestantObj = new ContestantDAO();
    private final TeamDAO teamObj = new TeamDAO();


    //---------------------------------------------------
    public ConnectToServer() throws SQLException {
    }

    //METHOD THAT GETS A LEADERBOARD OF A GIVEN STAGE
    public Map getStageLeaderboard(Integer stageNumber) throws SQLException {
        return stageObj.makeStageLeaderboard(stageNumber);
    }

    //METHOD THAT GETS THE FINAL LEADERBOARD BY THE SCORE OF EACH CONTESTANTS
    public Map getFinalLeaderboard() throws SQLException {
        return stageObj.makeFinalLeaderboard();
    }

    //METHOD THAT RETRIVES EVERY TEAM FROM THE DATABASE
    public Set seeAllTeams() throws SQLException {
       return teamObj.makeAllTeams();
    }

    //METHOD THAT RETRIVES A TEAM BY TEAM NUMBER
    public Set seeTeamContestants(Integer teamNumber) throws SQLException {
        return teamObj.makeTeamContestants(teamNumber);
    }

    //METHOD THAT MAKES A TEAM'S LEADERBOARD
    public Map getTeamLeaderboard(Integer teamNumber) throws SQLException {
        return stageObj.makeTeamLeaderboard(teamNumber);
    }

    //METHOD TO GET TEAMS LEADERBOARD
    public Map getLeaderboardOfTeams() throws SQLException {
        return teamObj.makeLeaderboardOfTeams();
    }

    //METHOD THAT ADDS A NEW CONTESTANT TO DATABASE
    public void addContestant(String name) throws SQLException {
        contestantObj.addContestant(name);
    }

    public void addContestantToStage(Integer stageId,Integer contestantId) throws SQLException {
        contestantObj.addContestantToStage(stageId,contestantId);
    }
    //METHOD THAT LETS A USER LOGIN
    public Integer logIn(String username) throws SQLException {
        String SQL = "SELECT * FROM contestant";
        int userId = -1;
        DbConnection dbConnection = new DbConnection();
        Connection connection = dbConnection.makeConnection();
            PreparedStatement statement = connection.prepareStatement(SQL);
            ResultSet resultSet = statement.executeQuery();
            while(resultSet.next())
            {
                resultSet.getString("name");
                if(username.equals(resultSet.getString("name")))
                {
                    userId = resultSet.getInt("id");
                    break;
                }
            }
        return userId;
    }

    //METHOD THAT LETS THE USER SET ITS SCORE
    public void setScore(Integer contestantId, Integer stageId, Integer newScore) throws SQLException {
            contestantObj.setScore(contestantId,stageId,newScore);
    }

    //METHOD THAT ADDS TEAM TO DATA BASE
    public void addTeamToDB(String tName, Set<Integer> contestants) throws SQLException {
        Integer teamId = teamObj.addTeamToDB(tName);
        for(Integer id : contestants)
            teamObj.addContestantToTeam(teamId,id);

    }

    public void addContestantToTeam(Integer teamId,Integer contestantId) throws SQLException {
        if(teamObj.getTeamSize(teamId) < 5)
            teamObj.addContestantToTeam(teamId,contestantId);
    }

    //METHOD THAT CHECKS IF A CONTESTANT DID NOT REGISTER HIS SCORE
    public boolean checkMissingScore(Integer id) throws SQLException {
        return contestantObj.checkMissingScore(id);
    }

    public void addStageToDB(String stageName) throws SQLException {
        stageObj.addStageToDB(stageName);
    }

    public void deleteContestant(Integer contestantId) throws SQLException {
            contestantObj.deleteContestant(contestantId);
    }

    public void deleteContestantFromStage(Integer contestantId) throws SQLException {
        contestantObj.deleteContestantFromStage(contestantId);
    }
    public void deleteContestantFromTeam(Integer contestantId) throws SQLException {
        contestantObj.deleteContestantFromTeam(contestantId);
    }

    public void updateContestant(Integer updateContestantId, String newContestantName) throws SQLException {
        contestantObj.updateContestant(updateContestantId,newContestantName);
    }

    public void deleteTeamFromDB(Integer deleteTeamId) throws SQLException {
        teamObj.deleteTeamFromDB(deleteTeamId);
    }

    public void updateTeamName(Integer updateTeamId,String newTeamName) throws SQLException {
        teamObj.updateTeamName(updateTeamId,newTeamName);
    }

    public void updateStage(Integer updateStageId, String newStageName) throws SQLException {
        stageObj.updateStage(updateStageId,newStageName);
    }

    public void deleteStage(Integer deleteStageId) throws SQLException {
        stageObj.deleteStage(deleteStageId);
    }
}




