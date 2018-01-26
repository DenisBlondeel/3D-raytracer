package domain;

import java.util.HashMap;

public class VertexDB
{
	private HashMap<Integer,Vertex> vertexes;
	public VertexDB()
	{
		vertexes = new HashMap<Integer, Vertex>();
	}
	public void addVertex(Vertex v)
	{
		vertexes.put(v.getIndex(), v);
	}
	public int getSize()
	{
		return vertexes.size();
	}
	public Vertex getVertex(int index)
	{
		return vertexes.get(index);
	}
}
