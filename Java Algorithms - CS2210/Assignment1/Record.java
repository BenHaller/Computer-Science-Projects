// the Record.java class represents a record to be stored in the hash table implemented through the Dictionary.java class



public class Record {

	/*
	 * key corresponds to key provided in constructor
	 * score corresponds to score provided in constructor
	 * level corresponds to level provided in constructor
	 */
	private String key;
	private int score;
	private int level;
	
	// key, score, level represent information about record to be stored in has table
	public Record(String key, int score, int level) {
		
		// variable names correspond to constructor parameters to maintain simplicity
		this.key = key;
		this.score = score;
		this.level = level;
	}
	
	/* getter method to provide key
	 * key parameter of Record object */
	public String getKey() {
		
		return this.key;
	}
	
	/* getter method to provide score
	 * score parameter of Record object */
	public int getScore() {
		
		return this.score;
	}
	
	/* getter method to provide level
	 * level parameter of Record object */
	public int getLevel() {
		
		return this.level;
	}
	
}
