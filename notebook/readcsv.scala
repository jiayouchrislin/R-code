import scala.io.Source

object readcsv{
	def main(arfs:Array[String]):Unit = {
		//val filepath = "~/Desktop/醫療整合資料庫_急診部方震中醫師/"
		val filename = "/Users/chris/spark-notebook-0.7.0-scala-2.11.7-spark-1.6.3-hadoop-2.7.2-with-hive-with-parquet/notebooks/precoess/data/C44_病人條件檔.csv"
		val file=  filename
		val source = Source.fromFile(file)
		val lines = source.getLines
		source.close


		for(line <-lines){
			println(line)
		}

	}
}
