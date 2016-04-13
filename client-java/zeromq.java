import java.util.Vector;

import org.json.JSONObject;
import org.zeromq.ZMQ;

public class zeromq {
	public static boolean boolRunning = false;
	
	public static void start() {
		{
			zeromq.boolRunning = true;
		}
		
		{
			ZMQ.Context contextHandle = ZMQ.context(1);
			ZMQ.Socket socketHandle = contextHandle.socket(ZMQ.PAIR);
			
			{
				socketHandle.bind("tcp://*:" + main.intZeromq);
			}
			
			{
				do {
					JSONObject jsonobjectIn = null;
					JSONObject jsonobjectOut = new JSONObject();
					
					{
						jsonobjectIn = new JSONObject(socketHandle.recvStr());
					}
					
					{
						if (jsonobjectIn.getString("strFunction").equals("ping") == true) {
							jsonobjectOut.put("strOut", main.strName);
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_reset") == true) {
							four.reset();
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_boardGet") == true) {
							jsonobjectOut.put("strOut", four.boardGet());
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_boardSet") == true) {
							four.boardSet(jsonobjectIn.getString("strIn"));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_winner") == true) {
							jsonobjectOut.put("strReturn", four.winner() + "\0");
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_isValid") == true) {
							jsonobjectOut.put("boolReturn", four.isValid(jsonobjectIn.getInt("intX"), jsonobjectIn.getInt("intY")));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_isEnemy") == true) {
							jsonobjectOut.put("boolReturn", four.isEnemy(jsonobjectIn.getString("strPiece").charAt(0)));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_isOwn") == true) {
							jsonobjectOut.put("boolReturn", four.isOwn(jsonobjectIn.getString("strPiece").charAt(0)));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_isNothing") == true) {
							jsonobjectOut.put("boolReturn", four.isNothing(jsonobjectIn.getString("strPiece").charAt(0)));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_eval") == true) {
							jsonobjectOut.put("intReturn", four.eval());
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_moves") == true) {
							Vector<String> strOut = four.moves();
							
							jsonobjectOut.put("intOut", strOut.size());
							jsonobjectOut.put("strOut", "");
							
							for (int intFor1 = 0; intFor1 < strOut.size(); intFor1 += 1) {
								jsonobjectOut.put("strOut", jsonobjectOut.get("strOut") + strOut.get(intFor1));
							}
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_movesShuffled") == true) {
							Vector<String> strOut = four.movesShuffled();
							
							jsonobjectOut.put("intOut", strOut.size());
							jsonobjectOut.put("strOut", "");
							
							for (int intFor1 = 0; intFor1 < strOut.size(); intFor1 += 1) {
								jsonobjectOut.put("strOut", jsonobjectOut.get("strOut") + strOut.get(intFor1));
							}
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_movesEvaluated") == true) {
							Vector<String> strOut = four.movesEvaluated();
							
							jsonobjectOut.put("intOut", strOut.size());
							jsonobjectOut.put("strOut", "");
							
							for (int intFor1 = 0; intFor1 < strOut.size(); intFor1 += 1) {
								jsonobjectOut.put("strOut", jsonobjectOut.get("strOut") + strOut.get(intFor1));
							}
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_move") == true) {
							four.move(jsonobjectIn.getString("strIn"));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_moveRandom") == true) {
							jsonobjectOut.put("strOut", four.moveRandom());
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_moveGreedy") == true) {
							jsonobjectOut.put("strOut", four.moveGreedy());
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_moveNegamax") == true) {
							jsonobjectOut.put("strOut", four.moveNegamax(jsonobjectIn.getInt("intDepth"), jsonobjectIn.getInt("intDuration")));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_moveAlphabeta") == true) {
							jsonobjectOut.put("strOut", four.moveAlphabeta(jsonobjectIn.getInt("intDepth"), jsonobjectIn.getInt("intDuration")));
							
						} else if (jsonobjectIn.getString("strFunction").equals("four_undo") == true) {
							four.undo();
							
						}
					}
					
					{
						socketHandle.send(jsonobjectOut.toString());
					}
				} while (zeromq.boolRunning == true);
			}
			
			socketHandle.close();
			contextHandle.term();
		}
	}
	
	public static void stop() {
		{
			zeromq.boolRunning = false;
		}
	}
}
