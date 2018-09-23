import random

##########################################################

def four_reset():
	# reset the state of the game / your internal variables - note that this function is highly dependent on your implementation
	
	pass
# end

def four_boardGet():
	# return the state of the game - one example is given below - note that the state has exactly 52 or 53 characters
	
	strOut = ''
	
	strOut += '1 X\n'
	strOut += '       \n'
	strOut += '       \n'
	strOut += '       \n'
	strOut += '       \n'
	strOut += '       \n'
	strOut += '       \n'
	
	return strOut
# end

def four_boardSet(strIn):
	# read the state of the game from the provided argument and set your internal variables accordingly - note that the state has exactly 40 or 41 characters
	
	pass
# end

def four_winner():
	# determine the winner of the current state of the game and return '?' or '=' or 'X' or 'O' - note that we are returning a character and not a string
	
	return '?'
# end

def four_isValid(intX, intY):
	if intX < 0:
		return False
		
	elif intX > 6:
		return False
	
	if intY < 0:
		return False
		
	elif intY > 5:
		return False
	
	return True
# end

def four_isEnemy(strPiece):
	# with reference to the state of the game, return whether the provided argument is a piece from the side not on move - note that we could but should not use the other is() functions in here but probably
	
	return False
# end

def four_isOwn(strPiece):
	# with reference to the state of the game, return whether the provided argument is a piece from the side on move - note that we could but should not use the other is() functions in here but probably
	
	return False
# end

def four_isNothing(strPiece):
	# return whether the provided argument is not a piece / is an empty field - note that we could but should not use the other is() functions in here but probably
	
	return False
# end

def four_eval():
	# with reference to the state of the game, return the the evaluation score of the side on move - note that positive means an advantage while negative means a disadvantage
	
	return 0
# end

def four_moves():
	# with reference to the state of the game and return the possible moves - one example is given below - note that a move has exactly 3 characters
	
	strOut = []
	
	strOut.append('a1\n')
	strOut.append('b1\n')
	strOut.append('c1\n')
	strOut.append('d1\n')
	strOut.append('e1\n')
	strOut.append('f1\n')
	strOut.append('g1\n')
	
	return strOut
# end

def four_movesShuffled():
	# with reference to the state of the game, determine the possible moves and shuffle them before returning them- note that you can call the four_moves() function in here
	
	return []
# end

def four_movesEvaluated():
	# with reference to the state of the game, determine the possible moves and sort them in order of an increasing evaluation score before returning them - note that you can call the four_movesShuffled() function in here
	
	return []
# end

def four_move(strIn):
	# perform the supplied move (for example 'a5-a4\n') and update the state of the game / your internal variables accordingly - note that it advised to do a sanity check of the supplied move
	
	pass
# end

def four_moveRandom():
	# perform a random move and return it - one example output is given below - note that you can call the four_movesShuffled() function as well as the four_move() function in here
	
	return 'd1\n'
# end

def four_moveGreedy():
	# perform a greedy move and return it - one example output is given below - note that you can call the four_movesEvaluated() function as well as the four_move() function in here
	
	return 'd1\n'
# end

def four_moveNegamax(intMaxdepth, intDuration):
	# perform a negamax move and return it - one example output is given below - note that you can call the the other functions in here
	
	return 'd1\n'
# end

def four_moveAlphabeta(intMaxdepth, intDuration):
	# perform a alphabeta move and return it - one example output is given below - note that you can call the the other functions in here
	
	return 'd1\n'
# end

def four_undo():
	# undo the last move and update the state of the game / your internal variables accordingly - note that you need to maintain an internal variable that keeps track of the previous history for this
	
	pass
# end