package main;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import org.json.JSONArray;
import org.json.JSONObject;
import org.smurn.jply.Element;
import org.smurn.jply.ElementReader;
import org.smurn.jply.ElementType;
import org.smurn.jply.PlyReader;
import org.smurn.jply.PlyReaderFile;

import domain.Accelerator;
import domain.Box;
import domain.Face;
import domain.FaceDB;
import domain.Vertex;
import domain.VertexDB;

/**
 * Console application that prints out the positions of all vertices.
 */
public class App {
	
	public static FaceDB fdb = new FaceDB();


    public static void main(String[] args) throws IOException {
    	try
    	{
    		JSONArray result = new JSONArray();
    		File txt = new File("denis.txt");
    		PrintWriter writer = new PrintWriter(txt);
    		writer.print("");
    		writer.close();
        	int index = 0;
        	VertexDB vdb = new VertexDB();
    		PlyReader ply;         
    		File f = new File("big_spider.ply");
    		ply = new PlyReaderFile(f);
    		ElementReader reader = ply.nextElementReader();
    		System.out.println(ply.getElementCount("vertex")+ " Vertices");
    		System.out.println(ply.getElementCount("face")+ " Faces");
    		while (reader != null) {
    			ElementType type = reader.getElementType();
    			if (type.getName().equals("vertex")) {
    				printVertices(vdb,index,reader);
    			}
    			else
    			{
    				printFaces(result,vdb,reader);
    			}
            reader.close();
            reader = ply.nextElementReader();
    		}
            ply.close();
        	Accelerator accelerator = new Accelerator(fdb);
            printToFile(txt, accelerator);
            //printToTxt(txt,result);
        }
    	catch(Exception e)
    	{
    		System.out.println(e.getMessage());
    		e.printStackTrace();
    	}
    }

    private static void printToTxt(File f, JSONArray array)
    {
    	try
    	{
    	  BufferedWriter outputWriter = null;
    	  outputWriter = new BufferedWriter(new FileWriter(f));
    	  for(Object obj : array)
    	  {
    		  JSONObject j = (JSONObject) obj;
    		  outputWriter.write(j.toString());
    		  outputWriter.newLine();
    	  }
    	  outputWriter.flush();
    	  outputWriter.close();
    	}
    	catch(Exception e)
    	{
    		System.out.println(e.getMessage());
    	}
    }
    private static void printVertices(VertexDB vdb,int index, ElementReader reader) throws IOException {
        System.out.println("There are " + reader.getCount() + " vertices:");
        Element element = reader.readElement();
        while (element != null)
        {   
        	Vertex v = new Vertex(index, element.getDouble("x"),element.getDouble("y"),element.getDouble("z"));
            vdb.addVertex(v);
			index++;
            element = reader.readElement();
        }
    }
    private static void printFaces(JSONArray result,VertexDB vdb,ElementReader reader) throws IOException 
    {
    	Element triangle = reader.readElement();
    	while(triangle != null)
    	{
    		int[] indices = triangle.getIntList("vertex_indices");
    		Vertex v1 = vdb.getVertex(indices[0]);
    		Vertex v2 = vdb.getVertex(indices[1]);
    		Vertex v3 = vdb.getVertex(indices[2]);
    		Face f = new Face(v1, v2, v3);
    		fdb.addFace(f);
    		result.put(f.toJSON());
    		triangle = reader.readElement();
    	}
    }
    
    private static void printToFile(File f, Accelerator accelerator)
    {
    	try
    	{
    	  BufferedWriter outputWriter = null;
    	  
    	  outputWriter = new BufferedWriter(new FileWriter(f));
    	  
    	  for(Box box : accelerator.getEndNodes())
    	  {
    		  outputWriter.write(box.toJSON().toString());
    		  outputWriter.newLine();
    	  }
    	  
    	  outputWriter.flush();
    	  outputWriter.close();
    	}
    	catch(Exception e)
    	{
    		System.out.println(e.getMessage());
    	}
    }
    
}
