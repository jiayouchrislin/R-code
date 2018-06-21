import scala.io.Source
import scala.sys.process._

def readCSVLine(src :Source): Array[String]={
	var c = if(src.hasNext) src.next else ' '
	//如果有值才給值or 給0 
	var ret = List[String]()
	var inQuotes = false
	//確保你的輸入有直，如果沒有則為T
	var cur = ""
	while(src.hasNext & c!=13){
		if(c=="\\|" && !inQuotes){
			ret ::= cur
			cur = ""
		} else if(c=='\"'){
			inQuotes = !inQuotes
		} else if(c=='\\'){
			cur += src.next
		} else{
			cur += c
		}
		c = src.next
		//,
		//\
		//\
		// everything else
	}
    ret ::= cur
    //return the value
    ret.reverse.toArray
}
//val source = Source.fromFile("/Users/chris/spark-notebook-0.7.0-scala-2.11.7-spark-1.6.3-hadoop-2.7.2-with-hive-with-parquet/notebooks/precoess/data/C44_病人條件檔.csv")
val source = Source.fromFile("../data/C44_病人條件檔.csv")

//val source = Source.fromFile("../data/GC-data-juo_20150410rtc0nos.csv")
while(source.hasNext){
	println(readCSVLine(source).mkString(","))
}