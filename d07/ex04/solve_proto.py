#!/usr/bin/env python3
import sys
import contextlib
try:
    with contextlib.redirect_stdout(None):
        import networkx as nx
        from networkx.drawing.nx_pydot import write_dot
except ModuleNotFoundError:
    print("Ack")
    exit(1)

# node0 = ("Node 0", 20)
# node1 = ("Node 1", 10)
# node2 = ("Node 2", 5)
# node3 = ("Node 3", 15)
# edgelst = [[node0, node1],
#            [node1, node0],
#            [node1, node2],
#            [node1, node3],
#            [node2, node1],
#            [node2, node3],
#            [node3, node1],
#            [node3, node2]]
# G.add_edge(G["Node 0"], G["Node 1"])
# G.add_edge(G["Node 1"], G["Node 0"])
# G.add_edge(G["Node 1"], G["Node 2"])
# G.add_edge(G["Node 1"], G["Node 3"])
# G.add_edge(G["Node 2"], G["Node 1"])
# G.add_edge(G["Node 2"], G["Node 3"])
# G.add_edge(G["Node 3"], G["Node 1"])
# G.add_edge(G["Node 3"], G["Node 2"])

G = nx.Graph()
edgelst = [[0, 1],
           [1, 0],
           [1, 2],
           [1, 3],
           [2, 1],
           [2, 3],
           [3, 1],
           [3, 2]]
G.add_edges_from(edgelst)
G.add_node(0, nname="Node 0", population=20)
G.add_node(1, nname="Node 1", population=10)
G.add_node(2, nname="Node 2", population=5)
G.add_node(3, nname="Node 3", population=15)

# G.add_edge(G[0], G[1])
# G.add_edge(G[1], G[0])
# G.add_edge(G[1], G[2])
# G.add_edge(G[1], G[3])
# G.add_edge(G[2], G[1])
# G.add_edge(G[2], G[3])
# G.add_edge(G[3], G[1])
# G.add_edge(G[3], G[2])

# pos = nx.nx_agraph.graphviz_layout(G)
# pos = nx.kamada_kawai_layout(G)
# nx.draw(G, pos=pos)
# write_dot(G, 'file.dot')
print(list(G.nodes))
