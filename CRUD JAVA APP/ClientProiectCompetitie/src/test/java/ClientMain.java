import javax.xml.crypto.Data;
import java.io.*;
import java.net.Inet4Address;
import java.net.Socket;
import java.util.*;

public class ClientMain {

    public static void main(String[] args){
        String SERVER_IP = "192.168.0.104";
        int SERVER_PORT = 8888;
        //^^^^^ AICI MODIFIC CU IPURILE SI PORTURILE MELE
        System.out.println("Creating socket and connecting to socket");
        Socket clientSocket;
        try {
            clientSocket=new Socket(Inet4Address.getByName(SERVER_IP), SERVER_PORT);
            communicate(clientSocket);
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
            return;
        }
        try {
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //LOGIN METHOD
    public static Integer logIn(Socket clientSocket) throws IOException {
        while(true)
        {
            //-------------------------------------------------
            Scanner keyboard = new Scanner(System.in);
            System.out.println("Introduce your username: ");
            String username = keyboard.nextLine();
            //ASK THE USER FOR THE USERNAME -----------------------
            OutputStream out = clientSocket.getOutputStream();
            DataOutputStream dataOutputStream = new DataOutputStream(out);
            dataOutputStream.writeUTF(username);
            //CHECK FOR THE CASE THAT THE CLIENT MIGHT BE AN ADMIN
            if(username.equals("admin"))
                return -2;
            //------------------------------------------------------
            //SEND USERNAME TO SERVER-------------------------------
            InputStream inputStream = clientSocket.getInputStream();
            DataInputStream dataInputStream = new DataInputStream(inputStream);
            String stringId = dataInputStream.readUTF();
            //GET RESPONSE FROM SERVER-------------------------------------
            int id = Integer.parseInt(stringId);
            if(id != -1)
            {
                //IF THE USERNAME EXISTS LET THE USER USE THE CLIENT FUNCTIONS
                return id;
            }
            else{
                //ELSE ASK THE USER TO LOGIN AGAIN
                System.out.println("Wrong username.Try again. (error code -1)");
            }
        }

    }

    private static void communicate(Socket clientSocket) throws IOException, ClassNotFoundException {
        System.out.println("Communicating with server...");
        Integer clientId = logIn(clientSocket);
        boolean exit = false;
        if(clientId != -1)
        {
            if(checkRegisteredScoreRequest(clientSocket,clientId) == false)
            {
                System.out.println("You need to register your score");
            }
            while(true)
            {
                System.out.println("Press 1 to see a stage leaderboard.You will be asked to introduce the stage number: ");
                System.out.println("Press 2 to see the final leaderboard: ");
                System.out.println("Press 3 to see all teams: ");
                System.out.println("Press 4 to see a team members.You will be asked to introduce the team number: ");
                System.out.println("Press 5 to see leaderboard of all teams: ");
                System.out.println("Press 6 to see a team leaderboard: ");
                System.out.println("Press 7 to set your score");
                if(clientId == -2)
                {
                    System.out.println("Press 8 to add a new contestant");
                    System.out.println("Press 9 to add a new team");
                    System.out.println("Press 10 to add a contestant to a stage");
                    System.out.println("Press 11 to add a new stage");
                    System.out.println("Press 12 to delete a contestant");
                    System.out.println("Press 13 to delete a contestant from a stage");
                    System.out.println("Press 14 to delete a contestant from a team");
                    System.out.println("Press 15 to update data of a contestant");
                    System.out.println("Press 16 to delete a team");
                    System.out.println("Press 17 to update a team name");
                    System.out.println("Press 18 to update a stage name");
                    System.out.println("Press 19 to delete a stage by id");
                }
                System.out.println("Press 20 to exit the application");
                Scanner keyboard = new Scanner(System.in);
                Integer requestType = keyboard.nextInt();
                switch (requestType)
                {
                    //FIRST CASE WITCH LETS THE CLIENT SEE THE LEADERBOARD FOR A STAGE
                    case 1:
                        sendRequestTypeForStageLeaderboard(clientSocket,requestType);
                        InputStream stageInputStream = clientSocket.getInputStream();
                        ObjectInputStream stageResultsStream = new ObjectInputStream(stageInputStream);
                        Map stageResults =(Map) stageResultsStream.readObject();
                        stageResults.entrySet().stream().sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).forEach(System.out::println);
                        break;

                    //SECOND CASE WITCH LETS THE CLIENT SEE THE FINAL LEADERBOARD
                    case 2:
                        sendRequestTypeForFinalLeaderboard(clientSocket,requestType);
                        InputStream leaderboardInputStream = clientSocket.getInputStream();
                        ObjectInputStream resultsStream = new ObjectInputStream(leaderboardInputStream);
                        Map results =(Map) resultsStream.readObject();
                        results.entrySet().stream().sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).forEach(System.out::println);
                        break;

                    //THIRD CASE WITCH LETS THE CLIENT SEE ALL TEAMS
                    case 3:
                        sendRequestTypeForSeeAllTeams(clientSocket,requestType);
                        InputStream allTeamsInputStream = clientSocket.getInputStream();
                        ObjectInputStream teamsStream = new ObjectInputStream(allTeamsInputStream);
                        Set teams = (Set) teamsStream.readObject();
                        for(Object it : teams)
                        {
                            System.out.println(it);
                        }
                        break;

                    //FOURTH CASE WITCH LETS THE CLIENT SEE A TEAM BY ITS NUMBER
                    case 4:
                        sendRequestTypeForSeeTeamContestants(clientSocket,requestType);
                        InputStream membersInputStream = clientSocket.getInputStream();
                        ObjectInputStream membersStream = new ObjectInputStream(membersInputStream);
                        Set members = (Set) membersStream.readObject();
                        for(Object it:members)
                        {
                            System.out.println(it);
                        }
                        break;
                        //FIFTH CASE WITCH LETS THE CLIENT SEE EVERY LEADERBOARD
                    case 5:
                        sendRequestTypeForTeamsLeaderboard(clientSocket,requestType);
                        InputStream teamsLeaderboardInputStream = clientSocket.getInputStream();
                        ObjectInputStream teamsLeaderboardStream = new ObjectInputStream(teamsLeaderboardInputStream);
                        Map teamsLeaderboard = (Map) teamsLeaderboardStream.readObject();
                        System.out.println(teamsLeaderboard);
                        teamsLeaderboard.entrySet().stream().sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).forEach(System.out::println);
                        break;

                    //SIXTH CASE WITCH LETS THE CLIENT SEE A TEAMS LEADEBOARD
                    case 6:
                        sendRequestTypeForTeamLeaderboard(clientSocket,requestType);
                        InputStream teamLeaderboardInputStream = clientSocket.getInputStream();
                        ObjectInputStream teamLeaderboardStream = new ObjectInputStream(teamLeaderboardInputStream);
                        Map teamLeaderboard = (Map) teamLeaderboardStream.readObject();
                        teamLeaderboard.entrySet().stream().sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).forEach(System.out::println);
                        break;
                    //METHODS THAT WILL LET THE CLIENT SET ITS SCORE
                    case 7:
                        sendRequestTypeForSetScore(clientSocket,requestType);
                        System.out.println("Your score has been updated");
                        break;
                    //METHOD THAT LETS THE ADMIN ADD A NEW CONTESTANT TO DB
                    case 8:
                        sendRequestTypeForAddNewContestant(clientSocket,requestType);
                        System.out.println("Contestant added successfully");
                        break;
                    //METHOD THAT LETS ADMIN ADD A NEW TEAM TO DB
                    case 9:
                       sendRequestTypeForAddNewTeam(clientSocket,requestType);
                       System.out.println("Team added successfully");
                       break;
                    case 10:
                        sendRequestTypeForAddContestantToStage(clientSocket,requestType);
                        System.out.println("Contestant added to stage successfully");
                        break;
                    case 11:
                        sendRequestTypeForAddStageToDB(clientSocket,requestType);
                        System.out.println("Stage added successfully");
                        break;
                    case 12:
                        sendRequestTypeForDeleteContestant(clientSocket,requestType);
                        System.out.println("Contestant deleted successfully");
                        break;
                    case 13:
                        sendRequestTypeForAddDeleteContestantFromStage(clientSocket,requestType);
                        System.out.println("Contestant removed from stage successfully");
                        break;
                    case 14:
                        sendRequestTypeForRemoveContestantFromTeam(clientSocket,requestType);
                        System.out.println("Contestant removed from team successfully");
                        break;
                    case 15:
                        sendRequestTypeForUpdateDataOfContestant(clientSocket,requestType);
                        System.out.println("Contestant data updated successfully");
                        break;
                    case 16:
                        sendRequestForDeleteTeam(clientSocket,requestType);
                        System.out.println("Team deleted successfully");
                        break;
                    case 17:
                        sendRequestForUpdateTeamName(clientSocket,requestType);
                        System.out.println("Team deleted successfully");
                        break;
                    case 18:
                        sendRequestForUpdateStageName(clientSocket,requestType);
                        System.out.println("Stage updated successfully");
                        break;
                    case 19:
                        sendRequestForDeleteStage(clientSocket,requestType);
                        System.out.println("Stage deleted successfully");
                        break;
                    case 20:
                        exit = true;
                        break;
                }
                if(exit)
                    break;

            }
        }

        System.out.println("Communication with server ended");
    }

    private static void sendRequestForDeleteStage(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the stage you would like to delete");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        out.flush();
    }

    private static void sendRequestForUpdateStageName(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the stage you would like to update");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        System.out.println("Introduce the new stage name");
        String newStageName = keyboard.next();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        dataOutputStream.writeUTF(newStageName);
        out.flush();
    }

    private static void sendRequestForUpdateTeamName(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the team you would like to update");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        System.out.println("Introduce the name of the team you would like to update");
        String newStageName = keyboard.next();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        dataOutputStream.writeUTF(newStageName);
        out.flush();
    }

    private static void sendRequestForDeleteTeam(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the team you would like to delete");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        out.flush();
    }

    private static void sendRequestTypeForUpdateDataOfContestant(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the contestant you would like to update name of");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        System.out.println("Introduce the new name of the contestant");
        String newName = keyboard.next();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        dataOutputStream.writeUTF(newName);
        out.flush();
    }

    private static void sendRequestTypeForRemoveContestantFromTeam(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the contestant you would like to delete from its team");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        out.flush();
    }

    private static void sendRequestTypeForAddDeleteContestantFromStage(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the contestant you would like to delete from the stages that it registered");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        out.flush();
    }

    private static void sendRequestTypeForDeleteContestant(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the contestant you would like to delete");
        Scanner keyboard = new Scanner(System.in);
        Integer id = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(id));
        out.flush();
    }

    private static void sendRequestTypeForAddStageToDB(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the name of the stage");
        Scanner keyboard = new Scanner(System.in);
        String stageName = keyboard.nextLine();
        OutputStream out =clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(stageName));
        out.flush();
    }

    private static void sendRequestTypeForAddContestantToStage(Socket clientSocket, Integer requestType) throws IOException {
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));

        Scanner keyboard = new Scanner(System.in);
        System.out.println("Introduce the contestant id");
        Integer contestantId = keyboard.nextInt();
        System.out.println("Introduce the stage id");
        String stageId = keyboard.next();
        dataOutputStream.writeUTF(String.valueOf(contestantId));
        dataOutputStream.writeUTF(stageId);
        out.flush();
    }

    private static boolean sendRequestTypeForAddNewTeam(Socket clientSocket, Integer requestType) throws IOException {
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));

        Scanner keyboard = new Scanner(System.in);
        System.out.println("Introduce the new team id");
        Integer teamId = keyboard.nextInt();
        System.out.println("Introduce your new team name");
        String teamName = keyboard.next();
        System.out.println("Introude your new team size");
        Integer teamSize = keyboard.nextInt();
        if(teamSize <2 || teamSize >5)
        {System.out.println("Team size outside of the right parameters.Please try again"); return false;}
        System.out.println("Introduce your team memebers ids:");
        Set<Integer> members = new HashSet<>();
        for(int i=0;i<teamSize;i++)
        {
            Integer memeberId = keyboard.nextInt();
            members.add(memeberId);
        }

        dataOutputStream.writeUTF(String.valueOf(teamId));
        dataOutputStream.writeUTF(teamName);
        ObjectOutputStream membersOutputStream = new ObjectOutputStream(out);
        membersOutputStream.writeObject(members);
        out.flush();
        return true;
    }

    private static void sendRequestTypeForAddNewContestant(Socket clientSocket, Integer requestType) throws IOException {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Introduce the contestant name");
        String name = keyboard.next();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(name);
        out.flush();
    }

    private static void sendRequestTypeForSetScore(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Please introduce the number of the stage you want to register the score for: ");
        Scanner keyboard = new Scanner(System.in);
        Integer stageId = keyboard.nextInt();
        System.out.println("Please introduce your score");
        Integer score = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(stageId.toString());
        dataOutputStream.writeUTF(score.toString());
        out.flush();
    }

    //METHODS THAT SEND REQUEST TYPES TO SERVER
    private static void sendRequestTypeForTeamLeaderboard(Socket clientSocket, Integer requestType) throws IOException {
        System.out.println("Introduce the id of the team you would like to see leaderboard of: ");
        Scanner keyboard = new Scanner(System.in);
        Integer teamId = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(teamId));
        out.flush();
    }

    private static void sendRequestTypeForTeamsLeaderboard(Socket clientSocket, Integer requestType) throws IOException {
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        out.flush();
    }

    private static void sendRequestTypeForSeeTeamContestants(Socket clientSocket,Integer requestType) throws IOException {
        System.out.println("Introduce the id of the team you would like to see of: ");
        Scanner keyboard = new Scanner(System.in);
        Integer teamId = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(teamId));
        out.flush();
    }

    private static void sendRequestTypeForSeeAllTeams(Socket clientSocket, Integer requestType) throws IOException {
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        out.flush();
    }

    private static void sendRequestTypeForFinalLeaderboard(Socket clientSocket, Integer requestType) throws IOException {
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        out.flush();

    }

    private static void sendRequestTypeForStageLeaderboard(Socket clientSocket,Integer requestType) throws IOException {
        System.out.println("Introduce the id of the stage you would like to see the leaderboard of: ");
        Scanner keyboard = new Scanner(System.in);
        Integer stageId = keyboard.nextInt();
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(requestType));
        dataOutputStream.writeUTF(String.valueOf(stageId));
        out.flush();
    }

    private  static boolean checkRegisteredScoreRequest(Socket clientSocket,Integer id) throws IOException {
        OutputStream out = clientSocket.getOutputStream();
        DataOutputStream dataOutputStream = new DataOutputStream(out);
        dataOutputStream.writeUTF(String.valueOf(id));
        out.flush();
        //^^^^^^^^^^^^^^^^^^^^^ SEND THE SERVER THE CLIENT ID TO CHECK IF IT HAS MISSIOG SCORE
        InputStream in = clientSocket.getInputStream();
        DataInputStream dataInputStream = new DataInputStream(in);
        String responseString = dataInputStream.readUTF();
        Boolean response = Boolean.parseBoolean(responseString);
        return response;
    }

}