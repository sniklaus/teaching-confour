import java.util.Vector;

import org.json.JSONObject;
import org.zeromq.ZMQ;

public class zeromq {
    public static boolean boolRunning = false;
    
    public static void start() {
        zeromq.boolRunning = true;
        
        ZMQ.Context objContext = ZMQ.context(1);
        ZMQ.Socket objSocket = objContext.socket(ZMQ.PAIR); objSocket.bind("tcp://*:" + main.intZeromq);
        
        do {
            JSONObject objIn = new JSONObject(objSocket.recvStr());
            JSONObject objOut = new JSONObject();
        
            if (objIn.getString("strFunction").equals("ping") == true) {
                objOut.put("strOut", main.strName);
                
            } else if (objIn.getString("strFunction").equals("four_reset") == true) {
                four.reset();
                
            } else if (objIn.getString("strFunction").equals("four_boardGet") == true) {
                objOut.put("strOut", four.boardGet());
                
            } else if (objIn.getString("strFunction").equals("four_boardSet") == true) {
                four.boardSet(objIn.getString("strIn"));
                
            } else if (objIn.getString("strFunction").equals("four_winner") == true) {
                objOut.put("strReturn", four.winner() + "\0");
                
            } else if (objIn.getString("strFunction").equals("four_isValid") == true) {
                objOut.put("boolReturn", four.isValid(objIn.getInt("intX"), objIn.getInt("intY")));
                
            } else if (objIn.getString("strFunction").equals("four_isEnemy") == true) {
                objOut.put("boolReturn", four.isEnemy(objIn.getString("strPiece").charAt(0)));
                
            } else if (objIn.getString("strFunction").equals("four_isOwn") == true) {
                objOut.put("boolReturn", four.isOwn(objIn.getString("strPiece").charAt(0)));
                
            } else if (objIn.getString("strFunction").equals("four_isNothing") == true) {
                objOut.put("boolReturn", four.isNothing(objIn.getString("strPiece").charAt(0)));
                
            } else if (objIn.getString("strFunction").equals("four_eval") == true) {
                objOut.put("intReturn", four.eval());
                
            } else if (objIn.getString("strFunction").equals("four_moves") == true) {
                Vector<String> strOut = four.moves();
                
                objOut.put("intOut", strOut.size());
                objOut.put("strOut", "");
                
                for (int intMove = 0; intMove < strOut.size(); intMove += 1) {
                    objOut.put("strOut", objOut.get("strOut") + strOut.get(intMove));
                }
                
            } else if (objIn.getString("strFunction").equals("four_movesShuffled") == true) {
                Vector<String> strOut = four.movesShuffled();
                
                objOut.put("intOut", strOut.size());
                objOut.put("strOut", "");
                
                for (int intMove = 0; intMove < strOut.size(); intMove += 1) {
                    objOut.put("strOut", objOut.get("strOut") + strOut.get(intMove));
                }
                
            } else if (objIn.getString("strFunction").equals("four_movesEvaluated") == true) {
                Vector<String> strOut = four.movesEvaluated();
                
                objOut.put("intOut", strOut.size());
                objOut.put("strOut", "");
                
                for (int intMove = 0; intMove < strOut.size(); intMove += 1) {
                    objOut.put("strOut", objOut.get("strOut") + strOut.get(intMove));
                }
                
            } else if (objIn.getString("strFunction").equals("four_move") == true) {
                four.move(objIn.getString("strIn"));
                
            } else if (objIn.getString("strFunction").equals("four_moveRandom") == true) {
                objOut.put("strOut", four.moveRandom());
                
            } else if (objIn.getString("strFunction").equals("four_moveGreedy") == true) {
                objOut.put("strOut", four.moveGreedy());
                
            } else if (objIn.getString("strFunction").equals("four_moveNegamax") == true) {
                objOut.put("strOut", four.moveNegamax(objIn.getInt("intMaxdepth"), objIn.getInt("intDuration")));
                
            } else if (objIn.getString("strFunction").equals("four_moveAlphabeta") == true) {
                objOut.put("strOut", four.moveAlphabeta(objIn.getInt("intMaxdepth"), objIn.getInt("intDuration")));
                
            } else if (objIn.getString("strFunction").equals("four_undo") == true) {
                four.undo();
                
            }

            objSocket.send(objOut.toString());
        } while (zeromq.boolRunning == true);

        objSocket.close();
        objContext.term();
    }
    
    public static void stop() {
        zeromq.boolRunning = false;
    }
}
