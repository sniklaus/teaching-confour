import java.util.Vector;

import org.json.JSONObject;
import org.zeromq.ZMQ;

public class zeromq {
	public static boolean boolRunning = false;
	
	public static void start() {
		zeromq.boolRunning = true;
		
		ZMQ.Context objectContext = ZMQ.context(1);
		ZMQ.Socket objectSocket = objectContext.socket(ZMQ.PAIR); objectSocket.bind("tcp://*:" + main.intZeromq);
		
		do {
			JSONObject objectIn = new JSONObject(objectSocket.recvStr());
			JSONObject objectOut = new JSONObject();
		
			if (objectIn.getString("strFunction").equals("ping") == true) {
				objectOut.put("strOut", main.strName);
				
			} else if (objectIn.getString("strFunction").equals("four_reset") == true) {
				four.reset();
				
			} else if (objectIn.getString("strFunction").equals("four_boardGet") == true) {
				objectOut.put("strOut", four.boardGet());
				
			} else if (objectIn.getString("strFunction").equals("four_boardSet") == true) {
				four.boardSet(objectIn.getString("strIn"));
				
			} else if (objectIn.getString("strFunction").equals("four_winner") == true) {
				objectOut.put("strReturn", four.winner() + "\0");
				
			} else if (objectIn.getString("strFunction").equals("four_isValid") == true) {
				objectOut.put("boolReturn", four.isValid(objectIn.getInt("intX"), objectIn.getInt("intY")));
				
			} else if (objectIn.getString("strFunction").equals("four_isEnemy") == true) {
				objectOut.put("boolReturn", four.isEnemy(objectIn.getString("strPiece").charAt(0)));
				
			} else if (objectIn.getString("strFunction").equals("four_isOwn") == true) {
				objectOut.put("boolReturn", four.isOwn(objectIn.getString("strPiece").charAt(0)));
				
			} else if (objectIn.getString("strFunction").equals("four_isNothing") == true) {
				objectOut.put("boolReturn", four.isNothing(objectIn.getString("strPiece").charAt(0)));
				
			} else if (objectIn.getString("strFunction").equals("four_eval") == true) {
				objectOut.put("intReturn", four.eval());
				
			} else if (objectIn.getString("strFunction").equals("four_moves") == true) {
				Vector<String> strOut = four.moves();
				
				objectOut.put("intOut", strOut.size());
				objectOut.put("strOut", "");
				
				for (int intMove = 0; intMove < strOut.size(); intMove += 1) {
					objectOut.put("strOut", objectOut.get("strOut") + strOut.get(intMove));
				}
				
			} else if (objectIn.getString("strFunction").equals("four_movesShuffled") == true) {
				Vector<String> strOut = four.movesShuffled();
				
				objectOut.put("intOut", strOut.size());
				objectOut.put("strOut", "");
				
				for (int intMove = 0; intMove < strOut.size(); intMove += 1) {
					objectOut.put("strOut", objectOut.get("strOut") + strOut.get(intMove));
				}
				
			} else if (objectIn.getString("strFunction").equals("four_movesEvaluated") == true) {
				Vector<String> strOut = four.movesEvaluated();
				
				objectOut.put("intOut", strOut.size());
				objectOut.put("strOut", "");
				
				for (int intMove = 0; intMove < strOut.size(); intMove += 1) {
					objectOut.put("strOut", objectOut.get("strOut") + strOut.get(intMove));
				}
				
			} else if (objectIn.getString("strFunction").equals("four_move") == true) {
				four.move(objectIn.getString("strIn"));
				
			} else if (objectIn.getString("strFunction").equals("four_moveRandom") == true) {
				objectOut.put("strOut", four.moveRandom());
				
			} else if (objectIn.getString("strFunction").equals("four_moveGreedy") == true) {
				objectOut.put("strOut", four.moveGreedy());
				
			} else if (objectIn.getString("strFunction").equals("four_moveNegamax") == true) {
				objectOut.put("strOut", four.moveNegamax(objectIn.getInt("intMaxdepth"), objectIn.getInt("intDuration")));
				
			} else if (objectIn.getString("strFunction").equals("four_moveAlphabeta") == true) {
				objectOut.put("strOut", four.moveAlphabeta(objectIn.getInt("intMaxdepth"), objectIn.getInt("intDuration")));
				
			} else if (objectIn.getString("strFunction").equals("four_undo") == true) {
				four.undo();
				
			}

			objectSocket.send(objectOut.toString());
		} while (zeromq.boolRunning == true);

		objectSocket.close();
		objectContext.term();
	}
	
	public static void stop() {
		zeromq.boolRunning = false;
	}
}
