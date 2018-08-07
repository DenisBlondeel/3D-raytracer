package domain;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.json.JSONException;
import org.json.JSONObject;

public class JSONUtil
{
	public static JSONObject parseJSONFile(String filename) throws JSONException, IOException {
		try
		{
	        String content = new String(Files.readAllBytes(Paths.get(filename)));
	        return new JSONObject(content);
		}
		catch(Exception e)
		{
			System.out.println("JSONUTILS : "+ e.getMessage());
		}
		return null;
    }
}
