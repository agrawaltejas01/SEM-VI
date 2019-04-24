package music;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;

public class Music_1 extends Configured implements Tool
{
	public int run(String[] args) throws Exception
	{
		JobConf conf = new JobConf(getConf(), Music_1.class);
		conf.setJobName("Music_1");
		conf.setOutputKeyClass(Text.class);
        conf.setOutputValueClass(Text.class);
        
		conf.setMapperClass(Music_1Mapper.class);
		conf.setReducerClass(Music_1Reducer.class);
		
		Path in = new Path(args[0]);
		Path out = new Path(args[1]);
		
		FileInputFormat.addInputPath(conf, in);
		FileOutputFormat.setOutputPath(conf, out);
		
		JobClient.runJob(conf);
		return 0;
	}
	
	public static void main(String[] args) throws Exception
	{
		
		int res = ToolRunner.run(new Configuration(), new Music_1(), args);
		System.exit(res);
	}
}
