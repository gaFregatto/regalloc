#ifndef graph_h
#define graph_h

#include "list.h"
#include "integer.h"

typedef void *Graph;
typedef void *Vertex;

Graph newGraph();
void setGraphID(Graph gr, int id);
void setGraphK(Graph gr, int k);
void addVertexGraph(Graph gr, Vertex vtx);
void printGraph(Graph gr);
void freeGraph(Graph gr);
List getVertexes(Graph gr);
Vertex newVertex(int id);
List getEdges(Vertex vtx);
void printVertex(Vertex vtx);
int getVertexID(Vertex vtx);
int equalVertexes(Vertex a, Vertex b);
void upDegree(Vertex vtx);
void downDegree(Vertex vtx);
void freeVertex(Vertex vtx);
void addEdgeVertex(Integer itg, Vertex vtx);

#endif