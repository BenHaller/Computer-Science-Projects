// The BinarySearchTree class implements an ordered dictionary through means of a binary search tree.
// The BST is used to store BNode objects, which in turn creates a dictionary of Pel objects.

public class BinarySearchTree implements BinarySearchTreeADT {

	private BNode root; // Represents the root node of the BST
	
	// Class constructor initializes the BST root to a leaf node
	public BinarySearchTree() {
		
		this.root = new BNode();
	}
	
	/* The findNode method is a helper method to return the BNode in the BST with the given key value
	 * Returns the node if it exists, returns a leaf node if it does not
	 */
	private BNode findNode(BNode r, Location key) {
		
		if (r.isLeaf()) { // If a function call is made where the r parameter is a leaf node, no such key value exists and the leaf node is returned
			return r;
		}
		else {
			if (r.getData().getLocus().compareTo(key) == 0) return r; // If node's location equals key, the BNode is returned 
			else if (key.compareTo(r.getData().getLocus()) < 0) { // If this is true, the key value is less than that in the current node
				return findNode(r.leftChild(), key); // Thus, perform recursive call with the left subtree
			}
			else {
				return findNode(r.rightChild(), key); // Otherwise, key value is greater than that in the current node, perform recursive call with the right subtree
			}
		}
	}
	
	/* The findMin method is a helper method to return the node in the tree with root r that has the smallest key value
	 * Returns the smallest node if r is an internal node, returns r if it is a leaf node
	 */
	private BNode findMin(BNode r) {
		
		if (r.isLeaf()) return r; // If r is a leaf node return r
		else {
			
			BNode p = r;
			while (!p.isLeaf()) { // This loop continues until node p is the leftmost node in the tree with root r
				p = p.leftChild();
			}
			
			return p.parent(); // Then the parent of leaf node p is returned, this being the leftmost internal node in the tree with root r
		}
	}
	
	/* The get method is used to return the Pel object storing the given key value
	 * Returns the Pel object if the key value exists, null otherwise
	 * Takes parameters root r of BST and key value for which to search
	 */
	public Pel get(BNode r, Location key) {
		
		if (r.isLeaf()) return r.getData(); // If root r is a leaf, it means no such key value and r's data (null, since leaf node) is returned
		else {
			if (r.getData().getLocus().compareTo(key) == 0) return r.getData(); // If the data of the input node equals that of the parameter key, return r's data
			else if (key.compareTo(r.getData().getLocus()) < 0) { // If this is true, the key value is less than that in the current node
				return get(r.leftChild(), key); // Thus, perform recursive call with the left subtree
			}
			else return get(r.rightChild(), key); // Otherwise, key value is greater than that in the current node, perform recursive call with the right subtree
		}
	}
	
	/* The put method inserts a node with value newData into the BST
	 * Returns nothing if the node is successfully inserted, throws DuplicatedKeyException if a node already exists with the given value
	 * Takes parameters root node r and Pel object newData to be inserted
	 */
	public void put(BNode r, Pel newData) throws DuplicatedKeyException {
		
		BNode p = findNode(r, newData.getLocus()); // findNode method called to check if given value exists in some node already in the BST
		
		if (p.getData() != null) throw new DuplicatedKeyException("Error: given key already exists in the BST!"); // If value exists, error thrown
		
		// If value does not exist, initialize the node
		else {
			p.setContent(newData); // Set the value of node p to parameter newData
			BNode left_child = new BNode(); // Initialize leaf node left_child
			p.setLeftChild(left_child); // Set left_child to left child of node p
			BNode right_child = new BNode(); // Initialize leaf node right_child
			p.setRightChild(right_child); // Set right_child to the right child of p
			// Set p as the parent of nodes left_child and right_child
			left_child.setParent(p);
			right_child.setParent(p);
			// Now, the new node is inserted into the BST and properly implemented
		}
		
	}
	
	/* The remove method is used to remove a node with value key from the BST
	 * Returns nothing if the node is successfully removed, throws InexistentKeyException if no node exists with the given value
	 * Takes parameters root node r and Location object key for which to remove
	 */
	public void remove(BNode r, Location key) throws InexistentKeyException {
		
		BNode p = findNode(r, key); // findNode method called to ensure that a node exists with the given location key
				
		if (p.isLeaf()) throw new InexistentKeyException("Error: given key does not exist in the BST!"); // If no node exists with the key value, error thrown
		
		// If the value does exist, remove it 
		else {
			
			if (p.leftChild().isLeaf() || p.rightChild().isLeaf()) { // If either of the node's children are leafs
				
				if (p.leftChild().isLeaf()) { // If the node's left child is a leaf
					
					BNode c_prime = p.rightChild(); // Set new node c prime to the right child of node p
					BNode p_prime = p.parent(); // Set new node p prime to the parent of node p
					if (p_prime != null) { // If node p has a parent node
						p_prime.setLeftChild(c_prime); // Set c prime as the new left child of p prime
					}
					else this.root = c_prime; // Otherwise, set the node c prime to the new root of the BST
				}
				
				if (p.rightChild().isLeaf()) { // If the node's right child is a leaf
					
					BNode c_prime = p.leftChild(); // Set new node c prime to the left child of node p
					BNode p_prime = p.parent(); // Set new node p prime to the parent of node p
					if (p_prime != null) { // If node p has a parent node
						p_prime.setRightChild(c_prime); // Set c prime as the new right child of p prime
					}
					else this.root = c_prime; // Otherwise, set the node c prime to the new root of the BST
				}
			}
			
			else { // If neither of the node's children are leafs
				
				BNode s = findMin(p.rightChild()); // Using the findMin helper method, set node s to the smallest node within the right subtree of p
				p.setContent(s.getData()); // Copy the record of node s into node p
				remove(s, s.getData().getLocus()); // Remove node s from the BST
			}
		}
		
	}
	
