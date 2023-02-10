/* The MyMap class is used to represent the roadmap that is to be traversed through.
 * In this assignment, a graph is used to store the map.
 * The graph's nodes represent stops, and the edges represent roads between stops.
 * The goal here is to traverse the map from the start to the destination while satisfying the provided conditions.
 */

import java.util.Iterator;
import java.util.Stack;
import java.io.BufferedReader;
import java.io.FileReader;

public class MyMap {
	
	private Graph mapGraph;
	private Node startNode;
	private Node destNode;
	private int width;
	private int length;
	private int numPrivate;
	private int numConstruct;

	
	
	public MyMap(String inputFile) throws MapException {
		
		BufferedReader fileReader;
		
		try {
			
			fileReader = new BufferedReader(new FileReader(inputFile));
			
			fileReader.readLine(); // The first line, representing the scale, is read and ignored
			this.startNode = new Node(Integer.parseInt(fileReader.readLine()));
			this.destNode = new Node(Integer.parseInt(fileReader.readLine()));
			this.width = Integer.parseInt(fileReader.readLine());
			this.length = Integer.parseInt(fileReader.readLine());
			this.numPrivate = Integer.parseInt(fileReader.readLine());
			this.numConstruct = Integer.parseInt(fileReader.readLine());
			
			this.mapGraph = new Graph(width * length); // Initializes the graph's nodes			
			
			// Now, we are at the point in the file that represents the individual nodes and edges of the graph.
			
			String currLine = fileReader.readLine(); // Reads the first line that represents the graph
			
			int nodeNum = width - 1; // This variable will represent the id of the previous node used for the next edge to be created.
									 // This value is initialized to width - 1 and will be set to 0 during the reading of the first line
			int currRow; // This variable represents the index of the current row we are scanning
			int currChar; // This variable represents the character index of the string representing the current row we are scanning
			
			for (currRow = 0; currRow < length * 2 - 1; currRow++) { // Iterates through the remaining rows of the text file
				
				char[] lineCharArray = currLine.toCharArray(); // Converts the line of text from the file into a character array that can be iterated through
				
				if (currRow % 2 == 0) { // Handles rows with even index (row 0, 2, 4, etc.)
					
					nodeNum = nodeNum - width + 1; // Sets the value of nodeNum to the first node in the horizontal row of nodes to be connected
					
					for (currChar = 1; currChar < width * 2 - 1; currChar = currChar + 2) { // Iterates through characters at odd index in the text string
											
						// The following if/elif statements handle the different possible types of edges and initialize them properly
						if (lineCharArray[currChar] == 'P') {
							
							mapGraph.addEdge(mapGraph.getNode(nodeNum), mapGraph.getNode(++nodeNum), "public");
						}
						else if (lineCharArray[currChar] == 'V') {
							
							mapGraph.addEdge(mapGraph.getNode(nodeNum), mapGraph.getNode(++nodeNum), "private");
						}
						else if (lineCharArray[currChar] == 'C') {
							
							mapGraph.addEdge(mapGraph.getNode(nodeNum), mapGraph.getNode(++nodeNum), "construction");
						}
						else if (lineCharArray[currChar] == 'B') {
							
							nodeNum++;
						}
					}
				}
				
				else if (currRow % 2 == 1) { // Handles rows with odd index (row 1, 3, 5, etc.)
					
					for (currChar = 0; currChar < 2 * width - 1; currChar = currChar + 2) { // Iterates through characters at even index in the text string
										
						// The following if/elif statements handle the different possible types of edges and initialize them properly
						if (lineCharArray[currChar] == 'P') {
							
							mapGraph.addEdge(mapGraph.getNode(++nodeNum - width), mapGraph.getNode(nodeNum), "public");
						}
						else if (lineCharArray[currChar] == 'V') {
							
							mapGraph.addEdge(mapGraph.getNode(++nodeNum - width),  mapGraph.getNode(nodeNum),  "private");
						}
						else if (lineCharArray[currChar] == 'C') {
							
							mapGraph.addEdge(mapGraph.getNode(++nodeNum - width), mapGraph.getNode(nodeNum),  "construction");
						}
						else if (lineCharArray[currChar] == 'B') {
							
							nodeNum++;
						}
					}
				}
				
				currLine = fileReader.readLine(); // Read the next row of the text file
			}
			
			fileReader.close(); // Close fileReader once all lines of the text file have been read
		}
		catch (Exception e) { // If an exception is thrown, no file exists with whatever name is provided to the constructor
			
			throw new MapException("Error: no file exists with the given filename.");
		}
		
	}
	
