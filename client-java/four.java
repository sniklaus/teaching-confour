import java.util.Vector;

public class four {
    public static void reset() {
        // reset the state of the game / your internal variables - note that this function is highly dependent on your implementation
    }
    
    public static String boardGet() {
        // return the state of the game - one example is given below - note that the state has exactly 52 or 53 characters
        
        String strOut = "";
        
        strOut += "1 X\n";
        strOut += "       \n";
        strOut += "       \n";
        strOut += "       \n";
        strOut += "       \n";
        strOut += "       \n";
        strOut += "       \n";
        
        return strOut;
    }
    
    public static void boardSet(String strIn) {
        // read the state of the game from the provided argument and set your internal variables accordingly - note that the state has exactly 40 or 41 characters
    }
    
    public static char winner() {
        // determine the winner of the current state of the game and return '?' or '=' or 'X' or 'O' - note that we are returning a character and not a string
        
        return '?';
    }
    
    public static boolean isValid(int intX, int intY) {
        if (intX < 0) {
            return false;
            
        } else if (intX > 6) {
            return false;
            
        }
        
        if (intY < 0) {
            return false;
            
        } else if (intY > 5) {
            return false;
            
        }
        
        return true;
    }
    
    public static boolean isEnemy(char charPiece) {
        // with reference to the state of the game, return whether the provided argument is a piece from the side not on move - note that we could but should not use the other is() functions in here but probably
        
        return false;
    }
    
    public static boolean isOwn(char charPiece) {
        // with reference to the state of the game, return whether the provided argument is a piece from the side on move - note that we could but should not use the other is() functions in here but probably
        
        return false;
    }
    
    public static boolean isNothing(char charPiece) {
        // return whether the provided argument is not a piece / is an empty field - note that we could but should not use the other is() functions in here but probably
        
        return false;
    }
    
    public static int eval() {
        // with reference to the state of the game, return the the evaluation score of the side on move - note that positive means an advantage while negative means a disadvantage
        
        return 0;
    }
    
    public static Vector<String> moves() {
        // with reference to the state of the game and return the possible moves - one example is given below - note that a move has exactly 3 characters
        
        Vector<String> strOut = new Vector<String>();
        
        strOut.add("a1\n");
        strOut.add("b1\n");
        strOut.add("c1\n");
        strOut.add("d1\n");
        strOut.add("e1\n");
        strOut.add("f1\n");
        strOut.add("g1\n");
        
        return strOut;
    }
    
    public static Vector<String> movesShuffled() {
        // with reference to the state of the game, determine the possible moves and shuffle them before returning them - note that you can call the four.moves() function in here
        
        return new Vector<String>();
    }
    
    public static Vector<String> movesEvaluated() {
        // with reference to the state of the game, determine the possible moves and sort them in order of an increasing evaluation score before returning them - note that you can call the four.movesShuffled() function in here
        
        return new Vector<String>();
    }
    
    public static void move(String charIn) {
        // perform the supplied move (for example "a5-a4\n") and update the state of the game / your internal variables accordingly - note that it advised to do a sanity check of the supplied move
    }
    
    public static String moveRandom() {
        // perform a random move and return it - one example output is given below - note that you can call the four.movesShuffled() function as well as the four.move() function in here
        
        return "d1\n";
    }
    
    public static String moveGreedy() {
        // perform a greedy move and return it - one example output is given below - note that you can call the four.movesEvaluated() function as well as the four.move() function in here
        
        return "d1\n";
    }
    
    public static String moveNegamax(int intMaxdepth, int intDuration) {
        // perform a negamax move and return it - one example output is given below - note that you can call the the other functions in here
        
        return "d1\n";
    }
    
    public static String moveAlphabeta(int intMaxdepth, int intDuration) {
        // perform a alphabeta move and return it - one example output is given below - note that you can call the the other functions in here
        
        return "d1\n";
    }
    
    public static void undo() {
        // undo the last move and update the state of the game / your internal variables accordingly - note that you need to maintain an internal variable that keeps track of the previous history for this
    }
}