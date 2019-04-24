package music;

import java.io.IOException;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import java.util.Iterator;
import java.util.StringTokenizer;

public class Music_1Reducer extends MapReduceBase implements Reducer<Text, Text, Text, Text>
{
    //reduce method accepts the Key Value pairs from mappers, do the aggregation based on keys and produce the final out put
    public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, Text> output, Reporter reporter) throws IOException
    {
        int sum_user = 0, sum_shared=0, usr, share, i;
        int users[] = new int[50];
        String listener;
        while(values.hasNext())
        {
        	listener = values.next().toString();
        	StringTokenizer tokenizer = new StringTokenizer(listener);
        	usr = Integer.parseInt(tokenizer.nextToken());
        	share = Integer.parseInt(tokenizer.nextToken());
        	//checks if the user is present
        	for(i=0;i<sum_user;i++)
        	{
        		if(users[i] == usr)
        			break;
        	}
        	if(i == sum_user)
        	{
        		users[sum_user] = usr;
        		sum_user++;
        	}
        	//sums the number of times the song was shared
        	sum_shared+=share;
        }
        
        output.collect(key, new Text(sum_user+" "+sum_shared));
    }
}
