/**
 * Demonstrates a simple Breadth-First Search (BFS) algorithm
 * on a predefined, unweighted graph using standard Apex collections.
 * This is a pure algorithm simulation, independent of Salesforce data.
 */
public class GraphBFS {

    /**
     * Simulates a BFS traversal on a given graph starting from a specific node.
     *
     * @param graph The graph represented as an adjacency list (Map<Node, List<Neighbors>>).
     * @param startNode The node to begin the traversal from.
     * @return A List<String> representing the order in which nodes were visited.
     */
    public static List<String> traverseGraph(Map<String, List<String>> graph, String startNode) {

        // Input validation (optional, but good practice even in demos)
        if (graph == null || graph.isEmpty() || !graph.containsKey(startNode)) {
            System.debug('Error: Graph is null/empty or start node not found.');
            return new List<String>(); // Return empty list on invalid input
        }

        // 1. Initialize Data Structures:
        //    - Queue: Nodes to visit next (List acts as a queue)
        //    - Visited Set: Nodes we've already processed
        //    - Visited Order: The sequence in which nodes are visited (for output)

        List<String> queue = new List<String>();
        Set<String> visited = new Set<String>();
        List<String> visitedOrder = new List<String>();

        // 2. Start the BFS:
        //    - Add the start node to the queue and mark it as visited.

        queue.add(startNode);
        visited.add(startNode); // Mark as visited as soon as it's added to queue

        System.debug('--- Starting BFS from node: ' + startNode + ' ---');
        System.debug('Initial Queue: ' + queue);
        System.debug('Initial Visited Set: ' + visited);


        // 3. BFS Loop:
        //    - Process nodes level by level until the queue is empty.

        while (!queue.isEmpty()) {

            // a. Dequeue the current node (take the first element)
            String currentNode = queue.remove(0); // Remove the first element (FIFO)

            // b. Add the current node to the visited order list
            visitedOrder.add(currentNode);
            System.debug('Dequeued and visiting node: ' + currentNode);
            System.debug('Current Visited Order: ' + visitedOrder);


            // c. Find Neighbors: Get the neighbors of the current node from the graph
            List<String> neighbors = graph.get(currentNode);

            if (neighbors != null) { // Handle nodes with no neighbors
                System.debug('Neighbors of ' + currentNode + ': ' + neighbors);

                // d. Enqueue new neighbors: Iterate through neighbors
                for (String neighbor : neighbors) {
                    // If the neighbor has not been visited yet
                    if (!visited.contains(neighbor)) {
                        // Mark it as visited and add it to the queue for later processing
                        visited.add(neighbor); // Mark as visited
                        queue.add(neighbor);     // Add to the end of the queue
                        System.debug('  - Added unvisited neighbor to queue/visited: ' + neighbor);
                    } else {
                         System.debug('  - Neighbor ' + neighbor + ' already visited.');
                    }
                }
            } else {
                 System.debug('Node ' + currentNode + ' has no neighbors in the graph map.');
            }

            System.debug('Queue after processing ' + currentNode + ': ' + queue);
            System.debug('Visited Set after processing ' + currentNode + ': ' + visited);
             System.debug('------------------------');


        } // End of while loop

        System.debug('--- BFS Finished ---');
        System.debug('Final Visited Order: ' + visitedOrder);
        System.debug('Total Nodes Visited: ' + visitedOrder.size());

        return visitedOrder; // Return the list showing the order of traversal
    }


    // --- Example Usage ---
    public static void runExample() {

        // Define a simple graph using an adjacency list
        Map<String, List<String>> myGraph = new Map<String, List<String>>();
        myGraph.put('A', new List<String>{'B', 'C'});
        myGraph.put('B', new List<String>{'A', 'D'});
        myGraph.put('C', new List<String>{'A', 'D'});
        myGraph.put('D', new List<String>{'B', 'C', 'E'});
        myGraph.put('E', new List<String>{'D'});
        myGraph.put('F', new List<String>()); // Isolated node

        // Specify the starting node
        String startNode = 'A'; // Try changing this to 'B', 'D', or 'F'

        // Perform the BFS traversal
        List<String> traversalOrder = traverseGraph(myGraph, startNode);

        System.debug('BFS Traversal Order starting from ' + startNode + ': ' + traversalOrder);

        // Example with a different start node
        // List<String> traversalOrder2 = traverseGraph(myGraph, 'F');
        // System.debug('BFS Traversal Order starting from F: ' + traversalOrder2);
    }
}