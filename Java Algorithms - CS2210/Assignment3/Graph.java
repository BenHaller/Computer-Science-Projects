/* The Graph.java class represents an undirected graph.
 * This implementation uses an adjacency matrix to represent the graph.
 * The graph representation consists of two arrays, one representing the nodes, and another 2-dimensional array representing the edges between nodes.
 * The graph also has two integer values representing the current number of nodes and edges.
 */

import java.util.Iterator;
import java.util.*;

public class Graph implements GraphADT {

	private int numNodes; // Represents the number of nodes in the graph
	private Node nodesList[]; // An array of the nodes in the graph
	private Edge edgesList[][]; // A two-dimensional array of the edges in the graph
	
	/* This is the Graph class constructor.
	 * This constructor takes parameter n and creates a graph with n nodes.
	 * The constructor then sets the ids of all nodes to their respective index within the list.
	 * This constructor also initializes number of nodes and edges, and creates an empty edge list.
	 */
	public Graph(int n) {
		
		this.numNodes = n;		
		this.nodesList = new Node[n];
		this.edgesList = new Edge[n][n];
		
		for (int i = 0; i < n; i++) {
			
			nodesList[i] = new Node(i);
		}
	}

	// Getter method, returns the node with id equal to the parameter or throws an exception if it doesn't exist.
	public Node getNode(int id) throws GraphException {
		
		// Iterates through all nodes in the nodes list
		for (int i = 0; i < numNodes; i++) {
			
			if (nodesList[i].getId() == id) { // If current node has id equal to that in the parameter
				
				return nodesList[i]; // Return that node
			}
		}
		
		// If no node was found with the given id, an error is thrown.
		throw new GraphException("Error: no node exists with given id: " + id + ".");
	}
	
	/* The addEdge method adds an edge connecting nodeu and nodev with the given edge type.
	 * This method ensures that both nodeu and nodev exist, and also checks that no edge connecting these two already exists.
	 * If any of the above conditions are false, this method throws an exception.
	 */
	public void addEdge(Node nodeu, Node nodev, String edgeType) throws GraphException {
		
 		getNode(nodeu.getId()); // Throws GraphException if nodeu does not exist
		getNode(nodev.getId()); // Throws GraphException if nodev does not exist
		
		// Try catch block to handle exception
		try {
			
			getEdge(nodeu, nodev); // This will throw an exception if the edge does not exist
		}
		catch(GraphException e) { // If the edge in face does not exist, this handles the exception
			
			// Then, the edge is inserted into the correct places in the edges list
			edgesList[nodeu.getId()][nodev.getId()] = new Edge(nodeu, nodev, edgeType);
			edgesList[nodev.getId()][nodeu.getId()] = new Edge(nodev, nodeu, edgeType);
			return;
		}
		
		// If no exception was caught above, an exception is thrown indicating that an edge already exists connecting the two nodes.
		throw new GraphException("Error: there is already an edge connecting the given nodes.");
	}

	/* The incidentEdges method returns a Java Iterator storing all edges incident on the given node u.
	 * This method returns null if there are no incident edges on the node.
	 * This method also throws an exception if the node does not exist.
	 */
	public Iterator<Edge> incidentEdges(Node u) throws GraphException {
		
		getNode(u.getId()); // Throws an exception if the node u does not exist
		
		Stack<Edge> incidentEdges = new Stack<Edge>(); // A Java Stack will be created that will be iterated through by the iterator that is returned
		
		for (int i = 0; i < numNodes; i++) { // Iterates once for each possible node 
			
			if (edgesList[u.getId()][i] != null) { // If there is an edge connecting node u and some node with id 'i',
				
				incidentEdges.push(edgesList[u.getId()][i]); // Push that edge onto the stack
			}
		}
		
		if (incidentEdges.isEmpty()) {
			
			return null; // Avoids nullPointerException
		}
		
		else {
			
			return incidentEdges.iterator(); // Return an iterator of the stack
		}
	}

	// Getter method, returns the edge connecting nodes u and v if it exists, throws an exception otherwise
	public Edge getEdge(Node u, Node v) throws GraphException {
		
		getNode(u.getId()); // Throws an exception if the node u does not exist
		getNode(v.getId()); // Throws an exception of the node v does not exist
		
		Edge currEdge = edgesList[u.getId()][v.getId()]; // Sets current edge to the location in the edgesList where the connecting edge would be
		
		if (currEdge == null) throw new GraphException("Error: there is no edge between the two given nodes."); // Throws exception if the edge does not exist
		else return currEdge; // Otherwise, the edge connecting nodes u and v is returned
	}

	/* The areAdjacent method returns true if nodes u and v are adjacent, or false otherwise.
	 * This method also throws an exception if either nodes, u or v, do not exist.
	 */
	public boolean areAdjacent(Node u, Node v) throws GraphException {
	
		getNode(u.getId()); // Throws an exception if the node u does not exist
		getNode(v.getId()); // Throws an exception if the node v does not exist
		
		if (edgesList[u.getId()][v.getId()] != null) return true; // If an edge exists at the intersection of u and v in the edge matrix, return true
		else return false; // Otherwise, return false
	}

}
