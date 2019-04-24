package logfile;

import java.io.IOException;
import java.util.Iterator;

import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;

public class Login_LogoutReducer extends MapReduceBase
implements Reducer<Text, IntWritable, Text, IntWritable>
{
	private IntWritable result = new IntWritable();
	
	public void reduce(Text key, Iterator<IntWritable>value, OutputCollector<Text, IntWritable>output, Reporter reporter)
	throws IOException
	{
		int sum = 0;
		while(value.hasNext())
			sum += value.next().get();
		
		result.set(sum);
		output.collect(key, result);
	}

	

}
