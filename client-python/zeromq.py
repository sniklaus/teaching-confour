import json

##########################################################

import zmq # pip install pyzmq

##########################################################

zeromq_boolRunning = False

##########################################################

def zeromq_start():
    global zeromq_boolRunning
    
    zeromq_boolRunning = True
    
    objContext = zmq.Context()
    objSocket = objContext.socket(zmq.PAIR); objSocket.bind('tcp://*:' + str(main_intZeromq))
    
    while zeromq_boolRunning == True:
        objIn = json.loads(objSocket.recv().decode('utf-8'))
        objOut = {}
        
        if objIn['strFunction'] == 'ping':
            objOut['strOut'] = main_strName
            
        elif objIn['strFunction'] == 'four_reset':
            four_reset()
            
        elif objIn['strFunction'] == 'four_boardGet':
            objOut['strOut'] = four_boardGet()
            
        elif objIn['strFunction'] == 'four_boardSet':
            four_boardSet(objIn['strIn'])
            
        elif objIn['strFunction'] == 'four_winner':
            objOut['strReturn'] = four_winner()
            
        elif objIn['strFunction'] == 'four_isValid':
            objOut['boolReturn'] = four_isValid(objIn['intX'], objIn['intY'])
            
        elif objIn['strFunction'] == 'four_isEnemy':
            objOut['boolReturn'] = four_isEnemy(objIn['strPiece'])
            
        elif objIn['strFunction'] == 'four_isOwn':
            objOut['boolReturn'] = four_isOwn(objIn['strPiece'])
            
        elif objIn['strFunction'] == 'four_isNothing':
            objOut['boolReturn'] = four_isNothing(objIn['strPiece'])
            
        elif objIn['strFunction'] == 'four_eval':
            objOut['intReturn'] = four_eval()
            
        elif objIn['strFunction'] == 'four_moves':
            strOut = four_moves()
            
            objOut['intOut'] = len(strOut)
            objOut['strOut'] = str.join('', strOut)
            
        elif objIn['strFunction'] == 'four_movesShuffled':
            strOut = four_movesShuffled()
            
            objOut['intOut'] = len(strOut)
            objOut['strOut'] = str.join('', strOut)
            
        elif objIn['strFunction'] == 'four_movesEvaluated':
            strOut = four_movesEvaluated()
            
            objOut['intOut'] = len(strOut)
            objOut['strOut'] = str.join('', strOut)
            
        elif objIn['strFunction'] == 'four_move':
            four_move(objIn['strIn'])
            
        elif objIn['strFunction'] == 'four_moveRandom':
            objOut['strOut'] = four_moveRandom()
            
        elif objIn['strFunction'] == 'four_moveGreedy':
            objOut['strOut'] = four_moveGreedy()
            
        elif objIn['strFunction'] == 'four_moveNegamax':
            objOut['strOut'] = four_moveNegamax(objIn['intMaxdepth'], objIn['intDuration'])
            
        elif objIn['strFunction'] == 'four_moveAlphabeta':
            objOut['strOut'] = four_moveAlphabeta(objIn['intMaxdepth'], objIn['intDuration'])
            
        elif objIn['strFunction'] == 'four_undo':
            four_undo()

        # end
        
        objSocket.send_string(json.dumps(objOut))
    # end

    objSocket.close()
    objContext.destroy()
# end

def zeromq_stop():
    global zeromq_boolRunning

    zeromq_boolRunning = false
# end