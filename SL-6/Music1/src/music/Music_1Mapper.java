package music;

import java.io.IOException;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import java.util.StringTokenizer;

public class Music_1Mapper extends MapReduceBase implements  Mapper<LongWritable, Text, Text, Text>
{
	private Text song = new Text();
	private Text listener = new Text();
	//	private final static IntWritable one = new IntWritable(1);
	
	public void map(LongWritable key, Text value, OutputCollector<Text, Text> output, Reporter reporter) throws IOException
	{
		String line = value.toString();
		String val;
		StringTokenizer tokenizer = new StringTokenizer(line);
//		listener.set(tokenizer.nextToken());
		if(tokenizer.hasMoreTokens())
		{
			val = tokenizer.nextToken();
			song.set(tokenizer.nextToken());
			listener.set(val+" "+tokenizer.nextToken());
		}
		output.collect(song, listener);
	}
}

