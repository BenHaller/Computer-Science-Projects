// the Evaluate class implements the methods needed by the provided algorithm that plays the game to determine the game status

public class Evaluate {

	private char[][] gameBoard; // represents the current state of the game board
	private int winTiles; // represents the number of adjacent tiles to win the game
	@SuppressWarnings("unused") // prevents warning for playQuality variable as it is never used, but still initialized as it is defined within the assignment specifications
	private int playQuality; // represents the quality of how the game plays (never actually used in the assignment)
	private int dimension; // represents the board dimension
	
	/*
	 * class constructor initializes a game
	 * parameters size, tilesToWin and maxLevels represent dimension, winTiles and playQuality shown above
	 */
	public Evaluate(int size, int tilesToWin, int maxLevels) {
		
		gameBoard = new char[size][size];
		winTiles = tilesToWin;
		playQuality = maxLevels;
		dimension = size;

		for (int i = 0; i < size; i++) { // here, every tile within the game board is initialized to 'e' for empty
			for (int j = 0; j < size; j++) {
				gameBoard[i][j] = 'e';
			}
		}
	}
	
	/*
	 * method to create a dictionary for history of games played
	 */
	public Dictionary createDictionary() {
		
		int prime_size = 1187; // prime number is chosen for dictionary size, sufficiently large to reduce collisions over many possible usages
		Dictionary user_dict = new Dictionary(prime_size);
		
		return user_dict;
	}
	
	/*
	 * this method checks the dictionary for a game with record corresponding to the game's string representation
	 */
	public Record repeatedState(Dictionary dict) {
		
		String stringRep = "";
		
		for (int i = 0; i < dimension; i++) { // here, a string representation of the game board is created
			for (int j = 0; j < dimension; j++) {
				stringRep += gameBoard[i][j];
			}
		}
		
		Record gameRec = dict.get(stringRep); // this sets gameRec to the Record object if it exists, or null if it doesn't
		
		return gameRec;
	}
	
	/*
	 * this method creates a Record object corresponding to the gameBoard content and then stores it in the dictionary
	 */
	public void insertState(Dictionary dict, int score, int level) {
		
		String stringRep = "";
		
		for (int i = 0; i < dimension; i++) { // here, a string representation of the game board is created
			for (int j = 0; j < dimension; j++) {
				stringRep += gameBoard[i][j];
			}
		}
		
		Record gameRec = new Record(stringRep, score, level);
		
		dict.put(gameRec);
		
	}
	
	// this method stores the corresponding symbol of a play in the correct game board index
	public void storePlay(int row, int col, char symbol) {
		
		gameBoard[row][col] = symbol;
	}
	
	// returns true if square is empty 
	public boolean squareIsEmpty(int row, int col) {
		
		if (gameBoard[row][col] == 'e') return true;
		else return false;
	}
	
	// returns true if tile has been selected by the computer
	public boolean tileOfComputer(int row, int col) {
		
		if (gameBoard[row][col] == 'c') return true;
		else return false;
	}
	
	// returns true if tile has been selected by the human
	public boolean tileOfHuman(int row, int col) {
		
		if (gameBoard[row][col] == 'h') return true;
		else return false;
	}
	
	/*
	 * this method checks the board for a win by either the computer or human
	 * symbol represents the symbol to check for the required number of adjacent tiles
	 */
	public boolean wins(char symbol) {
		
		int i, j;
		int counter = 0;
		
		// check for required number of adjacent tiles in the same row
		
		for (i = 0; i < dimension; i++) {
			for (j = 0; j < dimension; j++) {
				int row = i;
				int column = j;
				
				while ((column < dimension) && (gameBoard[row][column] == symbol)) {
					counter++;
					column++;
					
					if (counter >= winTiles) return true;
				}
				
				counter = 0;
			}
		}
		
		// check for required number of adjacent tiles in same column
		
		for (i = 0; i < dimension; i++) {
			for (j = 0; j < dimension; j++) {
				int row = i;
				int column = j;
				
				while ((row < dimension) && (gameBoard[row][column] == symbol)) {
					counter++;
					row++;
					
					if (counter >= winTiles) return true;
				}
				
				counter = 0;
			}
		}
		
		// check for required number of adjacent tiles in diagonal from top left to bottom right
		
		for (i = 0; i < dimension; i++) {
			for (j = 0; j < dimension; j++) {
				int row = i;
				int column = j;
				
				while ((row < dimension) && (column < dimension) && (gameBoard[row][column] == symbol)) {
					counter++;
					row++;
					column++;
					
					if (counter >= winTiles) return true;
				}
				
				counter = 0;
			}
		}
		
		// check for required number of adjacent tiles in diagonal from top right to bottom left
		
		for (i = 0; i < dimension; i++) {
			for (j = 0; j < dimension; j++) {
				int row = i;
				int column = j;
				
				while ((row >= 0) && (column < dimension) && (gameBoard[row][column] == symbol)) {
					counter++;
					row--;
					column++;
					
					if (counter >= winTiles) return true;
				}
				
				counter = 0;
			}
		}
		
		// if none of the above conditions are met, return false
		
		return false;
	}
	
	// method checks whether all tiles are occupied to indicate a draw
	public boolean isDraw() {
		
		boolean draw = true;
		
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				if (gameBoard[i][j] == 'e') draw = false;
			}
		}
		
		return draw;
	}
	
	// method checks the game state
	public int evalBoard() {
		
		if (wins('c')) return 3; // return 3 if computer has won
		else if (wins('h')) return 0; // return 0 if human has won
		else if (isDraw()) return 2; // return 2 if game is a draw
		else return 1; // return 1 if game is undecided
	}
}
