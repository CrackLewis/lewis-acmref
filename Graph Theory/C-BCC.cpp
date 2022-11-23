/**
 * Bi-Connected Components
 *
 * Bi-Connected by nodes: for node u,v, if they keeps connected after we remove
 * one of any other nodes, then u,v is bi-connected by nodes.
 *
 * Bi-Connected by edges: for node u,v, if they keeps connected after we remove
 * one of any edges, then u,v is bi-connected by edges.
 *
 * Transitivity:
 * - Bi-connectivity by nodes does NOT have transitivity: if u,v are
 * bi-connected and v,w are bi-connected, we cannot deduce that u,w is
 * bi-connected.
 * - Bi-connectivity by edges has transitivity though.
 *
 * Method to solve bi-connectivity issue:
 *
 * To judge if u,v are bi-connected by edges, check if the path between them on
 * the DFS tree contains a bridge. If there is a bridge, they are not
 * bi-connected.
 *
 * To judge if u,v are bi-connected by nodes on graph G, construct a graph Z
 * where each node represents an edge on DFS tree of G, and add edges on u,v in
 * Z if they are both on a path on the DFS tree which form a non-DFS edge on
 * the original graph. Then check if DFS edges connected to u,v in G belongs to
 * the same connected component on Z.
 *
 */