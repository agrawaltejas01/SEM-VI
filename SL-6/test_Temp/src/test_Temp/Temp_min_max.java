package test_Temp;

/*import javax.lang.model.SourceVersion;
import javax.tools.Tool;
import org.apache.hadoop.io.*;

//import org.apache.hadoop.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.examples.SecondarySort.Reduce;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hdfs.tools.GetConf;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.mapreduce.Job;
//import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
//import org.apache.hadoop.io.LongWritable;
//import org.apache.hadoop.io.Text;



public class Temp_min_max extends Configured implements Tool
{
	public static class Temp_min_maxMapper extends MapReduceBase
	implements Mapper<LongWritable, Text, Text, Text>
	{
		private Text year = new Text();
		private Text temp = new Text();
		
		public void map(LongWritable key, Text value, OutputCollector<Text, Text> output, Reporter reporter)
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
	
	public static class Temp_min_maxReducer extends MapReduceBase
	implements Reducer<Text, Text, Text, Text>
	{
		public void reduce(Text key, Iterator<Text> value, OutputCollector<Text, Text>output, Reporter reporter)
		throws IOException
		{
			double min = 50000, max = 0, tmin, tmax;
			String temp;
			
			while(value.hasNext())
			{
				temp = value.next().toString();				
				StringTokenizer tokenizer = new StringTokenizer(temp);
				
				tmax = Double.parseDouble(tokenizer.nextToken());
				tmin = Double.parseDouble(tokenizer.nextToken());
				
				if(min > tmin)
					min = tmin;
				
				if(max < tmax)
					max = tmax;
			}
			
			output.collect(key, new Text(min + " " + max));
		}
	}
	
	public int run(String[] args) throws Exception
	{
		JobConf conf = new JobConf(getConf(), Temp_min_max.class);
		conf.setJobName("Temp_min_max");
		
		conf.setMapOutputKeyClass(Text.class);
		conf.setMapOutputValueClass(Text.class);
		
		conf.setOutputKeyClass(Text.class);
		conf.setOutputValueClass(Text.class);
		
		Path in = new Path(args[0]);
		Path out = new Path(args[1]);
		
		FileInputFormat.addInputPath(conf, in);
		FileOutputFormat.setOutputPath(conf, out);
		
		JobClient.runJob(conf);
		return 0;
	}
	
	@Override
	public Set<SourceVersion> getSourceVersions() {
		// TODO Auto-generated method stub
		return null;
	}
	
	public static void main(String[] args)
	throws Exception
	{
		
		int res = ToolRunner.run(new Configuration(), new Temp_min_max() , args);
		System.exit(res);
		
	}

	@Override
	public int run(InputStream in, OutputStream out, OutputStream err, String... arguments) {
		// TODO Auto-generated method stub
		return 0;
	}

}*/

/*public class Temp_min_max
{
	public static class Temp_min_maxMapper 
		extends Mapper<LongWritable, Text, Text, Text>
	{
		private Text year = new Text();
		private Text temp = new Text();
		
		
		public void map(LongWritable key, Text value, Context context )
		throws IOException, InterruptedException
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
			
			context.write(year, temp);
		}
	}
	
	public static class Temp_min_maxReducer
	extends Reducer<Text, Text, Text, Text>
	{
		public void reduce(Text key, Iterator<Text> value, Context context)
		throws IOException, InterruptedException
		{
			double min = 500000, max = -1;
			String temp;
			
			while(value.hasNext())
			{
				temp = value.next().toString();
				
				StringTokenizer tokenizer = new StringTokenizer(temp);
				
				double tmax = Double.parseDouble(tokenizer.nextToken());
				double tmin = Double.parseDouble(tokenizer.nextToken());
				
				if(tmax > max)
					max = tmax;
				
				if(tmin < min)
					min = tmin;
			}
			
			context.write(key, new Text(min + " " + max));
		}
	}
	
	public static void main(String[] args) throws Exception
	{
		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "Temp");
		
		job.setJarByClass(Temp_min_max.class);
		job.setMapperClass(Temp_min_maxMapper.class);
		job.setCombinerClass(Temp_min_maxReducer.class);
		job.setReducerClass(Temp_min_maxReducer.class);
		
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		
		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		
		System.exit(job.waitForCompletion(true) ? 0 : 1);
		
	}
}*/


import org.apache.hadoop.io.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.fs.Path;

public class Temp_min_max extends Configured implements Tool
{
	public int run(String[] args) throws Exception
	{
		JobConf conf = new JobConf(getConf(), Temp_min_max.class);
		conf.setJobName("Temp");
		
		conf.setOutputKeyClass(Text.class);
		conf.setOutputValueClass(Text.class);
		
		conf.setMapperClass(Temp_min_maxMapper.class);
		conf.setReducerClass(Temp_min_maxReducer.class);
		
		FileInputFormat.addInputPath(conf, new Path(args[0]));
		FileOutputFormat.setOutputPath(conf, new Path(args[1]));
		
		JobClient.runJob(conf);
		return 0;
		
	}
	
	public static void main(String[] args) throws Exception
	{
		int res = ToolRunner.run(new Configuration(), new Temp_min_max() ,args);
		System.exit(res);
	}
}















