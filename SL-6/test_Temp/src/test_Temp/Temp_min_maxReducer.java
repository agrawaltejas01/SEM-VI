package test_Temp;

import org.apache.hadoop.io.*;
import java.io.IOException;
import java.util.Iterator;
import java.util.StringTokenizer;
import org.apache.hadoop.mapred.*;


public class Temp_min_maxReducer extends MapReduceBase
implements Reducer<Text, Text, Text, Text>
{
	public void reduce(Text key, Iterator<Text> value, OutputCollector<Text, Text>output, Reporter reporter)
	throws IOException
	{
		double min = 50000, max = -1;
		String temp;
		double tmax, tmin;
		
		while(value.hasNext())
		{
			temp = value.next().toString();
			StringTokenizer tokenizer = new StringTokenizer(temp);
			
			tmax = Double.parseDouble(tokenizer.nextToken());
			tmin = Double.parseDouble(tokenizer.nextToken());
			
			if(max < tmax)
				max = tmax;
		
			if(min > tmin)
				min = tmin;		
		}
		
		output.collect(key, new Text(min + " " + max));
	}
}
