/* The Edge.java class is used to represent an edge of the graph.
 * Each edge contains the two nodes at its endpoints.
 * Each edge also contains a string declaring what type of edge it is (public, private, construction).
 */

public class Edge {

	private Node prevNode; // Represents the first node passed
	private Node nextNode; // Represents the second node passed
	private String edgeType; // Represents the edge type
	
	/* This is the Edge class constructor.
	 * This creates an edge with endpoint nodes u and v, respectively.
	 * Here, the type of the edge is also set to whatever string is passed to the constructor.
	 */
	public Edge(Node u, Node v, String type) {
		
		this.prevNode = u;
		this.nextNode = v;
		this.edgeType = type;
	}
	
	// Getter method, returns the first endpoint of the edge
	public Node firstNode() {
		
		return this.prevNode;
	}
	
	// Getter method, returns the second endpoint of the edge
	public Node secondNode() {
		
		return this.nextNode;
	}
	
	// Getter method, returns the type of the edge
	public String getType() {
		
		return this.edgeType;
	}
	
	
}
