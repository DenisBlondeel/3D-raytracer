package domain;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONObject;

public class Box {
	
	private Vertex begin;
	private Vertex end;
	
	private FaceDB fdb;
	
	private int depth = 0;
	
	private boolean hasChildren = false;
	
	private Box boxL;
	private Box boxR;

	public Box(Vertex begin, Vertex end, int depth)
	{
		this.begin = begin;
		this.end = end;
		this.depth = depth;
	}
	
	public Vertex getBegin()
	{
		return begin;
	}
	
	public List<Box> getSubBoxes()
	{
		List<Box> subBoxes = new ArrayList<Box>();
		subBoxes.add(boxL);
		subBoxes.add(boxR);
		return subBoxes;
	}
	
	public Vertex getEnd() 
	{
		return end;
	}
	
	public Box getSubBox(String direction)
	{
		if(direction.equals("left"))
		{
			return boxL;
		}
		else if(direction.equals("right"))
		{
			return boxR;
		}
		else return null;
	}
	
	public boolean hasChilden()
	{
		return hasChildren;
	}
	
	public void setDepth(int depth)
	{
		this.depth = depth;
	}
	
	public int getDepth()
	{
		return depth;
	}
	
	
	public void setFaceDB(FaceDB db)
	{
		fdb = db;
	}
	
	public FaceDB getTriangleCollection()
	{
		return fdb;
	}
	
	public void split()
	{
		Vertex newEnd = new Vertex(0, end.getX()/2, end.getY(), end.getZ());
		
		Vertex betterEnd = new Vertex(0,(end.getX() + begin.getX())/2, end.getY(), end.getZ());
		
		boxL = new Box(begin, betterEnd, depth);
		boxL.setFaceDB(facesInBox(boxL, fdb));
		
		Vertex newBegin = new Vertex(0, end.getX()/2, begin.getY(), begin.getZ());
		
		Vertex betterBegin = new Vertex(0,(end.getX() + begin.getX())/2, begin.getY(), begin.getZ());
		
		boxR = new Box(betterBegin, end, depth);
		boxR.setFaceDB(facesInBox(boxR, fdb));
		
		hasChildren = true;
	}
	
	private FaceDB facesInBox(Box box, FaceDB db)
	{
		FaceDB newFaceDB = new FaceDB();
		for(int i=0; i < db.getFaces().size(); i++)
		{
			if(contains(box, db.getFaces().get(i))) 
			{	newFaceDB.addFace(db.getFaces().get(i));
			}
		}
		return newFaceDB;
	}
	
	private boolean contains(Box box, Face face)
	{
		Vertex fV1 = face.getV1();
		Vertex fV2 = face.getV2();
		Vertex fV3 = face.getV3();
		if(fV1.getX() >= box.getBegin().getX() && fV1.getX() <= box.getEnd().getX() && fV1.getY() >= box.getBegin().getY() && fV1.getY() <= box.getEnd().getY() && fV1.getZ() >= box.getBegin().getZ() && fV1.getZ() <= box.getEnd().getZ())
		{
			return true;
		}
		
		else if(fV2.getX() >= box.getBegin().getX() && fV2.getX() <= box.getEnd().getX() && fV2.getY() >= box.getBegin().getY() && fV2.getY() <= box.getEnd().getY() && fV2.getZ() >= box.getBegin().getZ() && fV2.getZ() <= box.getEnd().getZ())
		{
			return true;
		}
		
		else if(fV3.getX() >= box.getBegin().getX() && fV3.getX() <= box.getEnd().getX() && fV3.getY() >= box.getBegin().getY() && fV3.getY() <= box.getEnd().getY() && fV3.getZ() >= box.getBegin().getZ() && fV3.getZ() <= box.getEnd().getZ())
		{
			return true;
		}
		else
		{
			return false;
		}
		
		/*if(fV1.getX() < box.getBegin().getX() && fV1.getX() > box.getEnd().getX() && fV1.getY() < box.getBegin().getY() && fV1.getY() > box.getEnd().getY() && fV1.getZ() < box.getBegin().getZ() && fV1.getZ() > box.getEnd().getZ())
		{
			return false;
		}
		
		else if(fV2.getX() < box.getBegin().getX() && fV2.getX() > box.getEnd().getX() && fV2.getY() < box.getBegin().getY() && fV2.getY() > box.getEnd().getY() && fV2.getZ() < box.getBegin().getZ() && fV2.getZ() > box.getEnd().getZ())
		{
			return false;
		}
		
		else if(fV3.getX() < box.getBegin().getX() && fV3.getX() > box.getEnd().getX() && fV3.getY() < box.getBegin().getY() && fV3.getY() > box.getEnd().getY() && fV3.getZ() < box.getBegin().getZ() && fV3.getZ() > box.getEnd().getZ())
		{
			return false;
		}
		else
		{
			return true;
		}*/
	}
	public JSONObject toJSON()
	{
		JSONObject result = new JSONObject();
		result.put("v1", begin.toJSON());
		result.put("v2", end.toJSON());
		result.put("triangles", fdb.getFaces());
		return result;
	}
}
