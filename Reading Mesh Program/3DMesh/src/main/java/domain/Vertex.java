package domain;

import org.json.JSONObject;

public class Vertex
{
	private Double x,y,z;
	private int index;
	public Vertex(int index,Double x, Double y, Double z)
	{
		this.setIndex(index);
		this.setX(x);
		this.setY(y);
		this.setZ(z);
	}
	public int getIndex()
	{
		return index;
	}
	private void setIndex(int index)
	{
		this.index = index;
	}
	public Double getX()
	{
		return x;
	}
	private void setX(Double x)
	{
		this.x = x;
	}
	public Double getY()
	{
		return y;
	}
	private void setY(Double y)
	{
		this.y = y;
	}
	public Double getZ()
	{
		return z;
	}
	private void setZ(Double z)
	{
		this.z = z;
	}
	public JSONObject toJSON()
	{
		JSONObject result = new JSONObject();
		result.put("x", this.getX());
		result.put("y", this.getY());
		result.put("z",this.getZ());
		return result;
	}
}
