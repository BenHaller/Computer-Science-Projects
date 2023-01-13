// The BNode class represents the nodes of the binary search tree.
// In each node, a Pel object is stored as well as references to its left child, right child and parent nodes.

public class BNode {

	private Pel node_value; // Represents the value of the node
	private BNode left_child; // Represents the node's left child
	private BNode right_child; // Represents the node's right child
	private BNode parent_node; // Represents the nodes's parent
	
	// This class constructor is used to initialize an internal node, taking parameters and initializing every node attribute
	public BNode(Pel value, BNode left, BNode right, BNode parent) {
		
		this.node_value = value;
		this.left_child = left;
		this.right_child = right;
		this.parent_node = parent;
	}
	
	// This class constructor is used to initialize a leaf node, setting all node attributes to null
	public BNode() {
		
		this.node_value = null;
		this.left_child = null;
		this.right_child = null;
		this.parent_node = null;
	}
	
	// Getter method to return node's parent node
	public BNode parent() {
		
		return this.parent_node;
	}
	
	/* Setter method to set node's parent node to a new node
	 * Takes parameter newParent
	 */
	public void setParent(BNode newParent) {
		
		this.parent_node = newParent; // Set newParent to node's parent
	}
	
	/* Setter method to set new node left child
	 * Takes parameter p
	 */
	public void setLeftChild(BNode p) {
		
		this.left_child = p; // Set node's left child to p
	}
	
	/* Setter method to set new node right child
	 * Takes parameter p
	 */
	public void setRightChild(BNode p) {
		
		this.right_child = p; // Set node's right child to p
	}
	
	/* Setter method to set new node value
	 * Takes parameter value
	 */
	public void setContent(Pel value) {
		
		this.node_value = value; // Set node's value to value
	}
	
	/* Method to determine whether the current node is a leaf of not
	 * Returns true if leaf, false otherwise
	 */
	public boolean isLeaf() {
		
		// In this BST implementation, leaf nodes have a null value
		return (this.node_value == null); // Return true if node value is null, false otherwise 
	}
	
	// Getter method returns the node's value
	public Pel getData() {
		
		return this.node_value;
	}
	
	// Getter method returns the node's left child
	public BNode leftChild() {
		
		return this.left_child;
	}
	
	// Getter method returns the node's right child
	public BNode rightChild() {
		
		return this.right_child;
	}
}
