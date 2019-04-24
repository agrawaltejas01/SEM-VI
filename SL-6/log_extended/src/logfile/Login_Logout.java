package logfile;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;

public class Login_Logout extends Configured implements Tool
{
	public int run(String[] args) throws Exception
	{
		JobConf conf = new JobConf(getConf(), Login_Logout.class);
		conf.setJobName("Login_Logout");
		
		conf.setMapperClass(Login_LogoutMapper.class);
		conf.setReducerClass(Login_LogoutReducer.class);
		
		conf.setOutputKeyClass(Text.class);
		conf.setOutputValueClass(IntWritable.class);
		
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
