package domain;

import java.util.ArrayList;
import java.util.List;

public class FaceDB
{
	private List<Face> faces;
	
	public FaceDB()
	{
		faces = new ArrayList<Face>();
	}
	public void addFace(Face f)
	{
		this.faces.add(f);
	}
	
	public List<Face> getFaces()
	{
		return faces;
	}
}
