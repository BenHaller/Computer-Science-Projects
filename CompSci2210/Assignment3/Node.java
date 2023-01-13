/* The Node.java class is used to represent a node of the graph.
 * Each node has a unique id, and has a boolean value representing whether or not the node is marked yet.
 */

public class Node {

	private int id; // Represents the id of the node
	private boolean isMarked; // Represents whether or not the node is marked yet
	
	/* This is the Node class constructor.
	 * This creates a node with id equal to the parameter passed.
	 * When a node is initially created it is not marked.
	 */
	public Node(int id) {
		
		this.id = id;
		isMarked = false;
	}
	
	// Setter method to or to not mark the node depending on the parameter 'mark'.
	public void markNode(boolean mark) {
		
		this.isMarked = mark;
	}
	
	// Getter method to return whether or not the node is marked.
	public boolean getMark() {
		
		return this.isMarked;
	}
	
	// Getter method to return the id of the node.
	public int getId() {
		
		return this.id;
	}
	
}
