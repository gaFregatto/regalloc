#ifndef graph_h
#define graph_h

#include "list.h"

typedef void *Graph;
typedef void *Vertex;

Graph newGraph();
void setGraphID(Graph gr, int id);
void setGraphK(Graph gr, int k);
void setGraphKC(Graph gr, int k);
void downGraphKC(Graph gr);
int getGraphID(Graph gr);
int getGraphKC(Graph gr);
int getGraphK(Graph gr);
void addVertexGraph(Graph gr, Vertex vtx, int assing);
void printGraph(Graph gr);
void freeGraph(Graph gr);
List getVertexes(Graph gr);
Vertex newVertex(int id);
List getEdges(Vertex vtx);
void printVertex(Vertex vtx);
int getVertexID(Vertex vtx);
int getVertexDegree(Vertex vtx);
void setVertexDegree(Vertex vtx, int d);
int equalVertexes(Vertex a, Vertex b);
void upDegree(Vertex vtx);
void downDegree(Vertex vtx);
void freeVertex(Vertex vtx);
void addVertexEdge(Vertex vtx, Vertex edge);
int vertexExists(Graph gr, int id);
int validVertex(Vertex vtx);
void disableVertex(Graph gr, Vertex vtx);
int validVertexExists(Graph gr);
int minValidDegree(Graph gr);
int maxValidDegree(Graph gr);
Vertex minValidID(Graph gr, int degree);
void setValidVertex(Vertex vtx);
void setInvalidVertex(Vertex vtx);
Vertex getVertexById(Graph gr, int id);
int getAvailableColors(Graph gr, Vertex vtx);
int getVertexColor(Vertex vtx);
int paintVertex(Graph gr, Vertex vtx, int color);
void setVertexColor(Vertex vtx, int color);
void enableVertexes(Graph gr);

#endif