package test_Temp;

import org.apache.hadoop.io.*;
import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.mapred.*;

public class Temp_min_maxMapper extends MapReduceBase 
implements Mapper<LongWritable, Text, Text, Text>
{
	Text year = new Text();
	Text temp = new Text();
	
	public void map(LongWritable key, Text value, OutputCollector<Text, Text>output, Reporter reporter)
	throws IOException
	{
		String line = value.toString();
		String val;
		StringTokenizer tokenizer = new StringTokenizer(line);
		
		if(tokenizer.hasMoreTokens())
			year.set(tokenizer.nextToken());
		
		if(tokenizer.hasMoreTokens())
		{
			val = tokenizer.nextToken() + " " + tokenizer.nextToken();
			temp.set(val);
		}
		
		output.collect(year, temp);
	}
}
