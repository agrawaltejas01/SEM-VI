package music;

import java.io.IOException;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import java.util.Iterator;
import java.util.StringTokenizer;

public class Music_2Reducer extends MapReduceBase implements Reducer<Text, Text, Text, Text>
{
    //reduce method accepts the Key Value pairs from mappers, do the aggregation based on keys and produce the final out put
    public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, Text> output, Reporter reporter) throws IOException
    {
        int sum_radio = 0, sum_skipped=0, skip, radio;
        String listener;
        while(values.hasNext())
        {
        	listener = values.next().toString();
        	StringTokenizer tokenizer = new StringTokenizer(listener);
        	radio = Integer.parseInt(tokenizer.nextToken());
        	skip = Integer.parseInt(tokenizer.nextToken());
        	//sums the number of times the song was heard on the radio
        	sum_radio+=radio;
        	//sums the number of times the song was heard skipped
        	sum_skipped+=skip;
        }
        
        output.collect(key, new Text(sum_radio+" "+sum_skipped));
    }
}