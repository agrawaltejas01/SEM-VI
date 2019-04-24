package logfile;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;

public class Login_LogoutMapper extends MapReduceBase
implements Mapper<LongWritable, Text, Text, IntWritable>
{
	private IntWritable diffMinutes = new IntWritable();
	private Text word = new Text();
	
	public void map(LongWritable key, Text value, OutputCollector<Text, IntWritable>output, Reporter reporter)
	throws IOException
	{
		String[] line = value.toString().split(",");
		String date1 = line[5];
		String date2 = line[7];
		
		SimpleDateFormat format = new SimpleDateFormat("yy-MM-dd HH:mm:ss");
		Date d1 = null;
		Date d2 = null;
		
		try
		{
			d1 = format.parse(date1);
			d2 = format.parse(date2);
			
			long diff = d2.getTime() - d1.getTime();
			long min = (diff/(1000));
			diffMinutes.set((int)min);
		}
		
		catch (Exception e) {
			// TODO: handle exception
		}
		
		word.set(line[1]);
		output.collect(word, diffMinutes);
		
	}
}