	// Getter method, returns the graph representing the map
	public Graph getGraph() {
		
		return this.mapGraph;
	}
	
	
	// Getter method, returns the id of the starting node on the map
	public int getStartingNode() {
	
		return this.startNode.getId();
	}
	
	// Getter method, returns the id of the destination node on the map
	public int getDestinationNode() {
		
		return this.destNode.getId();
	}
	
	// Getter method, returns the maximum number of private nodes that can be traversed
	public int maxPrivateRoads() {
		
		return this.numPrivate;
	}
	
	// Getter method, returns the maximum number of construction nodes that can be traversed
	public int maxConstructionRoads() {
		
		return this.numConstruct;
	}
	
	/* This method is used to find a path from the starting node to the destination node.
	 * This method also takes parameters maxPrivate and maxConstruction, which represent the maximum 
	 * number of private and construction nodes that can be traveled through, respectively.
	 * This method uses the 'path' helper method that is defined after this one.
	 */
	public Iterator<Node> findPath(int start, int destination, int maxPrivate, int maxConstruction) {
		
		Stack<Node> emptyPath = new Stack<Node>(); // Initialize an empty stack to be passed as a parameter to the helper method
		
		try {
			
			// The following line initializes a stack called pathToEnd that will contain all nodes found from the start to destination node, if a solution exists.
			Stack<Node> pathToEnd = path(mapGraph.getNode(start), mapGraph.getNode(destination), maxPrivate, maxConstruction, emptyPath);
			
			if (pathToEnd != null) { // An iterator of the pathToEnd stack is returned if there is a solution
				
				return pathToEnd.iterator();
			}
			
			else return null; // Otherwise, the method simply returns null
			
		} catch (GraphException e) {
			
			return null; // Return null if any exception is thrown (no path found in this case)
		}
	}
	
	/* The path method is a helper method that is used to find a path from the start node to the destination node.
	 * This method calls upon itself recursively whenever traversing to a new node, making the necessary parameter changes every time it does so.
	 * This method takes in the following parameters:
	 * curr - the Node currently being examined
	 * dest - the destination node
	 * privateLeft - the number of private roads we can traverse at this point in the map
	 * constructLeft - the number of construction roads we can traverse at this point in the map
	 * nodeStack - the current stack containing the nodes traversed in the current path
	 */
	private Stack<Node> path(Node curr, Node dest, int privateLeft, int constructLeft, Stack<Node> nodeStack) throws GraphException {
		
		curr.markNode(true); // The node we are attempting to add to our path is marked as true to avoid re-traversal
		nodeStack.push(curr); // The node is pushed onto the path stack
				
		if (curr.getId() == dest.getId()) return nodeStack; // If we are at the destination node, return the path stack
		
		Iterator<Edge> currEdges = mapGraph.incidentEdges(curr); // This creates an iterator containing the edges incident on the current node
		while (currEdges.hasNext()) { // Loops until all incident edges have been explored
			
			Edge nextEdge = currEdges.next(); // The 'discovery' edge is created for each iteration of the incidentEdges iterator
			Node next = nextEdge.secondNode(); // This represents the node at the end of the discovery edge
			
			if (next.getMark() == false) { // If the next node has not already been involved in our current path, attempt to travel to it
				
				if (nextEdge.getType() == "public") { // If the edge we are to travel is public,
					
					Stack<Node> result = path(next, dest, privateLeft, constructLeft, nodeStack); // The parameters of the recursive call need not change
					if (result != null) return result; // If this path or one of its descendants contains a solution, return that solution
				}
				
				else if ((nextEdge.getType() == "private") && (privateLeft >= 1)) { // If the edge we are to travel is private,
					
					Stack<Node> result = path(next, dest, privateLeft - 1, constructLeft, nodeStack); // The parameter representing the number of private roads we are still able to traverse is decremented
					if (result != null) return result; // If this path or one of its descendants contains a solution, return that solution
				}
				
				else if ((nextEdge.getType() == "construction") && (constructLeft >= 1)) { // If the edge we are to travel is a construction type,
					
					Stack<Node> result = path(next, dest, privateLeft, constructLeft - 1, nodeStack); // The parameter representing the number of construction roads we are still able to traverse is decremented
					if (result != null) return result; // If this path or one of its descendants contains a solution, return that solution
				}
			}
		}
				
		nodeStack.pop(); // If no solutions exist following any of the current node's edges, pop that node from the stack
		curr.markNode(false); // Then, mark the node as false in case we need to travel over it in some different path
		return null; // Return null, indicating no solution was found using the path up to this point
	}
}
