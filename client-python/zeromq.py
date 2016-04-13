import json

##########################################################

import zmq # pip install pyzmq

##########################################################

zeromq_boolRunning = False

##########################################################

def zeromq_start():
	global zeromq_boolRunning
	
	zeromq_boolRunning = True
	
	contextHandle = zmq.Context()
	socketHandle = contextHandle.socket(zmq.PAIR)
	
	socketHandle.bind("tcp://*:" + str(main_intZeromq))
	
	while zeromq_boolRunning == True:
		jsonIn = None
		jsonOut = {}
		
		jsonIn = json.loads(socketHandle.recv().decode())
		
		if jsonIn["strFunction"] == "ping":
			jsonOut["strOut"] = main_strName
			
		elif jsonIn["strFunction"] == "four_reset":
			four_reset()
			
		elif jsonIn["strFunction"] == "four_boardGet":
			jsonOut["strOut"] = four_boardGet()
			
		elif jsonIn["strFunction"] == "four_boardSet":
			four_boardSet(jsonIn["strIn"])
			
		elif jsonIn["strFunction"] == "four_winner":
			jsonOut["strReturn"] = four_winner()
			
		elif jsonIn["strFunction"] == "four_isValid":
			jsonOut["boolReturn"] = four_isValid(jsonIn["intX"], jsonIn["intY"])
			
		elif jsonIn["strFunction"] == "four_isEnemy":
			jsonOut["boolReturn"] = four_isEnemy(jsonIn["strPiece"])
			
		elif jsonIn["strFunction"] == "four_isOwn":
			jsonOut["boolReturn"] = four_isOwn(jsonIn["strPiece"])
			
		elif jsonIn["strFunction"] == "four_isNothing":
			jsonOut["boolReturn"] = four_isNothing(jsonIn["strPiece"])
			
		elif jsonIn["strFunction"] == "four_eval":
			jsonOut["intReturn"] = four_eval()
			
		elif jsonIn["strFunction"] == "four_moves":
			strOut = four_moves()
			
			jsonOut["intOut"] = len(strOut)
			jsonOut["strOut"] = str.join('', strOut)
			
		elif jsonIn["strFunction"] == "four_movesShuffled":
			strOut = four_movesShuffled()
			
			jsonOut["intOut"] = len(strOut)
			jsonOut["strOut"] = str.join('', strOut)
			
		elif jsonIn["strFunction"] == "four_movesEvaluated":
			strOut = four_movesEvaluated()
			
			jsonOut["intOut"] = len(strOut)
			jsonOut["strOut"] = str.join('', strOut)
			
		elif jsonIn["strFunction"] == "four_move":
			four_move(jsonIn["strIn"])
			
		elif jsonIn["strFunction"] == "four_moveRandom":
			jsonOut["strOut"] = four_moveRandom()
			
		elif jsonIn["strFunction"] == "four_moveGreedy":
			jsonOut["strOut"] = four_moveGreedy()
			
		elif jsonIn["strFunction"] == "four_moveNegamax":
			jsonOut["strOut"] = four_moveNegamax(jsonIn["intDepth"], jsonIn["intDuration"])
			
		elif jsonIn["strFunction"] == "four_moveAlphabeta":
			jsonOut["strOut"] = four_moveAlphabeta(jsonIn["intDepth"], jsonIn["intDuration"])
			
		elif jsonIn["strFunction"] == "four_undo":
			four_undo()
		
		socketHandle.send_string(json.dumps(jsonOut))
		
		jsonIn = None
		jsonOut = None
	
	socketHandle.close()
	contextHandle.destroy()


def zeromq_stop():
	global zeromq_boolRunning

	zeromq_boolRunning = false
