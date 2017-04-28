import json

##########################################################

import zmq # pip install pyzmq

##########################################################

zeromq_boolRunning = False

##########################################################

def zeromq_start():
	global zeromq_boolRunning
	
	zeromq_boolRunning = True
	
	objectContext = zmq.Context()
	objectSocket = objectContext.socket(zmq.PAIR)
	
	objectSocket.bind("tcp://*:" + str(main_intZeromq))
	
	while zeromq_boolRunning == True:
		objectIn = None
		objectOut = {}
		
		objectIn = json.loads(objectSocket.recv().decode())
		
		if objectIn["strFunction"] == "ping":
			objectOut["strOut"] = main_strName
			
		elif objectIn["strFunction"] == "four_reset":
			four_reset()
			
		elif objectIn["strFunction"] == "four_boardGet":
			objectOut["strOut"] = four_boardGet()
			
		elif objectIn["strFunction"] == "four_boardSet":
			four_boardSet(objectIn["strIn"])
			
		elif objectIn["strFunction"] == "four_winner":
			objectOut["strReturn"] = four_winner()
			
		elif objectIn["strFunction"] == "four_isValid":
			objectOut["boolReturn"] = four_isValid(objectIn["intX"], objectIn["intY"])
			
		elif objectIn["strFunction"] == "four_isEnemy":
			objectOut["boolReturn"] = four_isEnemy(objectIn["strPiece"])
			
		elif objectIn["strFunction"] == "four_isOwn":
			objectOut["boolReturn"] = four_isOwn(objectIn["strPiece"])
			
		elif objectIn["strFunction"] == "four_isNothing":
			objectOut["boolReturn"] = four_isNothing(objectIn["strPiece"])
			
		elif objectIn["strFunction"] == "four_eval":
			objectOut["intReturn"] = four_eval()
			
		elif objectIn["strFunction"] == "four_moves":
			strOut = four_moves()
			
			objectOut["intOut"] = len(strOut)
			objectOut["strOut"] = str.join('', strOut)
			
		elif objectIn["strFunction"] == "four_movesShuffled":
			strOut = four_movesShuffled()
			
			objectOut["intOut"] = len(strOut)
			objectOut["strOut"] = str.join('', strOut)
			
		elif objectIn["strFunction"] == "four_movesEvaluated":
			strOut = four_movesEvaluated()
			
			objectOut["intOut"] = len(strOut)
			objectOut["strOut"] = str.join('', strOut)
			
		elif objectIn["strFunction"] == "four_move":
			four_move(objectIn["strIn"])
			
		elif objectIn["strFunction"] == "four_moveRandom":
			objectOut["strOut"] = four_moveRandom()
			
		elif objectIn["strFunction"] == "four_moveGreedy":
			objectOut["strOut"] = four_moveGreedy()
			
		elif objectIn["strFunction"] == "four_moveNegamax":
			objectOut["strOut"] = four_moveNegamax(objectIn["intDepth"], objectIn["intDuration"])
			
		elif objectIn["strFunction"] == "four_moveAlphabeta":
			objectOut["strOut"] = four_moveAlphabeta(objectIn["intDepth"], objectIn["intDuration"])
			
		elif objectIn["strFunction"] == "four_undo":
			four_undo()

		# end
		
		objectSocket.send_string(json.dumps(objectOut))
		
		objectIn = None
		objectOut = None
	# end

	objectSocket.close()
	objectContext.destroy()
# end

def zeromq_stop():
	global zeromq_boolRunning

	zeromq_boolRunning = false
# end