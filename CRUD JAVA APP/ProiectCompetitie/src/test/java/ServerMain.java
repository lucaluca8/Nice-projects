import java.io.*;
import java.net.Inet4Address;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.SQLException;
import java.util.Map;
import java.util.Set;


public class ServerMain {

    private static String SERVER_IP;
    private static int SERVER_PORT;

    public static void main(String[] args){

        SERVER_IP= "192.168.0.104";
        SERVER_PORT= 8888;

        System.out.println("Creating socket,binding socket and now listening");
        ServerSocket serverSocket;
        try {
            serverSocket=new ServerSocket(SERVER_PORT,5,Inet4Address.getByName(SERVER_IP));
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }
        while(true){
            try {
                Socket clientSocket=serverSocket.accept();
                ServeAction serveAction=new ServeAction(clientSocket);
                Thread thread=new Thread(serveAction);
                thread.start();


            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

class ServeAction implements Runnable {

    private Socket clientSocket;

    public ServeAction(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }

    public void serve() throws IOException, ClassNotFoundException, SQLException {

        Integer userId = logIn(clientSocket);
        if (userId != -1) {
            //----------------------------------------------------------------
            InputStream inputStream = clientSocket.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);
            String idStr = dataInputStream.readUTF();
            ConnectToServer user = new ConnectToServer();
            Integer id = Integer.parseInt(idStr);
            Boolean response = user.checkMissingScore(id);
            OutputStream out = clientSocket.getOutputStream();
            DataOutputStream dataOutputStream = new DataOutputStream(out);
            dataOutputStream.writeUTF(String.valueOf(response));
            //CHECKS IF THE CLIENT THAT LOGGED IN HAS MISSING SCORE
            while (true) {
                user = new ConnectToServer();
                InputStream requestInputStream = clientSocket.getInputStream();
                DataInputStream requestDataInputStream = new DataInputStream(requestInputStream);
                String requestString = requestDataInputStream.readUTF();
                Integer request = Integer.parseInt(requestString);
                System.out.println("THE REQUEST IS: " + request);

                Boolean exit = false;
                switch (request) {
                    //FIRST CASE WITCH LETS THE CLIENT SEE THE LEADERBOARD FOR A STAGE
                    case 1:
                        String idString = dataInputStream.readUTF();
                        Integer stageId = Integer.parseInt(idString);
                        Map stageResult = user.getStageLeaderboard(stageId);
                        OutputStream stageOutput = clientSocket.getOutputStream();
                        ObjectOutputStream stageResultsOutput = new ObjectOutputStream(stageOutput);
                        stageResultsOutput.writeObject(stageResult);
                        break;

                    //SECOND CASE WITCH LETS THE CLIENT SEE THE FINAL LEADERBOARD
                    case 2:
                        Map finalResult = user.getFinalLeaderboard();
                        OutputStream output = clientSocket.getOutputStream();
                        ObjectOutputStream resultsOutput = new ObjectOutputStream(output);
                        resultsOutput.writeObject(finalResult);
                        break;

                        //THIRD CASE WITCH LETS THE CLIENT SEE ALL TEAMS
                    case 3:
                        Set teams = user.seeAllTeams();
                        OutputStream teamsOutput = clientSocket.getOutputStream();
                        ObjectOutputStream teamsObject = new ObjectOutputStream(teamsOutput);
                        teamsObject.writeObject(teams);
                        break;
                        //FORTH CASE WITCH LETS THE CLIENT SEE A GIVEN TEAM MEMBERS
                    case 4:
                        String teamIdString = dataInputStream.readUTF();
                        Integer teamsId = Integer.parseInt(teamIdString);
                        Set teamResult = user.seeTeamContestants(teamsId);
                        OutputStream membersOutput = clientSocket.getOutputStream();
                        ObjectOutputStream membersResultsOutput = new ObjectOutputStream(membersOutput);
                        membersResultsOutput.writeObject(teamResult);
                        break;
                    //FIFTH CASE WITCH LETS THE USER SEE ALL TEAMS LEADERBOARD
                    case 5:
                        Map teamsLeaderboard = user.getLeaderboardOfTeams();
                        OutputStream teamsLeaderboardOutput = clientSocket.getOutputStream();
                        ObjectOutputStream teamsLeaderboardObject = new ObjectOutputStream(teamsLeaderboardOutput);
                        teamsLeaderboardObject.writeObject(teamsLeaderboard);
                        break;
                    //SIXTH CASE WITCH LETS THE USER SEE A GIVEN TEAM LEADERBOARD
                    case 6:
                        String teamLeaderboardIdString = dataInputStream.readUTF();
                        Integer teamLeaderboardId = Integer.parseInt(teamLeaderboardIdString);
                        Map teamLeaderboardResult = user.getTeamLeaderboard(teamLeaderboardId);
                        OutputStream teamLeaderboardOutput = clientSocket.getOutputStream();
                        ObjectOutputStream teamLeaderboardResultsOutput = new ObjectOutputStream(teamLeaderboardOutput);
                        teamLeaderboardResultsOutput.writeObject(teamLeaderboardResult);
                        break;
                    //SEVENTH CASE WITCH LETS THE CLIENT UPDATE ITS SCORE
                    case 7:
                        String contestantStageIdString = dataInputStream.readUTF();
                        Integer contestantStageId = Integer.parseInt(contestantStageIdString);
                        String contestantUpdateIdString = dataInputStream.readUTF();
                        Integer contestantUpdateId = Integer.parseInt(contestantUpdateIdString);
                        user.setScore(userId,contestantStageId, contestantUpdateId);
                        break;
                    //EIGHT CASE WITCH LETS THE CLIENT ADD A NEW CONTESTANT TO THE DB
                    case 8:
                        String contestantName = dataInputStream.readUTF();
                        user.addContestant(contestantName);
                        break;
                    //NINTH CASE WITCH LETS THE CLIENT ADD A NEW TEAM TO DB
                    case 9:
                        String addTeamIdString = dataInputStream.readUTF();
                        System.out.println(addTeamIdString);
                        Integer addTeamId = Integer.parseInt(addTeamIdString);
                        System.out.println(addTeamId);
                        String teamName = dataInputStream.readUTF();
                        System.out.println(teamName);
                        ObjectInputStream membersStream = new ObjectInputStream(requestInputStream);
                        Set members = (Set) membersStream.readObject();
                        System.out.println(members);
                        user.addTeamToDB(teamName,members);
                        break;
                    //CASE THAT LETS THE CLIENT ADD A CONTESTANT TO A STAGE
                    case 10:
                        String addContestantIdStr = dataInputStream.readUTF();
                        Integer addContestantId = Integer.parseInt(addContestantIdStr);
                        String stageIdStr = dataInputStream.readUTF();
                        Integer addStageId = Integer.parseInt(stageIdStr);
                        user.addContestantToStage(addStageId,addContestantId);
                        break;
                     //CASE THAT LETS CLIENT ADD STAGE TO DB
                    case 11:
                        String addStageName = dataInputStream.readUTF();
                        user.addStageToDB(addStageName);
                        break;
                    //CASE THAT LETS CLIENT DELETE CONTESTANTS FROM DB
                    case 12:
                        String deleteContestantIdStr = dataInputStream.readUTF();
                        Integer deleteContestantId = Integer.parseInt(deleteContestantIdStr);
                        user.deleteContestant(deleteContestantId);
                        break;
                    case 13:
                        String deleteContestantFromStageIdStr = dataInputStream.readUTF();
                        Integer deleteContestantFromStageId = Integer.parseInt(deleteContestantFromStageIdStr);
                        user.deleteContestantFromStage(deleteContestantFromStageId);
                        break;
                    case 14:
                        String deleteContestantFromTeamIdStr = dataInputStream.readUTF();
                        Integer deleteContestantFromTeamId = Integer.parseInt(deleteContestantFromTeamIdStr);
                        user.deleteContestantFromTeam(deleteContestantFromTeamId);
                        break;
                    case 15:
                        String updateContestantIDStr = dataInputStream.readUTF();
                        Integer updateContestantId = Integer.parseInt(updateContestantIDStr);
                        String newContestantName = dataInputStream.readUTF();
                        user.updateContestant(updateContestantId,newContestantName);
                        break;
                    case 16:
                        String deleteTeamIdStr = dataInputStream.readUTF();
                        Integer deleteTeamId = Integer.parseInt(deleteTeamIdStr);
                        user.deleteTeamFromDB(deleteTeamId);
                        break;
                    case 17:
                        String updateTeamIdStr = dataInputStream.readUTF();
                        Integer updateTeamId = Integer.parseInt(updateTeamIdStr);
                        String newTeamName = dataInputStream.readUTF();
                        user.updateTeamName(updateTeamId,newTeamName);
                        break;
                    case 18:
                        String updateStageIDStr = dataInputStream.readUTF();
                        Integer updateStageId = Integer.parseInt(updateStageIDStr);
                        String newStageName = dataInputStream.readUTF();
                        user.updateStage(updateStageId,newStageName);
                        break;
                    case 19:
                        String deleteStageIDStr = dataInputStream.readUTF();
                        Integer deleteStageId = Integer.parseInt(deleteStageIDStr);
                        user.deleteStage(deleteStageId);
                        break;

                }
                if (exit == true)
                    break;
            }
            System.out.println("Served client:" + clientSocket.getInetAddress().toString());
        }
    }

    @Override
    public void run() {
        try {
            serve();
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Integer logIn(Socket clientSocket) throws IOException, SQLException {
        ConnectToServer user = new ConnectToServer();
        while(true)
        {
            InputStream inputStream = clientSocket.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);
            String username = dataInputStream.readUTF();
            if(username.equals("admin"))
                return -2;
            Integer id = user.logIn(username);
            if(id != -1)
            {
                OutputStream out = clientSocket.getOutputStream();
                DataOutputStream dataOutputStream = new DataOutputStream(out);
                dataOutputStream.writeUTF(id.toString());
                return id;
            }
            else {
                OutputStream out = clientSocket.getOutputStream();
                DataOutputStream dataOutputStream = new DataOutputStream(out);
                dataOutputStream.writeUTF("-1");
            }
        }
    }
}