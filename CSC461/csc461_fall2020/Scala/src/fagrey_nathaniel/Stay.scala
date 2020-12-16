package fagrey_nathaniel

import scala.collection.mutable
import scala.xml._

class Stay()extends RDP {
  private var travel = "no"
  private var days = 1

  override def add(): Unit = {
    print("\nUpdate traveling: ")
    val traveling = io.StdIn.readLine()

    if( traveling.toLowerCase() == "yes" )
        travel = "yes"

    else if (traveling.toLowerCase() == "no")
      travel = "no"

    print("Update days: ")
    days = io.StdIn.readInt()

  }

  override def displayString(starter: String): String = {
    val returnString = s"\n$starter--Traveling: ${travel} Days: $days"
    returnString
  }

  def getStay: String = {
    travel
  }

  def getDays : Int = days

  override def xmlWrite(): Elem = {
    var attr: mutable.HashMap[String, String] = mutable.HashMap(("traveling", travel))
    attr("days") = days.toString

    XMLHelper.makeNode("stay", attr)
  }

  override def xmlRead(node : Node): Unit = {
      travel =  node.attribute("traveling").getOrElse("").toString
      days = node.attribute("days").getOrElse("1").toString.toInt
  }
}

object Stay {
  def apply (): Stay = new Stay()
}
