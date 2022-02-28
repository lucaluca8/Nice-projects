package Competition.DAO;


import java.sql.*;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class TeamDAO {


  private Connection connection;
  public TeamDAO() throws SQLException {
    DbConnection dbConnection = new DbConnection();
    connection = dbConnection.makeConnection();
  }

  public Set<String> makeAllTeams() throws SQLException {
    Set<String> teamsName = new HashSet<>();
    String SQL = "SELECT * FROM team";
      PreparedStatement statement = connection.prepareStatement(SQL);
      ResultSet resultSet = statement.executeQuery();
      while (resultSet.next()) {
        String name = resultSet.getString("t_name");
        teamsName.add(name);
      }
    return teamsName;
  }

  public Set makeTeamContestants(Integer teamNumber) throws SQLException {
    String SQL = "SELECT c.name as name, c.id as id,t.t_name as t_name, t.t_id as id\n" +
            "FROM contestant AS c JOIN team_contestant_link AS scl ON c.id = scl.contestant_id\n" +
            "JOIN team AS t  on scl.team_id = t.t_id WHERE t.t_id = (?)";
    Set<String> team = new HashSet<>();

      PreparedStatement statement = connection.prepareStatement(SQL);
      statement.setInt(1, teamNumber);
      ResultSet resultSet = statement.executeQuery();
      while (resultSet.next()) {
        String name = resultSet.getString("name");
        team.add(name);
      }
    return team;
  }

  public Map makeLeaderboardOfTeams() throws SQLException {
    Map<Integer, String> leaderboard = new TreeMap<>();
    int teamCt = 1;
    Set<String> teams = makeAllTeams();
    for (Object t : teams) {
      StageDAO stageObj = new StageDAO();
      leaderboard.put(stageObj.makeTeamTotalPoints(teamCt), (String) t);
      teamCt++;
    }
    return leaderboard;
  }

  public Integer addTeamToDB(String tName) throws SQLException {
    String insertSQL = "INSERT INTO team(t_name) VALUES (?)";
    Integer teamId = 0;

      PreparedStatement insertStatement = connection.prepareStatement(insertSQL);
      insertStatement.setString(1,tName);
      insertStatement.executeUpdate();
      String SQL = "SELECT * FROM team WHERE t_name = (?) ";
      PreparedStatement getIdStatement = connection.prepareStatement(SQL);
      getIdStatement.setString(1,tName);
      ResultSet idSet = insertStatement.executeQuery();
      while (idSet.next())
      {
        teamId = idSet.getInt("t_id");
      }
    return teamId;
  }

  public void addContestantToTeam(Integer teamId,Integer contestantId) throws SQLException {

      String linkSQL = "INSERT INTO team_contestant_link(team_id,contestant_id) VALUES (?,?)";
      PreparedStatement linkStatement = connection.prepareStatement(linkSQL);
      linkStatement.setInt(1,teamId);
      linkStatement.setInt(2,contestantId);
      linkStatement.executeUpdate();

  }

  public Integer getTeamSize(Integer teamId) throws SQLException {
    String SQL = "SELECT COUNT(contestant_id) FROM team_contestant_link WHERE team_id = (?)";
    Integer teamSize = 0;
      PreparedStatement countStatement = connection.prepareStatement(SQL);
      countStatement.setInt(1,teamId);
      ResultSet count = countStatement.executeQuery();
      while(count.next())
      {
        teamSize = count.getInt("count");
      }
    return teamSize;
  }

  public void deleteTeamFromDB(Integer deleteTeamId) throws SQLException {
    clearTeamLinkByTeamId(deleteTeamId);
    String SQL ="DELETE FROM team\n" +
            "WHERE t_id = (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,deleteTeamId);
    statement.executeUpdate();
  }

  private void clearTeamLinkByTeamId(Integer deleteTeamId) throws SQLException {
    String SQL = "DELETE FROM team_contestant_link\n" +
            "WHERE team_id = (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,deleteTeamId);
    statement.executeUpdate();
  }

  public void updateTeamName(Integer updateTeamId,String newTeamName) throws SQLException {
    String SQL ="UPDATE team\n" +
            "SET t_name = (?)\n" +
            "WHERE t_id = (?)";
    PreparedStatement statement = connection.prepareStatement(SQL);
    statement.setInt(1,updateTeamId);
    statement.setString(2,newTeamName);
    statement.executeUpdate();
  }
}
