package test_log;

//import java.io.*;
//import java.util.*;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;

public class Login_Logout extends Configured implements Tool
{
	/*public class Login_LogoutMapper extends MapReduceBase
		implements Mapper<LongWritable, Text, Text, IntWritable>
	{
		private Text ip = new Text();
		private IntWritable timestamp = new IntWritable();
		
		public void map(LongWritable key, Text value, OutputCollector<Text, IntWritable>output, Reporter reporter)
		throws IOException
		{
			String line = value.toString();
			StringTokenizer tokenizer = new StringTokenizer(line);
			
			ip.set(tokenizer.nextToken());
			timestamp.set(Integer.parseInt(tokenizer.nextToken()));
			
			output.collect(ip, timestamp);
		}
	}*/
	
	/*public class Login_LogoutReducer extends MapReduceBase
	implements Reducer<Text, IntWritable, Text, IntWritable>
	{
		public void reduce(Text key, Iterator<IntWritable> value, OutputCollector<Text, IntWritable>output, Reporter reporter)
		throws IOException
		{
			int sum = 0;
			while(value.hasNext())
				sum += value.next().get();	
			
			output.collect(key,new IntWritable(sum));
		}
			
	}*/
	
	public int run(String[] args) throws Exception
	{
		JobConf conf = new JobConf(getConf(), Login_Logout.class);
		conf.setJobName("Login_Logout");
		
		conf.setOutputKeyClass(Text.class);
		conf.setOutputValueClass(IntWritable.class);
		
		conf.setMapperClass(Login_LogoutMapper.class);
		conf.setReducerClass(Login_LogoutReducer.class);
		
		FileInputFormat.addInputPath(conf, new Path(args[0]));
		FileOutputFormat.setOutputPath(conf, new Path(args[1]));
		
		JobClient.runJob(conf);
		return 0;
	}
	
	public static void main(String[] args) throws Exception
	{
		int res = ToolRunner.run(new Configuration(), new Login_Logout(), args);
		System.exit(res);
	}
	
}




