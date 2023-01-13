// Dictionary class implements a dictionary and utilizes a hash table with separate chaining to handle collisions

/* java.util package used to create object of type LinkedList without creating additional classes
 *  Dr. Roberto Solis-Oba was contacted to verify that using this package doesn't violate assignment specifications
 */
import java.util.*;

public class Dictionary implements DictionaryADT {

	private LinkedList<Record>[] boardHash; // represents the hash table
	private int length; // represents the size of the hash table
	private int numRecords = 0; //represents how many records are stored in the hash table at a given moment
	
	// unchecked warnings suppressed as this class does not have to account for invalid input
	@SuppressWarnings("unchecked")
	
	/*
	 * class constructor initializes a hash table
	 * size the size of the hash table
	 */
	public Dictionary(int size) {
		
		boardHash = new LinkedList[size];
		length = size;
	}
	
	/*
	 * this function inserts record into the hash table, throws exception if the record already exists
	 * rec represents the record to be inserted
	 */
	public int put(Record rec) throws DuplicatedKeyException {
		
		String key = rec.getKey(); // the record's key attribute, 'key' is retrieved
		int position = hashFunction(key); // the record's position within the hash table is determined using the hash function
		LinkedList<Record> currList = boardHash[position];
		
		if (get(key) != null) throw new DuplicatedKeyException("Object is already in dictionary");
		
		else if (currList == null) { // new LinkedList is created at correct index if no other records exists there
			LinkedList<Record> newList = new LinkedList<Record>();
			boardHash[position] = newList;
			newList.add(rec);
			numRecords++; // number of records is incremented
			
			return 0;
		}
		
		else { // if a record already exists at this index, the new record is added to the LinkedList there
			currList.add(rec);
			numRecords++; // number of records is incremented
			
			return 1;
		}
	}
	
	/*
	 * this function removes a key from the hash table, throws an exception if the key does not exist
	 * key represents the key attribute at which to remove
	 */
	public void remove(String key) throws InexistentKeyException {
		
		int position = hashFunction(key); // the key's position within the hash table is determined using the hash function
		LinkedList<Record> currList = boardHash[position];
		
		if (get(key) == null) throw new InexistentKeyException("No stored Record object with given value");
		
		else {
			currList.remove(get(key));
			numRecords--; // number of records is decremented
		}
	}
	
	/*
	 * getter method to return the record object stored at the index corresponding to parameter key
	 * key represents the key attribute
	 */
	public Record get(String key) {
		
		int position = hashFunction(key); // the key's position within the hash table is determined using the has function
		LinkedList<Record> currList = boardHash[position];
		
		if (currList == null) return null; // null is returned if there is no record object at the key value
		
		for (int i = 0; i < currList.size(); i++) {
			if (currList.get(i).getKey().equals(key)) {
				return currList.get(i);
			}
		}
		
		return null;
	}
	
	/*
	 * this method returns to the user the number of records stored in the hash table
	 */
	public int numRecords() {
		
		return numRecords; // this function can simply return the numRecords variable as it is incremented and decremented whenever necessary in this class' other methods
	}
	
	/*
	 * this method operates as a hash function to compute a hash table index given the key attribute, key
	 * key represents the key attribute
	 */
	private int hashFunction(String key) {
		
		int currHashCode = 0; // the hash code is initialized and set to zero
		int primeNum = 43; // this value is chosen as it gives a relatively low number of collisions
		
		currHashCode = (int)key.charAt(0);
		for (int i = 1; i < key.length(); i++) {
			currHashCode = (currHashCode * primeNum + (int)key.charAt(i)) % length; // Here, Horner's Rule is implemented to mitigate integer overflow
		}
		
		int hashCode = currHashCode; // once hash code is finalized it is set to variable hashCode
		
		return hashCode;
	}
}
