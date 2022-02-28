package Competition.DAO;


import javax.persistence.PrePersist;
import java.sql.*;

public class ContestantDAO {

  private Connection connection;

  public ContestantDAO() throws SQLException {
    DbConnection dbConnection = new DbConnection();
    connection = dbConnection.makeConnection();
  }

  //METHOD TO ADD A CONTESTANT TO DB
  public void addContestant(String name) throws SQLException {
    String SQL = "INSERT INTO contestant(name) values (?)";
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setString(1, name);
      statement.execute();

  }

  public void addContestantToStage(Integer stageId,Integer contestantId) throws SQLException {
    String SQL = "INSERT INTO stage_contestant_link(stage_id,contestant_id) values (?,?)";
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(1, stageId);
      statement.setInt(2, contestantId);
      statement.execute();
  }

  //METHOD THAT LETS THE USER SET ITS SCORE
  public void setScore(Integer contestantId, Integer stageId,Integer newScore) throws SQLException {
    String SQL = "UPDATE stage_contestant_link SET score = (?) WHERE contestant_id = (?) AND stage_id = (?)";
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(3,stageId);
      statement.setInt(2,contestantId);
      statement.setInt(1,newScore);
      statement.executeUpdate();
    System.out.println("Contestant with id " + contestantId + " score updated successfully" );
  }

  public boolean checkMissingScore(Integer id) throws SQLException {
    String SQL = "SELECT score FROM stage_contestant_link WHERE contestant_id = (?)";
    Integer score = -1;
      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(1,id);
      ResultSet resultSet = statement.executeQuery();
      while(resultSet.next())
      {
        score = resultSet.getInt("score");
      }
    if(score == -1)
      return false;
    return true;
  }

  public void deleteContestantFromTeam(Integer contestantId) throws SQLException {
    String SQL = "DELETE FROM team_contestant_link WHERE contestant_id = (?);\n";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,contestantId);
    statement.executeUpdate();
  }
  public void deleteContestantFromStage(Integer contestantId) throws SQLException {
    String SQL = "DELETE FROM stage_contestant_link WHERE contestant_id = (?);\n";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,contestantId);
    statement.executeUpdate();
  }
  public void deleteContestant(Integer contestantId) throws SQLException {
    deleteContestantFromTeam(contestantId);
    deleteContestantFromStage(contestantId);
    String SQL = "DELETE FROM contestant WHERE id = (?); ";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,contestantId);
    statement.executeUpdate();
  }

  public void updateContestant(Integer updateContestantId, String newContestantName) throws SQLException {
    String SQL ="UPDATE contestant\n" +
            "SET name = (?)\n" +
            "WHERE id =(?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(2,updateContestantId);
    statement.setString(1,newContestantName);
    statement.executeUpdate();
  }
}
