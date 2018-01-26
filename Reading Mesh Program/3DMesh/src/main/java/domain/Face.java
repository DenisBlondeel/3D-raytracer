package domain;

import org.json.JSONObject;

public class Face
{
	Vertex v1,v2,v3;
	public Face(Vertex v1, Vertex v2,Vertex v3)
	{
		this.setV1(v1);
		this.setV2(v2);
		this.setV3(v3);
	}
	public Vertex getV1()
	{
		return v1;
	}
	private void setV1(Vertex v1)
	{
		this.v1 = v1;
	}
	public Vertex getV2()
	{
		return v2;
	}
	private void setV2(Vertex v2)
	{
		this.v2 = v2;
	}
	public Vertex getV3()
	{
		return v3;
	}
	private void setV3(Vertex v3)
	{
		this.v3 = v3;
	}
	public JSONObject toJSON()
	{
		JSONObject result = new JSONObject();
		result.put("v1", v1.toJSON());
		result.put("v2", v2.toJSON());
		result.put("v3", v3.toJSON());
		return result;
	}
}
