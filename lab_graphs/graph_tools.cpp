/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <climits>
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> all_vertices = graph.getVertices();
    vector<Edge> all_edges = graph.getEdges();
    int min_weight = INT_MAX;
    Edge min_edge;
    queue<Vertex> traversal_queue;

    //initialize all vertices to unexplored
    for (size_t i = 0; i < all_vertices.size(); i++) {
        graph.setVertexLabel(all_vertices[i], "UNEXPLORED");
    }

    //initialize all edges to unexplored
    for (size_t i = 0; i < all_edges.size(); i++) {
        graph.setEdgeLabel(all_edges[i].source, all_edges[i].dest, "UNEXPLORED");
    }

    //set first vertex to be explored
    graph.setVertexLabel(all_vertices[0], "VISITED");

    //push all adjacent vertices to queue
    vector<Vertex> adjacent_vertices = graph.getAdjacent(all_vertices[0]);
    for (size_t i = 0; i < adjacent_vertices.size(); i++) {
        traversal_queue.push(adjacent_vertices[i]);
    }

    //traversal: start at first vertex
    while (!traversal_queue.empty()) {
        Vertex curr = traversal_queue.front();
        traversal_queue.pop();
        graph.setVertexLabel(curr, "VISITED");

        //check all adjacent vertices
        for (size_t i = 0; i < graph.getAdjacent(curr).size(); i++) {
            Vertex adj_vertex = graph.getAdjacent(curr)[i];
            Edge curr_edge = graph.getEdge(curr, adj_vertex);

            //if edge is unexplored, check if it is the minimum
            if (graph.getEdgeLabel(curr, adj_vertex) == "UNEXPLORED") {
                if (curr_edge.weight < min_weight) {
                    min_weight = curr_edge.weight;
                    min_edge = curr_edge;
                }
                graph.setEdgeLabel(curr, adj_vertex, "VISITED");
                traversal_queue.push(adj_vertex);
            }else{
                if(graph.getEdgeLabel(curr, adj_vertex) == "UNEXPLORED"){
                    graph.setEdgeLabel(curr, adj_vertex, "CROSS");
                    if(curr_edge.weight < min_weight){
                        min_weight = curr_edge.weight;
                        min_edge = curr_edge;
                    }
                }
            }
        }
    }
    graph.setEdgeLabel(min_edge.source, min_edge.dest, "MIN");
    return min_weight;

}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> all_vertices = graph.getVertices();
    vector<Edge> all_edges = graph.getEdges();
    unordered_map<Vertex, Vertex> parent;
    queue<Vertex> traversal_queue;
    int dist = 0;

    //initialize all vertices to unexplored
    for(size_t i = 0; i < all_vertices.size(); i++){
        graph.setVertexLabel(all_vertices[i], "UNEXPLORED");
    }

    //initialize all edges to unexplored
    for(size_t i = 0; i < all_edges.size(); i++){
        graph.setEdgeLabel(all_edges[i].source, all_edges[i].dest, "UNEXPLORED");
    }

    //traversal: start at start vertex
    traversal_queue.push(start);
    graph.setVertexLabel(start, "VISITED");
    while(!traversal_queue.empty()){
        Vertex curr = traversal_queue.front();
        traversal_queue.pop();
        //get adjacent vertices
        vector<Vertex> adj = graph.getAdjacent(curr);
        //kruskal algorithm
        for(size_t i = 0; i < adj.size(); i++){
            if(graph.getVertexLabel(adj[i]) == "UNEXPLORED"){
                graph.setEdgeLabel(curr, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                parent[adj[i]] = curr;
                traversal_queue.push(adj[i]);
            }
            else{
                if(graph.getEdgeLabel(curr, adj[i]) == "UNEXPLORED"){
                    graph.setEdgeLabel(curr, adj[i], "CROSS");
                }
            }
        }
    }
    Vertex cur = end;
    while(cur != start){
        graph.setEdgeLabel(cur, parent[cur], "MINPATH");
        cur = parent[cur];
        dist += 1;
    }   
    return dist;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> all_vertices = graph.getVertices();
    vector<Edge> all_edges = graph.getEdges();
    unordered_map<Vertex, Vertex> match;
    DisjointSets union_find;

    //initialize union_find
    union_find.addelements(all_vertices.size());

    //match vertices to their indices
    for(size_t i = 0; i < all_vertices.size(); i++){
        match[all_vertices[i]] = i;
    }

    // Sort all edges
    std::sort(all_edges.begin(), all_edges.end(),
        [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

    //label the MST
    for(size_t i = 0; i < all_edges.size(); i++){
        Vertex source = all_edges[i].source;
        Vertex dest = all_edges[i].dest;
        if(union_find.find(match[source]) != union_find.find(match[dest])){
            graph.setEdgeLabel(source, dest, "MST");
            union_find.setunion(match[source], match[dest]);
        }
    }

}

