package domain;

import java.util.ArrayList;
import java.util.List;

public class Accelerator {
	
	private FaceDB fdb;
	private List<Box> boxList;
	
	public Accelerator(FaceDB fdb)
	{
		this.fdb = fdb;
		optimize(2);
	}
	
	public List<Box> getAllBoxes()
	{
		return boxList;
	}
	
	public Vertex findSmallest(FaceDB db)
	{
		double x=0;
		double y=0;
		double z=0; 
		
		for(int i = 0; i < db.getFaces().size(); i++)
		{
			Face face = db.getFaces().get(i);
			if(face.getV1().getX() < x) x=face.getV1().getX();
			if(face.getV2().getX() < x) x=face.getV2().getX();
			if(face.getV3().getX() < x) x=face.getV3().getX();
			
			if(face.getV1().getY() < y) y=face.getV1().getY();
			if(face.getV2().getY() < y) y=face.getV2().getY();
			if(face.getV3().getY() < y) y=face.getV3().getY();
			
			if(face.getV1().getZ() < z) z=face.getV1().getZ();
			if(face.getV2().getZ() < z) z=face.getV2().getZ();
			if(face.getV3().getZ() < z) z=face.getV3().getZ();
			
		}
		
		return new Vertex(0,x,y,z);
	}
	
	public Vertex findBiggest(FaceDB db)
	{
		double x=0;
		double y=0;
		double z=0; 
		
		for(int i = 0; i < db.getFaces().size(); i++)
		{
			Face face = db.getFaces().get(i);
			if(face.getV1().getX() > x) x=face.getV1().getX();
			if(face.getV2().getX() > x) x=face.getV2().getX();
			if(face.getV3().getX() > x) x=face.getV3().getX();
			
			if(face.getV1().getY() > y) y=face.getV1().getY();
			if(face.getV2().getY() > y) y=face.getV2().getY();
			if(face.getV3().getY() > y) y=face.getV3().getY();
			
			if(face.getV1().getZ() > z) z=face.getV1().getZ();
			if(face.getV2().getZ() > z) z=face.getV2().getZ();
			if(face.getV3().getZ() > z) z=face.getV3().getZ();
		}
		
		return new Vertex(0,x,y,z);
	}
	
	public List<Box> getEndNodes()
	{
		List<Box> leaves = new ArrayList<Box>();
		
		for(Box box : boxList)
		{
			if(!box.hasChilden())
			{
				leaves.add(box);
			}
		}
		return leaves;
	}
	
	private void optimize(int depth)
	{
		Box uberBox = new Box(findSmallest(fdb), findBiggest(fdb),0);
		
		boxList = new ArrayList<Box>();
		
		
		boxList.add(uberBox);
		
		uberBox.setFaceDB(fdb);		
		for(int i = 0; i <= depth; i++)
		{
			List<Box> temp = new ArrayList<Box>();
			for(Box box : boxList)
			{
				if(!box.hasChilden())
				{
					box.split();
					temp.add(box.getSubBox("left"));
					temp.add(box.getSubBox("right"));
				}
			}
			boxList.addAll(temp);
		}
		System.out.println("There are : " + boxList.size() + " boxes");
		for(Box box : boxList)
		{
			if(!box.hasChilden())
			{
				
				System.out.println("In this box; " + box.getTriangleCollection().getFaces().size() + " trizngles");
				System.out.println("BEGIN " + box.getBegin().toJSON());
				System.out.println("EIND " + box.getEnd().toJSON());
				System.out.println("");
			}
		}
	}

}