	/* The successor method is used to find the successor of the value key in the BST
	 * Returns null if the given key value has no successor, returns the Pel object with the smallest key greater than the given one otherwise
	 * Note: this method returns the successor even if the given key value itself does not exist within the BST
	 * Takes parameters root node r and Location object key
	 */
	public Pel successor(BNode r, Location key) {
		
		BNode p = findNode(r, key); // Helper method findNode used to search for a node with the given key value key
		
		if (!p.isLeaf() && !p.rightChild().isLeaf()) // If neither p or its right child are leaf nodes
			try { // Try catch block used to account for 'smallest' method which may throw an EmptyTreeException
				return smallest(p.rightChild()); // In this case, the successor is the smallest node within the right subtree of node p
			} catch (EmptyTreeException e) {
				return null;
			}
		
		else {
			
			BNode p_prime = p.parent(); // Set node p_prime to the parent of node p
			while (p_prime != null && p == p_prime.rightChild()) { // While loop used to go up BST hierarchy to find successor
				
				p = p_prime;
				p_prime = p_prime.parent();
			}
			
			return p_prime.getData(); // Successor is now node p_prime, the data of that node is returned
		}
		
	}
	
	/* The predecessor method is used to find the predecessor of the value key in the BST
	 * Returns null if the given key value has no predecessor, returns the Pel object with the largest key lesser than the given one otherwise
	 * Note: this method returns the predecessor even if the given key value itself does not exist within the BST
	 * Takes parameters root node r and Location object key
	 * This method is very similar to the successor method, but with some minor differences that are highlighted below
	 */
	public Pel predecessor(BNode r, Location key) {
		
		BNode p = findNode(r, key);
		
		if (!p.isLeaf() && !p.leftChild().isLeaf()) // Checks left child instead of right one
			try { // 'largest' method also requires a try catch block
				return largest(p.leftChild()); // In this case, predecessor is the largest node within the left subtree of node p
			} catch (EmptyTreeException e) {
				return null;
			}
		
		else {
			
			BNode p_prime = p.parent();
			while (p_prime != null && p == p_prime.leftChild()) { // Go up BST hierarchy
				
				p = p_prime;
				p_prime = p_prime.parent();
			}
			
			return p_prime.getData(); // Predecessor is now node p_prime, whose data is returned
		}
	}
	
	/* The smallest method is used to find the smallest value in the tree with root r
	 * Returns the Pel object of the node with smallest value if it exists, throws EmptyTreeException otherwise
	 * Takes parameter r, the root node of the tree for which to search
	 */
	public Pel smallest(BNode r) throws EmptyTreeException {
		
		if (r.isLeaf()) throw new EmptyTreeException("Error: given BST is empty!"); // If the root node is a leaf then the provided BST has no values
		
		else {
			
			BNode p = r; // Set node p to have attributes equal to node r
			while (!p.isLeaf()) { // Iterates until p is the leftmost leaf in the BST
				
				p = p.leftChild();
			}
			
			return p.parent().getData(); // Returns the parent of the leftmost leaf, this being the leftmost internal node
		}
	}
	
	/* The largest method is used to find the largest value in the tree with root r
	 * Returns the Pel object of the node with largest value if it exists, throws EmptyTreeException otherwise
	 * Takes parameter r, the root node of the tree for which to search
	 * This method is very similar to the smallest method, but with some minor differences that are highlighted below
	 */
	public Pel largest(BNode r) throws EmptyTreeException {
		
		if (r.isLeaf()) throw new EmptyTreeException("Error: given BST is empty!");
		
		else {
			
			BNode p = r;
			while (!p.isLeaf()) { // Iterates until p is the rightmost leaf in the BST
				
				p = p.rightChild();
			}
			
			return p.parent().getData(); // Returns the parent of the rightmost leaf, this being the rightmost internal node
		}
	}
	
	// Getter method getRoot is used to return the root node of the BST
	public BNode getRoot() {
		
		return this.root;
	}
}
