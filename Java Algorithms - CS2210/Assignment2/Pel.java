// The Pel class represents the data items stored in the nodes of the binary search tree.
// Each Pel object can be thought of as representing some pixel on the screen, having both a position and a colour attribute.

public class Pel {

	private Location curr_location; // Represents the on-screen position
	private int color; // An integer representation of the Pel object's colour
	
	// Class constructor, initializes the object's location and colour
	public Pel(Location p, int color) {
		
		this.curr_location = p;
		this.color = color;
	}
	
	// Getter method, returns object's location
	public Location getLocus() {
		
		return this.curr_location;
	}
	
	// Getter method, returns object's colour
	public int getColor() {
		
		return this.color;
	}
}
