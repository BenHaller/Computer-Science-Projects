// The Location class is used to represent the (x,y) coordinate location of a pel (a data item stored in the node of the binary search tree).
// A Pel's object's location will be the position of some pixel on the screen.

public class Location {
	
	private int x_location; // The x coordinate
	private int y_location; // The y coordinate
	
	// Class constructor, initializes object's coordinates
	public Location(int x, int y) { 
		
		this.x_location = x;
		this.y_location = y;
	}
	
	// Getter method to return the x coordinate of a Location
	public int getx() {
		
		return this.x_location;
	}
	
	// Getter method to return the y coordinate of a Location
	public int gety() {
		
		return this.y_location;
	}
	
	/* This method is used to compare the positions of two Location objects
	 * Takes parameter p representing the Location object to compare against
	 * Returns 1 if 'this' Location object's position is greater than the 'p' object's position
	 * Returns 0 if 'this' object's position is equal to that of the 'p' object
	 * Otherwise, returns 1
	 */
	public int compareTo(Location p) {
		
		if (this.gety() > p.gety() || (this.gety() == p.gety() && (this.getx() > p.getx()))) return 1; // Determine if 'this' object's position is greater than p, first by y coordinate then by x
		else if ((this.getx() == p.getx()) && (this.gety() == p.gety())) return 0; // Check if positions are equal
		else return -1; // If neither case satisfied, return -1
	}
	
}
