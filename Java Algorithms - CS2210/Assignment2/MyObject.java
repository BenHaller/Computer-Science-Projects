// The MyObject class represents an object within the game.

public class MyObject implements MyObjectADT{

	private int object_id; // Represents the object's identifier
	private int object_width; // Represents the width of the object
	private int object_height; // Represents the height of the object
	private String object_type; // Represents the object's type, can take on values 'fixed', 'user', 'computer' or 'target'
	private Location position; // Represents the current location of the object
	private BinarySearchTree tree; // Represents the BST used to store an ordered dictionary
	
	// Class constructor initializes the MyObject, taking parameters for id, width, height, type and position and initializing a BST to store information about the object
	public MyObject(int id, int width, int height, String type, Location pos) {
		
		this.object_id = id;
		this.object_width = width;
		this.object_height = height;
		this.object_type = type;
		this.position = pos;
		this.tree = new BinarySearchTree();
	}
	
	// Setter method to set the 'type' attribute
	public void setType(String type) {
		
		this.object_type = type;
	}
	
	// Getter method returns the object's width
	public int getWidth() {
		
		return this.object_width;
	}
	
	// Getter method returns the object's height
	public int getHeight() {
		
		return this.object_height;
	}
	
	// Getter method returns the object's type
	public String getType() {
		
		return this.object_type;
	}
	
	
	// Getter method returns the object's identifier
	public int getId() {
		
		return this.object_id;
	}
	
	// Getter method returns the position of the object
	public Location getLocus() {
		
		return this.position;
	}
	
	/* Setter method to set the position of the object to a new value
	 * Takes parameter value to set new object position to
	 */
	public void setLocus(Location value) {
		
		this.position = value;
	}
	
	/* The addPel method is used to add a new node to the BST
	 * Returns nothing if the node is successfully added, throws DuplicatedKeyException if a node already exists with the given key value
	 * Takes parameter pix to set to new node's key value
	 */
	public void addPel(Pel pix) throws DuplicatedKeyException{
		
		this.tree.put(tree.getRoot(), pix); // The put method is called to insert the new node into the BST
	}
	
	/* The intersects method is used to check for intersections between the current 'this' object and the otherObject
	 * Returns true if the objects intersect, false if they do not
	 * Takes parameter otherObject to check for intersection
	 */
	public boolean intersects(MyObject otherObject) {
		
		// Here, the x and y locations for both the 'this' object and the otherObject
		int BST_x_value = this.getLocus().getx();
		int BST_y_value = this.getLocus().gety();
		int other_x_value = otherObject.getLocus().getx();
		int other_y_value = otherObject.getLocus().gety();
		
		try {
			
			// This for loop is used to iterate through the BST and get the x and y values for each Pel object
			// Starts at the smallest value within the tree, takes the successor of that value repeatedly until all values have been iterated through
			for (Pel BST_pel = tree.smallest(tree.getRoot()); BST_pel != null; BST_pel = tree.successor(tree.getRoot(), BST_pel.getLocus())) {
				
				int x_value = BST_pel.getLocus().getx(); // Sets x_value to current node's x value
				int y_value = BST_pel.getLocus().gety(); // Sets y_value to current node's y value
				
				// If the otherObject's tree has some Pel object with coordinates equal to the value below
				if (otherObject.tree.get(otherObject.tree.getRoot(), new Location(x_value + BST_x_value - other_x_value, y_value + BST_y_value - other_y_value)) != null) return true; // Return true, as an intersection has occurred
			}
		}
		catch (Exception e) {} // Catch block used to ensure no exceptions cause crash
		
		return false; // If no iteration of the above loop returns true, no intersection is currently happening and the method returns false
	}
}
