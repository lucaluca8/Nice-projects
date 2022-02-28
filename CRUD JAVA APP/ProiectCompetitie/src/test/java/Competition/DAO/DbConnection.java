package Competition.DAO;

import java.sql.*;

public class DbConnection {
    private final String USERNAME;
    private final String PASSWORD;
    private final String URL;

    public DbConnection()
    {
        this.URL = "jdbc:postgresql://localhost:5432/proiect_competitie";
        this.USERNAME = "postgres";
        this.PASSWORD = "2134";
    }
    public Connection makeConnection() throws SQLException {
        Connection connection = DriverManager.getConnection(URL,USERNAME,PASSWORD);
        return connection;
    }


}
