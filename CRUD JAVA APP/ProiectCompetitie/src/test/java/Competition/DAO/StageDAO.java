package Competition.DAO;

import Competition.DAO.DbConnection;

import java.sql.*;
import java.util.*;

public class StageDAO {

  private Connection connection;

  public StageDAO() throws SQLException {
    DbConnection dbConnection = new DbConnection();
    connection = dbConnection.makeConnection();
  }

  //METHOD THAT GETS A LEADERBOARD OF A GIVEN STAGE
  public Map makeStageLeaderboard(Integer stageNumber) throws SQLException {

    String SQL = "select c.name as name, scl.score as score\n" +
            "       from stage as st join stage_contestant_link as scl on st.id = scl.stage_id\n" +
            "       join contestant as c on c.id = scl.contestant_id\n" +
            "       where st.id = (?)\n" +
            "       order by scl.score desc";
    Map<String, Integer> leaderboard = new TreeMap();
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(1, stageNumber);
      ResultSet resultSet = statement.executeQuery();

      while (resultSet.next()) {
        String name = resultSet.getString("name");
        Integer score = resultSet.getInt("score");
        if(score != -1)
          leaderboard.put(name,score);
      }


   return leaderboard;
  }

  //METHOD THAT MAKE THE FINAL LEADEBOARD
  public Map makeFinalLeaderboard() throws SQLException {
    String SQL = "SELECT c.name as name,s.score as score\n" +
            "FROM contestant AS c JOIN stage_contestant_link AS s ON c.id = s.contestant_id\n" +
            "ORDER BY s.score desc";
    Map<String, Integer> mapLeaderboard = new TreeMap<>();
      PreparedStatement statement = connection.prepareStatement(SQL);
      ResultSet resultSet = statement.executeQuery();
      while (resultSet.next()) {
        Integer score = resultSet.getInt("score");
        String name = resultSet.getString("name");
        if(score != -1)
          mapLeaderboard.put(name,score);
      }
    return mapLeaderboard;
}

  //--------------------------------------------------------------------------------
  //METHOD THAT MAKES THE LEADEBORD OF A TEAM
  public Map makeTeamLeaderboard(Integer teamNumber) throws SQLException {
    String SQL = "SELECT c.name AS name,s.score as score\n" +
            "            FROM contestant AS c JOIN team_contestant_link AS tcl ON c.id = tcl.contestant_id\n" +
            "            JOIN team AS t ON tcl.team_id = t.t_id\n" +
            "\t\t\tJOIN stage_contestant_link AS s ON  s.contestant_id = c.id\n" +
            "            WHERE t.t_id = (?)\n" +
            "            ORDER BY s.score desc";
    Map<String,Integer> team = new TreeMap<>();
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(1, teamNumber);
      ResultSet resultSet = statement.executeQuery();
      while (resultSet.next()) {
        String name = resultSet.getString("name");
        Integer score = resultSet.getInt("score");
        team.put(name,score);
      }
    return  team;
  }

  //METHOD THAT GETS A TEAM POINTS
  public Integer makeTeamTotalPoints(Integer teamNumber) throws SQLException {
    String SQL = "SELECT s.score as score\n" +
            "            FROM contestant AS c JOIN team_contestant_link AS tcl ON c.id = tcl.contestant_id\n" +
            "            JOIN team AS t on tcl.team_id = t.t_id\n" +
            "            JOIN stage_contestant_link as s on s.contestant_id = c.id\n" +
            "            WHERE t.t_id = (?)\n" +
            "            ORDER BY s.score desc";
    Integer scoreTotal = 0;
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(1, teamNumber);
      ResultSet resultSet = statement.executeQuery();
      while (resultSet.next()) {
        Integer score = resultSet.getInt("score");
        scoreTotal = scoreTotal + score;
      }

    return scoreTotal;
  }

  public boolean stageFinished(Integer stageId) throws SQLException {
    String contCountSQL = "SELECT COUNT(contestant_id) \n" +
            "FROM stage_contestant_link WHERE stage_id =(?) ";
    String scoreCountSQL = "SELECT COUNT(score) \n" +
            "FROM stage_contestant_link WHERE stage_id =(?) AND score >(?) ";
    Integer contCount = 0;
    Integer scoreCount = 0;
      PreparedStatement contCountStatement = connection.prepareStatement(contCountSQL);
      contCountStatement.setInt(1, stageId);
      PreparedStatement scoreCountStatement = connection.prepareStatement(scoreCountSQL);
      scoreCountStatement.setInt(1,stageId);
      scoreCountStatement.setInt(2,-1);
      ResultSet contSet = contCountStatement.executeQuery();
      ResultSet scoreSet = scoreCountStatement.executeQuery();
      while (contSet.next()) {
        contCount = contSet.getInt("count");
      }
      while(scoreSet.next())
      {
        scoreCount = scoreSet.getInt("count");
      }
    if(contCount.equals(scoreCount))
      return true;
    return false;
  }

  public void addStageToDB(String stageName) throws SQLException {
    String SQL ="INSERT INTO stage(name) VALUES (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setString(1,stageName);
    statement.executeUpdate();
  }

  public void updateStage(Integer updateStageId, String newStageName) throws SQLException {
    String SQL = "UPDATE stage\n" +
            "SET name = (?)\n" +
            "WHERE id = (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(2,updateStageId);
    statement.setString(1,newStageName);
    statement.executeUpdate();
  }

  public void deleteFromStageContestantLink(Integer stageId) throws SQLException {
    String SQL = "DELETE FROM stage_contestant_link\n" +
            "WHERE stage_id = (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,stageId);
    statement.executeUpdate();
  }
  public void deleteStage(Integer stageId) throws SQLException {
    deleteFromStageContestantLink(stageId);
    String SQL = "DELETE FROM stage\n" +
            "WHERE id = (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,stageId);
    statement.executeUpdate();
  }
}
